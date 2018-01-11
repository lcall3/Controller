% This script sets the model parameters for the SLS 3-D Printer
CONSTANTS;
DEFAULT;
         
% ==========================
% Choose Motor 0
% ==========================
AMAX22_5W_SB;     
% ==========================
% Motor Parameters
% ==========================
NomI0   = MotorParam(NomCurr);                 	% Max average current
StallI0 = MotorParam(StallCurr);                % Max peak current


% ==========================
% Values for Q0
% ==========================

% Physical Dimensions of Motor 1
AMAX12_p75W_SB;

Diam_m	 		= MotorParam(OuterDiam)/1000;       	% Motor Diameter
r_m 			= Diam_m / 2;							% Motor Radius
Length_m 		= MotorParam(Length)/1000;             	% Motor Length
Weight_m		= MotorParam(Weight)/1000;             	% Motor Weight (kg)


% Reset to chosen Motor 0
AMAX22_5W_SB;

% ==========================
% Inertia Calculations
% ==========================

rho_motor = Weight_m / (pi * r_m^2 * Length_m);
Weight_1 = rho_motor * pi * r_m^2 * Width_laser;
Weight_2 = Weight_m + Weight_1;

J_motor = (1 / 12) * Weight_2 * (3 * r_m^2 + (Length_m + Width_laser)^2) - (1 / 12) * Weight_1 * (3 * r_m^2 + Width_laser^2);
J_rotor = MotorParam(RotJ) / 1e4 / 1000;

J_system = J_motor + J_rotor;

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

% No load values
I_noload = MotorParam(NoLoadCurr) / 1000;				% Convert from mA to A
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
Amp0n   = [1];                      	% Numerator
Amp0d   = [1];               			% Denominator
AmpSat0 = MotorParam(NomV);						% Amplifier saturates at nominal voltage of motor

% Electrical Motor Dynamics
Elec0n  = [1];               					% Numerator
Elec0d  = [L_a R_a];              	 			% Denominator

% Torque Const & Back EMF
TConst0  = K_T;
BackEMF0 = 1/K_B;

% Mechanical Motor Dynamics
Mech0n  = [1 0];               					% Numerator
Mech0d  = [J_system F_kf 0];					% Denominator
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
J_rotor = MotorParam(RotJ) / 1e4 / 1000 ;			% Convert from g cm^2 to (kg m^2)

% ==========================
% Motor Operating Parameters
% ==========================

% Armature Resistance and Inductance
R_a = MotorParam(TermR);							% Ohms
L_a = MotorParam(TermL)/1000;						% Convert from mH to (H)

% Torque Constant
K_T1 = MotorParam(TorqueK)/1000;					% Convert from mNm/A to (Nm/A)

% Back EMF Constant
K_B1 = MotorParam(SpdK)*RadPSecPerRPM;				% Convert rmp/V to ((rad/s)/V)

% ==========================
% Friction Calculations
% ==========================

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

