#include "__cf_motor.h"
#include "rt_logging_mmi.h"
#include "motor_capi.h"
#include <math.h>
#include "motor.h"
#include "motor_private.h"
#include "motor_dt.h"
extern void * CreateDiagnosticAsVoidPtr_wrapper ( const char * id , int nargs
, ... ) ; RTWExtModeInfo * gblRTWExtModeInfo = NULL ; extern boolean_T
gblExtModeStartPktReceived ; void raccelForceExtModeShutdown ( ) { if ( !
gblExtModeStartPktReceived ) { boolean_T stopRequested = false ;
rtExtModeWaitForStartPkt ( gblRTWExtModeInfo , 3 , & stopRequested ) ; }
rtExtModeShutdown ( 3 ) ; }
#include "slsv_diagnostic_codegen_c_api.h"
const int_T gblNumToFiles = 3 ; const int_T gblNumFrFiles = 0 ; const int_T
gblNumFrWksBlocks = 0 ;
#ifdef RSIM_WITH_SOLVER_MULTITASKING
boolean_T gbl_raccel_isMultitasking = 1 ;
#else
boolean_T gbl_raccel_isMultitasking = 0 ;
#endif
boolean_T gbl_raccel_tid01eq = 0 ; int_T gbl_raccel_NumST = 4 ; const char_T
* gbl_raccel_Version = "9.0 (R2017b) 24-Jul-2017" ; void
raccel_setup_MMIStateLog ( SimStruct * S ) {
#ifdef UseMMIDataLogging
rt_FillStateSigInfoFromMMI ( ssGetRTWLogInfo ( S ) , & ssGetErrorStatus ( S )
) ;
#else
UNUSED_PARAMETER ( S ) ;
#endif
} static DataMapInfo rt_dataMapInfo ; DataMapInfo * rt_dataMapInfoPtr = &
rt_dataMapInfo ; rtwCAPI_ModelMappingInfo * rt_modelMapInfoPtr = & (
rt_dataMapInfo . mmi ) ; const char * gblSlvrJacPatternFileName =
"slprj\\raccel\\motor\\motor_Jpattern.mat" ; const int_T gblNumRootInportBlks
= 0 ; const int_T gblNumModelInputs = 0 ; extern rtInportTUtable *
gblInportTUtables ; extern const char * gblInportFileName ; const int_T
gblInportDataTypeIdx [ ] = { - 1 } ; const int_T gblInportDims [ ] = { - 1 }
; const int_T gblInportComplex [ ] = { - 1 } ; const int_T
gblInportInterpoFlag [ ] = { - 1 } ; const int_T gblInportContinuous [ ] = {
- 1 } ;
#include "simstruc.h"
#include "fixedpoint.h"
B rtB ; X rtX ; DW rtDW ; static SimStruct model_S ; SimStruct * const rtS =
& model_S ; void MdlInitialize ( void ) { rtX . nvaocs00bc = rtP .
Integrator3_IC ; rtX . pfcrbgvmdb = rtP . Integrator_IC ; rtX . mjgnwkqw0t =
0.0 ; rtDW . jhudklf0yp = rtP . Memory2_InitialCondition ; rtDW . b2ftxry5zj
= rtP . Memory1_InitialCondition ; rtX . o2vdlc3lwj = rtP .
Integrator_IC_i2h5jsmjmj ; rtX . lgupwhixdz = rtP . Filter_IC ; rtX .
bkgokwpcki = rtP . Integrator1_IC ; rtX . f3greldmrk [ 0 ] = 0.0 ; rtX .
igwsihwpdp [ 0 ] = 0.0 ; rtX . f3greldmrk [ 1 ] = 0.0 ; rtX . igwsihwpdp [ 1
] = 0.0 ; rtX . puo0nzqs35 = 0.0 ; rtX . f3s5lse3uq = rtP . Integrator2_IC ;
rtX . hcazinuy1s = rtP . Integrator_IC_hgnjre2kl0 ; rtX . av5owbi5i4 = rtP .
Filter_IC_hkzbi0o3xl ; rtX . dihsnra40r = 0.0 ; rtX . fkehg4zumr [ 0 ] = 0.0
; rtX . fkehg4zumr [ 1 ] = 0.0 ; } void MdlStart ( void ) { { void * *
slioCatalogueAddr = rt_slioCatalogueAddr ( ) ; void * r2 = ( NULL ) ; void *
* pOSigstreamManagerAddr = ( NULL ) ; const char *
errorCreatingOSigstreamManager = ( NULL ) ; const char *
errorAddingR2SharedResource = ( NULL ) ; * slioCatalogueAddr =
rtwGetNewSlioCatalogue ( rt_GetMatSigLogSelectorFileName ( ) ) ;
errorAddingR2SharedResource = rtwAddR2SharedResource (
rtwGetPointerFromUniquePtr ( rt_slioCatalogue ( ) ) , 1 ) ; if (
errorAddingR2SharedResource != ( NULL ) ) { rtwTerminateSlioCatalogue (
slioCatalogueAddr ) ; * slioCatalogueAddr = ( NULL ) ; ssSetErrorStatus ( rtS
, errorAddingR2SharedResource ) ; return ; } r2 = rtwGetR2SharedResource (
rtwGetPointerFromUniquePtr ( rt_slioCatalogue ( ) ) ) ;
pOSigstreamManagerAddr = rt_GetOSigstreamManagerAddr ( ) ;
errorCreatingOSigstreamManager = rtwOSigstreamManagerCreateInstance (
rt_GetMatSigLogSelectorFileName ( ) , r2 , pOSigstreamManagerAddr ) ; if (
errorCreatingOSigstreamManager != ( NULL ) ) { * pOSigstreamManagerAddr = (
NULL ) ; ssSetErrorStatus ( rtS , errorCreatingOSigstreamManager ) ; return ;
} } { void * slioCatalogue = rt_slioCatalogue ( ) ?
rtwGetPointerFromUniquePtr ( rt_slioCatalogue ( ) ) : sdiGetSlioCatalogue (
rt_dataMapInfo . mmi . InstanceMap . fullPath ) ; if ( ! slioCatalogue || !
rtwDisableStreamingToRepository ( slioCatalogue ) ) { { sdiSignalSourceInfoU
srcInfo ; sdiLabelU loggedName = sdiGetLabelFromChars ( "Burnt" ) ; sdiLabelU
origSigName = sdiGetLabelFromChars ( "Burnt" ) ; sdiLabelU propName =
sdiGetLabelFromChars ( "" ) ; sdiLabelU blockPath = sdiGetLabelFromChars (
"motor/Jnt Controller" ) ; sdiLabelU blockSID = sdiGetLabelFromChars ( "" ) ;
sdiLabelU subPath = sdiGetLabelFromChars ( "" ) ; sdiDims sigDims ; sdiLabelU
sigName = sdiGetLabelFromChars ( "Burnt" ) ; sdiAsyncRepoDataTypeHandle hDT =
sdiAsyncRepoGetBuiltInDataTypeHandle ( DATA_TYPE_BOOLEAN ) ; { sdiComplexity
sigComplexity = REAL ; sdiSampleTimeContinuity stCont = SAMPLE_TIME_DISCRETE
; int_T sigDimsArray [ 1 ] = { 1 } ; sigDims . nDims = 1 ; sigDims .
dimensions = sigDimsArray ; srcInfo . numBlockPathElems = 1 ; srcInfo .
fullBlockPath = ( sdiFullBlkPathU ) & blockPath ; srcInfo . SID = (
sdiSignalIDU ) & blockSID ; srcInfo . subPath = subPath ; srcInfo . portIndex
= 1 + 1 ; srcInfo . signalName = sigName ; srcInfo . sigSourceUUID = 0 ; rtDW
. oc5c35nsjw . AQHandles = sdiAsyncRepoCreateAsyncioQueue ( hDT , & srcInfo ,
rt_dataMapInfo . mmi . InstanceMap . fullPath ,
"c842e491-6feb-419f-8b25-c2bb20b93f3c" , sigComplexity , & sigDims ,
DIMENSIONS_MODE_FIXED , stCont , "" ) ; if ( rtDW . oc5c35nsjw . AQHandles )
{ sdiSetSignalSampleTimeString ( rtDW . oc5c35nsjw . AQHandles , "Continuous"
, 0.0 , ssGetTFinal ( rtS ) ) ; sdiSetRunStartTime ( rtDW . oc5c35nsjw .
AQHandles , ssGetTaskTime ( rtS , 1 ) ) ; sdiAsyncRepoSetSignalExportSettings
( rtDW . oc5c35nsjw . AQHandles , 1 , 0 ) ; sdiAsyncRepoSetSignalExportName (
rtDW . oc5c35nsjw . AQHandles , loggedName , origSigName , propName ) ; }
sdiFreeLabel ( sigName ) ; sdiFreeLabel ( loggedName ) ; sdiFreeLabel (
origSigName ) ; sdiFreeLabel ( propName ) ; sdiFreeLabel ( blockPath ) ;
sdiFreeLabel ( blockSID ) ; sdiFreeLabel ( subPath ) ; } } } { void *
treeVector = ( NULL ) ; void * accessor = ( NULL ) ; const void *
signalDescriptor = ( NULL ) ; void * loggingInterval = ( NULL ) ; char *
datasetName = "tmp_raccel_logsout" ; if ( slioCatalogue && rtwIsLoggingToFile
( slioCatalogue ) ) { treeVector = rtwGetTreeVector ( ) ; { int_T
sigDimsArray [ 1 ] = { 1 } ; rtwAddLeafNode ( 8 , "Burnt" , "zoh" , 0 , (
unsigned int * ) sigDimsArray , 1 , "logical" , "" , "Continuous" , 0.0 ,
ssGetTFinal ( rtS ) , treeVector ) ; } signalDescriptor =
rtwGetSignalDescriptor ( treeVector , 1 , 1 , 0 , 1 , "Burnt" , "" ,
rt_dataMapInfo . mmi . InstanceMap . fullPath , "motor/Jnt Controller" , 2 ,
0 , slioCatalogue , ( NULL ) , 0 , ( NULL ) , 0 ) ; if ( ! rt_slioCatalogue (
) ) { sdiSlioIsLoggingSignal ( rt_dataMapInfo . mmi . InstanceMap . fullPath
, "motor/Jnt Controller" , 2 , "Burnt" ) ; } if ( rtwLoggingOverride (
signalDescriptor , slioCatalogue ) ) { if ( ssGetRootSS ( rtS ) -> mdlInfo ->
rtwLogInfo ) { loggingInterval = rtliGetLoggingInterval ( ssGetRootSS ( rtS )
-> mdlInfo -> rtwLogInfo ) ; } else { loggingInterval =
sdiGetLoggingIntervals ( rt_dataMapInfo . mmi . InstanceMap . fullPath ) ;
datasetName = "" ; } accessor = rtwGetAccessor ( signalDescriptor ,
loggingInterval ) ; rtwAddR2Client ( accessor , signalDescriptor ,
slioCatalogue , datasetName , 1 ) ; rtDW . oc5c35nsjw . SlioLTF = accessor ;
} } } } { void * slioCatalogue = rt_slioCatalogue ( ) ?
rtwGetPointerFromUniquePtr ( rt_slioCatalogue ( ) ) : sdiGetSlioCatalogue (
rt_dataMapInfo . mmi . InstanceMap . fullPath ) ; if ( ! slioCatalogue || !
rtwDisableStreamingToRepository ( slioCatalogue ) ) { { sdiSignalSourceInfoU
srcInfo ; sdiLabelU loggedName = sdiGetLabelFromChars ( "" ) ; sdiLabelU
origSigName = sdiGetLabelFromChars ( "" ) ; sdiLabelU propName =
sdiGetLabelFromChars ( "" ) ; sdiLabelU blockPath = sdiGetLabelFromChars (
"motor/Jnt Controller/Quantize to 2pi//1" ) ; sdiLabelU blockSID =
sdiGetLabelFromChars ( "" ) ; sdiLabelU subPath = sdiGetLabelFromChars ( "" )
; sdiDims sigDims ; sdiLabelU sigName = sdiGetLabelFromChars ( "" ) ;
sdiAsyncRepoDataTypeHandle hDT = sdiAsyncRepoGetBuiltInDataTypeHandle (
DATA_TYPE_DOUBLE ) ; { sdiComplexity sigComplexity = REAL ;
sdiSampleTimeContinuity stCont = SAMPLE_TIME_DISCRETE ; int_T sigDimsArray [
1 ] = { 1 } ; sigDims . nDims = 1 ; sigDims . dimensions = sigDimsArray ;
srcInfo . numBlockPathElems = 1 ; srcInfo . fullBlockPath = ( sdiFullBlkPathU
) & blockPath ; srcInfo . SID = ( sdiSignalIDU ) & blockSID ; srcInfo .
subPath = subPath ; srcInfo . portIndex = 0 + 1 ; srcInfo . signalName =
sigName ; srcInfo . sigSourceUUID = 0 ; rtDW . oy51qzwlsb . AQHandles =
sdiAsyncRepoCreateAsyncioQueue ( hDT , & srcInfo , rt_dataMapInfo . mmi .
InstanceMap . fullPath , "570c5cd2-3682-4578-9513-6daef4d09ee7" ,
sigComplexity , & sigDims , DIMENSIONS_MODE_FIXED , stCont , "" ) ; if ( rtDW
. oy51qzwlsb . AQHandles ) { sdiSetSignalSampleTimeString ( rtDW . oy51qzwlsb
. AQHandles , "Continuous" , 0.0 , ssGetTFinal ( rtS ) ) ; sdiSetRunStartTime
( rtDW . oy51qzwlsb . AQHandles , ssGetTaskTime ( rtS , 1 ) ) ;
sdiAsyncRepoSetSignalExportSettings ( rtDW . oy51qzwlsb . AQHandles , 1 , 0 )
; sdiAsyncRepoSetSignalExportName ( rtDW . oy51qzwlsb . AQHandles ,
loggedName , origSigName , propName ) ; } sdiFreeLabel ( sigName ) ;
sdiFreeLabel ( loggedName ) ; sdiFreeLabel ( origSigName ) ; sdiFreeLabel (
propName ) ; sdiFreeLabel ( blockPath ) ; sdiFreeLabel ( blockSID ) ;
sdiFreeLabel ( subPath ) ; } } } { void * treeVector = ( NULL ) ; void *
accessor = ( NULL ) ; const void * signalDescriptor = ( NULL ) ; void *
loggingInterval = ( NULL ) ; char * datasetName = "tmp_raccel_logsout" ; if (
slioCatalogue && rtwIsLoggingToFile ( slioCatalogue ) ) { treeVector =
rtwGetTreeVector ( ) ; { int_T sigDimsArray [ 1 ] = { 1 } ; rtwAddLeafNode (
0 , "" , "zoh" , 0 , ( unsigned int * ) sigDimsArray , 1 , "double" , "" ,
"Continuous" , 0.0 , ssGetTFinal ( rtS ) , treeVector ) ; } signalDescriptor
= rtwGetSignalDescriptor ( treeVector , 1 , 1 , 0 , 1 , "" , "" ,
rt_dataMapInfo . mmi . InstanceMap . fullPath ,
"motor/Jnt Controller/Quantize to 2pi//1" , 1 , 0 , slioCatalogue , ( NULL )
, 0 , ( NULL ) , 0 ) ; if ( ! rt_slioCatalogue ( ) ) { sdiSlioIsLoggingSignal
( rt_dataMapInfo . mmi . InstanceMap . fullPath ,
"motor/Jnt Controller/Quantize to 2pi//1" , 1 , "" ) ; } if (
rtwLoggingOverride ( signalDescriptor , slioCatalogue ) ) { if ( ssGetRootSS
( rtS ) -> mdlInfo -> rtwLogInfo ) { loggingInterval = rtliGetLoggingInterval
( ssGetRootSS ( rtS ) -> mdlInfo -> rtwLogInfo ) ; } else { loggingInterval =
sdiGetLoggingIntervals ( rt_dataMapInfo . mmi . InstanceMap . fullPath ) ;
datasetName = "" ; } accessor = rtwGetAccessor ( signalDescriptor ,
loggingInterval ) ; rtwAddR2Client ( accessor , signalDescriptor ,
slioCatalogue , datasetName , 1 ) ; rtDW . oy51qzwlsb . SlioLTF = accessor ;
} } } } { void * slioCatalogue = rt_slioCatalogue ( ) ?
rtwGetPointerFromUniquePtr ( rt_slioCatalogue ( ) ) : sdiGetSlioCatalogue (
rt_dataMapInfo . mmi . InstanceMap . fullPath ) ; if ( ! slioCatalogue || !
rtwDisableStreamingToRepository ( slioCatalogue ) ) { { sdiSignalSourceInfoU
srcInfo ; sdiLabelU loggedName = sdiGetLabelFromChars ( "" ) ; sdiLabelU
origSigName = sdiGetLabelFromChars ( "" ) ; sdiLabelU propName =
sdiGetLabelFromChars ( "" ) ; sdiLabelU blockPath = sdiGetLabelFromChars (
"motor/Jnt Controller/Step Response Control1" ) ; sdiLabelU blockSID =
sdiGetLabelFromChars ( "" ) ; sdiLabelU subPath = sdiGetLabelFromChars ( "" )
; sdiDims sigDims ; sdiLabelU sigName = sdiGetLabelFromChars ( "" ) ;
sdiAsyncRepoDataTypeHandle hDT = sdiAsyncRepoGetBuiltInDataTypeHandle (
DATA_TYPE_DOUBLE ) ; { sdiComplexity sigComplexity = REAL ;
sdiSampleTimeContinuity stCont = SAMPLE_TIME_CONTINUOUS ; int_T sigDimsArray
[ 1 ] = { 1 } ; sigDims . nDims = 1 ; sigDims . dimensions = sigDimsArray ;
srcInfo . numBlockPathElems = 1 ; srcInfo . fullBlockPath = ( sdiFullBlkPathU
) & blockPath ; srcInfo . SID = ( sdiSignalIDU ) & blockSID ; srcInfo .
subPath = subPath ; srcInfo . portIndex = 0 + 1 ; srcInfo . signalName =
sigName ; srcInfo . sigSourceUUID = 0 ; rtDW . odasxv14ku . AQHandles =
sdiAsyncRepoCreateAsyncioQueue ( hDT , & srcInfo , rt_dataMapInfo . mmi .
InstanceMap . fullPath , "02488c4a-17bf-47ad-986f-d5b565a2c0d4" ,
sigComplexity , & sigDims , DIMENSIONS_MODE_FIXED , stCont , "" ) ; if ( rtDW
. odasxv14ku . AQHandles ) { sdiSetSignalSampleTimeString ( rtDW . odasxv14ku
. AQHandles , "Continuous" , 0.0 , ssGetTFinal ( rtS ) ) ; sdiSetRunStartTime
( rtDW . odasxv14ku . AQHandles , ssGetTaskTime ( rtS , 1 ) ) ;
sdiAsyncRepoSetSignalExportSettings ( rtDW . odasxv14ku . AQHandles , 1 , 0 )
; sdiAsyncRepoSetSignalExportName ( rtDW . odasxv14ku . AQHandles ,
loggedName , origSigName , propName ) ; } sdiFreeLabel ( sigName ) ;
sdiFreeLabel ( loggedName ) ; sdiFreeLabel ( origSigName ) ; sdiFreeLabel (
propName ) ; sdiFreeLabel ( blockPath ) ; sdiFreeLabel ( blockSID ) ;
sdiFreeLabel ( subPath ) ; } } } { void * treeVector = ( NULL ) ; void *
accessor = ( NULL ) ; const void * signalDescriptor = ( NULL ) ; void *
loggingInterval = ( NULL ) ; char * datasetName = "tmp_raccel_logsout" ; if (
slioCatalogue && rtwIsLoggingToFile ( slioCatalogue ) ) { treeVector =
rtwGetTreeVector ( ) ; { int_T sigDimsArray [ 1 ] = { 1 } ; rtwAddLeafNode (
0 , "" , "linear" , 0 , ( unsigned int * ) sigDimsArray , 1 , "double" , "" ,
"Continuous" , 0.0 , ssGetTFinal ( rtS ) , treeVector ) ; } signalDescriptor
= rtwGetSignalDescriptor ( treeVector , 1 , 1 , 0 , 1 , "" , "" ,
rt_dataMapInfo . mmi . InstanceMap . fullPath ,
"motor/Jnt Controller/Step Response Control1" , 1 , 0 , slioCatalogue , (
NULL ) , 0 , ( NULL ) , 0 ) ; if ( ! rt_slioCatalogue ( ) ) {
sdiSlioIsLoggingSignal ( rt_dataMapInfo . mmi . InstanceMap . fullPath ,
"motor/Jnt Controller/Step Response Control1" , 1 , "" ) ; } if (
rtwLoggingOverride ( signalDescriptor , slioCatalogue ) ) { if ( ssGetRootSS
( rtS ) -> mdlInfo -> rtwLogInfo ) { loggingInterval = rtliGetLoggingInterval
( ssGetRootSS ( rtS ) -> mdlInfo -> rtwLogInfo ) ; } else { loggingInterval =
sdiGetLoggingIntervals ( rt_dataMapInfo . mmi . InstanceMap . fullPath ) ;
datasetName = "" ; } accessor = rtwGetAccessor ( signalDescriptor ,
loggingInterval ) ; rtwAddR2Client ( accessor , signalDescriptor ,
slioCatalogue , datasetName , 1 ) ; rtDW . odasxv14ku . SlioLTF = accessor ;
} } } } { void * slioCatalogue = rt_slioCatalogue ( ) ?
rtwGetPointerFromUniquePtr ( rt_slioCatalogue ( ) ) : sdiGetSlioCatalogue (
rt_dataMapInfo . mmi . InstanceMap . fullPath ) ; if ( ! slioCatalogue || !
rtwDisableStreamingToRepository ( slioCatalogue ) ) { { sdiSignalSourceInfoU
srcInfo ; sdiLabelU loggedName = sdiGetLabelFromChars ( "Torque (Nm)" ) ;
sdiLabelU origSigName = sdiGetLabelFromChars ( "Torque (Nm)" ) ; sdiLabelU
propName = sdiGetLabelFromChars ( "" ) ; sdiLabelU blockPath =
sdiGetLabelFromChars ( "motor/Jnt Controller/Torque Const 3" ) ; sdiLabelU
blockSID = sdiGetLabelFromChars ( "" ) ; sdiLabelU subPath =
sdiGetLabelFromChars ( "" ) ; sdiDims sigDims ; sdiLabelU sigName =
sdiGetLabelFromChars ( "Torque (Nm)" ) ; sdiAsyncRepoDataTypeHandle hDT =
sdiAsyncRepoGetBuiltInDataTypeHandle ( DATA_TYPE_DOUBLE ) ; { sdiComplexity
sigComplexity = REAL ; sdiSampleTimeContinuity stCont =
SAMPLE_TIME_CONTINUOUS ; int_T sigDimsArray [ 1 ] = { 1 } ; sigDims . nDims =
1 ; sigDims . dimensions = sigDimsArray ; srcInfo . numBlockPathElems = 1 ;
srcInfo . fullBlockPath = ( sdiFullBlkPathU ) & blockPath ; srcInfo . SID = (
sdiSignalIDU ) & blockSID ; srcInfo . subPath = subPath ; srcInfo . portIndex
= 0 + 1 ; srcInfo . signalName = sigName ; srcInfo . sigSourceUUID = 0 ; rtDW
. ix54ulvqvm . AQHandles = sdiAsyncRepoCreateAsyncioQueue ( hDT , & srcInfo ,
rt_dataMapInfo . mmi . InstanceMap . fullPath ,
"7bea003a-3d06-4fd2-a58f-5f98373de183" , sigComplexity , & sigDims ,
DIMENSIONS_MODE_FIXED , stCont , "" ) ; if ( rtDW . ix54ulvqvm . AQHandles )
{ sdiSetSignalSampleTimeString ( rtDW . ix54ulvqvm . AQHandles , "Continuous"
, 0.0 , ssGetTFinal ( rtS ) ) ; sdiSetRunStartTime ( rtDW . ix54ulvqvm .
AQHandles , ssGetTaskTime ( rtS , 1 ) ) ; sdiAsyncRepoSetSignalExportSettings
( rtDW . ix54ulvqvm . AQHandles , 1 , 0 ) ; sdiAsyncRepoSetSignalExportName (
rtDW . ix54ulvqvm . AQHandles , loggedName , origSigName , propName ) ; }
sdiFreeLabel ( sigName ) ; sdiFreeLabel ( loggedName ) ; sdiFreeLabel (
origSigName ) ; sdiFreeLabel ( propName ) ; sdiFreeLabel ( blockPath ) ;
sdiFreeLabel ( blockSID ) ; sdiFreeLabel ( subPath ) ; } } } { void *
treeVector = ( NULL ) ; void * accessor = ( NULL ) ; const void *
signalDescriptor = ( NULL ) ; void * loggingInterval = ( NULL ) ; char *
datasetName = "tmp_raccel_logsout" ; if ( slioCatalogue && rtwIsLoggingToFile
( slioCatalogue ) ) { treeVector = rtwGetTreeVector ( ) ; { int_T
sigDimsArray [ 1 ] = { 1 } ; rtwAddLeafNode ( 0 , "Torque (Nm)" , "linear" ,
0 , ( unsigned int * ) sigDimsArray , 1 , "double" , "" , "Continuous" , 0.0
, ssGetTFinal ( rtS ) , treeVector ) ; } signalDescriptor =
rtwGetSignalDescriptor ( treeVector , 1 , 1 , 0 , 1 , "Torque (Nm)" , "" ,
rt_dataMapInfo . mmi . InstanceMap . fullPath ,
"motor/Jnt Controller/Torque Const 3" , 1 , 0 , slioCatalogue , ( NULL ) , 0
, ( NULL ) , 0 ) ; if ( ! rt_slioCatalogue ( ) ) { sdiSlioIsLoggingSignal (
rt_dataMapInfo . mmi . InstanceMap . fullPath ,
"motor/Jnt Controller/Torque Const 3" , 1 , "Torque (Nm)" ) ; } if (
rtwLoggingOverride ( signalDescriptor , slioCatalogue ) ) { if ( ssGetRootSS
( rtS ) -> mdlInfo -> rtwLogInfo ) { loggingInterval = rtliGetLoggingInterval
( ssGetRootSS ( rtS ) -> mdlInfo -> rtwLogInfo ) ; } else { loggingInterval =
sdiGetLoggingIntervals ( rt_dataMapInfo . mmi . InstanceMap . fullPath ) ;
datasetName = "" ; } accessor = rtwGetAccessor ( signalDescriptor ,
loggingInterval ) ; rtwAddR2Client ( accessor , signalDescriptor ,
slioCatalogue , datasetName , 1 ) ; rtDW . ix54ulvqvm . SlioLTF = accessor ;
} } } } { void * slioCatalogue = rt_slioCatalogue ( ) ?
rtwGetPointerFromUniquePtr ( rt_slioCatalogue ( ) ) : sdiGetSlioCatalogue (
rt_dataMapInfo . mmi . InstanceMap . fullPath ) ; if ( ! slioCatalogue || !
rtwDisableStreamingToRepository ( slioCatalogue ) ) { { sdiSignalSourceInfoU
srcInfo ; sdiLabelU loggedName = sdiGetLabelFromChars ( "" ) ; sdiLabelU
origSigName = sdiGetLabelFromChars ( "" ) ; sdiLabelU propName =
sdiGetLabelFromChars ( "" ) ; sdiLabelU blockPath = sdiGetLabelFromChars (
"motor/Jnt Controller/Motor Current/Burned Motor" ) ; sdiLabelU blockSID =
sdiGetLabelFromChars ( "" ) ; sdiLabelU subPath = sdiGetLabelFromChars ( "" )
; sdiDims sigDims ; sdiLabelU sigName = sdiGetLabelFromChars ( "" ) ;
sdiAsyncRepoDataTypeHandle hDT = sdiAsyncRepoGetBuiltInDataTypeHandle (
DATA_TYPE_BOOLEAN ) ; { sdiComplexity sigComplexity = REAL ;
sdiSampleTimeContinuity stCont = SAMPLE_TIME_DISCRETE ; int_T sigDimsArray [
1 ] = { 1 } ; sigDims . nDims = 1 ; sigDims . dimensions = sigDimsArray ;
srcInfo . numBlockPathElems = 1 ; srcInfo . fullBlockPath = ( sdiFullBlkPathU
) & blockPath ; srcInfo . SID = ( sdiSignalIDU ) & blockSID ; srcInfo .
subPath = subPath ; srcInfo . portIndex = 0 + 1 ; srcInfo . signalName =
sigName ; srcInfo . sigSourceUUID = 0 ; rtDW . jpmbni14kg . AQHandles =
sdiAsyncRepoCreateAsyncioQueue ( hDT , & srcInfo , rt_dataMapInfo . mmi .
InstanceMap . fullPath , "9677bf84-4f33-4a79-8593-7c03e053ce45" ,
sigComplexity , & sigDims , DIMENSIONS_MODE_FIXED , stCont , "" ) ; if ( rtDW
. jpmbni14kg . AQHandles ) { sdiSetSignalSampleTimeString ( rtDW . jpmbni14kg
. AQHandles , "Continuous" , 0.0 , ssGetTFinal ( rtS ) ) ; sdiSetRunStartTime
( rtDW . jpmbni14kg . AQHandles , ssGetTaskTime ( rtS , 1 ) ) ;
sdiAsyncRepoSetSignalExportSettings ( rtDW . jpmbni14kg . AQHandles , 1 , 0 )
; sdiAsyncRepoSetSignalExportName ( rtDW . jpmbni14kg . AQHandles ,
loggedName , origSigName , propName ) ; } sdiFreeLabel ( sigName ) ;
sdiFreeLabel ( loggedName ) ; sdiFreeLabel ( origSigName ) ; sdiFreeLabel (
propName ) ; sdiFreeLabel ( blockPath ) ; sdiFreeLabel ( blockSID ) ;
sdiFreeLabel ( subPath ) ; } } } { void * treeVector = ( NULL ) ; void *
accessor = ( NULL ) ; const void * signalDescriptor = ( NULL ) ; void *
loggingInterval = ( NULL ) ; char * datasetName = "tmp_raccel_logsout" ; if (
slioCatalogue && rtwIsLoggingToFile ( slioCatalogue ) ) { treeVector =
rtwGetTreeVector ( ) ; { int_T sigDimsArray [ 1 ] = { 1 } ; rtwAddLeafNode (
8 , "" , "zoh" , 0 , ( unsigned int * ) sigDimsArray , 1 , "logical" , "" ,
"Continuous" , 0.0 , ssGetTFinal ( rtS ) , treeVector ) ; } signalDescriptor
= rtwGetSignalDescriptor ( treeVector , 1 , 1 , 0 , 1 , "" , "" ,
rt_dataMapInfo . mmi . InstanceMap . fullPath ,
"motor/Jnt Controller/Motor Current/Burned Motor" , 1 , 0 , slioCatalogue , (
NULL ) , 0 , ( NULL ) , 0 ) ; if ( ! rt_slioCatalogue ( ) ) {
sdiSlioIsLoggingSignal ( rt_dataMapInfo . mmi . InstanceMap . fullPath ,
"motor/Jnt Controller/Motor Current/Burned Motor" , 1 , "" ) ; } if (
rtwLoggingOverride ( signalDescriptor , slioCatalogue ) ) { if ( ssGetRootSS
( rtS ) -> mdlInfo -> rtwLogInfo ) { loggingInterval = rtliGetLoggingInterval
( ssGetRootSS ( rtS ) -> mdlInfo -> rtwLogInfo ) ; } else { loggingInterval =
sdiGetLoggingIntervals ( rt_dataMapInfo . mmi . InstanceMap . fullPath ) ;
datasetName = "" ; } accessor = rtwGetAccessor ( signalDescriptor ,
loggingInterval ) ; rtwAddR2Client ( accessor , signalDescriptor ,
slioCatalogue , datasetName , 1 ) ; rtDW . jpmbni14kg . SlioLTF = accessor ;
} } } } { void * slioCatalogue = rt_slioCatalogue ( ) ?
rtwGetPointerFromUniquePtr ( rt_slioCatalogue ( ) ) : sdiGetSlioCatalogue (
rt_dataMapInfo . mmi . InstanceMap . fullPath ) ; if ( ! slioCatalogue || !
rtwDisableStreamingToRepository ( slioCatalogue ) ) { { sdiSignalSourceInfoU
srcInfo ; sdiLabelU loggedName = sdiGetLabelFromChars ( "" ) ; sdiLabelU
origSigName = sdiGetLabelFromChars ( "" ) ; sdiLabelU propName =
sdiGetLabelFromChars ( "" ) ; sdiLabelU blockPath = sdiGetLabelFromChars (
"motor/Jnt Controller/Motor Current/MinMax1" ) ; sdiLabelU blockSID =
sdiGetLabelFromChars ( "" ) ; sdiLabelU subPath = sdiGetLabelFromChars ( "" )
; sdiDims sigDims ; sdiLabelU sigName = sdiGetLabelFromChars ( "" ) ;
sdiAsyncRepoDataTypeHandle hDT = sdiAsyncRepoGetBuiltInDataTypeHandle (
DATA_TYPE_DOUBLE ) ; { sdiComplexity sigComplexity = REAL ;
sdiSampleTimeContinuity stCont = SAMPLE_TIME_CONTINUOUS ; int_T sigDimsArray
[ 1 ] = { 1 } ; sigDims . nDims = 1 ; sigDims . dimensions = sigDimsArray ;
srcInfo . numBlockPathElems = 1 ; srcInfo . fullBlockPath = ( sdiFullBlkPathU
) & blockPath ; srcInfo . SID = ( sdiSignalIDU ) & blockSID ; srcInfo .
subPath = subPath ; srcInfo . portIndex = 0 + 1 ; srcInfo . signalName =
sigName ; srcInfo . sigSourceUUID = 0 ; rtDW . ksnq4jprhj . AQHandles =
sdiAsyncRepoCreateAsyncioQueue ( hDT , & srcInfo , rt_dataMapInfo . mmi .
InstanceMap . fullPath , "7e243aac-ae97-46b8-b129-39a7958c20f3" ,
sigComplexity , & sigDims , DIMENSIONS_MODE_FIXED , stCont , "" ) ; if ( rtDW
. ksnq4jprhj . AQHandles ) { sdiSetSignalSampleTimeString ( rtDW . ksnq4jprhj
. AQHandles , "Continuous" , 0.0 , ssGetTFinal ( rtS ) ) ; sdiSetRunStartTime
( rtDW . ksnq4jprhj . AQHandles , ssGetTaskTime ( rtS , 1 ) ) ;
sdiAsyncRepoSetSignalExportSettings ( rtDW . ksnq4jprhj . AQHandles , 1 , 0 )
; sdiAsyncRepoSetSignalExportName ( rtDW . ksnq4jprhj . AQHandles ,
loggedName , origSigName , propName ) ; } sdiFreeLabel ( sigName ) ;
sdiFreeLabel ( loggedName ) ; sdiFreeLabel ( origSigName ) ; sdiFreeLabel (
propName ) ; sdiFreeLabel ( blockPath ) ; sdiFreeLabel ( blockSID ) ;
sdiFreeLabel ( subPath ) ; } } } { void * treeVector = ( NULL ) ; void *
accessor = ( NULL ) ; const void * signalDescriptor = ( NULL ) ; void *
loggingInterval = ( NULL ) ; char * datasetName = "tmp_raccel_logsout" ; if (
slioCatalogue && rtwIsLoggingToFile ( slioCatalogue ) ) { treeVector =
rtwGetTreeVector ( ) ; { int_T sigDimsArray [ 1 ] = { 1 } ; rtwAddLeafNode (
0 , "" , "linear" , 0 , ( unsigned int * ) sigDimsArray , 1 , "double" , "" ,
"Continuous" , 0.0 , ssGetTFinal ( rtS ) , treeVector ) ; } signalDescriptor
= rtwGetSignalDescriptor ( treeVector , 1 , 1 , 0 , 1 , "" , "" ,
rt_dataMapInfo . mmi . InstanceMap . fullPath ,
"motor/Jnt Controller/Motor Current/MinMax1" , 1 , 0 , slioCatalogue , ( NULL
) , 0 , ( NULL ) , 0 ) ; if ( ! rt_slioCatalogue ( ) ) {
sdiSlioIsLoggingSignal ( rt_dataMapInfo . mmi . InstanceMap . fullPath ,
"motor/Jnt Controller/Motor Current/MinMax1" , 1 , "" ) ; } if (
rtwLoggingOverride ( signalDescriptor , slioCatalogue ) ) { if ( ssGetRootSS
( rtS ) -> mdlInfo -> rtwLogInfo ) { loggingInterval = rtliGetLoggingInterval
( ssGetRootSS ( rtS ) -> mdlInfo -> rtwLogInfo ) ; } else { loggingInterval =
sdiGetLoggingIntervals ( rt_dataMapInfo . mmi . InstanceMap . fullPath ) ;
datasetName = "" ; } accessor = rtwGetAccessor ( signalDescriptor ,
loggingInterval ) ; rtwAddR2Client ( accessor , signalDescriptor ,
slioCatalogue , datasetName , 1 ) ; rtDW . ksnq4jprhj . SlioLTF = accessor ;
} } } } { void * slioCatalogue = rt_slioCatalogue ( ) ?
rtwGetPointerFromUniquePtr ( rt_slioCatalogue ( ) ) : sdiGetSlioCatalogue (
rt_dataMapInfo . mmi . InstanceMap . fullPath ) ; if ( ! slioCatalogue || !
rtwDisableStreamingToRepository ( slioCatalogue ) ) { { sdiSignalSourceInfoU
srcInfo ; sdiLabelU loggedName = sdiGetLabelFromChars ( "" ) ; sdiLabelU
origSigName = sdiGetLabelFromChars ( "" ) ; sdiLabelU propName =
sdiGetLabelFromChars ( "" ) ; sdiLabelU blockPath = sdiGetLabelFromChars (
"motor/Jnt Controller/Motor Current/Sum" ) ; sdiLabelU blockSID =
sdiGetLabelFromChars ( "" ) ; sdiLabelU subPath = sdiGetLabelFromChars ( "" )
; sdiDims sigDims ; sdiLabelU sigName = sdiGetLabelFromChars ( "" ) ;
sdiAsyncRepoDataTypeHandle hDT = sdiAsyncRepoGetBuiltInDataTypeHandle (
DATA_TYPE_UINT8 ) ; { sdiComplexity sigComplexity = REAL ;
sdiSampleTimeContinuity stCont = SAMPLE_TIME_DISCRETE ; int_T sigDimsArray [
1 ] = { 1 } ; sigDims . nDims = 1 ; sigDims . dimensions = sigDimsArray ;
srcInfo . numBlockPathElems = 1 ; srcInfo . fullBlockPath = ( sdiFullBlkPathU
) & blockPath ; srcInfo . SID = ( sdiSignalIDU ) & blockSID ; srcInfo .
subPath = subPath ; srcInfo . portIndex = 0 + 1 ; srcInfo . signalName =
sigName ; srcInfo . sigSourceUUID = 0 ; rtDW . bahcjcb1oc . AQHandles =
sdiAsyncRepoCreateAsyncioQueue ( hDT , & srcInfo , rt_dataMapInfo . mmi .
InstanceMap . fullPath , "d8caf64c-1ad0-4bda-89c1-de1e847751dd" ,
sigComplexity , & sigDims , DIMENSIONS_MODE_FIXED , stCont , "" ) ; if ( rtDW
. bahcjcb1oc . AQHandles ) { sdiSetSignalSampleTimeString ( rtDW . bahcjcb1oc
. AQHandles , "Continuous" , 0.0 , ssGetTFinal ( rtS ) ) ; sdiSetRunStartTime
( rtDW . bahcjcb1oc . AQHandles , ssGetTaskTime ( rtS , 1 ) ) ;
sdiAsyncRepoSetSignalExportSettings ( rtDW . bahcjcb1oc . AQHandles , 1 , 0 )
; sdiAsyncRepoSetSignalExportName ( rtDW . bahcjcb1oc . AQHandles ,
loggedName , origSigName , propName ) ; } sdiFreeLabel ( sigName ) ;
sdiFreeLabel ( loggedName ) ; sdiFreeLabel ( origSigName ) ; sdiFreeLabel (
propName ) ; sdiFreeLabel ( blockPath ) ; sdiFreeLabel ( blockSID ) ;
sdiFreeLabel ( subPath ) ; } } } { void * treeVector = ( NULL ) ; void *
accessor = ( NULL ) ; const void * signalDescriptor = ( NULL ) ; void *
loggingInterval = ( NULL ) ; char * datasetName = "tmp_raccel_logsout" ; if (
slioCatalogue && rtwIsLoggingToFile ( slioCatalogue ) ) { treeVector =
rtwGetTreeVector ( ) ; { int_T sigDimsArray [ 1 ] = { 1 } ; rtwAddLeafNode (
3 , "" , "zoh" , 0 , ( unsigned int * ) sigDimsArray , 1 , "uint8" , "" ,
"Continuous" , 0.0 , ssGetTFinal ( rtS ) , treeVector ) ; } signalDescriptor
= rtwGetSignalDescriptor ( treeVector , 1 , 1 , 0 , 1 , "" , "" ,
rt_dataMapInfo . mmi . InstanceMap . fullPath ,
"motor/Jnt Controller/Motor Current/Sum" , 1 , 0 , slioCatalogue , ( NULL ) ,
0 , ( NULL ) , 0 ) ; if ( ! rt_slioCatalogue ( ) ) { sdiSlioIsLoggingSignal (
rt_dataMapInfo . mmi . InstanceMap . fullPath ,
"motor/Jnt Controller/Motor Current/Sum" , 1 , "" ) ; } if (
rtwLoggingOverride ( signalDescriptor , slioCatalogue ) ) { if ( ssGetRootSS
( rtS ) -> mdlInfo -> rtwLogInfo ) { loggingInterval = rtliGetLoggingInterval
( ssGetRootSS ( rtS ) -> mdlInfo -> rtwLogInfo ) ; } else { loggingInterval =
sdiGetLoggingIntervals ( rt_dataMapInfo . mmi . InstanceMap . fullPath ) ;
datasetName = "" ; } accessor = rtwGetAccessor ( signalDescriptor ,
loggingInterval ) ; rtwAddR2Client ( accessor , signalDescriptor ,
slioCatalogue , datasetName , 1 ) ; rtDW . bahcjcb1oc . SlioLTF = accessor ;
} } } } { void * fp = ( NULL ) ; const char * fileNameOriginal =
"Step Velocity.mat" ; char * fileName = ( char * ) malloc ( 509 ) ; if (
fileName == ( NULL ) ) { ssSetErrorStatus ( rtS ,
"Error allocating memory for file name" ) ; return ; } strcpy ( fileName ,
fileNameOriginal ) ; { const char * blockpath =
"motor/Jnt Controller/To File" ; if ( slIsRapidAcceleratorSimulating ( ) ) {
rt_RAccelReplaceToFilename ( blockpath , fileName ) ; } } { const char *
errMsg = ( NULL ) ; errMsg = rtwH5LoggingCollectionCreateInstance ( 1 , & fp
, rtliGetLoggingInterval ( ssGetRootSS ( rtS ) -> mdlInfo -> rtwLogInfo ) ) ;
if ( errMsg != ( NULL ) ) { ssSetErrorStatus ( rtS , errMsg ) ; return ; } {
int_T dimensions [ 1 ] = { 1 } ; errMsg = rtwH5LoggingCollectionAddElement (
1 , fp , fileName , "ans" , 0 , "" , "linear" , "double" , 1 , dimensions , 0
, 1 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ) ; } if ( errMsg != ( NULL ) ) {
ssSetErrorStatus ( rtS , errMsg ) ; return ; } } if ( fileName != ( NULL ) )
{ free ( fileName ) ; } rtDW . j1xa3hpons . Count = 0 ; rtDW . j1xa3hpons .
Decimation = - 1 ; rtDW . oqnegpzh1g . FilePtr = fp ; } { void *
slioCatalogue = rt_slioCatalogue ( ) ? rtwGetPointerFromUniquePtr (
rt_slioCatalogue ( ) ) : sdiGetSlioCatalogue ( rt_dataMapInfo . mmi .
InstanceMap . fullPath ) ; if ( ! slioCatalogue || !
rtwDisableStreamingToRepository ( slioCatalogue ) ) { { sdiSignalSourceInfoU
srcInfo ; sdiLabelU loggedName = sdiGetLabelFromChars ( "" ) ; sdiLabelU
origSigName = sdiGetLabelFromChars ( "" ) ; sdiLabelU propName =
sdiGetLabelFromChars ( "" ) ; sdiLabelU blockPath = sdiGetLabelFromChars (
"motor/Jnt Controller/Quantize to 2pi//400" ) ; sdiLabelU blockSID =
sdiGetLabelFromChars ( "" ) ; sdiLabelU subPath = sdiGetLabelFromChars ( "" )
; sdiDims sigDims ; sdiLabelU sigName = sdiGetLabelFromChars ( "" ) ;
sdiAsyncRepoDataTypeHandle hDT = sdiAsyncRepoGetBuiltInDataTypeHandle (
DATA_TYPE_DOUBLE ) ; { sdiComplexity sigComplexity = REAL ;
sdiSampleTimeContinuity stCont = SAMPLE_TIME_DISCRETE ; int_T sigDimsArray [
1 ] = { 1 } ; sigDims . nDims = 1 ; sigDims . dimensions = sigDimsArray ;
srcInfo . numBlockPathElems = 1 ; srcInfo . fullBlockPath = ( sdiFullBlkPathU
) & blockPath ; srcInfo . SID = ( sdiSignalIDU ) & blockSID ; srcInfo .
subPath = subPath ; srcInfo . portIndex = 0 + 1 ; srcInfo . signalName =
sigName ; srcInfo . sigSourceUUID = 0 ; rtDW . e3mw3kxdbw . AQHandles =
sdiAsyncRepoCreateAsyncioQueue ( hDT , & srcInfo , rt_dataMapInfo . mmi .
InstanceMap . fullPath , "b8d9391e-e2f1-43b5-a52f-5a906eeda736" ,
sigComplexity , & sigDims , DIMENSIONS_MODE_FIXED , stCont , "" ) ; if ( rtDW
. e3mw3kxdbw . AQHandles ) { sdiSetSignalSampleTimeString ( rtDW . e3mw3kxdbw
. AQHandles , "Continuous" , 0.0 , ssGetTFinal ( rtS ) ) ; sdiSetRunStartTime
( rtDW . e3mw3kxdbw . AQHandles , ssGetTaskTime ( rtS , 1 ) ) ;
sdiAsyncRepoSetSignalExportSettings ( rtDW . e3mw3kxdbw . AQHandles , 1 , 0 )
; sdiAsyncRepoSetSignalExportName ( rtDW . e3mw3kxdbw . AQHandles ,
loggedName , origSigName , propName ) ; } sdiFreeLabel ( sigName ) ;
sdiFreeLabel ( loggedName ) ; sdiFreeLabel ( origSigName ) ; sdiFreeLabel (
propName ) ; sdiFreeLabel ( blockPath ) ; sdiFreeLabel ( blockSID ) ;
sdiFreeLabel ( subPath ) ; } } } { void * treeVector = ( NULL ) ; void *
accessor = ( NULL ) ; const void * signalDescriptor = ( NULL ) ; void *
loggingInterval = ( NULL ) ; char * datasetName = "tmp_raccel_logsout" ; if (
slioCatalogue && rtwIsLoggingToFile ( slioCatalogue ) ) { treeVector =
rtwGetTreeVector ( ) ; { int_T sigDimsArray [ 1 ] = { 1 } ; rtwAddLeafNode (
0 , "" , "zoh" , 0 , ( unsigned int * ) sigDimsArray , 1 , "double" , "" ,
"Continuous" , 0.0 , ssGetTFinal ( rtS ) , treeVector ) ; } signalDescriptor
= rtwGetSignalDescriptor ( treeVector , 1 , 1 , 0 , 1 , "" , "" ,
rt_dataMapInfo . mmi . InstanceMap . fullPath ,
"motor/Jnt Controller/Quantize to 2pi//400" , 1 , 0 , slioCatalogue , ( NULL
) , 0 , ( NULL ) , 0 ) ; if ( ! rt_slioCatalogue ( ) ) {
sdiSlioIsLoggingSignal ( rt_dataMapInfo . mmi . InstanceMap . fullPath ,
"motor/Jnt Controller/Quantize to 2pi//400" , 1 , "" ) ; } if (
rtwLoggingOverride ( signalDescriptor , slioCatalogue ) ) { if ( ssGetRootSS
( rtS ) -> mdlInfo -> rtwLogInfo ) { loggingInterval = rtliGetLoggingInterval
( ssGetRootSS ( rtS ) -> mdlInfo -> rtwLogInfo ) ; } else { loggingInterval =
sdiGetLoggingIntervals ( rt_dataMapInfo . mmi . InstanceMap . fullPath ) ;
datasetName = "" ; } accessor = rtwGetAccessor ( signalDescriptor ,
loggingInterval ) ; rtwAddR2Client ( accessor , signalDescriptor ,
slioCatalogue , datasetName , 1 ) ; rtDW . e3mw3kxdbw . SlioLTF = accessor ;
} } } } { void * slioCatalogue = rt_slioCatalogue ( ) ?
rtwGetPointerFromUniquePtr ( rt_slioCatalogue ( ) ) : sdiGetSlioCatalogue (
rt_dataMapInfo . mmi . InstanceMap . fullPath ) ; if ( ! slioCatalogue || !
rtwDisableStreamingToRepository ( slioCatalogue ) ) { { sdiSignalSourceInfoU
srcInfo ; sdiLabelU loggedName = sdiGetLabelFromChars ( "" ) ; sdiLabelU
origSigName = sdiGetLabelFromChars ( "" ) ; sdiLabelU propName =
sdiGetLabelFromChars ( "" ) ; sdiLabelU blockPath = sdiGetLabelFromChars (
"motor/Jnt Controller/Step Response Control" ) ; sdiLabelU blockSID =
sdiGetLabelFromChars ( "" ) ; sdiLabelU subPath = sdiGetLabelFromChars ( "" )
; sdiDims sigDims ; sdiLabelU sigName = sdiGetLabelFromChars ( "" ) ;
sdiAsyncRepoDataTypeHandle hDT = sdiAsyncRepoGetBuiltInDataTypeHandle (
DATA_TYPE_DOUBLE ) ; { sdiComplexity sigComplexity = REAL ;
sdiSampleTimeContinuity stCont = SAMPLE_TIME_CONTINUOUS ; int_T sigDimsArray
[ 1 ] = { 1 } ; sigDims . nDims = 1 ; sigDims . dimensions = sigDimsArray ;
srcInfo . numBlockPathElems = 1 ; srcInfo . fullBlockPath = ( sdiFullBlkPathU
) & blockPath ; srcInfo . SID = ( sdiSignalIDU ) & blockSID ; srcInfo .
subPath = subPath ; srcInfo . portIndex = 0 + 1 ; srcInfo . signalName =
sigName ; srcInfo . sigSourceUUID = 0 ; rtDW . lltjwuok3g . AQHandles =
sdiAsyncRepoCreateAsyncioQueue ( hDT , & srcInfo , rt_dataMapInfo . mmi .
InstanceMap . fullPath , "06a184fa-d90c-4c75-adee-7dd47596f9a1" ,
sigComplexity , & sigDims , DIMENSIONS_MODE_FIXED , stCont , "" ) ; if ( rtDW
. lltjwuok3g . AQHandles ) { sdiSetSignalSampleTimeString ( rtDW . lltjwuok3g
. AQHandles , "Continuous" , 0.0 , ssGetTFinal ( rtS ) ) ; sdiSetRunStartTime
( rtDW . lltjwuok3g . AQHandles , ssGetTaskTime ( rtS , 1 ) ) ;
sdiAsyncRepoSetSignalExportSettings ( rtDW . lltjwuok3g . AQHandles , 1 , 0 )
; sdiAsyncRepoSetSignalExportName ( rtDW . lltjwuok3g . AQHandles ,
loggedName , origSigName , propName ) ; } sdiFreeLabel ( sigName ) ;
sdiFreeLabel ( loggedName ) ; sdiFreeLabel ( origSigName ) ; sdiFreeLabel (
propName ) ; sdiFreeLabel ( blockPath ) ; sdiFreeLabel ( blockSID ) ;
sdiFreeLabel ( subPath ) ; } } } { void * treeVector = ( NULL ) ; void *
accessor = ( NULL ) ; const void * signalDescriptor = ( NULL ) ; void *
loggingInterval = ( NULL ) ; char * datasetName = "tmp_raccel_logsout" ; if (
slioCatalogue && rtwIsLoggingToFile ( slioCatalogue ) ) { treeVector =
rtwGetTreeVector ( ) ; { int_T sigDimsArray [ 1 ] = { 1 } ; rtwAddLeafNode (
0 , "" , "linear" , 0 , ( unsigned int * ) sigDimsArray , 1 , "double" , "" ,
"Continuous" , 0.0 , ssGetTFinal ( rtS ) , treeVector ) ; } signalDescriptor
= rtwGetSignalDescriptor ( treeVector , 1 , 1 , 0 , 1 , "" , "" ,
rt_dataMapInfo . mmi . InstanceMap . fullPath ,
"motor/Jnt Controller/Step Response Control" , 1 , 0 , slioCatalogue , ( NULL
) , 0 , ( NULL ) , 0 ) ; if ( ! rt_slioCatalogue ( ) ) {
sdiSlioIsLoggingSignal ( rt_dataMapInfo . mmi . InstanceMap . fullPath ,
"motor/Jnt Controller/Step Response Control" , 1 , "" ) ; } if (
rtwLoggingOverride ( signalDescriptor , slioCatalogue ) ) { if ( ssGetRootSS
( rtS ) -> mdlInfo -> rtwLogInfo ) { loggingInterval = rtliGetLoggingInterval
( ssGetRootSS ( rtS ) -> mdlInfo -> rtwLogInfo ) ; } else { loggingInterval =
sdiGetLoggingIntervals ( rt_dataMapInfo . mmi . InstanceMap . fullPath ) ;
datasetName = "" ; } accessor = rtwGetAccessor ( signalDescriptor ,
loggingInterval ) ; rtwAddR2Client ( accessor , signalDescriptor ,
slioCatalogue , datasetName , 1 ) ; rtDW . lltjwuok3g . SlioLTF = accessor ;
} } } } { void * slioCatalogue = rt_slioCatalogue ( ) ?
rtwGetPointerFromUniquePtr ( rt_slioCatalogue ( ) ) : sdiGetSlioCatalogue (
rt_dataMapInfo . mmi . InstanceMap . fullPath ) ; if ( ! slioCatalogue || !
rtwDisableStreamingToRepository ( slioCatalogue ) ) { { sdiSignalSourceInfoU
srcInfo ; sdiLabelU loggedName = sdiGetLabelFromChars ( "Torque (Nm)" ) ;
sdiLabelU origSigName = sdiGetLabelFromChars ( "Torque (Nm)" ) ; sdiLabelU
propName = sdiGetLabelFromChars ( "" ) ; sdiLabelU blockPath =
sdiGetLabelFromChars ( "motor/Jnt Controller/Torque Const 2" ) ; sdiLabelU
blockSID = sdiGetLabelFromChars ( "" ) ; sdiLabelU subPath =
sdiGetLabelFromChars ( "" ) ; sdiDims sigDims ; sdiLabelU sigName =
sdiGetLabelFromChars ( "Torque (Nm)" ) ; sdiAsyncRepoDataTypeHandle hDT =
sdiAsyncRepoGetBuiltInDataTypeHandle ( DATA_TYPE_DOUBLE ) ; { sdiComplexity
sigComplexity = REAL ; sdiSampleTimeContinuity stCont =
SAMPLE_TIME_CONTINUOUS ; int_T sigDimsArray [ 1 ] = { 1 } ; sigDims . nDims =
1 ; sigDims . dimensions = sigDimsArray ; srcInfo . numBlockPathElems = 1 ;
srcInfo . fullBlockPath = ( sdiFullBlkPathU ) & blockPath ; srcInfo . SID = (
sdiSignalIDU ) & blockSID ; srcInfo . subPath = subPath ; srcInfo . portIndex
= 0 + 1 ; srcInfo . signalName = sigName ; srcInfo . sigSourceUUID = 0 ; rtDW
. grojl3nk3g . AQHandles = sdiAsyncRepoCreateAsyncioQueue ( hDT , & srcInfo ,
rt_dataMapInfo . mmi . InstanceMap . fullPath ,
"176dffb3-9a44-4172-871b-c1ee81e26573" , sigComplexity , & sigDims ,
DIMENSIONS_MODE_FIXED , stCont , "" ) ; if ( rtDW . grojl3nk3g . AQHandles )
{ sdiSetSignalSampleTimeString ( rtDW . grojl3nk3g . AQHandles , "Continuous"
, 0.0 , ssGetTFinal ( rtS ) ) ; sdiSetRunStartTime ( rtDW . grojl3nk3g .
AQHandles , ssGetTaskTime ( rtS , 1 ) ) ; sdiAsyncRepoSetSignalExportSettings
( rtDW . grojl3nk3g . AQHandles , 1 , 0 ) ; sdiAsyncRepoSetSignalExportName (
rtDW . grojl3nk3g . AQHandles , loggedName , origSigName , propName ) ; }
sdiFreeLabel ( sigName ) ; sdiFreeLabel ( loggedName ) ; sdiFreeLabel (
origSigName ) ; sdiFreeLabel ( propName ) ; sdiFreeLabel ( blockPath ) ;
sdiFreeLabel ( blockSID ) ; sdiFreeLabel ( subPath ) ; } } } { void *
treeVector = ( NULL ) ; void * accessor = ( NULL ) ; const void *
signalDescriptor = ( NULL ) ; void * loggingInterval = ( NULL ) ; char *
datasetName = "tmp_raccel_logsout" ; if ( slioCatalogue && rtwIsLoggingToFile
( slioCatalogue ) ) { treeVector = rtwGetTreeVector ( ) ; { int_T
sigDimsArray [ 1 ] = { 1 } ; rtwAddLeafNode ( 0 , "Torque (Nm)" , "linear" ,
0 , ( unsigned int * ) sigDimsArray , 1 , "double" , "" , "Continuous" , 0.0
, ssGetTFinal ( rtS ) , treeVector ) ; } signalDescriptor =
rtwGetSignalDescriptor ( treeVector , 1 , 1 , 0 , 1 , "Torque (Nm)" , "" ,
rt_dataMapInfo . mmi . InstanceMap . fullPath ,
"motor/Jnt Controller/Torque Const 2" , 1 , 0 , slioCatalogue , ( NULL ) , 0
, ( NULL ) , 0 ) ; if ( ! rt_slioCatalogue ( ) ) { sdiSlioIsLoggingSignal (
rt_dataMapInfo . mmi . InstanceMap . fullPath ,
"motor/Jnt Controller/Torque Const 2" , 1 , "Torque (Nm)" ) ; } if (
rtwLoggingOverride ( signalDescriptor , slioCatalogue ) ) { if ( ssGetRootSS
( rtS ) -> mdlInfo -> rtwLogInfo ) { loggingInterval = rtliGetLoggingInterval
( ssGetRootSS ( rtS ) -> mdlInfo -> rtwLogInfo ) ; } else { loggingInterval =
sdiGetLoggingIntervals ( rt_dataMapInfo . mmi . InstanceMap . fullPath ) ;
datasetName = "" ; } accessor = rtwGetAccessor ( signalDescriptor ,
loggingInterval ) ; rtwAddR2Client ( accessor , signalDescriptor ,
slioCatalogue , datasetName , 1 ) ; rtDW . grojl3nk3g . SlioLTF = accessor ;
} } } } { void * fp = ( NULL ) ; const char * fileNameOriginal =
"Step Position.mat" ; char * fileName = ( char * ) malloc ( 509 ) ; if (
fileName == ( NULL ) ) { ssSetErrorStatus ( rtS ,
"Error allocating memory for file name" ) ; return ; } strcpy ( fileName ,
fileNameOriginal ) ; { const char * blockpath =
"motor/Jnt Controller/To File1" ; if ( slIsRapidAcceleratorSimulating ( ) ) {
rt_RAccelReplaceToFilename ( blockpath , fileName ) ; } } { const char *
errMsg = ( NULL ) ; errMsg = rtwH5LoggingCollectionCreateInstance ( 1 , & fp
, rtliGetLoggingInterval ( ssGetRootSS ( rtS ) -> mdlInfo -> rtwLogInfo ) ) ;
if ( errMsg != ( NULL ) ) { ssSetErrorStatus ( rtS , errMsg ) ; return ; } {
int_T dimensions [ 1 ] = { 1 } ; errMsg = rtwH5LoggingCollectionAddElement (
1 , fp , fileName , "ans" , 0 , "" , "linear" , "double" , 1 , dimensions , 0
, 1 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ) ; } if ( errMsg != ( NULL ) ) {
ssSetErrorStatus ( rtS , errMsg ) ; return ; } } if ( fileName != ( NULL ) )
{ free ( fileName ) ; } rtDW . pjbkr2i3xx . Count = 0 ; rtDW . pjbkr2i3xx .
Decimation = - 1 ; rtDW . lcl4opl5jx . FilePtr = fp ; } { void * fp = ( NULL
) ; const char * fileNameOriginal = "Step PWM.mat" ; char * fileName = ( char
* ) malloc ( 509 ) ; if ( fileName == ( NULL ) ) { ssSetErrorStatus ( rtS ,
"Error allocating memory for file name" ) ; return ; } strcpy ( fileName ,
fileNameOriginal ) ; { const char * blockpath =
"motor/Jnt Controller/To File2" ; if ( slIsRapidAcceleratorSimulating ( ) ) {
rt_RAccelReplaceToFilename ( blockpath , fileName ) ; } } { const char *
errMsg = ( NULL ) ; errMsg = rtwH5LoggingCollectionCreateInstance ( 1 , & fp
, rtliGetLoggingInterval ( ssGetRootSS ( rtS ) -> mdlInfo -> rtwLogInfo ) ) ;
if ( errMsg != ( NULL ) ) { ssSetErrorStatus ( rtS , errMsg ) ; return ; } {
int_T dimensions [ 1 ] = { 1 } ; errMsg = rtwH5LoggingCollectionAddElement (
1 , fp , fileName , "ans" , 0 , "" , "linear" , "double" , 1 , dimensions , 0
, 1 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 ) ; } if ( errMsg != ( NULL ) ) {
ssSetErrorStatus ( rtS , errMsg ) ; return ; } } if ( fileName != ( NULL ) )
{ free ( fileName ) ; } rtDW . o51b0uerqu . Count = 0 ; rtDW . o51b0uerqu .
Decimation = - 1 ; rtDW . lrc3gfcuvu . FilePtr = fp ; } MdlInitialize ( ) ; {
bool externalInputIsInDatasetFormat = false ; void * pISigstreamManager =
rt_GetISigstreamManager ( ) ; rtwISigstreamManagerGetInputIsInDatasetFormat (
pISigstreamManager , & externalInputIsInDatasetFormat ) ; if (
externalInputIsInDatasetFormat ) { } } } void MdlOutputs ( int_T tid ) {
uint8_T dti2r4i35e ; boolean_T gdapvilel4 ; real_T fzhlmjwsuv ; rtB .
ioc0okmkmy = rtX . nvaocs00bc ; if ( ssIsSampleHit ( rtS , 1 , 0 ) ) { rtDW .
if1ncvemx1 = ( ssGetTaskTime ( rtS , 1 ) >= rtP . Step_Time ) ; if ( rtDW .
if1ncvemx1 == 1 ) { rtB . o5y1y4cmrq = rtP . Step_YFinal ; } else { rtB .
o5y1y4cmrq = rtP . Step_Y0 ; } } if ( ssIsSampleHit ( rtS , 1 , 0 ) ) { } rtB
. anujv4qdwd = rtX . pfcrbgvmdb ; rtB . d3uyq13rzr = rtB . anujv4qdwd /
ssGetT ( rtS ) ; if ( ssIsSampleHit ( rtS , 1 , 0 ) ) { if (
ssIsMajorTimeStep ( rtS ) ) { rtDW . abahn02ksw = ( rtB . d3uyq13rzr > rtP .
NomCurrent ) ; } rtB . hryw525bko = rtDW . abahn02ksw ; } rtB . hjl5biokwy =
0.0 ; rtB . hjl5biokwy += rtP . Elec1n / rtP . Elec1d [ 0 ] * rtX .
mjgnwkqw0t ; if ( ssIsMajorTimeStep ( rtS ) ) { rtDW . pol4d4okmy = rtB .
hjl5biokwy >= rtP . MaxCurrent1_UpperSat ? 1 : rtB . hjl5biokwy > rtP .
MaxCurrent1_LowerSat ? 0 : - 1 ; } rtB . i2zgpmdtdd = rtDW . pol4d4okmy == 1
? rtP . MaxCurrent1_UpperSat : rtDW . pol4d4okmy == - 1 ? rtP .
MaxCurrent1_LowerSat : rtB . hjl5biokwy ; if ( ssIsMajorTimeStep ( rtS ) ) {
rtDW . fwwxv0t4om = ( rtB . i2zgpmdtdd >= 0.0 ) ; } rtB . j1d4ade1zr = rtDW .
fwwxv0t4om > 0 ? rtB . i2zgpmdtdd : - rtB . i2zgpmdtdd ; if ( ssIsSampleHit (
rtS , 1 , 0 ) ) { rtB . hnoyfag32g = rtDW . jhudklf0yp ; } rtB . agiv5am4pg =
muDoubleScalarMax ( rtB . j1d4ade1zr , rtB . hnoyfag32g ) ; if (
ssIsSampleHit ( rtS , 1 , 0 ) ) { if ( ssIsMajorTimeStep ( rtS ) ) { rtDW .
dv104ugpzo = ( rtB . agiv5am4pg > rtP . StallCurrent ) ; } rtB . lm0riqbmwp =
rtDW . dv104ugpzo ; dti2r4i35e = ( uint8_T ) ( ( uint32_T ) rtB . hryw525bko
+ rtB . lm0riqbmwp ) ; gdapvilel4 = ( dti2r4i35e > rtP . Constant_Value ) ; {
if ( ( rtDW . oc5c35nsjw . AQHandles || rtDW . oc5c35nsjw . SlioLTF ) &&
ssGetLogOutput ( rtS ) ) { sdiSlioSdiWriteSignal ( rtDW . oc5c35nsjw .
AQHandles , rtDW . oc5c35nsjw . SlioLTF , 0 , ssGetTaskTime ( rtS , 1 ) , (
void * ) & gdapvilel4 ) ; } } rtB . gmjwvr4my1 = rtDW . b2ftxry5zj ; } rtB .
bs4j1hqktx = rtB . ioc0okmkmy - rtB . o5y1y4cmrq ; if ( ssIsMajorTimeStep (
rtS ) ) { rtDW . mcsw1g0pr4 = ( rtB . bs4j1hqktx >= 0.0 ) ; } rtB .
gterhc2ycg = rtDW . mcsw1g0pr4 > 0 ? rtB . bs4j1hqktx : - rtB . bs4j1hqktx ;
rtB . jqe1l2xedg = muDoubleScalarMax ( rtB . gmjwvr4my1 , rtB . gterhc2ycg )
; rtB . jdxhpskhxu = rtB . jqe1l2xedg * rtP . Conversion_Value ; rtB .
dn5v5kwhgm = muDoubleScalarRound ( rtB . ioc0okmkmy / rtP .
Quantizeto2pi1_Interval ) * rtP . Quantizeto2pi1_Interval ; if (
ssIsSampleHit ( rtS , 1 , 0 ) ) { { if ( ( rtDW . oy51qzwlsb . AQHandles ||
rtDW . oy51qzwlsb . SlioLTF ) && ssGetLogOutput ( rtS ) ) {
sdiSlioSdiWriteSignal ( rtDW . oy51qzwlsb . AQHandles , rtDW . oy51qzwlsb .
SlioLTF , 0 , ssGetTaskTime ( rtS , 1 ) , ( void * ) & rtB . dn5v5kwhgm ) ; }
} } rtB . jgwwnwtolk = rtB . o5y1y4cmrq - rtB . dn5v5kwhgm ; rtB . amsfxvim15
= rtP . StepResponseControl1_P * rtB . jgwwnwtolk ; rtB . dngwxi52p3 = rtX .
o2vdlc3lwj ; rtB . paygzk0zoc = rtP . StepResponseControl1_D * rtB .
jgwwnwtolk ; rtB . nkhyo2j0jl = rtX . lgupwhixdz ; rtB . no3lkd1xft = rtB .
paygzk0zoc - rtB . nkhyo2j0jl ; rtB . el2gn1lphk = rtP .
StepResponseControl1_N * rtB . no3lkd1xft ; rtB . btapnh3csw = ( rtB .
amsfxvim15 + rtB . dngwxi52p3 ) + rtB . el2gn1lphk ; if ( ssIsSampleHit ( rtS
, 1 , 0 ) ) { { if ( ( rtDW . odasxv14ku . AQHandles || rtDW . odasxv14ku .
SlioLTF ) && ssGetLogOutput ( rtS ) ) { sdiSlioSdiWriteSignal ( rtDW .
odasxv14ku . AQHandles , rtDW . odasxv14ku . SlioLTF , 0 , ssGetTaskTime (
rtS , 1 ) , ( void * ) & rtB . btapnh3csw ) ; } } } rtB . fhsc2gicgw = rtP .
TConst1 * rtB . i2zgpmdtdd ; if ( ssIsSampleHit ( rtS , 1 , 0 ) ) { { if ( (
rtDW . ix54ulvqvm . AQHandles || rtDW . ix54ulvqvm . SlioLTF ) &&
ssGetLogOutput ( rtS ) ) { sdiSlioSdiWriteSignal ( rtDW . ix54ulvqvm .
AQHandles , rtDW . ix54ulvqvm . SlioLTF , 0 , ssGetTaskTime ( rtS , 1 ) , (
void * ) & rtB . fhsc2gicgw ) ; } } } rtB . k4ktntecy5 = 0.0 ; rtB .
k4ktntecy5 += rtP . Mech1n [ 0 ] / rtP . Mech1d [ 0 ] * rtX . f3greldmrk [ 0
] ; rtB . k4ktntecy5 += rtP . Mech1n [ 1 ] / rtP . Mech1d [ 0 ] * rtX .
f3greldmrk [ 1 ] ; rtB . e1pup3cj2f = rtP . BackEMF1 * rtB . k4ktntecy5 ; if
( ssIsMajorTimeStep ( rtS ) ) { rtDW . ifrsgr5d25 = rtB . btapnh3csw >= rtP .
MaxDutyCycle2_UpperSat ? 1 : rtB . btapnh3csw > rtP . MaxDutyCycle2_LowerSat
? 0 : - 1 ; } rtB . ou2ycdjzh0 = rtDW . ifrsgr5d25 == 1 ? rtP .
MaxDutyCycle2_UpperSat : rtDW . ifrsgr5d25 == - 1 ? rtP .
MaxDutyCycle2_LowerSat : rtB . btapnh3csw ; rtB . o1ro1rhovm =
muDoubleScalarRound ( rtB . ou2ycdjzh0 / rtP . NearestInt1_Interval ) * rtP .
NearestInt1_Interval ; rtB . puti2xcwwj = rtP . PWMConversion [ 0 ] ; rtB .
puti2xcwwj = rtB . puti2xcwwj * rtB . o1ro1rhovm + rtP . PWMConversion [ 1 ]
; rtB . puti2xcwwj = rtB . puti2xcwwj * rtB . o1ro1rhovm + rtP .
PWMConversion [ 2 ] ; rtB . puti2xcwwj = rtB . puti2xcwwj * rtB . o1ro1rhovm
+ rtP . PWMConversion [ 3 ] ; rtB . puti2xcwwj = rtB . puti2xcwwj * rtB .
o1ro1rhovm + rtP . PWMConversion [ 4 ] ; if ( ssIsMajorTimeStep ( rtS ) ) {
rtDW . p4il5t3tsl = rtB . puti2xcwwj >= rtP . AmpSat1 ? 1 : rtB . puti2xcwwj
> - rtP . AmpSat1 ? 0 : - 1 ; } rtB . mtjjfm5fkq = rtDW . p4il5t3tsl == 1 ?
rtP . AmpSat1 : rtDW . p4il5t3tsl == - 1 ? - rtP . AmpSat1 : rtB . puti2xcwwj
; if ( ssIsSampleHit ( rtS , 1 , 0 ) ) { { if ( ( rtDW . jpmbni14kg .
AQHandles || rtDW . jpmbni14kg . SlioLTF ) && ssGetLogOutput ( rtS ) ) {
sdiSlioSdiWriteSignal ( rtDW . jpmbni14kg . AQHandles , rtDW . jpmbni14kg .
SlioLTF , 0 , ssGetTaskTime ( rtS , 1 ) , ( void * ) & gdapvilel4 ) ; } } {
if ( ( rtDW . ksnq4jprhj . AQHandles || rtDW . ksnq4jprhj . SlioLTF ) &&
ssGetLogOutput ( rtS ) ) { sdiSlioSdiWriteSignal ( rtDW . ksnq4jprhj .
AQHandles , rtDW . ksnq4jprhj . SlioLTF , 0 , ssGetTaskTime ( rtS , 1 ) , (
void * ) & rtB . agiv5am4pg ) ; } } { if ( ( rtDW . bahcjcb1oc . AQHandles ||
rtDW . bahcjcb1oc . SlioLTF ) && ssGetLogOutput ( rtS ) ) {
sdiSlioSdiWriteSignal ( rtDW . bahcjcb1oc . AQHandles , rtDW . bahcjcb1oc .
SlioLTF , 0 , ssGetTaskTime ( rtS , 1 ) , ( void * ) & dti2r4i35e ) ; } } }
if ( ssIsMajorTimeStep ( rtS ) ) { rtDW . l2sav3arsj = ( rtB . fhsc2gicgw >=
0.0 ) ; } rtB . bqokd1dwue = rtDW . l2sav3arsj > 0 ? rtB . fhsc2gicgw : - rtB
. fhsc2gicgw ; if ( ssIsSampleHit ( rtS , 1 , 0 ) ) { if ( ssIsMajorTimeStep
( rtS ) ) { rtDW . dzorqaujrj = ( rtB . bqokd1dwue < rtP . StaticFric ) ; }
rtB . emy34hfzxp = rtDW . dzorqaujrj ; } rtB . c133a0jqdk = rtB . fhsc2gicgw
* ( real_T ) rtB . emy34hfzxp ; rtB . i51k3nx1do = rtP .
StepResponseControl1_I * rtB . jgwwnwtolk ; rtB . n014xvirka = rtB .
mtjjfm5fkq - rtB . e1pup3cj2f ; rtB . gucmiu55ed = rtB . fhsc2gicgw - rtB .
c133a0jqdk ; rtB . m2egujefvv = rtX . bkgokwpcki ; if ( ssIsSampleHit ( rtS ,
1 , 0 ) ) { rtDW . hnqwxnzjee = ( ssGetTaskTime ( rtS , 1 ) >= rtP . PWM_Time
) ; if ( rtDW . hnqwxnzjee == 1 ) { fzhlmjwsuv = rtP . PWM_YFinal ; } else {
fzhlmjwsuv = rtP . PWM_Y0 ; } rtB . ozd5y1bdbm = rtP . PWMConversion [ 0 ] ;
rtB . ozd5y1bdbm = rtB . ozd5y1bdbm * fzhlmjwsuv + rtP . PWMConversion [ 1 ]
; rtB . ozd5y1bdbm = rtB . ozd5y1bdbm * fzhlmjwsuv + rtP . PWMConversion [ 2
] ; rtB . ozd5y1bdbm = rtB . ozd5y1bdbm * fzhlmjwsuv + rtP . PWMConversion [
3 ] ; rtB . ozd5y1bdbm = rtB . ozd5y1bdbm * fzhlmjwsuv + rtP . PWMConversion
[ 4 ] ; } rtB . l2d0v0tkwo = 0.0 ; rtB . l2d0v0tkwo += rtP . Mech1n [ 0 ] /
rtP . Mech1d [ 0 ] * rtX . igwsihwpdp [ 0 ] ; rtB . l2d0v0tkwo += rtP .
Mech1n [ 1 ] / rtP . Mech1d [ 0 ] * rtX . igwsihwpdp [ 1 ] ; rtB . gjaaa2fhno
= 0.0 ; rtB . gjaaa2fhno += rtP . Elec1n / rtP . Elec1d [ 0 ] * rtX .
puo0nzqs35 ; rtB . ccn2pszgjr = rtP . TConst1 * rtB . gjaaa2fhno ; if (
ssIsSampleHit ( rtS , 2 , 0 ) ) { if ( ssGetLogOutput ( rtS ) ) { { const
char * errMsg = ( NULL ) ; void * fp = ( void * ) rtDW . oqnegpzh1g . FilePtr
; if ( fp != ( NULL ) ) { { real_T t ; void * u ; t = ssGetTaskTime ( rtS , 2
) ; u = ( void * ) & rtB . l2d0v0tkwo ; errMsg = rtwH5LoggingCollectionWrite
( 1 , fp , 0 , t , u ) ; if ( errMsg != ( NULL ) ) { ssSetErrorStatus ( rtS ,
errMsg ) ; return ; } } } } } } rtB . ke4p3coxhb = rtP . BackEMF1 * rtB .
l2d0v0tkwo ; rtB . gxpiulydd2 = rtB . ozd5y1bdbm - rtB . ke4p3coxhb ; rtB .
odkwwsipfi = rtX . f3s5lse3uq ; rtB . lksfqnpvfh = muDoubleScalarRound ( rtB
. odkwwsipfi / rtP . Quantizeto2pi400_Interval ) * rtP .
Quantizeto2pi400_Interval ; if ( ssIsSampleHit ( rtS , 1 , 0 ) ) { { if ( (
rtDW . e3mw3kxdbw . AQHandles || rtDW . e3mw3kxdbw . SlioLTF ) &&
ssGetLogOutput ( rtS ) ) { sdiSlioSdiWriteSignal ( rtDW . e3mw3kxdbw .
AQHandles , rtDW . e3mw3kxdbw . SlioLTF , 0 , ssGetTaskTime ( rtS , 1 ) , (
void * ) & rtB . lksfqnpvfh ) ; } } rtDW . f3t0nzed5p = ( ssGetTaskTime ( rtS
, 1 ) >= rtP . DesiredAngleInput_Time ) ; if ( rtDW . f3t0nzed5p == 1 ) { rtB
. obo5lyqljg = rtP . DesiredAngleInput_YFinal ; } else { rtB . obo5lyqljg =
rtP . DesiredAngleInput_Y0 ; } } rtB . gmkdc4mlzx = rtB . obo5lyqljg - rtB .
lksfqnpvfh ; rtB . nv3h1alees = rtP . StepResponseControl_P * rtB .
gmkdc4mlzx ; rtB . fjewmqeu3b = rtX . hcazinuy1s ; rtB . etljz0mm2f = rtP .
StepResponseControl_D * rtB . gmkdc4mlzx ; rtB . biwfzm5zhf = rtX .
av5owbi5i4 ; rtB . ntrwuhfs2g = rtB . etljz0mm2f - rtB . biwfzm5zhf ; rtB .
g5rilccwnf = rtP . StepResponseControl_N * rtB . ntrwuhfs2g ; rtB .
ciip4hb2p2 = ( rtB . nv3h1alees + rtB . fjewmqeu3b ) + rtB . g5rilccwnf ; if
( ssIsSampleHit ( rtS , 1 , 0 ) ) { { if ( ( rtDW . lltjwuok3g . AQHandles ||
rtDW . lltjwuok3g . SlioLTF ) && ssGetLogOutput ( rtS ) ) {
sdiSlioSdiWriteSignal ( rtDW . lltjwuok3g . AQHandles , rtDW . lltjwuok3g .
SlioLTF , 0 , ssGetTaskTime ( rtS , 1 ) , ( void * ) & rtB . ciip4hb2p2 ) ; }
} } rtB . f3xnhsznvk = 0.0 ; rtB . f3xnhsznvk += rtP . Elec1n / rtP . Elec1d
[ 0 ] * rtX . dihsnra40r ; if ( ssIsMajorTimeStep ( rtS ) ) { rtDW .
id1uld5v45 = rtB . f3xnhsznvk >= rtP . MaxCurrent_UpperSat ? 1 : rtB .
f3xnhsznvk > rtP . MaxCurrent_LowerSat ? 0 : - 1 ; } rtB . awmqggonyb = rtDW
. id1uld5v45 == 1 ? rtP . MaxCurrent_UpperSat : rtDW . id1uld5v45 == - 1 ?
rtP . MaxCurrent_LowerSat : rtB . f3xnhsznvk ; rtB . i2ml1fewle = rtP .
TConst1 * rtB . awmqggonyb ; if ( ssIsSampleHit ( rtS , 1 , 0 ) ) { { if ( (
rtDW . grojl3nk3g . AQHandles || rtDW . grojl3nk3g . SlioLTF ) &&
ssGetLogOutput ( rtS ) ) { sdiSlioSdiWriteSignal ( rtDW . grojl3nk3g .
AQHandles , rtDW . grojl3nk3g . SlioLTF , 0 , ssGetTaskTime ( rtS , 1 ) , (
void * ) & rtB . i2ml1fewle ) ; } } } if ( ssIsSampleHit ( rtS , 2 , 0 ) ) {
if ( ssGetLogOutput ( rtS ) ) { { const char * errMsg = ( NULL ) ; void * fp
= ( void * ) rtDW . lcl4opl5jx . FilePtr ; if ( fp != ( NULL ) ) { { real_T t
; void * u ; t = ssGetTaskTime ( rtS , 2 ) ; u = ( void * ) & rtB .
odkwwsipfi ; errMsg = rtwH5LoggingCollectionWrite ( 1 , fp , 0 , t , u ) ; if
( errMsg != ( NULL ) ) { ssSetErrorStatus ( rtS , errMsg ) ; return ; } } } }
} } if ( ssIsMajorTimeStep ( rtS ) ) { rtDW . gjgazova4y = rtB . ciip4hb2p2
>= rtP . MaxDutyCycle1_UpperSat ? 1 : rtB . ciip4hb2p2 > rtP .
MaxDutyCycle1_LowerSat ? 0 : - 1 ; } rtB . eixzkkukbm = rtDW . gjgazova4y ==
1 ? rtP . MaxDutyCycle1_UpperSat : rtDW . gjgazova4y == - 1 ? rtP .
MaxDutyCycle1_LowerSat : rtB . ciip4hb2p2 ; rtB . bnpnp05c3l =
muDoubleScalarRound ( rtB . eixzkkukbm / rtP . NearestInt_Interval ) * rtP .
NearestInt_Interval ; if ( ssIsMajorTimeStep ( rtS ) ) { rtDW . m0qklhvna2 =
rtB . bnpnp05c3l >= rtP . u0to255_UpperSat ? 1 : rtB . bnpnp05c3l > rtP .
u0to255_LowerSat ? 0 : - 1 ; } rtB . cjp5mog4yq = rtDW . m0qklhvna2 == 1 ?
rtP . u0to255_UpperSat : rtDW . m0qklhvna2 == - 1 ? rtP . u0to255_LowerSat :
rtB . bnpnp05c3l ; if ( ssIsMajorTimeStep ( rtS ) ) { rtDW . f2vrqerrls = rtB
. bnpnp05c3l >= rtP . u55to30_UpperSat ? 1 : rtB . bnpnp05c3l > rtP .
u55to30_LowerSat ? 0 : - 1 ; } rtB . jrm53acbhq = rtDW . f2vrqerrls == 1 ?
rtP . u55to30_UpperSat : rtDW . f2vrqerrls == - 1 ? rtP . u55to30_LowerSat :
rtB . bnpnp05c3l ; if ( ssIsMajorTimeStep ( rtS ) ) { rtDW . pjivo2ki1n = (
rtB . bnpnp05c3l > rtP . Switch_Threshold ) ; } if ( rtDW . pjivo2ki1n ) {
rtB . fixgevc5xe = rtB . cjp5mog4yq ; } else { rtB . fixgevc5xe = rtB .
jrm53acbhq ; } if ( ssIsSampleHit ( rtS , 2 , 0 ) ) { if ( ssGetLogOutput (
rtS ) ) { { const char * errMsg = ( NULL ) ; void * fp = ( void * ) rtDW .
lrc3gfcuvu . FilePtr ; if ( fp != ( NULL ) ) { { real_T t ; void * u ; t =
ssGetTaskTime ( rtS , 2 ) ; u = ( void * ) & rtB . fixgevc5xe ; errMsg =
rtwH5LoggingCollectionWrite ( 1 , fp , 0 , t , u ) ; if ( errMsg != ( NULL )
) { ssSetErrorStatus ( rtS , errMsg ) ; return ; } } } } } } rtB . lul5450swo
= 0.0 ; rtB . lul5450swo += rtP . Mech1n [ 0 ] / rtP . Mech1d [ 0 ] * rtX .
fkehg4zumr [ 0 ] ; rtB . lul5450swo += rtP . Mech1n [ 1 ] / rtP . Mech1d [ 0
] * rtX . fkehg4zumr [ 1 ] ; rtB . brgflil51h = rtP . BackEMF1 * rtB .
lul5450swo ; rtB . jaj4esgdh0 = rtP . PWMConversion [ 0 ] ; rtB . jaj4esgdh0
= rtB . jaj4esgdh0 * rtB . fixgevc5xe + rtP . PWMConversion [ 1 ] ; rtB .
jaj4esgdh0 = rtB . jaj4esgdh0 * rtB . fixgevc5xe + rtP . PWMConversion [ 2 ]
; rtB . jaj4esgdh0 = rtB . jaj4esgdh0 * rtB . fixgevc5xe + rtP .
PWMConversion [ 3 ] ; rtB . jaj4esgdh0 = rtB . jaj4esgdh0 * rtB . fixgevc5xe
+ rtP . PWMConversion [ 4 ] ; if ( ssIsMajorTimeStep ( rtS ) ) { rtDW .
lnlaljtbyn = rtB . jaj4esgdh0 >= rtP . AmpSat1 ? 1 : rtB . jaj4esgdh0 > - rtP
. AmpSat1 ? 0 : - 1 ; rtDW . ep2uw1gbbk = ( rtB . i2ml1fewle >= 0.0 ) ; } rtB
. ioesu1dalb = rtDW . lnlaljtbyn == 1 ? rtP . AmpSat1 : rtDW . lnlaljtbyn ==
- 1 ? - rtP . AmpSat1 : rtB . jaj4esgdh0 ; rtB . hxxkhd0gkz = rtDW .
ep2uw1gbbk > 0 ? rtB . i2ml1fewle : - rtB . i2ml1fewle ; if ( ssIsSampleHit (
rtS , 1 , 0 ) ) { if ( ssIsMajorTimeStep ( rtS ) ) { rtDW . nqjspphkim = (
rtB . hxxkhd0gkz < rtP . StaticFric ) ; } rtB . avhiv2ojkj = rtDW .
nqjspphkim ; } rtB . kta0dglp1y = rtB . i2ml1fewle * ( real_T ) rtB .
avhiv2ojkj ; rtB . o3wu3v2g2b = rtP . StepResponseControl_I * rtB .
gmkdc4mlzx ; rtB . ijsvvv0me4 = rtB . ioesu1dalb - rtB . brgflil51h ; rtB .
kx4hloeszq = rtB . i2ml1fewle - rtB . kta0dglp1y ; UNUSED_PARAMETER ( tid ) ;
} void MdlUpdate ( int_T tid ) { if ( ssIsSampleHit ( rtS , 1 , 0 ) ) { rtDW
. jhudklf0yp = rtB . agiv5am4pg ; rtDW . b2ftxry5zj = rtB . jqe1l2xedg ; }
UNUSED_PARAMETER ( tid ) ; } void MdlUpdateTID3 ( int_T tid ) {
UNUSED_PARAMETER ( tid ) ; } void MdlDerivatives ( void ) { XDot * _rtXdot ;
_rtXdot = ( ( XDot * ) ssGetdX ( rtS ) ) ; _rtXdot -> nvaocs00bc = rtB .
k4ktntecy5 ; _rtXdot -> pfcrbgvmdb = rtB . j1d4ade1zr ; _rtXdot -> mjgnwkqw0t
= 0.0 ; _rtXdot -> mjgnwkqw0t += - rtP . Elec1d [ 1 ] / rtP . Elec1d [ 0 ] *
rtX . mjgnwkqw0t ; _rtXdot -> mjgnwkqw0t += rtB . n014xvirka ; _rtXdot ->
o2vdlc3lwj = rtB . i51k3nx1do ; _rtXdot -> lgupwhixdz = rtB . el2gn1lphk ;
_rtXdot -> f3greldmrk [ 0 ] = 0.0 ; _rtXdot -> f3greldmrk [ 0 ] += - rtP .
Mech1d [ 1 ] / rtP . Mech1d [ 0 ] * rtX . f3greldmrk [ 0 ] ; _rtXdot ->
f3greldmrk [ 1 ] = 0.0 ; _rtXdot -> f3greldmrk [ 0 ] += - rtP . Mech1d [ 2 ]
/ rtP . Mech1d [ 0 ] * rtX . f3greldmrk [ 1 ] ; _rtXdot -> f3greldmrk [ 1 ]
+= rtX . f3greldmrk [ 0 ] ; _rtXdot -> f3greldmrk [ 0 ] += rtB . gucmiu55ed ;
_rtXdot -> bkgokwpcki = rtB . l2d0v0tkwo ; _rtXdot -> igwsihwpdp [ 0 ] = 0.0
; _rtXdot -> igwsihwpdp [ 0 ] += - rtP . Mech1d [ 1 ] / rtP . Mech1d [ 0 ] *
rtX . igwsihwpdp [ 0 ] ; _rtXdot -> igwsihwpdp [ 1 ] = 0.0 ; _rtXdot ->
igwsihwpdp [ 0 ] += - rtP . Mech1d [ 2 ] / rtP . Mech1d [ 0 ] * rtX .
igwsihwpdp [ 1 ] ; _rtXdot -> igwsihwpdp [ 1 ] += rtX . igwsihwpdp [ 0 ] ;
_rtXdot -> igwsihwpdp [ 0 ] += rtB . ccn2pszgjr ; _rtXdot -> puo0nzqs35 = 0.0
; _rtXdot -> puo0nzqs35 += - rtP . Elec1d [ 1 ] / rtP . Elec1d [ 0 ] * rtX .
puo0nzqs35 ; _rtXdot -> puo0nzqs35 += rtB . gxpiulydd2 ; _rtXdot ->
f3s5lse3uq = rtB . lul5450swo ; _rtXdot -> hcazinuy1s = rtB . o3wu3v2g2b ;
_rtXdot -> av5owbi5i4 = rtB . g5rilccwnf ; _rtXdot -> dihsnra40r = 0.0 ;
_rtXdot -> dihsnra40r += - rtP . Elec1d [ 1 ] / rtP . Elec1d [ 0 ] * rtX .
dihsnra40r ; _rtXdot -> dihsnra40r += rtB . ijsvvv0me4 ; _rtXdot ->
fkehg4zumr [ 0 ] = 0.0 ; _rtXdot -> fkehg4zumr [ 0 ] += - rtP . Mech1d [ 1 ]
/ rtP . Mech1d [ 0 ] * rtX . fkehg4zumr [ 0 ] ; _rtXdot -> fkehg4zumr [ 1 ] =
0.0 ; _rtXdot -> fkehg4zumr [ 0 ] += - rtP . Mech1d [ 2 ] / rtP . Mech1d [ 0
] * rtX . fkehg4zumr [ 1 ] ; _rtXdot -> fkehg4zumr [ 1 ] += rtX . fkehg4zumr
[ 0 ] ; _rtXdot -> fkehg4zumr [ 0 ] += rtB . kx4hloeszq ; } void
MdlProjection ( void ) { } void MdlZeroCrossings ( void ) { ZCV * _rtZCSV ;
_rtZCSV = ( ( ZCV * ) ssGetSolverZcSignalVector ( rtS ) ) ; _rtZCSV ->
d4cfarnuxg = ssGetT ( rtS ) - rtP . Step_Time ; _rtZCSV -> dl2rec3iq5 = rtB .
d3uyq13rzr - rtP . NomCurrent ; _rtZCSV -> kvph4uuxhw = rtB . hjl5biokwy -
rtP . MaxCurrent1_UpperSat ; _rtZCSV -> ed2ukm5fft = rtB . hjl5biokwy - rtP .
MaxCurrent1_LowerSat ; _rtZCSV -> linbijbzri = rtB . i2zgpmdtdd ; _rtZCSV ->
m5zd1wh33t = rtB . agiv5am4pg - rtP . StallCurrent ; _rtZCSV -> a3wuanjgmk =
rtB . bs4j1hqktx ; _rtZCSV -> js12ctyuwj = rtB . btapnh3csw - rtP .
MaxDutyCycle2_UpperSat ; _rtZCSV -> d3nt5octq5 = rtB . btapnh3csw - rtP .
MaxDutyCycle2_LowerSat ; _rtZCSV -> p0h3fuy3y5 = rtB . puti2xcwwj - rtP .
AmpSat1 ; _rtZCSV -> pcw4qfr235 = rtB . puti2xcwwj - ( - rtP . AmpSat1 ) ;
_rtZCSV -> gai1020gpf = rtB . fhsc2gicgw ; _rtZCSV -> fb1wk2ass1 = rtB .
bqokd1dwue - rtP . StaticFric ; _rtZCSV -> aadd3pfro1 = ssGetT ( rtS ) - rtP
. PWM_Time ; _rtZCSV -> dzmwbh1gyj = ssGetT ( rtS ) - rtP .
DesiredAngleInput_Time ; _rtZCSV -> pzc0e4zttf = rtB . f3xnhsznvk - rtP .
MaxCurrent_UpperSat ; _rtZCSV -> cuvi30r0xz = rtB . f3xnhsznvk - rtP .
MaxCurrent_LowerSat ; _rtZCSV -> b04vdkrp0q = rtB . ciip4hb2p2 - rtP .
MaxDutyCycle1_UpperSat ; _rtZCSV -> dg3bgegovs = rtB . ciip4hb2p2 - rtP .
MaxDutyCycle1_LowerSat ; _rtZCSV -> g3spp13qf2 = rtB . bnpnp05c3l - rtP .
u0to255_UpperSat ; _rtZCSV -> ayodvjrca5 = rtB . bnpnp05c3l - rtP .
u0to255_LowerSat ; _rtZCSV -> lkftuvlorw = rtB . bnpnp05c3l - rtP .
u55to30_UpperSat ; _rtZCSV -> d40bzasok5 = rtB . bnpnp05c3l - rtP .
u55to30_LowerSat ; _rtZCSV -> gcos3yfhmp = rtB . bnpnp05c3l - rtP .
Switch_Threshold ; _rtZCSV -> dsx4qmcx2h = rtB . jaj4esgdh0 - rtP . AmpSat1 ;
_rtZCSV -> ehlrsyzdec = rtB . jaj4esgdh0 - ( - rtP . AmpSat1 ) ; _rtZCSV ->
cae2rljtqz = rtB . i2ml1fewle ; _rtZCSV -> ft22grzbnv = rtB . hxxkhd0gkz -
rtP . StaticFric ; } void MdlTerminate ( void ) { { if ( rtDW . oc5c35nsjw .
AQHandles ) { sdiTerminateStreaming ( & rtDW . oc5c35nsjw . AQHandles ) ; }
if ( rtDW . oc5c35nsjw . SlioLTF ) { rtwDestructAccessorPointer ( rtDW .
oc5c35nsjw . SlioLTF ) ; } } { if ( rtDW . oy51qzwlsb . AQHandles ) {
sdiTerminateStreaming ( & rtDW . oy51qzwlsb . AQHandles ) ; } if ( rtDW .
oy51qzwlsb . SlioLTF ) { rtwDestructAccessorPointer ( rtDW . oy51qzwlsb .
SlioLTF ) ; } } { if ( rtDW . odasxv14ku . AQHandles ) {
sdiTerminateStreaming ( & rtDW . odasxv14ku . AQHandles ) ; } if ( rtDW .
odasxv14ku . SlioLTF ) { rtwDestructAccessorPointer ( rtDW . odasxv14ku .
SlioLTF ) ; } } { if ( rtDW . ix54ulvqvm . AQHandles ) {
sdiTerminateStreaming ( & rtDW . ix54ulvqvm . AQHandles ) ; } if ( rtDW .
ix54ulvqvm . SlioLTF ) { rtwDestructAccessorPointer ( rtDW . ix54ulvqvm .
SlioLTF ) ; } } { if ( rtDW . jpmbni14kg . AQHandles ) {
sdiTerminateStreaming ( & rtDW . jpmbni14kg . AQHandles ) ; } if ( rtDW .
jpmbni14kg . SlioLTF ) { rtwDestructAccessorPointer ( rtDW . jpmbni14kg .
SlioLTF ) ; } } { if ( rtDW . ksnq4jprhj . AQHandles ) {
sdiTerminateStreaming ( & rtDW . ksnq4jprhj . AQHandles ) ; } if ( rtDW .
ksnq4jprhj . SlioLTF ) { rtwDestructAccessorPointer ( rtDW . ksnq4jprhj .
SlioLTF ) ; } } { if ( rtDW . bahcjcb1oc . AQHandles ) {
sdiTerminateStreaming ( & rtDW . bahcjcb1oc . AQHandles ) ; } if ( rtDW .
bahcjcb1oc . SlioLTF ) { rtwDestructAccessorPointer ( rtDW . bahcjcb1oc .
SlioLTF ) ; } } { const char * errMsg = ( NULL ) ; void * fp = ( void * )
rtDW . oqnegpzh1g . FilePtr ; if ( fp != ( NULL ) ) { errMsg =
rtwH5LoggingCollectionDestroyInstance ( 1 , fp ) ; if ( errMsg != ( NULL ) )
{ ssSetErrorStatus ( rtS , errMsg ) ; return ; } } } { if ( rtDW . e3mw3kxdbw
. AQHandles ) { sdiTerminateStreaming ( & rtDW . e3mw3kxdbw . AQHandles ) ; }
if ( rtDW . e3mw3kxdbw . SlioLTF ) { rtwDestructAccessorPointer ( rtDW .
e3mw3kxdbw . SlioLTF ) ; } } { if ( rtDW . lltjwuok3g . AQHandles ) {
sdiTerminateStreaming ( & rtDW . lltjwuok3g . AQHandles ) ; } if ( rtDW .
lltjwuok3g . SlioLTF ) { rtwDestructAccessorPointer ( rtDW . lltjwuok3g .
SlioLTF ) ; } } { if ( rtDW . grojl3nk3g . AQHandles ) {
sdiTerminateStreaming ( & rtDW . grojl3nk3g . AQHandles ) ; } if ( rtDW .
grojl3nk3g . SlioLTF ) { rtwDestructAccessorPointer ( rtDW . grojl3nk3g .
SlioLTF ) ; } } { const char * errMsg = ( NULL ) ; void * fp = ( void * )
rtDW . lcl4opl5jx . FilePtr ; if ( fp != ( NULL ) ) { errMsg =
rtwH5LoggingCollectionDestroyInstance ( 1 , fp ) ; if ( errMsg != ( NULL ) )
{ ssSetErrorStatus ( rtS , errMsg ) ; return ; } } } { const char * errMsg =
( NULL ) ; void * fp = ( void * ) rtDW . lrc3gfcuvu . FilePtr ; if ( fp != (
NULL ) ) { errMsg = rtwH5LoggingCollectionDestroyInstance ( 1 , fp ) ; if (
errMsg != ( NULL ) ) { ssSetErrorStatus ( rtS , errMsg ) ; return ; } } } if
( rt_slioCatalogue ( ) != ( NULL ) ) { void * * slioCatalogueAddr =
rt_slioCatalogueAddr ( ) ; rtwSaveDatasetsToMatFile (
rtwGetPointerFromUniquePtr ( rt_slioCatalogue ( ) ) ,
rt_GetMatSigstreamLoggingFileName ( ) ) ; rtwTerminateSlioCatalogue (
slioCatalogueAddr ) ; * slioCatalogueAddr = NULL ; } } void
MdlInitializeSizes ( void ) { ssSetNumContStates ( rtS , 17 ) ;
ssSetNumPeriodicContStates ( rtS , 0 ) ; ssSetNumY ( rtS , 0 ) ; ssSetNumU (
rtS , 0 ) ; ssSetDirectFeedThrough ( rtS , 0 ) ; ssSetNumSampleTimes ( rtS ,
3 ) ; ssSetNumBlocks ( rtS , 113 ) ; ssSetNumBlockIO ( rtS , 74 ) ;
ssSetNumBlockParams ( rtS , 65 ) ; } void MdlInitializeSampleTimes ( void ) {
ssSetSampleTime ( rtS , 0 , 0.0 ) ; ssSetSampleTime ( rtS , 1 , 0.0 ) ;
ssSetSampleTime ( rtS , 2 , 0.01 ) ; ssSetOffsetTime ( rtS , 0 , 0.0 ) ;
ssSetOffsetTime ( rtS , 1 , 1.0 ) ; ssSetOffsetTime ( rtS , 2 , 0.0 ) ; }
void raccel_set_checksum ( ) { ssSetChecksumVal ( rtS , 0 , 143558795U ) ;
ssSetChecksumVal ( rtS , 1 , 2582642242U ) ; ssSetChecksumVal ( rtS , 2 ,
304599836U ) ; ssSetChecksumVal ( rtS , 3 , 2494036382U ) ; }
#if defined(_MSC_VER)
#pragma optimize( "", off )
#endif
SimStruct * raccel_register_model ( void ) { static struct _ssMdlInfo mdlInfo
; ( void ) memset ( ( char * ) rtS , 0 , sizeof ( SimStruct ) ) ; ( void )
memset ( ( char * ) & mdlInfo , 0 , sizeof ( struct _ssMdlInfo ) ) ;
ssSetMdlInfoPtr ( rtS , & mdlInfo ) ; { static time_T mdlPeriod [
NSAMPLE_TIMES ] ; static time_T mdlOffset [ NSAMPLE_TIMES ] ; static time_T
mdlTaskTimes [ NSAMPLE_TIMES ] ; static int_T mdlTsMap [ NSAMPLE_TIMES ] ;
static int_T mdlSampleHits [ NSAMPLE_TIMES ] ; static boolean_T
mdlTNextWasAdjustedPtr [ NSAMPLE_TIMES ] ; static int_T mdlPerTaskSampleHits
[ NSAMPLE_TIMES * NSAMPLE_TIMES ] ; static time_T mdlTimeOfNextSampleHit [
NSAMPLE_TIMES ] ; { int_T i ; for ( i = 0 ; i < NSAMPLE_TIMES ; i ++ ) {
mdlPeriod [ i ] = 0.0 ; mdlOffset [ i ] = 0.0 ; mdlTaskTimes [ i ] = 0.0 ;
mdlTsMap [ i ] = i ; mdlSampleHits [ i ] = 1 ; } } ssSetSampleTimePtr ( rtS ,
& mdlPeriod [ 0 ] ) ; ssSetOffsetTimePtr ( rtS , & mdlOffset [ 0 ] ) ;
ssSetSampleTimeTaskIDPtr ( rtS , & mdlTsMap [ 0 ] ) ; ssSetTPtr ( rtS , &
mdlTaskTimes [ 0 ] ) ; ssSetSampleHitPtr ( rtS , & mdlSampleHits [ 0 ] ) ;
ssSetTNextWasAdjustedPtr ( rtS , & mdlTNextWasAdjustedPtr [ 0 ] ) ;
ssSetPerTaskSampleHitsPtr ( rtS , & mdlPerTaskSampleHits [ 0 ] ) ;
ssSetTimeOfNextSampleHitPtr ( rtS , & mdlTimeOfNextSampleHit [ 0 ] ) ; }
ssSetSolverMode ( rtS , SOLVER_MODE_SINGLETASKING ) ; { ssSetBlockIO ( rtS ,
( ( void * ) & rtB ) ) ; ( void ) memset ( ( ( void * ) & rtB ) , 0 , sizeof
( B ) ) ; } ssSetDefaultParam ( rtS , ( real_T * ) & rtP ) ; { real_T * x = (
real_T * ) & rtX ; ssSetContStates ( rtS , x ) ; ( void ) memset ( ( void * )
x , 0 , sizeof ( X ) ) ; } { void * dwork = ( void * ) & rtDW ;
ssSetRootDWork ( rtS , dwork ) ; ( void ) memset ( dwork , 0 , sizeof ( DW )
) ; } { static DataTypeTransInfo dtInfo ; ( void ) memset ( ( char_T * ) &
dtInfo , 0 , sizeof ( dtInfo ) ) ; ssSetModelMappingInfo ( rtS , & dtInfo ) ;
dtInfo . numDataTypes = 14 ; dtInfo . dataTypeSizes = & rtDataTypeSizes [ 0 ]
; dtInfo . dataTypeNames = & rtDataTypeNames [ 0 ] ; dtInfo . BTransTable = &
rtBTransTable ; dtInfo . PTransTable = & rtPTransTable ; }
motor_InitializeDataMapInfo ( ) ; ssSetIsRapidAcceleratorActive ( rtS , true
) ; ssSetRootSS ( rtS , rtS ) ; ssSetVersion ( rtS , SIMSTRUCT_VERSION_LEVEL2
) ; ssSetModelName ( rtS , "motor" ) ; ssSetPath ( rtS , "motor" ) ;
ssSetTStart ( rtS , 0.0 ) ; ssSetTFinal ( rtS , 2.0 ) ; { static RTWLogInfo
rt_DataLoggingInfo ; rt_DataLoggingInfo . loggingInterval = NULL ;
ssSetRTWLogInfo ( rtS , & rt_DataLoggingInfo ) ; } { rtliSetLogXSignalInfo (
ssGetRTWLogInfo ( rtS ) , ( NULL ) ) ; rtliSetLogXSignalPtrs (
ssGetRTWLogInfo ( rtS ) , ( NULL ) ) ; rtliSetLogT ( ssGetRTWLogInfo ( rtS )
, "tout" ) ; rtliSetLogX ( ssGetRTWLogInfo ( rtS ) , "" ) ; rtliSetLogXFinal
( ssGetRTWLogInfo ( rtS ) , "" ) ; rtliSetLogVarNameModifier (
ssGetRTWLogInfo ( rtS ) , "none" ) ; rtliSetLogFormat ( ssGetRTWLogInfo ( rtS
) , 4 ) ; rtliSetLogMaxRows ( ssGetRTWLogInfo ( rtS ) , 0 ) ;
rtliSetLogDecimation ( ssGetRTWLogInfo ( rtS ) , 1 ) ; rtliSetLogY (
ssGetRTWLogInfo ( rtS ) , "" ) ; rtliSetLogYSignalInfo ( ssGetRTWLogInfo (
rtS ) , ( NULL ) ) ; rtliSetLogYSignalPtrs ( ssGetRTWLogInfo ( rtS ) , ( NULL
) ) ; } { static struct _ssStatesInfo2 statesInfo2 ; ssSetStatesInfo2 ( rtS ,
& statesInfo2 ) ; } { static ssPeriodicStatesInfo periodicStatesInfo ;
ssSetPeriodicStatesInfo ( rtS , & periodicStatesInfo ) ; } { static
ssSolverInfo slvrInfo ; static boolean_T contStatesDisabled [ 17 ] ; static
real_T absTol [ 17 ] = { 1.0E-6 , 1.0E-6 , 1.0E-6 , 1.0E-6 , 1.0E-6 , 1.0E-6
, 1.0E-6 , 1.0E-6 , 1.0E-6 , 1.0E-6 , 1.0E-6 , 1.0E-6 , 1.0E-6 , 1.0E-6 ,
1.0E-6 , 1.0E-6 , 1.0E-6 } ; static uint8_T absTolControl [ 17 ] = { 0U , 0U
, 0U , 0U , 0U , 0U , 0U , 0U , 0U , 0U , 0U , 0U , 0U , 0U , 0U , 0U , 0U }
; static uint8_T zcAttributes [ 28 ] = { ( ZC_EVENT_ALL_UP ) , ( ZC_EVENT_ALL
) , ( ZC_EVENT_ALL ) , ( ZC_EVENT_ALL ) , ( ZC_EVENT_ALL ) , ( ZC_EVENT_ALL )
, ( ZC_EVENT_ALL ) , ( ZC_EVENT_ALL ) , ( ZC_EVENT_ALL ) , ( ZC_EVENT_ALL ) ,
( ZC_EVENT_ALL ) , ( ZC_EVENT_ALL ) , ( ZC_EVENT_ALL ) , ( ZC_EVENT_ALL_UP )
, ( ZC_EVENT_ALL_UP ) , ( ZC_EVENT_ALL ) , ( ZC_EVENT_ALL ) , ( ZC_EVENT_ALL
) , ( ZC_EVENT_ALL ) , ( ZC_EVENT_ALL ) , ( ZC_EVENT_ALL ) , ( ZC_EVENT_ALL )
, ( ZC_EVENT_ALL ) , ( ZC_EVENT_ALL ) , ( ZC_EVENT_ALL ) , ( ZC_EVENT_ALL ) ,
( ZC_EVENT_ALL ) , ( ZC_EVENT_ALL ) } ; static ssNonContDerivSigInfo
nonContDerivSigInfo [ 5 ] = { { 1 * sizeof ( boolean_T ) , ( char * ) ( & rtB
. avhiv2ojkj ) , ( NULL ) } , { 1 * sizeof ( real_T ) , ( char * ) ( & rtB .
obo5lyqljg ) , ( NULL ) } , { 1 * sizeof ( real_T ) , ( char * ) ( & rtB .
ozd5y1bdbm ) , ( NULL ) } , { 1 * sizeof ( boolean_T ) , ( char * ) ( & rtB .
emy34hfzxp ) , ( NULL ) } , { 1 * sizeof ( real_T ) , ( char * ) ( & rtB .
o5y1y4cmrq ) , ( NULL ) } } ; ssSetSolverRelTol ( rtS , 0.001 ) ;
ssSetStepSize ( rtS , 0.0 ) ; ssSetMinStepSize ( rtS , 0.0 ) ;
ssSetMaxNumMinSteps ( rtS , - 1 ) ; ssSetMinStepViolatedError ( rtS , 0 ) ;
ssSetMaxStepSize ( rtS , 0.01 ) ; ssSetSolverMaxOrder ( rtS , 5 ) ;
ssSetSolverRefineFactor ( rtS , 1 ) ; ssSetOutputTimes ( rtS , ( NULL ) ) ;
ssSetNumOutputTimes ( rtS , 0 ) ; ssSetOutputTimesOnly ( rtS , 0 ) ;
ssSetOutputTimesIndex ( rtS , 0 ) ; ssSetZCCacheNeedsReset ( rtS , 1 ) ;
ssSetDerivCacheNeedsReset ( rtS , 0 ) ; ssSetNumNonContDerivSigInfos ( rtS ,
5 ) ; ssSetNonContDerivSigInfos ( rtS , nonContDerivSigInfo ) ;
ssSetSolverInfo ( rtS , & slvrInfo ) ; ssSetSolverName ( rtS , "ode15s" ) ;
ssSetVariableStepSolver ( rtS , 1 ) ; ssSetSolverConsistencyChecking ( rtS ,
0 ) ; ssSetSolverAdaptiveZcDetection ( rtS , 0 ) ;
ssSetSolverRobustResetMethod ( rtS , 0 ) ; ssSetAbsTolVector ( rtS , absTol )
; ssSetAbsTolControlVector ( rtS , absTolControl ) ;
ssSetSolverAbsTol_Obsolete ( rtS , absTol ) ;
ssSetSolverAbsTolControl_Obsolete ( rtS , absTolControl ) ;
ssSetSolverStateProjection ( rtS , 0 ) ; ssSetSolverMassMatrixType ( rtS , (
ssMatrixType ) 0 ) ; ssSetSolverMassMatrixNzMax ( rtS , 0 ) ;
ssSetModelOutputs ( rtS , MdlOutputs ) ; ssSetModelLogData ( rtS ,
rt_UpdateTXYLogVars ) ; ssSetModelLogDataIfInInterval ( rtS ,
rt_UpdateTXXFYLogVars ) ; ssSetModelUpdate ( rtS , MdlUpdate ) ;
ssSetModelDerivatives ( rtS , MdlDerivatives ) ; ssSetSolverZcSignalAttrib (
rtS , zcAttributes ) ; ssSetSolverNumZcSignals ( rtS , 28 ) ;
ssSetModelZeroCrossings ( rtS , MdlZeroCrossings ) ;
ssSetSolverConsecutiveZCsStepRelTol ( rtS , 2.8421709430404007E-13 ) ;
ssSetSolverMaxConsecutiveZCs ( rtS , 1000 ) ; ssSetSolverConsecutiveZCsError
( rtS , 2 ) ; ssSetSolverMaskedZcDiagnostic ( rtS , 1 ) ;
ssSetSolverIgnoredZcDiagnostic ( rtS , 1 ) ; ssSetSolverMaxConsecutiveMinStep
( rtS , 1 ) ; ssSetSolverShapePreserveControl ( rtS , 2 ) ; ssSetTNextTid (
rtS , INT_MIN ) ; ssSetTNext ( rtS , rtMinusInf ) ; ssSetSolverNeedsReset (
rtS ) ; ssSetNumNonsampledZCs ( rtS , 28 ) ; ssSetContStateDisabled ( rtS ,
contStatesDisabled ) ; ssSetSolverMaxConsecutiveMinStep ( rtS , 1 ) ; }
ssSetChecksumVal ( rtS , 0 , 143558795U ) ; ssSetChecksumVal ( rtS , 1 ,
2582642242U ) ; ssSetChecksumVal ( rtS , 2 , 304599836U ) ; ssSetChecksumVal
( rtS , 3 , 2494036382U ) ; { static const sysRanDType rtAlwaysEnabled =
SUBSYS_RAN_BC_ENABLE ; static RTWExtModeInfo rt_ExtModeInfo ; static const
sysRanDType * systemRan [ 1 ] ; gblRTWExtModeInfo = & rt_ExtModeInfo ;
ssSetRTWExtModeInfo ( rtS , & rt_ExtModeInfo ) ;
rteiSetSubSystemActiveVectorAddresses ( & rt_ExtModeInfo , systemRan ) ;
systemRan [ 0 ] = & rtAlwaysEnabled ; rteiSetModelMappingInfoPtr (
ssGetRTWExtModeInfo ( rtS ) , & ssGetModelMappingInfo ( rtS ) ) ;
rteiSetChecksumsPtr ( ssGetRTWExtModeInfo ( rtS ) , ssGetChecksums ( rtS ) )
; rteiSetTPtr ( ssGetRTWExtModeInfo ( rtS ) , ssGetTPtr ( rtS ) ) ; } return
rtS ; }
#if defined(_MSC_VER)
#pragma optimize( "", on )
#endif
const int_T gblParameterTuningTid = 3 ; void MdlOutputsParameterSampleTime (
int_T tid ) { UNUSED_PARAMETER ( tid ) ; }
