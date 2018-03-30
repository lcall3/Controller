
%%%%%%%%%%%%%%%%%%
% Motor 		 %
%%%%%%%%%%%%%%%%%%

% Weight of 3D printed motor casing
CasingWeight = 0;

% Joint Limit
JntLim = 180;

NomCurrent   		= 3.2;                 				% Max average current
StallCurrent 		= 6.031;                			% Max peak current (A)
NomVoltage 			= 12;

MotorDiam	 		= 0.03;       						% Motor Diameter (m)
MotorRadius 		= MotorDiam / 2;					% Motor Radius (m)
MotorLength 		= 0.047;             				% Motor Length (m)
MotorWeight			= 0.114;             				% Motor Weight (kg)


% Armature Resistance and Inductance
Ra = 4.18;												% Ohms
La = 1.51e-3;											% H



% Torque Constant
KTorque = 	23.54/1000;									% Convert from mNm/A to (Nm/A)


% Back EMF Constant
KEmf = 609.18*RadPSecPerRPM;								% Convert rmp/V to ((rad/s)/V)


% No load values
NoLoadCurrent = 0.135;									% A
NoLoadSpeed = 6114 * RadPSecPerRPM;						% Convert from rmp to rad/s

JRotor = 5.932e-6;

PWMConversion = [-1.3118e-8 8.6063e-6 -2.0381e-3 0.2134 -0.33242];

StaticFric = 12e-3;

	
% Kinetic Friction
% Kinetic friction = torque / speed 
KineticFriction = KTorque * NoLoadCurrent / NoLoadSpeed;			
% No load condition implies input torque = torque lost to friction