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


% Material & Spring Constant
RhoJoint   	= 1;           	% Density of Joint Material

% Coeff of static friction
uSF    = 700;            	% (um) = (uNm/N)

% Supplied Voltage
Vss = 12;
