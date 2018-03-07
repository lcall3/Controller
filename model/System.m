% This script sets the model parameters for the SLS 3-D Printer
CONSTANTS;


% ==========================
% Inertia Calculations
% ==========================

RhoMotor = MotorWeight / (pi * (MotorRadius)^2 * MotorLength);
Weight1 = RhoMotor * pi * (MotorRadius)^2 * MotorOffset;
Weight2 = MotorWeight + Weight1 + CasingWeight;

JMotor = (1 / 12) * Weight2 * (3 * (MotorRadius)^2 + (MotorLength + MotorOffset)^2) - (1 / 12) * Weight1 * (3 * (MotorRadius)^2 + MotorOffset^2);
JRod = (1 / 2) * RodWeight * (RodRadius^2 + RodInnerRadius^2);

JSystem = JRotor + JMotor + JRod;


% =============================
% Q0 : Rotation about y-axis
% =============================

% Current Driver (H-Bridge)
Amp0n   = [Vss];               					% Numerator
Amp0d   = [1];               					% Denominator
AmpSat0 = NomVoltage;

% Electrical Motor Dynamics
Elec0n = [1];                					% Numerator
Elec0d = [La Ra];                				% Denominator

% Torque Const & Back EMF
TConst0  = KTorque;
BackEMF0 = 1/KEmf;

% Mechanical Motor Dynamics
Mech0n = [1 0];                					% Numerator
Mech0d = [JSystem KineticFriction 0];            % Denominator 
JntSat0 =  JntLim * RadPerDeg;

% Sensor Dynamics
Sens0    =  SensV / (SensAng * RadPerDeg);
SensSat0 =  SensV;

% Static Friction
StFric0 = 0;									% Mass of rotor is negligible

KFeedback = 1;


	

% ==========================
% Values for Q1
% ==========================


% =============================
% Q1 : Rotation about x-axis
% =============================

% Current Driver (H-Bridge)
Amp1n   = [Vss];               					% Numerator
Amp1d   = [1];               					% Denominator
AmpSat1 = NomVoltage;

% Electrical Motor Dynamics
Elec1n = [1];                					% Numerator
Elec1d = [La Ra];                				% Denominator

% Torque Const & Back EMF
TConst1  = KTorque;
BackEMF1 = 1/KEmf;

% Mechanical Motor Dynamics
Mech1n = [1 0];                					% Numerator
Mech1d = [JRotor KineticFriction 0];            % Denominator 
JntSat1 =  JntLim * RadPerDeg;

% Sensor Dynamics
Sens1    =  SensV / (SensAng * RadPerDeg);
SensSat1 =  SensV;

% Static Friction
StFric1 = 0;									% Mass of rotor is negligible

KFeedback = 1;


% ==========================================
% Transfer Functions
% ==========================================

% Amplifier Transfer Function
tf_amp0 = tf(Amp0n, Amp0d);
tf_amp1 = tf(Amp1n, Amp1d);

% Electrical Dynamics Transfer Function
tf_elec0 = tf(Elec0n, Elec0d);
tf_elec1 = tf(Elec1n, Elec1d);

% Mechanical Dynamics Transfer Functions
tf_mech0 = tf(Mech0n, Mech0d);
tf_mech1 = tf(Mech1n, Mech1d);

% The open loop transfer function maps voltage to radians/s
% Motor 0
g_q0 = tf_elec0 * TConst0 * tf_mech0;
h_q0 = BackEMF0;
oltf_q0 = tf_amp0 * (g_q0 / (1 + g_q0 * h_q0)) / tf('s'); 

% Simplified 
ol_q0 = zpk(minreal(oltf_q0));

% Motor 1
g_q1 = tf_elec1 * TConst1 * tf_mech1;
h_q1 = BackEMF1;
oltf_q1 = tf_amp1 * (g_q1 / (1 + g_q1 * h_q1)) / tf('s');

% Simplified 
ol_q1 = zpk(minreal(oltf_q1));
