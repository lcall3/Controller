#include "__cf_motor.h"
#include "ext_types.h"
static uint_T rtDataTypeSizes [ ] = { sizeof ( real_T ) , sizeof ( real32_T )
, sizeof ( int8_T ) , sizeof ( uint8_T ) , sizeof ( int16_T ) , sizeof (
uint16_T ) , sizeof ( int32_T ) , sizeof ( uint32_T ) , sizeof ( boolean_T )
, sizeof ( fcn_call_T ) , sizeof ( int_T ) , sizeof ( pointer_T ) , sizeof (
action_T ) , 2 * sizeof ( uint32_T ) } ; static const char_T *
rtDataTypeNames [ ] = { "real_T" , "real32_T" , "int8_T" , "uint8_T" ,
"int16_T" , "uint16_T" , "int32_T" , "uint32_T" , "boolean_T" , "fcn_call_T"
, "int_T" , "pointer_T" , "action_T" , "timer_uint32_pair_T" } ; static
DataTypeTransition rtBTransitions [ ] = { { ( char_T * ) ( & rtB . ioc0okmkmy
) , 0 , 0 , 70 } , { ( char_T * ) ( & rtB . hryw525bko ) , 8 , 0 , 4 } , { (
char_T * ) ( & rtDW . jhudklf0yp ) , 0 , 0 , 2 } , { ( char_T * ) ( & rtDW .
k2x5bpwds1 . LoggedData ) , 11 , 0 , 27 } , { ( char_T * ) ( & rtDW .
j1xa3hpons . Count ) , 10 , 0 , 18 } , { ( char_T * ) ( & rtDW . abahn02ksw )
, 8 , 0 , 5 } } ; static DataTypeTransitionTable rtBTransTable = { 6U ,
rtBTransitions } ; static DataTypeTransition rtPTransitions [ ] = { { (
char_T * ) ( & rtP . AmpSat1 ) , 0 , 0 , 64 } , { ( char_T * ) ( & rtP .
Constant_Value ) , 3 , 0 , 1 } } ; static DataTypeTransitionTable
rtPTransTable = { 2U , rtPTransitions } ;
