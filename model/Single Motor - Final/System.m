CONSTANTS;

 
% ==========================================
% YAW MOTOR
% ==========================================

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
Mech0d = [JRotor KineticFriction 0];            % Denominator 
JntSat0 =  JntLim * RadPerDeg;

% Sensor Dynamics
Sens0    =  SensV / (SensAng * RadPerDeg);
SensSat0 =  SensV;

% Static Friction
StFric0 = 0;									% Mass of rotor is negligible

% ==========================================
% PITCH MOTOR
% ==========================================


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
% PID Values
% ==========================================

% Initial Value
PID1 = [0 1 0]; 


% ==========================================
% Transfer Functions
% ==========================================

% Electrical Dynamics Transfer Function
tf_elec1 = tf(Elec1n, Elec1d);

% Mechanical Dynamics Transfer Functions
tf_mech1 = tf(Mech1n, Mech1d);


% Motor Transfer Function
g_q1 = tf_elec1 * TConst1 * tf_mech1;
h_q1 = BackEMF1;


%% PID
tf_pid = tf(PID1,[1,0]);

%% OPEN LOOP TF
tf_motor = tf_poly * (g_q1 / (1 + g_q1 * h_q1));
tf_ol = tf_pid * tf_poly * (g_q1 / (1 + g_q1 * h_q1)) / tf('s');
tf_control = tf_ol / (1 + tf_ol);
tf_cl = zpk(minreal(tf_control));
