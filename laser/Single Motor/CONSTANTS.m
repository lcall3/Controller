% This script contains all physical constants and specifications for the
% SLS 3-D Printer

% Start with a clean slate
% Erase entire Matlab environment
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

Width_laser = 0.01;			% Diameter of laser 					(m)

% Material & Spring Constant
RhoJoint   	= 1;           	% Density of Joint Material

% Coeff of static friction
% Amount of torque required to set a body in motion which has a given
% amount of radial force being applied to it (usually due to gravity)
uSF    = 700;            	% (um) = (uNm/N)

% Joint Limit
JntLim = 180;             % Q1 only (deg)

% Supplied Voltage
V_ss = 12;

%%%%%%%%%%%%%%%%%%
% Motor 1		 %
%%%%%%%%%%%%%%%%%%

NomI1   = 3.2;                 					% Max average current
StallI1 = 6.031;                				% Max peak current (A)
V_nom1 	= 12;

Diam_m1	 		= 0.03;       							% Motor Diameter (m)
r_m1 			= Diam_m1 / 2;							% Motor Radius (m)
Length_m1 		= 0.047;             					% Motor Length (m)
%% Find weight!!
Weight_m1		= 0.3;             						% Motor Weight (kg)

J_rotor1		= Sml;

% Armature Resistance and Inductance
R_a1 = 1.75;										% Ohms
L_a1 = 0.00112;										% H

% Torque Constant
K_T1 = 	157.45/1000;								% Convert from mNm/A to (Nm/A)

% Back EMF Constant
K_B1 = 93.31*RadPSecPerRPM;							% Convert rmp/V to ((rad/s)/V)

% No load values
I_noload1 = 0.19;									% A
w_noload1 = 7200 * RadPSecPerRPM;					% Convert from rmp to rad/s