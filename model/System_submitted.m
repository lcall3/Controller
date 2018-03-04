% This script sets the model parameters for the SLS 3-D Printer

% Example: Specifying a Dynamics Block
% n = [1 2 3];
% d = [4 5 6];
% Transfer Function = (s^2 + 2s + 3) / (4s^2 + 5s + 6)

% This assumption determines which equation to use for cylindrical moment of inertia calculation
ASSUME_THIN_ROD = true;

% ========================
% PHYSICAL UNIT CONVERSION
% ========================
% Example: if you decide to work in (Kg), all masses must be represented
%          in (Kg) but the spec sheet may provide masses in (g)
% Amplifier circuit elements (units normalized)
R1_ = R1 * 1e6;
R2_ = R2;
C_  = C * 1e-6;
L_  = L * 1e-3;

% Prefix conversion
MILLIS_TO = 1e3;
TO_MILLIS = 1e-3;

% Geometry conversion
link_iR     = LinkR1 * 1e-3;    % (m)
link_oR     = LinkR2 * 1e-3;    % (m)
link_depth  = LinkD * 1e-3;     % (m)
link_offset = LinkOff * 1e-3;   % (m)

% Material and spring constant
alum_density = RhoAl * 1e3;                     % (kg/m^3)
spring_k     = SpringK * 1e-3 / (2 * pi);       % (Nm/rad)

% Coefficient of static friction
mu_SF = uSF * 1e-6;             % (m)

% Joint limit
joint_limit = JntLim * RadPerDeg;               % (rad)

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Over-write the default values from DEFAULT.m %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% ==========================
% Choose Motors
% ==========================
% =====================[Motor Parameter Unit Conversion]========================
motor_param_unit_convert = ...
[
    1                           % (V)
    1 * RadPSecPerRPM           % (rad/s)
    1 * 1e-3                    % (A)
    1 * RadPSecPerRPM           % (rad/s)
    1 * 1e-3                    % (Nm)
    1                           % (A)
    1 * 1e-3                    % (Nm)
    1                           % (A)
    1                           % (%)
    1                           % (Ohms)
    1 * 1e-3                    % (H)
    1 * 1e-3                    % (Nm/A)
    1 * RadPSecPerRPM           % ((rad/s)/V)
    1 * 1e3 * RadPSecPerRPM     % ((rad/s)/Nm)
    1 * 1e-3                    % (s)
    1 * 1e-3 * 1e-4             % (kgm^2)
    1                           % (K/W)
    1                           % (K/W)
    1                           % (s)
    1                           % (s)
    1                           % (degC)
    1                           % (degC)
    1 * RadPSecPerRPM           % (rad/s)
    1 * 1e-3                    % (m)
    1 * 1e-3                    % (m)
    1                           % (N)
    1                           % (N)
    1                           % (N)
    1                           % ()
    1                           % ()
    1 * 1e-3                    % (kg)
    1 * 1e-3                    % (m)
    1 * 1e-3                    % (m)
];


% ==========================
% Motor Parameters
% ==========================
AMAX22_6W_SB;
q0 = MotorParam .* motor_param_unit_convert;
AMAX12_p75W_SB;
q1 = MotorParam .* motor_param_unit_convert;

% Motor current limit
NomI0   = q0(NomCurr);          % Max average current
StallI0 = q0(StallCurr);        % Max peak current
NomI1   = q1(NomCurr);          % Max average current
StallI1 = q1(StallCurr);        % Max peak current

% =============================
% Q0 : Rotation about y-axis
% =============================
% =====================[Amplifier Dynamics]========================
% Transfer function coefficients
Amp0n0 = (C_ * R2_ * R1_) - L_;
Amp0d0 = C_ * R1_ * R2_;
Amp0d1 = L_ * C_ * R1_;

% Transfer Function Recomputation
% TF= ______Amp0n0______ = ___C_ * R1_ * R2____
%      Amp0d1*s + Amp0d0   L_ * C_ * R1_*s + C_ * R1_ * R2_
Amp0n = Amp0n0;
Amp0d = [Amp0d1 Amp0d0];

% Saturation voltage such that 
AmpSat0 = q0(NomV);

% =====================[Electrical Motor Dynamics]========================
% This specifies the transfer function for the electric motor
% INPUT: voltage (V)
% OUTPUT: current (A)
% TF= ______Elec0d0______ = ___1_______________
%      Elec0d1*s + Elec0d0    TermL*s + TermR
Elec0d0 = q0(TermR);                % (Ohms)
Elec0d1 = q0(TermL);                % (H)
Elec0n  = 1;
Elec0d  = [Elec0d1, Elec0d0];

% =====================[Torque Const & Back EMF]========================
% TORQUE CONSTANT
% The gain between the output of electric dynamics and input of mechanical dynamics
% Input: current (A)
% Output: torque (Nm)
% Equation: Torque = K_T    * Current
% Units:    (Nm)   = (Nm/A) * (A)
TConst0 = q0(TorqueK);              % (Nm/A)

% SPEED CONSTANT
% The gain between the output speed and induced back-EMF
% Input: Speed (rad/s)
% Output: Voltage (V)
% Equation: Back EMF = K_V         * Speed
% Units:    (V)      = (V/(rad/s)) * (rad/s)
BackEMF0 = 1 / q0(SpdK);            % (V/(rad/s))

% =====================[Mechanical Motor Dynamics]========================
% Transfer function is given as:
% TF(S) = ______s______
%         Js^2 + Bs + K
% The unit of J is kgm^2
% The unit of B is kgm^2/s
% The unit of K is kgm^2/s^2

% ======== Moment of Inertia Calculations ========
% Moment of Inertia (J) is contributed by:
% - Wrist frame (aluminium link)
% - Rotor
% - Inner motor (q1)
% - Counter weight (aluminium)

% === Moment of inertia due to the wrist frame ===
% Compute the mass of the 6061 cylindrical shell / ring
ring_volume = (link_oR^2 - link_iR^2) * pi * link_depth;    % Volume (m^3)
ring_mass   = ring_volume * alum_density;                   % Mass   (kg)

% Moment of inertial from the cylindrical shell given by formula:
% J = (m/12)*(3*(r_1^2+r_2^2)+h^2)
% Where:
% - 'J' is moment of inertia    (kgm^2)
% - 'm' is mass                 (kg)
% - 'r_1' is inner radius       (m)
% - 'r_2' is outer radius       (m)
% - 'h' is height / length of the cylinderical rod (m)
ring_J = (ring_mass / 12) * (3 * (link_iR^2 + link_oR^2) + link_depth^2);

% === Moment of inertia from motor's internal rotor ===
q0_rotor_J = q0(RotJ);          % (kgm^2)

% === Moment of inertia from the inner motor (q1) and the counter weight ===
% Find the density of the motor by treating it as a cylindrical rod
motor_length  = q1(Length);                         % (m)
motor_radius  = q1(OuterDiam) / 2;                  % (m)
motor_volume  = motor_radius^2 * pi * motor_length; % (m^3)
motor_mass    = q1(Weight);                         % (kg)
motor_density = motor_mass / motor_volume;          % (kg/m^3)

% Compute using the right equation based on assumption
if (ASSUME_THIN_ROD)

    % Find the length and mass of the extended rod (including the imaginary part in the link)
    q1_extension_volume = link_offset * motor_radius^2 * pi;                 % (m^3)
    q1_extended_mass    = motor_mass + (motor_density * q1_extension_volume); % (kg)


    % Find the moment of inertia due to the extended rod(including the imaginary parts):
    % The moment of inertia for a rod turning on its end is given as:
    % J = (1/3)ml^2
    % Where:
    % - 'J' is moment of inertia    (kgm^2)
    % - 'm' is mass                 (kg)
    % - 'h' is the length of rod    (m)
    % - 'r' is the radius of the rod
    % Computing the J from the motor and the imaginary extension
    q1_extended_length = link_offset + motor_length;                        % (m)
    q1_extended_J      = q1_extended_mass * q1_extended_length^2 / 3;       % (kgm^2)

    % Compute the same thing from just the imaginary (extension) part
    q1_imaginary_mass = motor_density * link_offset * motor_radius^2 * pi;  % (kg)
    q1_imaginary_J    = q1_imaginary_mass * link_offset^2 / 3;              % (kgm^2)

    % The moment of inertia by the motor is a superposition
    q1_J = q1_extended_J - q1_imaginary_J;                                  % (kgm^2)

    % Since there's also the counter weight, the moment of inertial is effectively doubled
    q1_J = q1_J * 2;
else

    % Find the length and mass of the extended rod (including the imaginary part in the link)
    q1_extended_length = link_offset * 2 + motor_length * 2 ;     % (m^3)
    q1_extended_mass   = q1_extended_length * motor_density * pi * motor_radius ^ 2; % (kg)

    % Find the moment of inertia due to the extended rod(including the imaginary parts)
    q1_extended_J = 1/12 * q1_extended_mass * (3 * motor_radius ^ 2 + q1_extended_length ^ 2);       % (kgm^2)

    % Compute the J from just the imaginary part
    q1_imaginary_Length = 2 * link_offset;          % (m)
    q1_imaginary_mass   = motor_density * q1_imaginary_Length * motor_radius^2 * pi;  % (kg)
    q1_imaginary_J      = 1/12 * q1_imaginary_mass * (3 * motor_radius ^ 2 + q1_imaginary_Length ^ 2);       % (kgm^2)

    % The moment of inertia by the motor is a superposition
    q1_J = q1_extended_J - q1_imaginary_J;                                  % (kgm^2)
end
% ========= End of Moment of Inertia Calculations ========

% Finding 'B' via speed-torque gradient
% The damping constant B is given by (no load current * torque constant) / (no load speed)
q0_B = q0(NoLoadCurr) * q0(TorqueK) / q0(NoLoadSpd);
% q0_B = 1 / motor_param(SpdTorqueGrad);          % (Nm/(rad/s))

% Since there's a bearing that also has fiction with the same factor
% essentially the friction is doubled
q0_B = 2 * q0_B;                                % (Nm/(rad/s))

% Spring behavior associated with motor q0
q0_K = spring_k;                                % (Nm/rad)

% Putting it all together
J_0 = ring_J + q0_rotor_J + q1_J;               % (kgm^2)
B_0 = q0_B;                                     % ((rad/s)/Nm)  === (kgm^2/s)
K_0 = q0_K;                                     % (Nm/rad)      === (kgm^2/s^2)

% Insert coefficients into transfer function
Mech0n  = [1, 0];
Mech0d  = [J_0, B_0, K_0];

% Motor q0 has unlimited joint limit
JntSat0 = Big;

% =====================[Sensor Dynamics]========================
% Sensor gain maps angle (in radians) to voltages (V) [-180, 180]->[-5, 5]
Sens0    = SensV / (SensAng * RadPerDeg);       % (V/rad)
SensSat0 = SensV;                               % (V)

% =====================[Static Friction]========================
% computing the force of gravity acting on the inner assembly
inner_mass = 2 * motor_mass + ring_mass;        % (kg)
inner_fg   = G * inner_mass;                    % (N)
StFric0    = mu_SF * inner_fg;                  % (N)

% =============================
% Q1 : Rotation about x-axis (Only carrying the laser)
% =============================

% =====================[Amplifier Dynamics]========================
% Since the same amplifier is used on both motors, the transfer function is the same
Amp1n   = Amp0n;
Amp1d   = Amp0d;
AmpSat1 = AmpSat0;

% =====================[Electrical Motor Dynamics]========================
% Since the same electric motor is used on both motors, the transfer function is the same
Elec1d0 = q1(TermR);                            % (Ohms)
Elec1d1 = q1(TermL);                            % (H)
Elec1n  = 1;
Elec1d  = [Elec1d1, Elec1d0];

% =====================[Torque Const & Back EMF]========================
% NOTE: Current using identical values from q0 motor
TConst1 = q1(TorqueK);                          % (Nm/A)

BackEMF1 = 1 / q1(SpdK);                        % (V/(rad/s))

% =====================[Mechanical Motor Dynamics]========================
% Transfer function is given as:
% TF(S) = ______s______
%         Js^2 + Bs + K
% The unit of J is kgm^2
% The unit of B is kgm^2/s
% The unit of K is kgm^2/s^2

% Get rotor inertia and do unit conversion
q1_rotor_J = q1(RotJ);                 % (kgm^2)

% Motor speed torque gradient and do unit conversion
q1_B = q1(NoLoadCurr) * q1(TorqueK) / q1(NoLoadSpd);
% q1_B = 1 / motor_param(SpdTorqueGrad);          % (Nm/(rad/s))
                                                % (kgm^2/s)

% Putting it all together
% Moment of inertia only depends on the rotor
J_1 = q1_rotor_J;

% Friction
B_1 = q1_B;

% Inner motor has no spring behavior
K_1 = 0;

% Q1 mechanical dynamics transfer function
Mech1n  = [1, 0];
Mech1d  = [J_1, B_1, K_1];

% Maximum the joint can turn
JntSat1 = joint_limit;


% =====================[Sensor Dynamics]========================
Sens1    = SensV / (SensAng * RadPerDeg);       % (V/rad)
SensSat1 = SensV;                               % (V)

% =====================[Static Friction]========================
% I don't think this is used any where so we can leave it 0
StFric1 = 0;

% ==========================================
% Transfer Functions
% ==========================================
% Compute transfer functions from above values and perform system analysis
% You may prefer to put this section in a separate .m file

% Amplifier Transfer Function
tf_amp0 = tf(Amp0n, Amp0d);
tf_amp1 = tf(Amp1n, Amp1d);

% Electrical Dynamics Transfer Function
tf_elec0 = tf(Elec0n, Elec0d);
tf_elec1 = tf(Elec1n, Elec1d);

% Mechanical Dynamics Transfer Functions
tf_mech0 = tf(Mech0n, Mech0d);
tf_mech1 = tf(Mech1n, Mech1d);

% ==========================================
% System.m analysis 
% ==========================================
% The open loop transfer function maps voltage to radians/s
% Motor 0
g_q0 = tf_elec0 * TConst0 * tf_mech0;
h_q0 = BackEMF0;
oltf_q0 = tf_amp0 * (g_q0 / (1 + g_q0 * h_q0)) / tf('s'); 

% Simplified (these are verified to be correct)
ol_q0 = zpk(minreal(oltf_q0));

% Motor 1
g_q1 = tf_elec1 * TConst1 * tf_mech1;
h_q1 = BackEMF1;
oltf_q1 = tf_amp1 * (g_q1 / (1 + g_q1 * h_q1)) / tf('s');

% Simplified (also verified to be correct)
ol_q1 = zpk(minreal(oltf_q1));