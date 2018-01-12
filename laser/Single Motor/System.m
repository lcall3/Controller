% This script sets the model parameters for the SLS 3-D Printer
CONSTANTS;

	

% ==========================
% Values for Q1
% ==========================


% Kinetic Friction
F_kf = K_T1 * I_noload1 / w_noload1;			% Kinetic friction = torque / speed 
												% No load condition implies input torque = torque lost to friction
	
% =============================
% Q1 : Rotation about x-axis
% =============================

% Amplifier Dynamics
Amp1n   = [V_ss];               				% Numerator
Amp1d   = [1];               					% Denominator
AmpSat1 = V_nom1;

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


% ==========================================
% Transfer Functions
% ==========================================

% Amplifier Transfer Function
tf_amp1 = tf(Amp1n, Amp1d);

% Electrical Dynamics Transfer Function
tf_elec1 = tf(Elec1n, Elec1d);

% Mechanical Dynamics Transfer Functions
tf_mech1 = tf(Mech1n, Mech1d);


% Motor 1
g_q1 = tf_elec1 * TConst1 * tf_mech1;
h_q1 = BackEMF1;
oltf_q1 = tf_amp1 * (g_q1 / (1 + g_q1 * h_q1)) / tf('s');

% Simplified 
ol_q1 = zpk(minreal(oltf_q1));


% ==========================================
% Control
% ==========================================
PID0 = [1 0 0];   % Copied from above
PID1 = [1 0 0];   % Copied from above