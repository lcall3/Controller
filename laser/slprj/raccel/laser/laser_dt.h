#include "__cf_laser.h"
#include "ext_types.h"
static uint_T rtDataTypeSizes [ ] = { sizeof ( real_T ) , sizeof ( real32_T )
, sizeof ( int8_T ) , sizeof ( uint8_T ) , sizeof ( int16_T ) , sizeof (
uint16_T ) , sizeof ( int32_T ) , sizeof ( uint32_T ) , sizeof ( boolean_T )
, sizeof ( fcn_call_T ) , sizeof ( int_T ) , sizeof ( pointer_T ) , sizeof (
action_T ) , 2 * sizeof ( uint32_T ) } ; static const char_T *
rtDataTypeNames [ ] = { "real_T" , "real32_T" , "int8_T" , "uint8_T" ,
"int16_T" , "uint16_T" , "int32_T" , "uint32_T" , "boolean_T" , "fcn_call_T"
, "int_T" , "pointer_T" , "action_T" , "timer_uint32_pair_T" } ; static
DataTypeTransition rtBTransitions [ ] = { { ( char_T * ) ( & rtB . hbmlhug0bx
[ 0 ] ) , 0 , 0 , 72 } , { ( char_T * ) ( & rtB . nblejb4ulo ) , 8 , 0 , 1 }
, { ( char_T * ) ( & rtDW . edqnr03j4o [ 0 ] ) , 0 , 0 , 9 } , { ( char_T * )
( & rtDW . ihyfkimqv5 . AQHandles ) , 11 , 0 , 5 } , { ( char_T * ) ( & rtDW
. frnbyss1yt [ 0 ] ) , 10 , 0 , 11 } , { ( char_T * ) ( & rtDW . lufveoz2ya )
, 2 , 0 , 3 } , { ( char_T * ) ( & rtDW . kylvmh4w13 ) , 8 , 0 , 5 } } ;
static DataTypeTransitionTable rtBTransTable = { 7U , rtBTransitions } ;
static DataTypeTransition rtPTransitions [ ] = { { ( char_T * ) ( & rtP .
Amp0d ) , 0 , 0 , 64 } , { ( char_T * ) ( & rtP . Constant_Value ) , 3 , 0 ,
1 } } ; static DataTypeTransitionTable rtPTransTable = { 2U , rtPTransitions
} ;
