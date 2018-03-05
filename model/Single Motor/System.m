CONSTANTS;

				
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

ol_pid = zpk(ol_q1 * tf([1 8.005 0],[1 0]));

tf_control = zpk(minreal(ol_q1 * tf([1 8.005 0], [1 0])));


% ==========================================
% Control
% ==========================================

% Initial Value
PID1 = [1 0 2.6]; 

% PID1 = [3 0.01 2]; 
% PID1 = [210 0 5.5]; 
