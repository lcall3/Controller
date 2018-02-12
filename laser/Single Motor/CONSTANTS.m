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

LaserWidth = 0.01;			% Diameter of laser 					(m)

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
%% Find weight!!
MotorWeight			= 0.3;             					% Motor Weight (kg)


% Armature Resistance and Inductance
Ra = 8.4;												% Ohms
La = 1.12e-3;											% H

% Torque Constant
KTorque = 	23.54/1000;									% Convert from mNm/A to (Nm/A)

% Back EMF Constant
KEmf = 628.5*RadPSecPerRPM;								% Convert rmp/V to ((rad/s)/V)

% No load values
NoLoadCurrent = 0.19;									% A
NoLoadSpeed = 7200 * RadPSecPerRPM;						% Convert from rmp to rad/s

JRotor	= 4.646e-5;