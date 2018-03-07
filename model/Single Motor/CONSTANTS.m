clear all;

%%%%%%%%%%%%%%%%%%%%%%
% Physical Constants %
%%%%%%%%%%%%%%%%%%%%%%
G = 9.81;               % m/s^2
FtPerM = 3.28;          % ft / m
RadPerDeg = pi/180;     % rad / deg
DegPerRad = 180/pi;     % deg / rad
RadPSecPerRPM = pi/30;  % (rad/s) / rpm

Big = 1e6;              % General purpose large number
Sml = 1e-6;             % General purpose small number


%%%%%%%%%%%%%%%%%%
% Specifications %
%%%%%%%%%%%%%%%%%%

% Simulation Execution Time
TotalTime = 20;          % (s)

% Sensor
SensV   = 5;             	% Min/Max sensor outpout voltage     (V)
SensAng = 180;           	% Min/Max sensor angle               (deg)

% Geometry
Distance   	= 1;          	% Distance from laser to screen      	(m)
JointX		= 1;			% Horizontal displacement from Motor 0 	(m)
JointY 		= 1;			% Vertical displacement from Motor 0	(m)

% Laser
LaserWidth = 0.01;			% Diameter of laser 					(m)
MotorOffset = 0.02;

% Center axle parameters
RodLength = 0;
RodRadius = 0;
RodInnerRadius = 0;
RodWeight = 0;

% Weight of 3D printed motor casing
CasingWeight = 0;

% Material & Spring Constant
RhoJoint   	= 1;           	% Density of Joint Material

% Coeff of static friction
uSF    = 700;            	% (um) = (uNm/N)

% Joint Limit
JntLim = 180;

% Supplied Voltage
Vss = 12;

%%%%%%%%%%%%%%%%%%
% Motor 		 %
%%%%%%%%%%%%%%%%%%

NomCurrent   		= 3.2;                 				% Max average current
StallCurrent 		= 6.031;                			% Max peak current (A)
NomVoltage 			= 12;

MotorDiam	 		= 0.03;       						% Motor Diameter (m)
MotorRadius 		= MotorDiam / 2;					% Motor Radius (m)
MotorLength 		= 0.047;             				% Motor Length (m)
MotorWeight			= 0.114;             					% Motor Weight (kg)


% Armature Resistance and Inductance
Ra = 8.4;												% Ohms
La = 1.12e-3;											% H



% Torque Constant
KTorque = 	23.54/1000;									% Convert from mNm/A to (Nm/A)


% Back EMF Constant
KEmf = 609.18*RadPSecPerRPM;								% Convert rmp/V to ((rad/s)/V)


% No load values
NoLoadCurrent = 0.135;									% A
NoLoadSpeed = 6114 * RadPSecPerRPM;						% Convert from rmp to rad/s

JRotor = 5.932e-6;

PWMConversion = [-1.3118e-8 8.6063e-6 -2.0381e-3 0.2134 -0.33242];

StaticFric = 12.2e-3;

% Test
% JRotor = 3.5e-6;
% Ra = 10.5;
KEmf = 630 * RadPSecPerRPM;

	
% Kinetic Friction
% Kinetic friction = torque / speed 
KineticFriction = KTorque * NoLoadCurrent / NoLoadSpeed;			
% No load condition implies input torque = torque lost to friction	