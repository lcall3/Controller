% This script sets the model parameters for the SLS 3-D Printer
CONSTANTS;
DEFAULT;
         



% ==========================
% Inertia Calculations
% ==========================

rho_motor = Weight_m0 / (pi * r_m0^2 * Length_m0);
Weight_1 = rho_motor * pi * r_m0^2 * Width_laser;
Weight_2 = Weight_m0 + Weight_1;

J_motor = (1 / 12) * Weight_2 * (3 * r_m0^2 + (Length_m0 + Width_laser)^2) - (1 / 12) * Weight_1 * (3 * r_m0^2 + Width_laser^2);

J_system = J_motor + J_rotor0;



% ==========================
% Friction Calculations
% ==========================

% Static Friction
F_sf = 0;

% Kinetic Friction
F_kf = 2 * K_T0 * I_noload0 / w_noload0;					% Kinetic friction = torque / speed 
															% No load condition implies input torque = torque lost to friction
% =============================
% Q0 : Rotation about y-axis
% =============================

% Amplifier Dynamics
Amp0n   = [1];                      	% Numerator
Amp0d   = [1];               			% Denominator
AmpSat0 = V_nom0;						% Amplifier saturates at nominal voltage of motor

% Electrical Motor Dynamics
Elec0n  = [1];               					% Numerator
Elec0d  = [L_a0 R_a0];              	 			% Denominator

% Torque Const & Back EMF
TConst0  = K_T0;
BackEMF0 = 1/K_B0;

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
% Values for Q1
% ==========================


% ==========================
% Friction Calculations
% ==========================



% Kinetic Friction
F_kf = K_T1 * I_noload1 / w_noload1;			% Kinetic friction = torque / speed 
												% No load condition implies input torque = torque lost to friction
	


% =============================
% Q1 : Rotation about x-axis
% =============================

% Amplifier Dynamics
Amp1n   = Amp0n;               					% Numerator
Amp1d   = Amp0d;               					% Denominator
AmpSat1 = Big;

% Electrical Motor Dynamics
Elec1n = [1];                					% Numerator
Elec1d = [L_a1 R_a1];                			% Denominator

% Torque Const & Back EMF
TConst1  = K_T1;
BackEMF1 = 1/K_B1;

% Mechanical Motor Dynamics
Mech1n = [1 0];                					% Numerator
Mech1d = [J_rotor1 F_kf 0];                		% Denominator (No spring)
JntSat1 =  JntLim * RadPerDeg;

% Sensor Dynamics
Sens1    =  SensV / (SensAng * RadPerDeg);		% Same as motor 0
SensSat1 =  SensV;

% Static Friction
StFric1 = 0;									% Mass of rotor is negligible

K_FB1 = 1;

