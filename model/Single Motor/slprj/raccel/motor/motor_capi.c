#include "__cf_motor.h"
#include "rtw_capi.h"
#ifdef HOST_CAPI_BUILD
#include "motor_capi_host.h"
#define sizeof(s) ((size_t)(0xFFFF))
#undef rt_offsetof
#define rt_offsetof(s,el) ((uint16_T)(0xFFFF))
#define TARGET_CONST
#define TARGET_STRING(s) (s)    
#else
#include "builtin_typeid_types.h"
#include "motor.h"
#include "motor_capi.h"
#include "motor_private.h"
#ifdef LIGHT_WEIGHT_CAPI
#define TARGET_CONST                  
#define TARGET_STRING(s)               (NULL)                    
#else
#define TARGET_CONST                   const
#define TARGET_STRING(s)               (s)
#endif
#endif
static const rtwCAPI_Signals rtBlockSignals [ ] = { { 0 , 0 , TARGET_STRING (
"motor/Step" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 0 } , { 1 , 0 ,
TARGET_STRING ( "motor/Error Calc/Abs" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 ,
0 , 1 } , { 2 , 0 , TARGET_STRING ( "motor/Error Calc/Memory1" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 0 } , { 3 , 0 , TARGET_STRING (
"motor/Error Calc/MinMax" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , {
4 , 0 , TARGET_STRING ( "motor/Error Calc/Product" ) , TARGET_STRING ( "" ) ,
0 , 0 , 0 , 0 , 1 } , { 5 , 0 , TARGET_STRING ( "motor/Error Calc/Subtract" )
, TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 6 , 0 , TARGET_STRING (
"motor/Jnt Controller/Back EMF 1" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 ,
1 } , { 7 , 0 , TARGET_STRING ( "motor/Jnt Controller/Back EMF 2" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 8 , 0 , TARGET_STRING (
"motor/Jnt Controller/Back EMF 3" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 ,
1 } , { 9 , 0 , TARGET_STRING ( "motor/Jnt Controller/Torque Const 1" ) ,
TARGET_STRING ( "Torque (Nm)" ) , 0 , 0 , 0 , 0 , 1 } , { 10 , 0 ,
TARGET_STRING ( "motor/Jnt Controller/Torque Const 2" ) , TARGET_STRING (
"Torque (Nm)" ) , 0 , 0 , 0 , 0 , 1 } , { 11 , 0 , TARGET_STRING (
"motor/Jnt Controller/Torque Const 3" ) , TARGET_STRING ( "Torque (Nm)" ) , 0
, 0 , 0 , 0 , 1 } , { 12 , 0 , TARGET_STRING (
"motor/Jnt Controller/Integrator 1" ) , TARGET_STRING ( "Angle (rad)" ) , 0 ,
0 , 0 , 0 , 1 } , { 13 , 0 , TARGET_STRING (
"motor/Jnt Controller/Integrator 2" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0
, 1 } , { 14 , 0 , TARGET_STRING ( "motor/Jnt Controller/Integrator 3" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 15 , 0 , TARGET_STRING (
"motor/Jnt Controller/Polynomial1" ) , TARGET_STRING (
"Average Voltage \nSupplied" ) , 0 , 0 , 0 , 0 , 0 } , { 16 , 0 ,
TARGET_STRING ( "motor/Jnt Controller/Polynomial2" ) , TARGET_STRING ( "" ) ,
0 , 0 , 0 , 0 , 1 } , { 17 , 0 , TARGET_STRING (
"motor/Jnt Controller/Polynomial3" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 ,
1 } , { 18 , 0 , TARGET_STRING ( "motor/Jnt Controller/Nearest Int" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 19 , 0 , TARGET_STRING (
"motor/Jnt Controller/Nearest Int1" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0
, 1 } , { 20 , 0 , TARGET_STRING ( "motor/Jnt Controller/Quantize to 2pi//1"
) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 21 , 0 , TARGET_STRING (
"motor/Jnt Controller/Quantize to 2pi//400" ) , TARGET_STRING ( "" ) , 0 , 0
, 0 , 0 , 1 } , { 22 , 0 , TARGET_STRING ( "motor/Jnt Controller/Max Current"
) , TARGET_STRING ( "Current (A)" ) , 0 , 0 , 0 , 0 , 1 } , { 23 , 0 ,
TARGET_STRING ( "motor/Jnt Controller/Max Current1" ) , TARGET_STRING (
"Current (A)" ) , 0 , 0 , 0 , 0 , 1 } , { 24 , 0 , TARGET_STRING (
"motor/Jnt Controller/Max Duty  Cycle1" ) , TARGET_STRING (
"PWM\n Duty Cycle" ) , 0 , 0 , 0 , 0 , 1 } , { 25 , 0 , TARGET_STRING (
"motor/Jnt Controller/Max Duty  Cycle2" ) , TARGET_STRING (
"PWM\n Duty Cycle" ) , 0 , 0 , 0 , 0 , 1 } , { 26 , 0 , TARGET_STRING (
"motor/Jnt Controller/Max Voltage" ) , TARGET_STRING (
"Average \nVoltage Supplied" ) , 0 , 0 , 0 , 0 , 1 } , { 27 , 0 ,
TARGET_STRING ( "motor/Jnt Controller/Max Voltage1" ) , TARGET_STRING (
"Average \nVoltage Supplied" ) , 0 , 0 , 0 , 0 , 1 } , { 28 , 0 ,
TARGET_STRING ( "motor/Jnt Controller/Desired Angle Input" ) , TARGET_STRING
( "(rad)" ) , 0 , 0 , 0 , 0 , 0 } , { 29 , 0 , TARGET_STRING (
"motor/Jnt Controller/Sum1" ) , TARGET_STRING ( "Voltage (V)" ) , 0 , 0 , 0 ,
0 , 1 } , { 30 , 0 , TARGET_STRING ( "motor/Jnt Controller/Sum2" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 31 , 0 , TARGET_STRING (
"motor/Jnt Controller/Sum3" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } ,
{ 32 , 0 , TARGET_STRING ( "motor/Jnt Controller/Sum4" ) , TARGET_STRING ( ""
) , 0 , 0 , 0 , 0 , 1 } , { 33 , 0 , TARGET_STRING (
"motor/Jnt Controller/Sum5" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } ,
{ 34 , 0 , TARGET_STRING ( "motor/Jnt Controller/Sum6" ) , TARGET_STRING ( ""
) , 0 , 0 , 0 , 0 , 1 } , { 35 , 0 , TARGET_STRING (
"motor/Jnt Controller/Sum7" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } ,
{ 36 , 0 , TARGET_STRING ( "motor/Jnt Controller/Elec Dyn  1" ) ,
TARGET_STRING ( "Current (A)" ) , 0 , 0 , 0 , 0 , 1 } , { 37 , 0 ,
TARGET_STRING ( "motor/Jnt Controller/Elec Dyn  2" ) , TARGET_STRING ( "" ) ,
0 , 0 , 0 , 0 , 1 } , { 38 , 0 , TARGET_STRING (
"motor/Jnt Controller/Elec Dyn  3" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 ,
1 } , { 39 , 0 , TARGET_STRING ( "motor/Jnt Controller/Mech Dyn 1" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 40 , 0 , TARGET_STRING (
"motor/Jnt Controller/Mech Dyn 2" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 ,
1 } , { 41 , 0 , TARGET_STRING ( "motor/Jnt Controller/Mech Dyn 3" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 42 , 0 , TARGET_STRING (
"motor/Jnt Controller/Motor Current/Abs" ) , TARGET_STRING ( "" ) , 0 , 0 , 0
, 0 , 1 } , { 43 , 0 , TARGET_STRING (
"motor/Jnt Controller/Motor Current/Integrator" ) , TARGET_STRING ( "" ) , 0
, 0 , 0 , 0 , 1 } , { 44 , 0 , TARGET_STRING (
"motor/Jnt Controller/Motor Current/Memory2" ) , TARGET_STRING ( "" ) , 0 , 0
, 0 , 0 , 0 } , { 45 , 0 , TARGET_STRING (
"motor/Jnt Controller/Motor Current/MinMax1" ) , TARGET_STRING ( "" ) , 0 , 0
, 0 , 0 , 1 } , { 46 , 0 , TARGET_STRING (
"motor/Jnt Controller/Motor Current/Divide" ) , TARGET_STRING ( "" ) , 0 , 0
, 0 , 0 , 1 } , { 47 , 0 , TARGET_STRING (
"motor/Jnt Controller/PWM Limiter/-255 to -30" ) , TARGET_STRING ( "" ) , 0 ,
0 , 0 , 0 , 1 } , { 48 , 0 , TARGET_STRING (
"motor/Jnt Controller/PWM Limiter/30 to 255" ) , TARGET_STRING ( "" ) , 0 , 0
, 0 , 0 , 1 } , { 49 , 0 , TARGET_STRING (
"motor/Jnt Controller/PWM Limiter/Switch" ) , TARGET_STRING ( "" ) , 0 , 0 ,
0 , 0 , 1 } , { 50 , 0 , TARGET_STRING (
"motor/Jnt Controller/Static Friction Q1/Abs" ) , TARGET_STRING ( "" ) , 0 ,
0 , 0 , 0 , 1 } , { 51 , 0 , TARGET_STRING (
"motor/Jnt Controller/Static Friction Q1/Product" ) , TARGET_STRING ( "" ) ,
0 , 0 , 0 , 0 , 1 } , { 52 , 0 , TARGET_STRING (
"motor/Jnt Controller/Static Friction Q1/Relational Operator" ) ,
TARGET_STRING ( "" ) , 0 , 1 , 0 , 0 , 0 } , { 53 , 0 , TARGET_STRING (
"motor/Jnt Controller/Static Friction Q2/Abs" ) , TARGET_STRING ( "" ) , 0 ,
0 , 0 , 0 , 1 } , { 54 , 0 , TARGET_STRING (
"motor/Jnt Controller/Static Friction Q2/Product" ) , TARGET_STRING ( "" ) ,
0 , 0 , 0 , 0 , 1 } , { 55 , 0 , TARGET_STRING (
"motor/Jnt Controller/Static Friction Q2/Relational Operator" ) ,
TARGET_STRING ( "" ) , 0 , 1 , 0 , 0 , 0 } , { 56 , 0 , TARGET_STRING (
"motor/Jnt Controller/Step Response Control/Derivative Gain" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 57 , 0 , TARGET_STRING (
"motor/Jnt Controller/Step Response Control/Filter Coefficient" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 58 , 0 , TARGET_STRING (
"motor/Jnt Controller/Step Response Control/Integral Gain" ) , TARGET_STRING
( "" ) , 0 , 0 , 0 , 0 , 1 } , { 59 , 0 , TARGET_STRING (
"motor/Jnt Controller/Step Response Control/Proportional Gain" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 60 , 0 , TARGET_STRING (
"motor/Jnt Controller/Step Response Control/Filter" ) , TARGET_STRING ( "" )
, 0 , 0 , 0 , 0 , 1 } , { 61 , 0 , TARGET_STRING (
"motor/Jnt Controller/Step Response Control/Integrator" ) , TARGET_STRING (
"" ) , 0 , 0 , 0 , 0 , 1 } , { 62 , 0 , TARGET_STRING (
"motor/Jnt Controller/Step Response Control/Sum" ) , TARGET_STRING ( "" ) , 0
, 0 , 0 , 0 , 1 } , { 63 , 0 , TARGET_STRING (
"motor/Jnt Controller/Step Response Control/SumD" ) , TARGET_STRING ( "" ) ,
0 , 0 , 0 , 0 , 1 } , { 64 , 0 , TARGET_STRING (
"motor/Jnt Controller/Step Response Control1/Derivative Gain" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 65 , 0 , TARGET_STRING (
"motor/Jnt Controller/Step Response Control1/Filter Coefficient" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 66 , 0 , TARGET_STRING (
"motor/Jnt Controller/Step Response Control1/Integral Gain" ) , TARGET_STRING
( "" ) , 0 , 0 , 0 , 0 , 1 } , { 67 , 0 , TARGET_STRING (
"motor/Jnt Controller/Step Response Control1/Proportional Gain" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , { 68 , 0 , TARGET_STRING (
"motor/Jnt Controller/Step Response Control1/Filter" ) , TARGET_STRING ( "" )
, 0 , 0 , 0 , 0 , 1 } , { 69 , 0 , TARGET_STRING (
"motor/Jnt Controller/Step Response Control1/Integrator" ) , TARGET_STRING (
"" ) , 0 , 0 , 0 , 0 , 1 } , { 70 , 0 , TARGET_STRING (
"motor/Jnt Controller/Step Response Control1/Sum" ) , TARGET_STRING ( "" ) ,
0 , 0 , 0 , 0 , 1 } , { 71 , 0 , TARGET_STRING (
"motor/Jnt Controller/Step Response Control1/SumD" ) , TARGET_STRING ( "" ) ,
0 , 0 , 0 , 0 , 1 } , { 72 , 0 , TARGET_STRING (
"motor/Jnt Controller/Motor Current/Compare To Constant2/Compare" ) ,
TARGET_STRING ( "" ) , 0 , 1 , 0 , 0 , 0 } , { 73 , 0 , TARGET_STRING (
"motor/Jnt Controller/Motor Current/Compare To Constant3/Compare" ) ,
TARGET_STRING ( "" ) , 0 , 1 , 0 , 0 , 0 } , { 0 , 0 , ( NULL ) , ( NULL ) ,
0 , 0 , 0 , 0 , 0 } } ; static const rtwCAPI_BlockParameters
rtBlockParameters [ ] = { { 74 , TARGET_STRING ( "motor/Step" ) ,
TARGET_STRING ( "Time" ) , 0 , 0 , 0 } , { 75 , TARGET_STRING ( "motor/Step"
) , TARGET_STRING ( "Before" ) , 0 , 0 , 0 } , { 76 , TARGET_STRING (
"motor/Step" ) , TARGET_STRING ( "After" ) , 0 , 0 , 0 } , { 77 ,
TARGET_STRING ( "motor/Error Calc/Conversion" ) , TARGET_STRING ( "Value" ) ,
0 , 0 , 0 } , { 78 , TARGET_STRING ( "motor/Error Calc/Memory1" ) ,
TARGET_STRING ( "InitialCondition" ) , 0 , 0 , 0 } , { 79 , TARGET_STRING (
"motor/Jnt Controller/Step Response Control" ) , TARGET_STRING ( "P" ) , 0 ,
0 , 0 } , { 80 , TARGET_STRING ( "motor/Jnt Controller/Step Response Control"
) , TARGET_STRING ( "I" ) , 0 , 0 , 0 } , { 81 , TARGET_STRING (
"motor/Jnt Controller/Step Response Control" ) , TARGET_STRING ( "D" ) , 0 ,
0 , 0 } , { 82 , TARGET_STRING ( "motor/Jnt Controller/Step Response Control"
) , TARGET_STRING ( "N" ) , 0 , 0 , 0 } , { 83 , TARGET_STRING (
"motor/Jnt Controller/Step Response Control1" ) , TARGET_STRING ( "P" ) , 0 ,
0 , 0 } , { 84 , TARGET_STRING (
"motor/Jnt Controller/Step Response Control1" ) , TARGET_STRING ( "I" ) , 0 ,
0 , 0 } , { 85 , TARGET_STRING (
"motor/Jnt Controller/Step Response Control1" ) , TARGET_STRING ( "D" ) , 0 ,
0 , 0 } , { 86 , TARGET_STRING (
"motor/Jnt Controller/Step Response Control1" ) , TARGET_STRING ( "N" ) , 0 ,
0 , 0 } , { 87 , TARGET_STRING ( "motor/Jnt Controller/Integrator 1" ) ,
TARGET_STRING ( "InitialCondition" ) , 0 , 0 , 0 } , { 88 , TARGET_STRING (
"motor/Jnt Controller/Integrator 2" ) , TARGET_STRING ( "InitialCondition" )
, 0 , 0 , 0 } , { 89 , TARGET_STRING ( "motor/Jnt Controller/Integrator 3" )
, TARGET_STRING ( "InitialCondition" ) , 0 , 0 , 0 } , { 90 , TARGET_STRING (
"motor/Jnt Controller/Nearest Int" ) , TARGET_STRING ( "QuantizationInterval"
) , 0 , 0 , 0 } , { 91 , TARGET_STRING ( "motor/Jnt Controller/Nearest Int1"
) , TARGET_STRING ( "QuantizationInterval" ) , 0 , 0 , 0 } , { 92 ,
TARGET_STRING ( "motor/Jnt Controller/Quantize to 2pi//1" ) , TARGET_STRING (
"QuantizationInterval" ) , 0 , 0 , 0 } , { 93 , TARGET_STRING (
"motor/Jnt Controller/Quantize to 2pi//400" ) , TARGET_STRING (
"QuantizationInterval" ) , 0 , 0 , 0 } , { 94 , TARGET_STRING (
"motor/Jnt Controller/Max Current" ) , TARGET_STRING ( "UpperLimit" ) , 0 , 0
, 0 } , { 95 , TARGET_STRING ( "motor/Jnt Controller/Max Current" ) ,
TARGET_STRING ( "LowerLimit" ) , 0 , 0 , 0 } , { 96 , TARGET_STRING (
"motor/Jnt Controller/Max Current1" ) , TARGET_STRING ( "UpperLimit" ) , 0 ,
0 , 0 } , { 97 , TARGET_STRING ( "motor/Jnt Controller/Max Current1" ) ,
TARGET_STRING ( "LowerLimit" ) , 0 , 0 , 0 } , { 98 , TARGET_STRING (
"motor/Jnt Controller/Max Duty  Cycle1" ) , TARGET_STRING ( "UpperLimit" ) ,
0 , 0 , 0 } , { 99 , TARGET_STRING ( "motor/Jnt Controller/Max Duty  Cycle1"
) , TARGET_STRING ( "LowerLimit" ) , 0 , 0 , 0 } , { 100 , TARGET_STRING (
"motor/Jnt Controller/Max Duty  Cycle2" ) , TARGET_STRING ( "UpperLimit" ) ,
0 , 0 , 0 } , { 101 , TARGET_STRING ( "motor/Jnt Controller/Max Duty  Cycle2"
) , TARGET_STRING ( "LowerLimit" ) , 0 , 0 , 0 } , { 102 , TARGET_STRING (
"motor/Jnt Controller/Desired Angle Input" ) , TARGET_STRING ( "Time" ) , 0 ,
0 , 0 } , { 103 , TARGET_STRING ( "motor/Jnt Controller/Desired Angle Input"
) , TARGET_STRING ( "Before" ) , 0 , 0 , 0 } , { 104 , TARGET_STRING (
"motor/Jnt Controller/Desired Angle Input" ) , TARGET_STRING ( "After" ) , 0
, 0 , 0 } , { 105 , TARGET_STRING ( "motor/Jnt Controller/PWM" ) ,
TARGET_STRING ( "Time" ) , 0 , 0 , 0 } , { 106 , TARGET_STRING (
"motor/Jnt Controller/PWM" ) , TARGET_STRING ( "Before" ) , 0 , 0 , 0 } , {
107 , TARGET_STRING ( "motor/Jnt Controller/PWM" ) , TARGET_STRING ( "After"
) , 0 , 0 , 0 } , { 108 , TARGET_STRING (
"motor/Jnt Controller/Motor Current/Integrator" ) , TARGET_STRING (
"InitialCondition" ) , 0 , 0 , 0 } , { 109 , TARGET_STRING (
"motor/Jnt Controller/Motor Current/Memory2" ) , TARGET_STRING (
"InitialCondition" ) , 0 , 0 , 0 } , { 110 , TARGET_STRING (
"motor/Jnt Controller/PWM Limiter/-255 to -30" ) , TARGET_STRING (
"UpperLimit" ) , 0 , 0 , 0 } , { 111 , TARGET_STRING (
"motor/Jnt Controller/PWM Limiter/-255 to -30" ) , TARGET_STRING (
"LowerLimit" ) , 0 , 0 , 0 } , { 112 , TARGET_STRING (
"motor/Jnt Controller/PWM Limiter/30 to 255" ) , TARGET_STRING ( "UpperLimit"
) , 0 , 0 , 0 } , { 113 , TARGET_STRING (
"motor/Jnt Controller/PWM Limiter/30 to 255" ) , TARGET_STRING ( "LowerLimit"
) , 0 , 0 , 0 } , { 114 , TARGET_STRING (
"motor/Jnt Controller/PWM Limiter/Switch" ) , TARGET_STRING ( "Threshold" ) ,
0 , 0 , 0 } , { 115 , TARGET_STRING (
"motor/Jnt Controller/Step Response Control/Filter" ) , TARGET_STRING (
"InitialCondition" ) , 0 , 0 , 0 } , { 116 , TARGET_STRING (
"motor/Jnt Controller/Step Response Control/Integrator" ) , TARGET_STRING (
"InitialCondition" ) , 0 , 0 , 0 } , { 117 , TARGET_STRING (
"motor/Jnt Controller/Step Response Control1/Filter" ) , TARGET_STRING (
"InitialCondition" ) , 0 , 0 , 0 } , { 118 , TARGET_STRING (
"motor/Jnt Controller/Step Response Control1/Integrator" ) , TARGET_STRING (
"InitialCondition" ) , 0 , 0 , 0 } , { 119 , TARGET_STRING (
"motor/Jnt Controller/Motor Current/Burned Motor/Constant" ) , TARGET_STRING
( "Value" ) , 2 , 0 , 0 } , { 0 , ( NULL ) , ( NULL ) , 0 , 0 , 0 } } ;
static const rtwCAPI_ModelParameters rtModelParameters [ ] = { { 120 ,
TARGET_STRING ( "AmpSat1" ) , 0 , 0 , 0 } , { 121 , TARGET_STRING (
"BackEMF1" ) , 0 , 0 , 0 } , { 122 , TARGET_STRING ( "Elec1d" ) , 0 , 1 , 0 }
, { 123 , TARGET_STRING ( "Elec1n" ) , 0 , 0 , 0 } , { 124 , TARGET_STRING (
"Mech1d" ) , 0 , 2 , 0 } , { 125 , TARGET_STRING ( "Mech1n" ) , 0 , 1 , 0 } ,
{ 126 , TARGET_STRING ( "NomCurrent" ) , 0 , 0 , 0 } , { 127 , TARGET_STRING
( "PWMConversion" ) , 0 , 3 , 0 } , { 128 , TARGET_STRING ( "StallCurrent" )
, 0 , 0 , 0 } , { 129 , TARGET_STRING ( "StaticFric" ) , 0 , 0 , 0 } , { 130
, TARGET_STRING ( "TConst1" ) , 0 , 0 , 0 } , { 0 , ( NULL ) , 0 , 0 , 0 } }
;
#ifndef HOST_CAPI_BUILD
static void * rtDataAddrMap [ ] = { & rtB . o5y1y4cmrq , & rtB . gterhc2ycg ,
& rtB . gmjwvr4my1 , & rtB . jqe1l2xedg , & rtB . jdxhpskhxu , & rtB .
bs4j1hqktx , & rtB . ke4p3coxhb , & rtB . brgflil51h , & rtB . e1pup3cj2f , &
rtB . ccn2pszgjr , & rtB . i2ml1fewle , & rtB . fhsc2gicgw , & rtB .
m2egujefvv , & rtB . odkwwsipfi , & rtB . ioc0okmkmy , & rtB . ozd5y1bdbm , &
rtB . jaj4esgdh0 , & rtB . puti2xcwwj , & rtB . bnpnp05c3l , & rtB .
o1ro1rhovm , & rtB . dn5v5kwhgm , & rtB . lksfqnpvfh , & rtB . awmqggonyb , &
rtB . i2zgpmdtdd , & rtB . eixzkkukbm , & rtB . ou2ycdjzh0 , & rtB .
ioesu1dalb , & rtB . mtjjfm5fkq , & rtB . obo5lyqljg , & rtB . gxpiulydd2 , &
rtB . ijsvvv0me4 , & rtB . n014xvirka , & rtB . gmkdc4mlzx , & rtB .
jgwwnwtolk , & rtB . gucmiu55ed , & rtB . kx4hloeszq , & rtB . gjaaa2fhno , &
rtB . f3xnhsznvk , & rtB . hjl5biokwy , & rtB . l2d0v0tkwo , & rtB .
lul5450swo , & rtB . k4ktntecy5 , & rtB . j1d4ade1zr , & rtB . anujv4qdwd , &
rtB . hnoyfag32g , & rtB . agiv5am4pg , & rtB . d3uyq13rzr , & rtB .
jrm53acbhq , & rtB . cjp5mog4yq , & rtB . fixgevc5xe , & rtB . hxxkhd0gkz , &
rtB . kta0dglp1y , & rtB . avhiv2ojkj , & rtB . bqokd1dwue , & rtB .
c133a0jqdk , & rtB . emy34hfzxp , & rtB . etljz0mm2f , & rtB . g5rilccwnf , &
rtB . o3wu3v2g2b , & rtB . nv3h1alees , & rtB . biwfzm5zhf , & rtB .
fjewmqeu3b , & rtB . ciip4hb2p2 , & rtB . ntrwuhfs2g , & rtB . paygzk0zoc , &
rtB . el2gn1lphk , & rtB . i51k3nx1do , & rtB . amsfxvim15 , & rtB .
nkhyo2j0jl , & rtB . dngwxi52p3 , & rtB . btapnh3csw , & rtB . no3lkd1xft , &
rtB . hryw525bko , & rtB . lm0riqbmwp , & rtP . Step_Time , & rtP . Step_Y0 ,
& rtP . Step_YFinal , & rtP . Conversion_Value , & rtP .
Memory1_InitialCondition , & rtP . StepResponseControl_P , & rtP .
StepResponseControl_I , & rtP . StepResponseControl_D , & rtP .
StepResponseControl_N , & rtP . StepResponseControl1_P , & rtP .
StepResponseControl1_I , & rtP . StepResponseControl1_D , & rtP .
StepResponseControl1_N , & rtP . Integrator1_IC , & rtP . Integrator2_IC , &
rtP . Integrator3_IC , & rtP . NearestInt_Interval , & rtP .
NearestInt1_Interval , & rtP . Quantizeto2pi1_Interval , & rtP .
Quantizeto2pi400_Interval , & rtP . MaxCurrent_UpperSat , & rtP .
MaxCurrent_LowerSat , & rtP . MaxCurrent1_UpperSat , & rtP .
MaxCurrent1_LowerSat , & rtP . MaxDutyCycle1_UpperSat , & rtP .
MaxDutyCycle1_LowerSat , & rtP . MaxDutyCycle2_UpperSat , & rtP .
MaxDutyCycle2_LowerSat , & rtP . DesiredAngleInput_Time , & rtP .
DesiredAngleInput_Y0 , & rtP . DesiredAngleInput_YFinal , & rtP . PWM_Time ,
& rtP . PWM_Y0 , & rtP . PWM_YFinal , & rtP . Integrator_IC , & rtP .
Memory2_InitialCondition , & rtP . u55to30_UpperSat , & rtP .
u55to30_LowerSat , & rtP . u0to255_UpperSat , & rtP . u0to255_LowerSat , &
rtP . Switch_Threshold , & rtP . Filter_IC_hkzbi0o3xl , & rtP .
Integrator_IC_hgnjre2kl0 , & rtP . Filter_IC , & rtP .
Integrator_IC_i2h5jsmjmj , & rtP . Constant_Value , & rtP . AmpSat1 , & rtP .
BackEMF1 , & rtP . Elec1d [ 0 ] , & rtP . Elec1n , & rtP . Mech1d [ 0 ] , &
rtP . Mech1n [ 0 ] , & rtP . NomCurrent , & rtP . PWMConversion [ 0 ] , & rtP
. StallCurrent , & rtP . StaticFric , & rtP . TConst1 , } ; static int32_T *
rtVarDimsAddrMap [ ] = { ( NULL ) } ;
#endif
static TARGET_CONST rtwCAPI_DataTypeMap rtDataTypeMap [ ] = { { "double" ,
"real_T" , 0 , 0 , sizeof ( real_T ) , SS_DOUBLE , 0 , 0 } , {
"unsigned char" , "boolean_T" , 0 , 0 , sizeof ( boolean_T ) , SS_BOOLEAN , 0
, 0 } , { "unsigned char" , "uint8_T" , 0 , 0 , sizeof ( uint8_T ) , SS_UINT8
, 0 , 0 } } ;
#ifdef HOST_CAPI_BUILD
#undef sizeof
#endif
static TARGET_CONST rtwCAPI_ElementMap rtElementMap [ ] = { { ( NULL ) , 0 ,
0 , 0 , 0 } , } ; static const rtwCAPI_DimensionMap rtDimensionMap [ ] = { {
rtwCAPI_SCALAR , 0 , 2 , 0 } , { rtwCAPI_VECTOR , 2 , 2 , 0 } , {
rtwCAPI_VECTOR , 4 , 2 , 0 } , { rtwCAPI_VECTOR , 6 , 2 , 0 } } ; static
const uint_T rtDimensionArray [ ] = { 1 , 1 , 1 , 2 , 1 , 3 , 1 , 5 } ;
static const real_T rtcapiStoredFloats [ ] = { 0.0 , 1.0 } ; static const
rtwCAPI_FixPtMap rtFixPtMap [ ] = { { ( NULL ) , ( NULL ) ,
rtwCAPI_FIX_RESERVED , 0 , 0 , 0 } , } ; static const rtwCAPI_SampleTimeMap
rtSampleTimeMap [ ] = { { ( const void * ) & rtcapiStoredFloats [ 0 ] , (
const void * ) & rtcapiStoredFloats [ 1 ] , 1 , 0 } , { ( const void * ) &
rtcapiStoredFloats [ 0 ] , ( const void * ) & rtcapiStoredFloats [ 0 ] , 0 ,
0 } } ; static rtwCAPI_ModelMappingStaticInfo mmiStatic = { { rtBlockSignals
, 74 , ( NULL ) , 0 , ( NULL ) , 0 } , { rtBlockParameters , 46 ,
rtModelParameters , 11 } , { ( NULL ) , 0 } , { rtDataTypeMap ,
rtDimensionMap , rtFixPtMap , rtElementMap , rtSampleTimeMap ,
rtDimensionArray } , "float" , { 143558795U , 2582642242U , 304599836U ,
2494036382U } , ( NULL ) , 0 , 0 } ; const rtwCAPI_ModelMappingStaticInfo *
motor_GetCAPIStaticMap ( void ) { return & mmiStatic ; }
#ifndef HOST_CAPI_BUILD
void motor_InitializeDataMapInfo ( void ) { rtwCAPI_SetVersion ( ( *
rt_dataMapInfoPtr ) . mmi , 1 ) ; rtwCAPI_SetStaticMap ( ( *
rt_dataMapInfoPtr ) . mmi , & mmiStatic ) ; rtwCAPI_SetLoggingStaticMap ( ( *
rt_dataMapInfoPtr ) . mmi , ( NULL ) ) ; rtwCAPI_SetDataAddressMap ( ( *
rt_dataMapInfoPtr ) . mmi , rtDataAddrMap ) ; rtwCAPI_SetVarDimsAddressMap (
( * rt_dataMapInfoPtr ) . mmi , rtVarDimsAddrMap ) ;
rtwCAPI_SetInstanceLoggingInfo ( ( * rt_dataMapInfoPtr ) . mmi , ( NULL ) ) ;
rtwCAPI_SetChildMMIArray ( ( * rt_dataMapInfoPtr ) . mmi , ( NULL ) ) ;
rtwCAPI_SetChildMMIArrayLen ( ( * rt_dataMapInfoPtr ) . mmi , 0 ) ; }
#else
#ifdef __cplusplus
extern "C" {
#endif
void motor_host_InitializeDataMapInfo ( motor_host_DataMapInfo_T * dataMap ,
const char * path ) { rtwCAPI_SetVersion ( dataMap -> mmi , 1 ) ;
rtwCAPI_SetStaticMap ( dataMap -> mmi , & mmiStatic ) ;
rtwCAPI_SetDataAddressMap ( dataMap -> mmi , NULL ) ;
rtwCAPI_SetVarDimsAddressMap ( dataMap -> mmi , NULL ) ; rtwCAPI_SetPath (
dataMap -> mmi , path ) ; rtwCAPI_SetFullPath ( dataMap -> mmi , NULL ) ;
rtwCAPI_SetChildMMIArray ( dataMap -> mmi , ( NULL ) ) ;
rtwCAPI_SetChildMMIArrayLen ( dataMap -> mmi , 0 ) ; }
#ifdef __cplusplus
}
#endif
#endif
