#include "__cf_laser.h"
#include "rtw_capi.h"
#ifdef HOST_CAPI_BUILD
#include "laser_capi_host.h"
#define sizeof(s) ((size_t)(0xFFFF))
#undef rt_offsetof
#define rt_offsetof(s,el) ((uint16_T)(0xFFFF))
#define TARGET_CONST
#define TARGET_STRING(s) (s)    
#else
#include "builtin_typeid_types.h"
#include "laser.h"
#include "laser_capi.h"
#include "laser_private.h"
#ifdef LIGHT_WEIGHT_CAPI
#define TARGET_CONST                  
#define TARGET_STRING(s)               (NULL)                    
#else
#define TARGET_CONST                   const
#define TARGET_STRING(s)               (s)
#endif
#endif
static const rtwCAPI_Signals rtBlockSignals [ ] = { { 0 , 0 , TARGET_STRING (
"laser/Sine Wave" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 0 } , { 1 , 0 ,
TARGET_STRING ( "laser/Sine Wave1" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 ,
0 } , { 2 , 0 , TARGET_STRING ( "laser/Direct Kin/Product" ) , TARGET_STRING
( "" ) , 0 , 0 , 0 , 0 , 0 } , { 3 , 0 , TARGET_STRING (
"laser/Direct Kin/Product1" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 0 } ,
{ 4 , 0 , TARGET_STRING ( "laser/Error Calc/Abs" ) , TARGET_STRING ( "" ) , 0
, 0 , 0 , 0 , 0 } , { 5 , 0 , TARGET_STRING ( "laser/Error Calc/Derivative" )
, TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 0 } , { 6 , 0 , TARGET_STRING (
"laser/Error Calc/Memory1" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , {
7 , 0 , TARGET_STRING ( "laser/Error Calc/MinMax" ) , TARGET_STRING ( "" ) ,
0 , 0 , 0 , 0 , 0 } , { 8 , 0 , TARGET_STRING ( "laser/Error Calc/MinMax1" )
, TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 0 } , { 9 , 0 , TARGET_STRING (
"laser/Error Calc/MinMax4" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 1 } , {
10 , 0 , TARGET_STRING ( "laser/Error Calc/Product1" ) , TARGET_STRING ( "" )
, 0 , 0 , 0 , 0 , 0 } , { 11 , 0 , TARGET_STRING (
"laser/Error Calc/Sum of Elements" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 ,
0 } , { 12 , 0 , TARGET_STRING ( "laser/Error Calc/Sqrt1" ) , TARGET_STRING (
"" ) , 0 , 0 , 0 , 0 , 0 } , { 13 , 0 , TARGET_STRING (
"laser/Error Calc/Sqrt3" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 0 } , {
14 , 0 , TARGET_STRING ( "laser/Inverse Kin/Math Function3" ) , TARGET_STRING
( "" ) , 0 , 0 , 0 , 0 , 2 } , { 15 , 0 , TARGET_STRING (
"laser/Inverse Kin/Math Function4" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 ,
2 } , { 16 , 0 , TARGET_STRING ( "laser/Inverse Kin/Product" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 0 } , { 17 , 0 , TARGET_STRING (
"laser/Inverse Kin/Product1" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 0 } ,
{ 18 , 0 , TARGET_STRING ( "laser/Jnt Controller/Back EMF Q0" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 0 } , { 19 , 0 , TARGET_STRING (
"laser/Jnt Controller/Back EMF Q1" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 ,
0 } , { 20 , 0 , TARGET_STRING ( "laser/Jnt Controller/FB Gain Q0" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 0 } , { 21 , 0 , TARGET_STRING (
"laser/Jnt Controller/FB Gain Q1" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 ,
0 } , { 22 , 0 , TARGET_STRING ( "laser/Jnt Controller/Sensor Gain Q0" ) ,
TARGET_STRING ( "(V)" ) , 0 , 0 , 0 , 0 , 0 } , { 23 , 0 , TARGET_STRING (
"laser/Jnt Controller/Sensor Gain Q1" ) , TARGET_STRING ( "(V)" ) , 0 , 0 , 0
, 0 , 0 } , { 24 , 0 , TARGET_STRING ( "laser/Jnt Controller/Torque Const Q0"
) , TARGET_STRING ( "Torque (Nm)" ) , 0 , 0 , 0 , 0 , 0 } , { 25 , 0 ,
TARGET_STRING ( "laser/Jnt Controller/Torque Const Q1" ) , TARGET_STRING (
"Torque (Nm)" ) , 0 , 0 , 0 , 0 , 0 } , { 26 , 0 , TARGET_STRING (
"laser/Jnt Controller/Integrator Q0" ) , TARGET_STRING ( "(rad)" ) , 0 , 0 ,
0 , 0 , 0 } , { 27 , 0 , TARGET_STRING ( "laser/Jnt Controller/Integrator Q1"
) , TARGET_STRING ( "Angle (rad)" ) , 0 , 0 , 0 , 0 , 0 } , { 28 , 0 ,
TARGET_STRING ( "laser/Jnt Controller/Jnt Limit Q1" ) , TARGET_STRING (
"(rad)" ) , 0 , 0 , 0 , 0 , 0 } , { 29 , 0 , TARGET_STRING (
"laser/Jnt Controller/Saturation Q0" ) , TARGET_STRING ( "Voltagee Supplied"
) , 0 , 0 , 0 , 0 , 0 } , { 30 , 0 , TARGET_STRING (
"laser/Jnt Controller/Saturation Q1" ) , TARGET_STRING ( "Voltage Supplied" )
, 0 , 0 , 0 , 0 , 0 } , { 31 , 0 , TARGET_STRING ( "laser/Jnt Controller/Sum"
) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 0 } , { 32 , 0 , TARGET_STRING (
"laser/Jnt Controller/Sum1" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 0 } ,
{ 33 , 0 , TARGET_STRING ( "laser/Jnt Controller/Sum2" ) , TARGET_STRING ( ""
) , 0 , 0 , 0 , 0 , 0 } , { 34 , 0 , TARGET_STRING (
"laser/Jnt Controller/Sum3" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 0 } ,
{ 35 , 0 , TARGET_STRING ( "laser/Jnt Controller/Sum5" ) , TARGET_STRING ( ""
) , 0 , 0 , 0 , 0 , 0 } , { 36 , 0 , TARGET_STRING (
"laser/Jnt Controller/Elec Dyn Q0" ) , TARGET_STRING ( "Current (A)" ) , 0 ,
0 , 0 , 0 , 0 } , { 37 , 0 , TARGET_STRING (
"laser/Jnt Controller/Elec Dyn  Q1" ) , TARGET_STRING ( "Current (A)" ) , 0 ,
0 , 0 , 0 , 0 } , { 38 , 0 , TARGET_STRING (
"laser/Jnt Controller/H-Bridge Q0" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 ,
0 } , { 39 , 0 , TARGET_STRING ( "laser/Jnt Controller/H-Bridge Q1" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 0 } , { 40 , 0 , TARGET_STRING (
"laser/Jnt Controller/Mech Dyn Q0" ) , TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 ,
0 } , { 41 , 0 , TARGET_STRING ( "laser/Jnt Controller/Mech Dyn Q1" ) ,
TARGET_STRING ( "" ) , 0 , 0 , 0 , 0 , 0 } , { 42 , 0 , TARGET_STRING (
"laser/Error Calc/Compare To Constant/Compare" ) , TARGET_STRING ( "" ) , 0 ,
1 , 0 , 0 , 1 } , { 43 , 0 , TARGET_STRING (
"laser/Jnt Controller/Controller Q0/Derivative Gain" ) , TARGET_STRING ( "" )
, 0 , 0 , 0 , 0 , 0 } , { 44 , 0 , TARGET_STRING (
"laser/Jnt Controller/Controller Q0/Filter Coefficient" ) , TARGET_STRING (
"" ) , 0 , 0 , 0 , 0 , 0 } , { 45 , 0 , TARGET_STRING (
"laser/Jnt Controller/Controller Q0/Integral Gain" ) , TARGET_STRING ( "" ) ,
0 , 0 , 0 , 0 , 0 } , { 46 , 0 , TARGET_STRING (
"laser/Jnt Controller/Controller Q0/Proportional Gain" ) , TARGET_STRING ( ""
) , 0 , 0 , 0 , 0 , 0 } , { 47 , 0 , TARGET_STRING (
"laser/Jnt Controller/Controller Q0/Filter" ) , TARGET_STRING ( "" ) , 0 , 0
, 0 , 0 , 0 } , { 48 , 0 , TARGET_STRING (
"laser/Jnt Controller/Controller Q0/Integrator" ) , TARGET_STRING ( "" ) , 0
, 0 , 0 , 0 , 0 } , { 49 , 0 , TARGET_STRING (
"laser/Jnt Controller/Controller Q0/Sum" ) , TARGET_STRING ( "" ) , 0 , 0 , 0
, 0 , 0 } , { 50 , 0 , TARGET_STRING (
"laser/Jnt Controller/Controller Q0/SumD" ) , TARGET_STRING ( "" ) , 0 , 0 ,
0 , 0 , 0 } , { 51 , 0 , TARGET_STRING (
"laser/Jnt Controller/Controller Q1/Derivative Gain" ) , TARGET_STRING ( "" )
, 0 , 0 , 0 , 0 , 0 } , { 52 , 0 , TARGET_STRING (
"laser/Jnt Controller/Controller Q1/Filter Coefficient" ) , TARGET_STRING (
"" ) , 0 , 0 , 0 , 0 , 0 } , { 53 , 0 , TARGET_STRING (
"laser/Jnt Controller/Controller Q1/Integral Gain" ) , TARGET_STRING ( "" ) ,
0 , 0 , 0 , 0 , 0 } , { 54 , 0 , TARGET_STRING (
"laser/Jnt Controller/Controller Q1/Proportional Gain" ) , TARGET_STRING ( ""
) , 0 , 0 , 0 , 0 , 0 } , { 55 , 0 , TARGET_STRING (
"laser/Jnt Controller/Controller Q1/Filter" ) , TARGET_STRING ( "" ) , 0 , 0
, 0 , 0 , 0 } , { 56 , 0 , TARGET_STRING (
"laser/Jnt Controller/Controller Q1/Integrator" ) , TARGET_STRING ( "" ) , 0
, 0 , 0 , 0 , 0 } , { 57 , 0 , TARGET_STRING (
"laser/Jnt Controller/Controller Q1/Sum" ) , TARGET_STRING ( "" ) , 0 , 0 , 0
, 0 , 0 } , { 58 , 0 , TARGET_STRING (
"laser/Jnt Controller/Controller Q1/SumD" ) , TARGET_STRING ( "" ) , 0 , 0 ,
0 , 0 , 0 } , { 59 , 0 , TARGET_STRING (
"laser/Jnt Controller/Motor Current/Abs" ) , TARGET_STRING ( "" ) , 0 , 0 , 1
, 0 , 0 } , { 60 , 0 , TARGET_STRING (
"laser/Jnt Controller/Motor Current/Integrator" ) , TARGET_STRING ( "" ) , 0
, 0 , 1 , 0 , 0 } , { 61 , 0 , TARGET_STRING (
"laser/Jnt Controller/Motor Current/Memory2" ) , TARGET_STRING ( "" ) , 0 , 0
, 1 , 0 , 1 } , { 62 , 0 , TARGET_STRING (
"laser/Jnt Controller/Motor Current/MinMax1" ) , TARGET_STRING ( "" ) , 0 , 0
, 1 , 0 , 0 } , { 63 , 0 , TARGET_STRING (
"laser/Jnt Controller/Motor Current/Divide" ) , TARGET_STRING ( "" ) , 0 , 0
, 1 , 0 , 0 } , { 0 , 0 , ( NULL ) , ( NULL ) , 0 , 0 , 0 , 0 , 0 } } ;
static const rtwCAPI_BlockParameters rtBlockParameters [ ] = { { 64 ,
TARGET_STRING ( "laser/Sine Wave" ) , TARGET_STRING ( "Amplitude" ) , 0 , 0 ,
0 } , { 65 , TARGET_STRING ( "laser/Sine Wave" ) , TARGET_STRING ( "Bias" ) ,
0 , 0 , 0 } , { 66 , TARGET_STRING ( "laser/Sine Wave" ) , TARGET_STRING (
"Frequency" ) , 0 , 0 , 0 } , { 67 , TARGET_STRING ( "laser/Sine Wave" ) ,
TARGET_STRING ( "Phase" ) , 0 , 0 , 0 } , { 68 , TARGET_STRING (
"laser/Sine Wave1" ) , TARGET_STRING ( "Amplitude" ) , 0 , 0 , 0 } , { 69 ,
TARGET_STRING ( "laser/Sine Wave1" ) , TARGET_STRING ( "Bias" ) , 0 , 0 , 0 }
, { 70 , TARGET_STRING ( "laser/Sine Wave1" ) , TARGET_STRING ( "Frequency" )
, 0 , 0 , 0 } , { 71 , TARGET_STRING ( "laser/Sine Wave1" ) , TARGET_STRING (
"Phase" ) , 0 , 0 , 0 } , { 72 , TARGET_STRING (
"laser/Error Calc/Compare To Constant" ) , TARGET_STRING ( "const" ) , 0 , 0
, 0 } , { 73 , TARGET_STRING ( "laser/Error Calc/Memory1" ) , TARGET_STRING (
"InitialCondition" ) , 0 , 0 , 0 } , { 74 , TARGET_STRING (
"laser/Error Calc/Memory3" ) , TARGET_STRING ( "InitialCondition" ) , 0 , 0 ,
0 } , { 75 , TARGET_STRING ( "laser/Error Calc/Memory4" ) , TARGET_STRING (
"InitialCondition" ) , 0 , 0 , 0 } , { 76 , TARGET_STRING (
"laser/Jnt Controller/Controller Q0" ) , TARGET_STRING ( "N" ) , 0 , 0 , 0 }
, { 77 , TARGET_STRING ( "laser/Jnt Controller/Controller Q1" ) ,
TARGET_STRING ( "N" ) , 0 , 0 , 0 } , { 78 , TARGET_STRING (
"laser/Jnt Controller/Integrator Q0" ) , TARGET_STRING ( "InitialCondition" )
, 0 , 0 , 0 } , { 79 , TARGET_STRING ( "laser/Jnt Controller/Integrator Q1" )
, TARGET_STRING ( "InitialCondition" ) , 0 , 0 , 0 } , { 80 , TARGET_STRING (
"laser/Jnt Controller/Controller Q0/Filter" ) , TARGET_STRING (
"InitialCondition" ) , 0 , 0 , 0 } , { 81 , TARGET_STRING (
"laser/Jnt Controller/Controller Q0/Integrator" ) , TARGET_STRING (
"InitialCondition" ) , 0 , 0 , 0 } , { 82 , TARGET_STRING (
"laser/Jnt Controller/Controller Q1/Filter" ) , TARGET_STRING (
"InitialCondition" ) , 0 , 0 , 0 } , { 83 , TARGET_STRING (
"laser/Jnt Controller/Controller Q1/Integrator" ) , TARGET_STRING (
"InitialCondition" ) , 0 , 0 , 0 } , { 84 , TARGET_STRING (
"laser/Jnt Controller/Motor Current/Integrator" ) , TARGET_STRING (
"InitialCondition" ) , 0 , 0 , 0 } , { 85 , TARGET_STRING (
"laser/Jnt Controller/Motor Current/Memory2" ) , TARGET_STRING (
"InitialCondition" ) , 0 , 0 , 0 } , { 86 , TARGET_STRING (
"laser/Jnt Controller/Motor Current/Burned Motor/Constant" ) , TARGET_STRING
( "Value" ) , 2 , 0 , 0 } , { 0 , ( NULL ) , ( NULL ) , 0 , 0 , 0 } } ;
static const rtwCAPI_ModelParameters rtModelParameters [ ] = { { 87 ,
TARGET_STRING ( "Amp0d" ) , 0 , 0 , 0 } , { 88 , TARGET_STRING ( "Amp0n" ) ,
0 , 0 , 0 } , { 89 , TARGET_STRING ( "Amp1d" ) , 0 , 0 , 0 } , { 90 ,
TARGET_STRING ( "Amp1n" ) , 0 , 0 , 0 } , { 91 , TARGET_STRING ( "AmpSat0" )
, 0 , 0 , 0 } , { 92 , TARGET_STRING ( "AmpSat1" ) , 0 , 0 , 0 } , { 93 ,
TARGET_STRING ( "BackEMF0" ) , 0 , 0 , 0 } , { 94 , TARGET_STRING (
"BackEMF1" ) , 0 , 0 , 0 } , { 95 , TARGET_STRING ( "Distance" ) , 0 , 0 , 0
} , { 96 , TARGET_STRING ( "Elec0d" ) , 0 , 2 , 0 } , { 97 , TARGET_STRING (
"Elec0n" ) , 0 , 0 , 0 } , { 98 , TARGET_STRING ( "Elec1d" ) , 0 , 2 , 0 } ,
{ 99 , TARGET_STRING ( "Elec1n" ) , 0 , 0 , 0 } , { 100 , TARGET_STRING (
"FB0" ) , 0 , 0 , 0 } , { 101 , TARGET_STRING ( "FB1" ) , 0 , 0 , 0 } , { 102
, TARGET_STRING ( "JntSat1" ) , 0 , 0 , 0 } , { 103 , TARGET_STRING (
"Mech0d" ) , 0 , 3 , 0 } , { 104 , TARGET_STRING ( "Mech0n" ) , 0 , 2 , 0 } ,
{ 105 , TARGET_STRING ( "Mech1d" ) , 0 , 3 , 0 } , { 106 , TARGET_STRING (
"Mech1n" ) , 0 , 2 , 0 } , { 107 , TARGET_STRING ( "NomI0" ) , 0 , 0 , 0 } ,
{ 108 , TARGET_STRING ( "NomI1" ) , 0 , 0 , 0 } , { 109 , TARGET_STRING (
"PID0" ) , 0 , 3 , 0 } , { 110 , TARGET_STRING ( "PID1" ) , 0 , 3 , 0 } , {
111 , TARGET_STRING ( "Sens0" ) , 0 , 0 , 0 } , { 112 , TARGET_STRING (
"Sens1" ) , 0 , 0 , 0 } , { 113 , TARGET_STRING ( "StallI0" ) , 0 , 0 , 0 } ,
{ 114 , TARGET_STRING ( "StallI1" ) , 0 , 0 , 0 } , { 115 , TARGET_STRING (
"TConst0" ) , 0 , 0 , 0 } , { 116 , TARGET_STRING ( "TConst1" ) , 0 , 0 , 0 }
, { 0 , ( NULL ) , 0 , 0 , 0 } } ;
#ifndef HOST_CAPI_BUILD
static void * rtDataAddrMap [ ] = { & rtB . oog2f0orgs , & rtB . pw553ih11r ,
& rtB . muyocrskli , & rtB . df2qekfpqc , & rtB . hwswxdjz2o , & rtB .
kqxihv51s2 , & rtB . d0ywb4iifr , & rtB . cnomiivfhs , & rtB . cborkiagpq , &
rtB . ezjo2kpzef , & rtB . jvi3aujz2y , & rtB . mv5es2qqht , & rtB .
fl4jmkviqg , & rtB . d2rjutehif , & rtB . jfrwj2ywep , & rtB . jtzc3yh3vr , &
rtB . h32e0arsda , & rtB . l43aesz3q0 , & rtB . abmatz0jsq , & rtB .
nb55jqhq34 , & rtB . lntm0zfacy , & rtB . jnetxfptgr , & rtB . gl55e1oxq3 , &
rtB . net2l52ebc , & rtB . iv32nbz1dr , & rtB . cnmmc5tlzm , & rtB .
jvcbsan3fm , & rtB . ciuxkrwmvl , & rtB . ifywyvlyix , & rtB . dhlo5n33b5 , &
rtB . nimsz2eln4 , & rtB . imugtlsrnt , & rtB . emcqf0ggw0 , & rtB .
chgqwipbrj , & rtB . d1asgjubos , & rtB . d0itolxywz , & rtB . imv2femxvj , &
rtB . oqaiej1ofv , & rtB . bfla2pij1s , & rtB . nl1yr2gtpd , & rtB .
e55n1mwom0 , & rtB . is2oky5nmn , & rtB . nblejb4ulo , & rtB . ohehgsdsa5 , &
rtB . nrvbbkpqfy , & rtB . bwejbx3gz4 , & rtB . esaxa4ejop , & rtB .
fycvf3ohxx , & rtB . izwwnicbg1 , & rtB . lp0vniw2vg , & rtB . kpbled4wwr , &
rtB . pbnfjx04cq , & rtB . eefrdns3vo , & rtB . a1vmpy24k5 , & rtB .
iullwlukrq , & rtB . nsfmqq4us5 , & rtB . pkzwaw50et , & rtB . aljytqlhqv , &
rtB . ipvn2dlajm , & rtB . lkpyinhslc [ 0 ] , & rtB . hbmlhug0bx [ 0 ] , &
rtB . grvfia1xdu [ 0 ] , & rtB . boq4gsls3l [ 0 ] , & rtB . py2taxmodw [ 0 ]
, & rtP . SineWave_Amp , & rtP . SineWave_Bias , & rtP . SineWave_Freq , &
rtP . SineWave_Phase , & rtP . SineWave1_Amp , & rtP . SineWave1_Bias , & rtP
. SineWave1_Freq , & rtP . SineWave1_Phase , & rtP . CompareToConstant_const
, & rtP . Memory1_InitialCondition , & rtP . Memory3_InitialCondition , & rtP
. Memory4_InitialCondition , & rtP . ControllerQ0_N , & rtP . ControllerQ1_N
, & rtP . IntegratorQ0_IC , & rtP . IntegratorQ1_IC , & rtP . Filter_IC , &
rtP . Integrator_IC_itl5ymsq54 , & rtP . Filter_IC_kyn4kgm3f4 , & rtP .
Integrator_IC_bz3z1grlau , & rtP . Integrator_IC , & rtP .
Memory2_InitialCondition , & rtP . Constant_Value , & rtP . Amp0d , & rtP .
Amp0n , & rtP . Amp1d , & rtP . Amp1n , & rtP . AmpSat0 , & rtP . AmpSat1 , &
rtP . BackEMF0 , & rtP . BackEMF1 , & rtP . Distance , & rtP . Elec0d [ 0 ] ,
& rtP . Elec0n , & rtP . Elec1d [ 0 ] , & rtP . Elec1n , & rtP . FB0 , & rtP
. FB1 , & rtP . JntSat1 , & rtP . Mech0d [ 0 ] , & rtP . Mech0n [ 0 ] , & rtP
. Mech1d [ 0 ] , & rtP . Mech1n [ 0 ] , & rtP . NomI0 , & rtP . NomI1 , & rtP
. PID0 [ 0 ] , & rtP . PID1 [ 0 ] , & rtP . Sens0 , & rtP . Sens1 , & rtP .
StallI0 , & rtP . StallI1 , & rtP . TConst0 , & rtP . TConst1 , } ; static
int32_T * rtVarDimsAddrMap [ ] = { ( NULL ) } ;
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
const uint_T rtDimensionArray [ ] = { 1 , 1 , 2 , 1 , 1 , 2 , 1 , 3 } ;
static const real_T rtcapiStoredFloats [ ] = { 0.0 , 1.0 } ; static const
rtwCAPI_FixPtMap rtFixPtMap [ ] = { { ( NULL ) , ( NULL ) ,
rtwCAPI_FIX_RESERVED , 0 , 0 , 0 } , } ; static const rtwCAPI_SampleTimeMap
rtSampleTimeMap [ ] = { { ( const void * ) & rtcapiStoredFloats [ 0 ] , (
const void * ) & rtcapiStoredFloats [ 0 ] , 0 , 0 } , { ( const void * ) &
rtcapiStoredFloats [ 0 ] , ( const void * ) & rtcapiStoredFloats [ 1 ] , 1 ,
0 } , { ( NULL ) , ( NULL ) , 2 , 0 } } ; static
rtwCAPI_ModelMappingStaticInfo mmiStatic = { { rtBlockSignals , 64 , ( NULL )
, 0 , ( NULL ) , 0 } , { rtBlockParameters , 23 , rtModelParameters , 30 } ,
{ ( NULL ) , 0 } , { rtDataTypeMap , rtDimensionMap , rtFixPtMap ,
rtElementMap , rtSampleTimeMap , rtDimensionArray } , "float" , { 2691800636U
, 3910809806U , 2654587771U , 2193301241U } , ( NULL ) , 0 , 0 } ; const
rtwCAPI_ModelMappingStaticInfo * laser_GetCAPIStaticMap ( void ) { return &
mmiStatic ; }
#ifndef HOST_CAPI_BUILD
void laser_InitializeDataMapInfo ( void ) { rtwCAPI_SetVersion ( ( *
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
void laser_host_InitializeDataMapInfo ( laser_host_DataMapInfo_T * dataMap ,
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
