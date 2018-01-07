% This script sets the model parameters for the SLS 3-D Printer
CONSTANTS;
DEFAULT;
         
% ========================
% PHYSICAL UNIT CONVERSION
% ========================

% ==========================
% Convert Amplifier Components to Standard Units
% ==========================
C  = C*1e-6;			% Convert to F
L  = L*1e-3;			% Convert to H
R1 = R1*1e6;			% Convert to Ohms
R2 = R2;				% Convert to Ohms


RhoAl 		= RhoAl/(1e-6)/1000;						% Convert from g/cm^3 to (kg/m^3)
SpringK 	= SpringK/1000/(2*pi);						% Convert from mNm/rev to (Nm/rad)


% ==========================
% Convert from length measurements from mm to m
% ==========================
LinkR1   		= LinkR1/1000;           				% Inner radius of wrist frame        
LinkR2   		= LinkR2/1000;           				% Outer radius of wrist frame        
LinkD    		= LinkD/1000;            				% Depth of wrist frame               
LinkOff  		= LinkOff/1000;          				% Distance from motor face to centre 



% ==========================
% Choose Motor 0
% ==========================
AMAX22_5W_SB;     
% ==========================
% Motor Parameters
% ==========================
NomI0   = MotorParam(NomCurr);                 % Max average current
StallI0 = MotorParam(StallCurr);                 % Max peak current


% ==========================
% Values for Q0
% ==========================

% Values required from Motor 1
AMAX12_p75W_SB;

MotorDiam 		= MotorParam(OuterDiam)/1000;       	% Motor Diameter
Length_m 		= MotorParam(Length)/1000;             	% Motor Length


% Mass of motor
Weight_m		= MotorParam(Weight)/1000;             					% Motor Weight (kg)


% Reset to chosen Motor 0
AMAX22_5W_SB;
% Mass of whole object
Weight_obj = Weight_m * (Length_m + LinkOff) / Length_m;			% Object weight is linearly proportional to motor for same radius
% Mass of imaginary section
Weight_img = Weight_m * (LinkOff) / Length_m;						% Imaginary weight is linearly proportional to motor for same radius
% Motor radius
r_motor = MotorDiam/2;


% ==========================
% Inertia Calculations
% ==========================

% Aluminum Link Weight
Weight_al = LinkD * pi * (LinkR2^2 - LinkR1^2) * RhoAl;							% Weight of link is h*2*pi*(r2^2 - r1^2)*density

% Inertia Resulting from Alumninum Link
J_link = Weight_al / 12 * (3 * (LinkR2^2 + LinkR1^2) + LinkD^2 );

% Inertia Resulting from Motor 1 and Counter Weight
J_obj = 1/3 * Weight_obj * (LinkOff + Length_m)^2;								% Extend motor 1 and counter weight into 1 connected long cylinder
% Inertial Resulting from Imaginary Part
J_img = 1/3 * Weight_img * (LinkOff)^2;											% Inertia of the imaginary extension between motor 1 and counter weight
% Resulting inertia
J_motor = J_obj - J_img; 														% By superposition, the inertia of these components is the whole object subtract the imaginary extension

% Motor Rotor Inertia
J_rotor = MotorParam(RotJ) / 1e4 / 1000 ;										% Convert from g cm^2 to (kg m^2)

% Total Inertia for Motor 1
J_system = J_link + 2 * J_motor + J_rotor;											% Total inertia of motor 0 is sum of all components by superposition

% ==========================
% Motor Operating Parameters
% ==========================

% Armature Resistance and Inductance
R_a = MotorParam(TermR);							% Ohms
L_a = MotorParam(TermL)/1000;						% Convert from mH to (H)

% Torque Constant
K_T = MotorParam(TorqueK)/1000;						% Convert from mNm/A to (Nm/A)

% Back EMF Constant
K_B = MotorParam(SpdK)*RadPSecPerRPM;				% Convert rmp/V to ((rad/s)/V)

% ==========================
% Friction Calculations
% ==========================

% Static Friction
F_sf = uSF*1e-6*G*(2*Weight_m + Weight_al); 		% Torque = Static Friction * Gravitational Force = (Convert from uM to M) * (Mass of link + Mass of motor + Mass of counterweight) * (Gravity)

% No load values
I_noload = MotorParam(NoLoadCurr)/1000;				% Convert from mA to A
w_noload = MotorParam(NoLoadSpd) * RadPSecPerRPM;	% Convert from rmp to rad/s

% Kinetic Friction
F_kf = 2 * K_T * I_noload / w_noload;					% Kinetic friction = torque / speed 
													% No load condition implies input torque = torque lost to friction

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Over-write the default values from DEFAULT.m %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


% =============================
% Q0 : Rotation about y-axis
% =============================

% Amplifier Dynamics
Amp0n   = [C*R1*R2-L];                      	% Numerator
Amp0d   = [C*L*R1 C*R1*R2];               		% Denominator
AmpSat0 = MotorParam(NomV);						% Amplifier saturates at nominal voltage of motor

% Electrical Motor Dynamics
Elec0n  = [1];               					% Numerator
Elec0d  = [L_a R_a];              	 			% Denominator

% Torque Const & Back EMF
TConst0  = K_T;
BackEMF0 = 1/K_B;

% Mechanical Motor Dynamics
Mech0n  = [1 0];               					% Numerator
Mech0d  = [J_system F_kf SpringK];				% Denominator
JntSat0 = pi;									% Maximum angle is +/- 180 degrees

% Sensor Dynamics
Sens0    =  SensV / (SensAng * RadPerDeg);		% Sensor converts angle to voltage
SensSat0 =  SensV;								% Maximum sensor voltage

% Static Friction
StFric0 = F_sf;

K_FB0 = 1;


	
% ==========================
% Choose Motor 1
% ==========================
AMAX12_p75W_SB;     
% ==========================
% Motor Parameters
% ==========================
NomI1   = MotorParam(NomCurr);                 % Max average current
StallI1 = MotorParam(StallCurr);                 % Max peak current


% ==========================
% Values for Q1
% ==========================

MotorDiam 		= MotorParam(OuterDiam)/1000;       	% Motor Diameter
Length_m 		= MotorParam(Length)/1000;             	% Motor Length



% Motor Rotor Inertia
J_rotor = MotorParam(RotJ) / 1e4 / 1000 ;										% Convert from g cm^2 to (kg m^2)

% ==========================
% Motor Operating Parameters
% ==========================

% Armature Resistance and Inductance
R_a = MotorParam(TermR);							% Ohms
L_a = MotorParam(TermL)/1000;						% Convert from mH to (H)

% Torque Constant
K_T1 = MotorParam(TorqueK)/1000;						% Convert from mNm/A to (Nm/A)

% Back EMF Constant
K_B1 = MotorParam(SpdK)*RadPSecPerRPM;				% Convert rmp/V to ((rad/s)/V)

% ==========================
% Friction Calculations
% ==========================

% Static Friction
F_sf = uSF*1e-6*G*(2*Weight_m + Weight_al); 		% Torque = Static Friction * Gravitational Force = (Convert from uM to M) * (Mass of link + Mass of motor + Mass of counterweight) * (Gravity)

% No load values
I_noload = MotorParam(NoLoadCurr)/1000;				% Convert from mA to A
w_noload = MotorParam(NoLoadSpd) * RadPSecPerRPM;	% Convert from rmp to rad/s

% Kinetic Friction
F_kf = K_T1 * I_noload / w_noload;					% Kinetic friction = torque / speed 
													% No load condition implies input torque = torque lost to friction
	


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Over-write the default values from DEFAULT.m %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


% =============================
% Q1 : Rotation about x-axis
% =============================

% Amplifier Dynamics
Amp1n   = Amp0n;               					% Numerator
Amp1d   = Amp0d;               					% Denominator
AmpSat1 = Big;

% Electrical Motor Dynamics
Elec1n = [1];                					% Numerator
Elec1d = [L_a R_a];                				% Denominator

% Torque Const & Back EMF
TConst1  = K_T1;
BackEMF1 = 1/K_B1;

% Mechanical Motor Dynamics
Mech1n = [1 0];                					% Numerator
Mech1d = [J_rotor F_kf 0];                		% Denominator (No spring)
JntSat1 =  JntLim * RadPerDeg;

% Sensor Dynamics
Sens1    =  SensV / (SensAng * RadPerDeg);		% Same as motor 0
SensSat1 =  SensV;

% Static Friction
StFric1 = 0;									% Mass of rotor is negligible

K_FB1 = 1;

% ==================
% TRANSFER FUNCTIONS
% ==================
% Compute transfer functions from above values and perform system analysis
% You may prefer to put this section in a separate .m file

% Amplifier
tf_amp = tf(Amp0n,Amp0d);
% Eletrical System
tf_elec0 = tf(Elec0n, Elec0d);
tf_elec1 = tf(Elec1n, Elec1d);
% Motor 0
tf_mech0 = tf(Mech0n, Mech0d);
% Motor 1
tf_mech1 = tf(Mech1n, Mech1d);

tf_pid0 = tf([1 1.945 96.72],[1 0]);
tf_pid1 = tf([1 1.347 0],[1 0]);

tf0_closed = (tf_pid0 * tf_amp * (tf_elec0 * TConst0 * tf_mech0)/(1 + tf_elec0 * TConst0 * tf_mech0 * BackEMF0) * tf([1],[1 0])) / ( 1 + (tf_pid0 * tf_amp * (tf_elec0 * TConst0 * tf_mech0)/(1 + tf_elec0 * TConst0 * tf_mech0 * BackEMF0) * tf([1],[1 0])) );
tf0_open = (tf_amp * (tf_elec0 * TConst0 * tf_mech0)/(1 + tf_elec0 * TConst0 * tf_mech0 * BackEMF0) * tf([1],[1 0]));
tf0_open_pid = zpk(minreal(tf_pid0 * tf0_open));
tf0_open = zpk(minreal(tf0_open));

tf1_open = (tf_amp * (tf_elec1 * TConst1 * tf_mech1)/(1 + tf_elec1 * TConst1 * tf_mech0 * BackEMF1) * tf([1],[1 0]));
tf1_open = zpk(minreal(tf1_open));
tf1_open_pid = zpk(minreal(tf_pid1 * tf1_open));
tf1_closed = (tf_pid1 * tf_amp * (tf_elec1 * TConst1 * tf_mech1)/(1 + tf_elec1 * TConst1 * tf_mech1 * BackEMF1) * tf([1],[1 0])) / ( 1 + (tf_pid1 * tf_amp * (tf_elec1 * TConst1 * tf_mech1)/(1 + tf_elec1 * TConst1 * tf_mech1 * BackEMF1) * tf([1],[1 0])) );

