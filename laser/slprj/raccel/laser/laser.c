#include "__cf_laser.h"
#include "rt_logging_mmi.h"
#include "laser_capi.h"
#include <math.h>
#include "laser.h"
#include "laser_private.h"
#include "laser_dt.h"
extern void * CreateDiagnosticAsVoidPtr_wrapper ( const char * id , int nargs
, ... ) ; RTWExtModeInfo * gblRTWExtModeInfo = NULL ; extern boolean_T
gblExtModeStartPktReceived ; void raccelForceExtModeShutdown ( ) { if ( !
gblExtModeStartPktReceived ) { boolean_T stopRequested = false ;
rtExtModeWaitForStartPkt ( gblRTWExtModeInfo , 2 , & stopRequested ) ; }
rtExtModeShutdown ( 2 ) ; }
#include "slsv_diagnostic_codegen_c_api.h"
const int_T gblNumToFiles = 0 ; const int_T gblNumFrFiles = 0 ; const int_T
gblNumFrWksBlocks = 0 ;
#ifdef RSIM_WITH_SOLVER_MULTITASKING
boolean_T gbl_raccel_isMultitasking = 1 ;
#else
boolean_T gbl_raccel_isMultitasking = 0 ;
#endif
boolean_T gbl_raccel_tid01eq = 0 ; int_T gbl_raccel_NumST = 3 ; const char_T
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
"slprj\\raccel\\laser\\laser_Jpattern.mat" ; const int_T gblNumRootInportBlks
= 0 ; const int_T gblNumModelInputs = 0 ; extern rtInportTUtable *
gblInportTUtables ; extern const char * gblInportFileName ; const int_T
gblInportDataTypeIdx [ ] = { - 1 } ; const int_T gblInportDims [ ] = { - 1 }
; const int_T gblInportComplex [ ] = { - 1 } ; const int_T
gblInportInterpoFlag [ ] = { - 1 } ; const int_T gblInportContinuous [ ] = {
- 1 } ;
#include "simstruc.h"
#include "fixedpoint.h"
B rtB ; X rtX ; DW rtDW ; static SimStruct model_S ; SimStruct * const rtS =
& model_S ; void MdlInitialize ( void ) { rtX . ngucjqsbmh = 0.0 ; rtX .
f1vfx1wka5 = 0.0 ; rtX . gucrjwde45 = rtP . IntegratorQ0_IC ; rtX .
mwebrdpwdq = rtP . IntegratorQ1_IC ; rtDW . hi3zk3zli4 = rtP .
Memory1_InitialCondition ; rtDW . euclalwh11 = rtP . Memory3_InitialCondition
; rtDW . beg153xvlk = ( rtInf ) ; rtDW . cnpublhlg5 = ( rtInf ) ; rtDW .
lgcrmtnzbq = rtP . Memory4_InitialCondition ; rtX . aijhcipwoo [ 0 ] = rtP .
Integrator_IC ; rtDW . edqnr03j4o [ 0 ] = rtP . Memory2_InitialCondition ;
rtX . cizfoddkjl [ 0 ] = 0.0 ; rtX . lunpvzrzl4 [ 0 ] = 0.0 ; rtX .
aijhcipwoo [ 1 ] = rtP . Integrator_IC ; rtDW . edqnr03j4o [ 1 ] = rtP .
Memory2_InitialCondition ; rtX . cizfoddkjl [ 1 ] = 0.0 ; rtX . lunpvzrzl4 [
1 ] = 0.0 ; rtX . pds5dexq0c = rtP . Filter_IC ; rtX . b5onyiwttn = rtP .
Integrator_IC_itl5ymsq54 ; rtX . ftfth001j0 = rtP . Filter_IC_kyn4kgm3f4 ;
rtX . lloaupur3b = rtP . Integrator_IC_bz3z1grlau ; } void MdlStart ( void )
{ { void * * slioCatalogueAddr = rt_slioCatalogueAddr ( ) ; void * r2 = (
NULL ) ; void * * pOSigstreamManagerAddr = ( NULL ) ; const char *
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
srcInfo ; sdiLabelU loggedName = sdiGetLabelFromChars ( "" ) ; sdiLabelU
origSigName = sdiGetLabelFromChars ( "" ) ; sdiLabelU propName =
sdiGetLabelFromChars ( "" ) ; sdiLabelU blockPath = sdiGetLabelFromChars (
"laser/Jnt Controller" ) ; sdiLabelU blockSID = sdiGetLabelFromChars ( "" ) ;
sdiLabelU subPath = sdiGetLabelFromChars ( "" ) ; sdiDims sigDims ; sdiLabelU
sigName = sdiGetLabelFromChars ( "" ) ; sdiAsyncRepoDataTypeHandle hDT =
sdiAsyncRepoGetBuiltInDataTypeHandle ( DATA_TYPE_BOOLEAN ) ; { sdiComplexity
sigComplexity = REAL ; sdiSampleTimeContinuity stCont = SAMPLE_TIME_DISCRETE
; int_T sigDimsArray [ 1 ] = { 1 } ; sigDims . nDims = 1 ; sigDims .
dimensions = sigDimsArray ; srcInfo . numBlockPathElems = 1 ; srcInfo .
fullBlockPath = ( sdiFullBlkPathU ) & blockPath ; srcInfo . SID = (
sdiSignalIDU ) & blockSID ; srcInfo . subPath = subPath ; srcInfo . portIndex
= 1 + 1 ; srcInfo . signalName = sigName ; srcInfo . sigSourceUUID = 0 ; rtDW
. ihyfkimqv5 . AQHandles = sdiAsyncRepoCreateAsyncioQueue ( hDT , & srcInfo ,
rt_dataMapInfo . mmi . InstanceMap . fullPath ,
"c842e491-6feb-419f-8b25-c2bb20b93f3c" , sigComplexity , & sigDims ,
DIMENSIONS_MODE_FIXED , stCont , "" ) ; if ( rtDW . ihyfkimqv5 . AQHandles )
{ sdiSetSignalSampleTimeString ( rtDW . ihyfkimqv5 . AQHandles , "Continuous"
, 0.0 , ssGetTFinal ( rtS ) ) ; sdiSetRunStartTime ( rtDW . ihyfkimqv5 .
AQHandles , ssGetTaskTime ( rtS , 1 ) ) ; sdiAsyncRepoSetSignalExportSettings
( rtDW . ihyfkimqv5 . AQHandles , 1 , 0 ) ; sdiAsyncRepoSetSignalExportName (
rtDW . ihyfkimqv5 . AQHandles , loggedName , origSigName , propName ) ; }
sdiFreeLabel ( sigName ) ; sdiFreeLabel ( loggedName ) ; sdiFreeLabel (
origSigName ) ; sdiFreeLabel ( propName ) ; sdiFreeLabel ( blockPath ) ;
sdiFreeLabel ( blockSID ) ; sdiFreeLabel ( subPath ) ; } } } { void *
treeVector = ( NULL ) ; void * accessor = ( NULL ) ; const void *
signalDescriptor = ( NULL ) ; void * loggingInterval = ( NULL ) ; char *
datasetName = "tmp_raccel_logsout" ; if ( slioCatalogue && rtwIsLoggingToFile
( slioCatalogue ) ) { treeVector = rtwGetTreeVector ( ) ; { int_T
sigDimsArray [ 1 ] = { 1 } ; rtwAddLeafNode ( 8 , "" , "zoh" , 0 , ( unsigned
int * ) sigDimsArray , 1 , "logical" , "" , "Continuous" , 0.0 , ssGetTFinal
( rtS ) , treeVector ) ; } signalDescriptor = rtwGetSignalDescriptor (
treeVector , 1 , 1 , 0 , 1 , "" , "" , rt_dataMapInfo . mmi . InstanceMap .
fullPath , "laser/Jnt Controller" , 2 , 0 , slioCatalogue , ( NULL ) , 0 , (
NULL ) , 0 ) ; if ( ! rt_slioCatalogue ( ) ) { sdiSlioIsLoggingSignal (
rt_dataMapInfo . mmi . InstanceMap . fullPath , "laser/Jnt Controller" , 2 ,
"" ) ; } if ( rtwLoggingOverride ( signalDescriptor , slioCatalogue ) ) { if
( ssGetRootSS ( rtS ) -> mdlInfo -> rtwLogInfo ) { loggingInterval =
rtliGetLoggingInterval ( ssGetRootSS ( rtS ) -> mdlInfo -> rtwLogInfo ) ; }
else { loggingInterval = sdiGetLoggingIntervals ( rt_dataMapInfo . mmi .
InstanceMap . fullPath ) ; datasetName = "" ; } accessor = rtwGetAccessor (
signalDescriptor , loggingInterval ) ; rtwAddR2Client ( accessor ,
signalDescriptor , slioCatalogue , datasetName , 1 ) ; rtDW . ihyfkimqv5 .
SlioLTF = accessor ; } } } } rtDW . lufveoz2ya = 0 ; rtDW . fnfpq0xxhm = 0 ;
rtDW . f0ckmjw1gj = 0 ; { void * slioCatalogue = rt_slioCatalogue ( ) ?
rtwGetPointerFromUniquePtr ( rt_slioCatalogue ( ) ) : sdiGetSlioCatalogue (
rt_dataMapInfo . mmi . InstanceMap . fullPath ) ; if ( ! slioCatalogue || !
rtwDisableStreamingToRepository ( slioCatalogue ) ) { { sdiSignalSourceInfoU
srcInfo ; sdiLabelU loggedName = sdiGetLabelFromChars ( "" ) ; sdiLabelU
origSigName = sdiGetLabelFromChars ( "" ) ; sdiLabelU propName =
sdiGetLabelFromChars ( "" ) ; sdiLabelU blockPath = sdiGetLabelFromChars (
"laser/Jnt Controller/Motor Current/Burned Motor" ) ; sdiLabelU blockSID =
sdiGetLabelFromChars ( "" ) ; sdiLabelU subPath = sdiGetLabelFromChars ( "" )
; sdiDims sigDims ; sdiLabelU sigName = sdiGetLabelFromChars ( "" ) ;
sdiAsyncRepoDataTypeHandle hDT = sdiAsyncRepoGetBuiltInDataTypeHandle (
DATA_TYPE_BOOLEAN ) ; { sdiComplexity sigComplexity = REAL ;
sdiSampleTimeContinuity stCont = SAMPLE_TIME_DISCRETE ; int_T sigDimsArray [
1 ] = { 1 } ; sigDims . nDims = 1 ; sigDims . dimensions = sigDimsArray ;
srcInfo . numBlockPathElems = 1 ; srcInfo . fullBlockPath = ( sdiFullBlkPathU
) & blockPath ; srcInfo . SID = ( sdiSignalIDU ) & blockSID ; srcInfo .
subPath = subPath ; srcInfo . portIndex = 0 + 1 ; srcInfo . signalName =
sigName ; srcInfo . sigSourceUUID = 0 ; rtDW . gchzjejcu3 . AQHandles =
sdiAsyncRepoCreateAsyncioQueue ( hDT , & srcInfo , rt_dataMapInfo . mmi .
InstanceMap . fullPath , "41c4eeb2-d925-4c7e-8e70-5e3fbe81f7ae" ,
sigComplexity , & sigDims , DIMENSIONS_MODE_FIXED , stCont , "" ) ; if ( rtDW
. gchzjejcu3 . AQHandles ) { sdiSetSignalSampleTimeString ( rtDW . gchzjejcu3
. AQHandles , "Continuous" , 0.0 , ssGetTFinal ( rtS ) ) ; sdiSetRunStartTime
( rtDW . gchzjejcu3 . AQHandles , ssGetTaskTime ( rtS , 1 ) ) ;
sdiAsyncRepoSetSignalExportSettings ( rtDW . gchzjejcu3 . AQHandles , 1 , 0 )
; sdiAsyncRepoSetSignalExportName ( rtDW . gchzjejcu3 . AQHandles ,
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
"laser/Jnt Controller/Motor Current/Burned Motor" , 1 , 0 , slioCatalogue , (
NULL ) , 0 , ( NULL ) , 0 ) ; if ( ! rt_slioCatalogue ( ) ) {
sdiSlioIsLoggingSignal ( rt_dataMapInfo . mmi . InstanceMap . fullPath ,
"laser/Jnt Controller/Motor Current/Burned Motor" , 1 , "" ) ; } if (
rtwLoggingOverride ( signalDescriptor , slioCatalogue ) ) { if ( ssGetRootSS
( rtS ) -> mdlInfo -> rtwLogInfo ) { loggingInterval = rtliGetLoggingInterval
( ssGetRootSS ( rtS ) -> mdlInfo -> rtwLogInfo ) ; } else { loggingInterval =
sdiGetLoggingIntervals ( rt_dataMapInfo . mmi . InstanceMap . fullPath ) ;
datasetName = "" ; } accessor = rtwGetAccessor ( signalDescriptor ,
loggingInterval ) ; rtwAddR2Client ( accessor , signalDescriptor ,
slioCatalogue , datasetName , 1 ) ; rtDW . gchzjejcu3 . SlioLTF = accessor ;
} } } } { void * slioCatalogue = rt_slioCatalogue ( ) ?
rtwGetPointerFromUniquePtr ( rt_slioCatalogue ( ) ) : sdiGetSlioCatalogue (
rt_dataMapInfo . mmi . InstanceMap . fullPath ) ; if ( ! slioCatalogue || !
rtwDisableStreamingToRepository ( slioCatalogue ) ) { { sdiSignalSourceInfoU
srcInfo ; sdiLabelU loggedName = sdiGetLabelFromChars ( "" ) ; sdiLabelU
origSigName = sdiGetLabelFromChars ( "" ) ; sdiLabelU propName =
sdiGetLabelFromChars ( "" ) ; sdiLabelU blockPath = sdiGetLabelFromChars (
"laser/Jnt Controller/Motor Current/MinMax1" ) ; sdiLabelU blockSID =
sdiGetLabelFromChars ( "" ) ; sdiLabelU subPath = sdiGetLabelFromChars ( "" )
; sdiDims sigDims ; sdiLabelU sigName = sdiGetLabelFromChars ( "" ) ;
sdiAsyncRepoDataTypeHandle hDT = sdiAsyncRepoGetBuiltInDataTypeHandle (
DATA_TYPE_DOUBLE ) ; { sdiComplexity sigComplexity = REAL ;
sdiSampleTimeContinuity stCont = SAMPLE_TIME_CONTINUOUS ; int_T sigDimsArray
[ 1 ] = { 2 } ; sigDims . nDims = 1 ; sigDims . dimensions = sigDimsArray ;
srcInfo . numBlockPathElems = 1 ; srcInfo . fullBlockPath = ( sdiFullBlkPathU
) & blockPath ; srcInfo . SID = ( sdiSignalIDU ) & blockSID ; srcInfo .
subPath = subPath ; srcInfo . portIndex = 0 + 1 ; srcInfo . signalName =
sigName ; srcInfo . sigSourceUUID = 0 ; rtDW . egn21ix41f . AQHandles =
sdiAsyncRepoCreateAsyncioQueue ( hDT , & srcInfo , rt_dataMapInfo . mmi .
InstanceMap . fullPath , "5acc5e92-a0f4-45a0-825c-31bb3e6ec4b7" ,
sigComplexity , & sigDims , DIMENSIONS_MODE_FIXED , stCont , "" ) ; if ( rtDW
. egn21ix41f . AQHandles ) { sdiSetSignalSampleTimeString ( rtDW . egn21ix41f
. AQHandles , "Continuous" , 0.0 , ssGetTFinal ( rtS ) ) ; sdiSetRunStartTime
( rtDW . egn21ix41f . AQHandles , ssGetTaskTime ( rtS , 1 ) ) ;
sdiAsyncRepoSetSignalExportSettings ( rtDW . egn21ix41f . AQHandles , 1 , 0 )
; sdiAsyncRepoSetSignalExportName ( rtDW . egn21ix41f . AQHandles ,
loggedName , origSigName , propName ) ; } sdiFreeLabel ( sigName ) ;
sdiFreeLabel ( loggedName ) ; sdiFreeLabel ( origSigName ) ; sdiFreeLabel (
propName ) ; sdiFreeLabel ( blockPath ) ; sdiFreeLabel ( blockSID ) ;
sdiFreeLabel ( subPath ) ; } } } { void * treeVector = ( NULL ) ; void *
accessor = ( NULL ) ; const void * signalDescriptor = ( NULL ) ; void *
loggingInterval = ( NULL ) ; char * datasetName = "tmp_raccel_logsout" ; if (
slioCatalogue && rtwIsLoggingToFile ( slioCatalogue ) ) { treeVector =
rtwGetTreeVector ( ) ; { int_T sigDimsArray [ 1 ] = { 2 } ; rtwAddLeafNode (
0 , "" , "linear" , 0 , ( unsigned int * ) sigDimsArray , 1 , "double" , "" ,
"Continuous" , 0.0 , ssGetTFinal ( rtS ) , treeVector ) ; } signalDescriptor
= rtwGetSignalDescriptor ( treeVector , 1 , 1 , 0 , 1 , "" , "" ,
rt_dataMapInfo . mmi . InstanceMap . fullPath ,
"laser/Jnt Controller/Motor Current/MinMax1" , 1 , 0 , slioCatalogue , ( NULL
) , 0 , ( NULL ) , 0 ) ; if ( ! rt_slioCatalogue ( ) ) {
sdiSlioIsLoggingSignal ( rt_dataMapInfo . mmi . InstanceMap . fullPath ,
"laser/Jnt Controller/Motor Current/MinMax1" , 1 , "" ) ; } if (
rtwLoggingOverride ( signalDescriptor , slioCatalogue ) ) { if ( ssGetRootSS
( rtS ) -> mdlInfo -> rtwLogInfo ) { loggingInterval = rtliGetLoggingInterval
( ssGetRootSS ( rtS ) -> mdlInfo -> rtwLogInfo ) ; } else { loggingInterval =
sdiGetLoggingIntervals ( rt_dataMapInfo . mmi . InstanceMap . fullPath ) ;
datasetName = "" ; } accessor = rtwGetAccessor ( signalDescriptor ,
loggingInterval ) ; rtwAddR2Client ( accessor , signalDescriptor ,
slioCatalogue , datasetName , 1 ) ; rtDW . egn21ix41f . SlioLTF = accessor ;
} } } } { void * slioCatalogue = rt_slioCatalogue ( ) ?
rtwGetPointerFromUniquePtr ( rt_slioCatalogue ( ) ) : sdiGetSlioCatalogue (
rt_dataMapInfo . mmi . InstanceMap . fullPath ) ; if ( ! slioCatalogue || !
rtwDisableStreamingToRepository ( slioCatalogue ) ) { { sdiSignalSourceInfoU
srcInfo ; sdiLabelU loggedName = sdiGetLabelFromChars ( "" ) ; sdiLabelU
origSigName = sdiGetLabelFromChars ( "" ) ; sdiLabelU propName =
sdiGetLabelFromChars ( "" ) ; sdiLabelU blockPath = sdiGetLabelFromChars (
"laser/Jnt Controller/Motor Current/Sum" ) ; sdiLabelU blockSID =
sdiGetLabelFromChars ( "" ) ; sdiLabelU subPath = sdiGetLabelFromChars ( "" )
; sdiDims sigDims ; sdiLabelU sigName = sdiGetLabelFromChars ( "" ) ;
sdiAsyncRepoDataTypeHandle hDT = sdiAsyncRepoGetBuiltInDataTypeHandle (
DATA_TYPE_UINT8 ) ; { sdiComplexity sigComplexity = REAL ;
sdiSampleTimeContinuity stCont = SAMPLE_TIME_DISCRETE ; int_T sigDimsArray [
1 ] = { 1 } ; sigDims . nDims = 1 ; sigDims . dimensions = sigDimsArray ;
srcInfo . numBlockPathElems = 1 ; srcInfo . fullBlockPath = ( sdiFullBlkPathU
) & blockPath ; srcInfo . SID = ( sdiSignalIDU ) & blockSID ; srcInfo .
subPath = subPath ; srcInfo . portIndex = 0 + 1 ; srcInfo . signalName =
sigName ; srcInfo . sigSourceUUID = 0 ; rtDW . ge33tuv1zo . AQHandles =
sdiAsyncRepoCreateAsyncioQueue ( hDT , & srcInfo , rt_dataMapInfo . mmi .
InstanceMap . fullPath , "c95e5821-e97c-44c5-82e5-37c7d00622d6" ,
sigComplexity , & sigDims , DIMENSIONS_MODE_FIXED , stCont , "" ) ; if ( rtDW
. ge33tuv1zo . AQHandles ) { sdiSetSignalSampleTimeString ( rtDW . ge33tuv1zo
. AQHandles , "Continuous" , 0.0 , ssGetTFinal ( rtS ) ) ; sdiSetRunStartTime
( rtDW . ge33tuv1zo . AQHandles , ssGetTaskTime ( rtS , 1 ) ) ;
sdiAsyncRepoSetSignalExportSettings ( rtDW . ge33tuv1zo . AQHandles , 1 , 0 )
; sdiAsyncRepoSetSignalExportName ( rtDW . ge33tuv1zo . AQHandles ,
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
"laser/Jnt Controller/Motor Current/Sum" , 1 , 0 , slioCatalogue , ( NULL ) ,
0 , ( NULL ) , 0 ) ; if ( ! rt_slioCatalogue ( ) ) { sdiSlioIsLoggingSignal (
rt_dataMapInfo . mmi . InstanceMap . fullPath ,
"laser/Jnt Controller/Motor Current/Sum" , 1 , "" ) ; } if (
rtwLoggingOverride ( signalDescriptor , slioCatalogue ) ) { if ( ssGetRootSS
( rtS ) -> mdlInfo -> rtwLogInfo ) { loggingInterval = rtliGetLoggingInterval
( ssGetRootSS ( rtS ) -> mdlInfo -> rtwLogInfo ) ; } else { loggingInterval =
sdiGetLoggingIntervals ( rt_dataMapInfo . mmi . InstanceMap . fullPath ) ;
datasetName = "" ; } accessor = rtwGetAccessor ( signalDescriptor ,
loggingInterval ) ; rtwAddR2Client ( accessor , signalDescriptor ,
slioCatalogue , datasetName , 1 ) ; rtDW . ge33tuv1zo . SlioLTF = accessor ;
} } } } MdlInitialize ( ) ; { bool externalInputIsInDatasetFormat = false ;
void * pISigstreamManager = rt_GetISigstreamManager ( ) ;
rtwISigstreamManagerGetInputIsInDatasetFormat ( pISigstreamManager , &
externalInputIsInDatasetFormat ) ; if ( externalInputIsInDatasetFormat ) { }
} } void MdlOutputs ( int_T tid ) { uint8_T jzpkgjtrth ; boolean_T iekvwvtqfd
; real_T * lastU ; real_T adixqnkfhd ; real_T hgbyo4at01 ; boolean_T
cx3k1qc3wi ; boolean_T ctmei2zb4t ; real_T adrgpjrulp_idx_1 ; real_T
gmhwb0q345_idx_1 ; real_T adrgpjrulp_idx_0 ; real_T gmhwb0q345_idx_0 ;
adixqnkfhd = ssGetT ( rtS ) ; rtB . hbmlhug0bx [ 0 ] = rtX . aijhcipwoo [ 0 ]
; rtB . py2taxmodw [ 0 ] = rtB . hbmlhug0bx [ 0 ] / adixqnkfhd ; rtB .
hbmlhug0bx [ 1 ] = rtX . aijhcipwoo [ 1 ] ; rtB . py2taxmodw [ 1 ] = rtB .
hbmlhug0bx [ 1 ] / adixqnkfhd ; if ( ssIsSampleHit ( rtS , 1 , 0 ) ) { if (
ssIsMajorTimeStep ( rtS ) ) { rtDW . kylvmh4w13 = ( rtB . py2taxmodw [ 0 ] >
rtP . NomI0 ) ; rtDW . kbqz5luorh = ( rtB . py2taxmodw [ 1 ] > rtP . NomI1 )
; } ctmei2zb4t = rtDW . kylvmh4w13 ; cx3k1qc3wi = rtDW . kbqz5luorh ; } rtB .
imv2femxvj = 0.0 ; rtB . imv2femxvj += rtP . Elec0n / rtP . Elec0d [ 0 ] *
rtX . ngucjqsbmh ; rtB . oqaiej1ofv = 0.0 ; rtB . oqaiej1ofv += rtP . Elec1n
/ rtP . Elec1d [ 0 ] * rtX . f1vfx1wka5 ; if ( ssIsMajorTimeStep ( rtS ) ) {
rtDW . frnbyss1yt [ 0 ] = ( rtB . imv2femxvj >= 0.0 ) ; rtDW . frnbyss1yt [ 1
] = ( rtB . oqaiej1ofv >= 0.0 ) ; } rtB . lkpyinhslc [ 0 ] = rtDW .
frnbyss1yt [ 0 ] > 0 ? rtB . imv2femxvj : - rtB . imv2femxvj ; rtB .
lkpyinhslc [ 1 ] = rtDW . frnbyss1yt [ 1 ] > 0 ? rtB . oqaiej1ofv : - rtB .
oqaiej1ofv ; if ( ssIsSampleHit ( rtS , 1 , 0 ) ) { rtB . grvfia1xdu [ 0 ] =
rtDW . edqnr03j4o [ 0 ] ; rtB . grvfia1xdu [ 1 ] = rtDW . edqnr03j4o [ 1 ] ;
} if ( ssIsMajorTimeStep ( rtS ) ) { adixqnkfhd = rtB . lkpyinhslc [ 0 ] ;
rtDW . jm5cialsp2 [ 0 ] = 0 ; if ( rtB . grvfia1xdu [ 0 ] > rtB . lkpyinhslc
[ 0 ] ) { adixqnkfhd = rtB . grvfia1xdu [ 0 ] ; rtDW . jm5cialsp2 [ 0 ] = 1 ;
} rtB . boq4gsls3l [ 0 ] = adixqnkfhd ; adixqnkfhd = rtB . lkpyinhslc [ 1 ] ;
rtDW . jm5cialsp2 [ 1 ] = 0 ; if ( rtB . grvfia1xdu [ 1 ] > rtB . lkpyinhslc
[ 1 ] ) { adixqnkfhd = rtB . grvfia1xdu [ 1 ] ; rtDW . jm5cialsp2 [ 1 ] = 1 ;
} rtB . boq4gsls3l [ 1 ] = adixqnkfhd ; } else { adixqnkfhd = rtB .
lkpyinhslc [ 0 ] ; if ( rtDW . jm5cialsp2 [ 0 ] == 1 ) { adixqnkfhd = rtB .
grvfia1xdu [ 0 ] ; } rtB . boq4gsls3l [ 0 ] = adixqnkfhd ; adixqnkfhd = rtB .
lkpyinhslc [ 1 ] ; if ( rtDW . jm5cialsp2 [ 1 ] == 1 ) { adixqnkfhd = rtB .
grvfia1xdu [ 1 ] ; } rtB . boq4gsls3l [ 1 ] = adixqnkfhd ; } if (
ssIsSampleHit ( rtS , 1 , 0 ) ) { if ( ssIsMajorTimeStep ( rtS ) ) { rtDW .
ekvz540vhq = ( rtB . boq4gsls3l [ 0 ] > rtP . StallI0 ) ; rtDW . eplu0qlvkz =
( rtB . boq4gsls3l [ 1 ] > rtP . StallI1 ) ; } jzpkgjtrth = ( uint8_T ) ( ( (
( uint32_T ) ctmei2zb4t + cx3k1qc3wi ) + rtDW . ekvz540vhq ) + rtDW .
eplu0qlvkz ) ; iekvwvtqfd = ( jzpkgjtrth > rtP . Constant_Value ) ; { if ( (
rtDW . ihyfkimqv5 . AQHandles || rtDW . ihyfkimqv5 . SlioLTF ) &&
ssGetLogOutput ( rtS ) ) { sdiSlioSdiWriteSignal ( rtDW . ihyfkimqv5 .
AQHandles , rtDW . ihyfkimqv5 . SlioLTF , 0 , ssGetTaskTime ( rtS , 1 ) , (
void * ) & iekvwvtqfd ) ; } } } rtB . jvcbsan3fm = rtX . gucrjwde45 ; rtB .
muyocrskli = muDoubleScalarTan ( rtB . jvcbsan3fm ) * rtP . Distance ; rtB .
ciuxkrwmvl = rtX . mwebrdpwdq ; if ( ssIsMajorTimeStep ( rtS ) ) { rtDW .
hoivdwve1d = rtB . ciuxkrwmvl >= rtP . JntSat1 ? 1 : rtB . ciuxkrwmvl > - rtP
. JntSat1 ? 0 : - 1 ; } rtB . ifywyvlyix = rtDW . hoivdwve1d == 1 ? rtP .
JntSat1 : rtDW . hoivdwve1d == - 1 ? - rtP . JntSat1 : rtB . ciuxkrwmvl ; rtB
. df2qekfpqc = muDoubleScalarTan ( rtB . ifywyvlyix ) * rtP . Distance ;
adrgpjrulp_idx_0 = rtB . muyocrskli ; adrgpjrulp_idx_1 = rtB . df2qekfpqc ;
adixqnkfhd = rtB . muyocrskli * rtB . muyocrskli + rtB . df2qekfpqc * rtB .
df2qekfpqc ; if ( ssIsMajorTimeStep ( rtS ) ) { if ( rtDW . lufveoz2ya != 0 )
{ ssSetBlockStateForSolverChangedAtMajorStep ( rtS ) ; rtDW . lufveoz2ya = 0
; } rtB . fl4jmkviqg = muDoubleScalarSqrt ( adixqnkfhd ) ; } else if (
adixqnkfhd < 0.0 ) { rtB . fl4jmkviqg = - muDoubleScalarSqrt (
muDoubleScalarAbs ( adixqnkfhd ) ) ; rtDW . lufveoz2ya = 1 ; } else { rtB .
fl4jmkviqg = muDoubleScalarSqrt ( adixqnkfhd ) ; } if ( ssIsSampleHit ( rtS ,
1 , 0 ) ) { if ( ssIsMajorTimeStep ( rtS ) ) { rtDW . ih4snyf23z = ( rtB .
fl4jmkviqg > rtP . CompareToConstant_const ) ; } rtB . nblejb4ulo = rtDW .
ih4snyf23z ; } rtB . oog2f0orgs = muDoubleScalarSin ( rtP . SineWave_Freq *
ssGetTaskTime ( rtS , 0 ) + rtP . SineWave_Phase ) * rtP . SineWave_Amp + rtP
. SineWave_Bias ; rtB . pw553ih11r = muDoubleScalarSin ( rtP . SineWave1_Freq
* ssGetTaskTime ( rtS , 0 ) + rtP . SineWave1_Phase ) * rtP . SineWave1_Amp +
rtP . SineWave1_Bias ; gmhwb0q345_idx_0 = rtB . oog2f0orgs ; gmhwb0q345_idx_1
= rtB . pw553ih11r ; adixqnkfhd = rtB . oog2f0orgs * rtB . oog2f0orgs + rtB .
pw553ih11r * rtB . pw553ih11r ; if ( ssIsMajorTimeStep ( rtS ) ) { if ( rtDW
. fnfpq0xxhm != 0 ) { ssSetBlockStateForSolverChangedAtMajorStep ( rtS ) ;
rtDW . fnfpq0xxhm = 0 ; } adixqnkfhd = muDoubleScalarSqrt ( adixqnkfhd ) ; }
else if ( adixqnkfhd < 0.0 ) { adixqnkfhd = - muDoubleScalarSqrt (
muDoubleScalarAbs ( adixqnkfhd ) ) ; rtDW . fnfpq0xxhm = 1 ; } else {
adixqnkfhd = muDoubleScalarSqrt ( adixqnkfhd ) ; } rtB . jvi3aujz2y = ( rtB .
fl4jmkviqg - adixqnkfhd ) * ( real_T ) rtB . nblejb4ulo ; if ( ssIsSampleHit
( rtS , 1 , 0 ) ) { rtB . d0ywb4iifr = rtDW . hi3zk3zli4 ; hgbyo4at01 = rtDW
. euclalwh11 ; } if ( ssIsMajorTimeStep ( rtS ) ) { adixqnkfhd = rtB .
jvi3aujz2y ; rtDW . njpfo0txij = 0 ; if ( rtB . d0ywb4iifr > rtB . jvi3aujz2y
) { adixqnkfhd = rtB . d0ywb4iifr ; rtDW . njpfo0txij = 1 ; } rtB .
cnomiivfhs = adixqnkfhd ; } else { adixqnkfhd = rtB . jvi3aujz2y ; if ( rtDW
. njpfo0txij == 1 ) { adixqnkfhd = rtB . d0ywb4iifr ; } rtB . cnomiivfhs =
adixqnkfhd ; } rtB . mv5es2qqht = gmhwb0q345_idx_0 + gmhwb0q345_idx_1 ; if (
( rtDW . beg153xvlk >= ssGetT ( rtS ) ) && ( rtDW . cnpublhlg5 >= ssGetT (
rtS ) ) ) { rtB . kqxihv51s2 = 0.0 ; } else { adixqnkfhd = rtDW . beg153xvlk
; lastU = & rtDW . mcbn5gls5g ; if ( rtDW . beg153xvlk < rtDW . cnpublhlg5 )
{ if ( rtDW . cnpublhlg5 < ssGetT ( rtS ) ) { adixqnkfhd = rtDW . cnpublhlg5
; lastU = & rtDW . h545t5oyoc ; } } else { if ( rtDW . beg153xvlk >= ssGetT (
rtS ) ) { adixqnkfhd = rtDW . cnpublhlg5 ; lastU = & rtDW . h545t5oyoc ; } }
rtB . kqxihv51s2 = ( rtB . mv5es2qqht - * lastU ) / ( ssGetT ( rtS ) -
adixqnkfhd ) ; } if ( ssIsMajorTimeStep ( rtS ) ) { rtDW . d1vwwr4s1r = ( rtB
. kqxihv51s2 >= 0.0 ) ; } rtB . hwswxdjz2o = rtDW . d1vwwr4s1r > 0 ? rtB .
kqxihv51s2 : - rtB . kqxihv51s2 ; if ( ssIsSampleHit ( rtS , 1 , 0 ) ) { if (
rtB . hwswxdjz2o > 0.0 ) { rtDW . icn2tg3hl2 = 1 ; } else if ( rtB .
hwswxdjz2o < 0.0 ) { rtDW . icn2tg3hl2 = - 1 ; } else { rtDW . icn2tg3hl2 = 0
; } rtB . ezjo2kpzef = muDoubleScalarMax ( hgbyo4at01 * ( real_T ) rtDW .
icn2tg3hl2 , rtDW . lgcrmtnzbq ) ; } if ( ssIsMajorTimeStep ( rtS ) ) {
adixqnkfhd = rtB . cnomiivfhs ; rtDW . ofvw1urmo2 = 0 ; if ( rtB . ezjo2kpzef
> rtB . cnomiivfhs ) { adixqnkfhd = rtB . ezjo2kpzef ; rtDW . ofvw1urmo2 = 1
; } rtB . cborkiagpq = adixqnkfhd ; } else { adixqnkfhd = rtB . cnomiivfhs ;
if ( rtDW . ofvw1urmo2 == 1 ) { adixqnkfhd = rtB . ezjo2kpzef ; } rtB .
cborkiagpq = adixqnkfhd ; } adrgpjrulp_idx_0 = gmhwb0q345_idx_0 -
adrgpjrulp_idx_0 ; hgbyo4at01 = adrgpjrulp_idx_0 * adrgpjrulp_idx_0 ;
adrgpjrulp_idx_0 = gmhwb0q345_idx_1 - adrgpjrulp_idx_1 ; hgbyo4at01 +=
adrgpjrulp_idx_0 * adrgpjrulp_idx_0 ; if ( ssIsMajorTimeStep ( rtS ) ) { if (
rtDW . f0ckmjw1gj != 0 ) { ssSetBlockStateForSolverChangedAtMajorStep ( rtS )
; rtDW . f0ckmjw1gj = 0 ; } rtB . d2rjutehif = muDoubleScalarSqrt (
hgbyo4at01 ) ; } else if ( hgbyo4at01 < 0.0 ) { rtB . d2rjutehif = -
muDoubleScalarSqrt ( muDoubleScalarAbs ( hgbyo4at01 ) ) ; rtDW . f0ckmjw1gj =
1 ; } else { rtB . d2rjutehif = muDoubleScalarSqrt ( hgbyo4at01 ) ; } rtB .
h32e0arsda = rtB . oog2f0orgs * rtB . jfrwj2ywep ; rtB . l43aesz3q0 = rtB .
pw553ih11r * rtB . jtzc3yh3vr ; rtB . e55n1mwom0 = 0.0 ; rtB . e55n1mwom0 +=
rtP . Mech0n [ 0 ] / rtP . Mech0d [ 0 ] * rtX . cizfoddkjl [ 0 ] ; rtB .
e55n1mwom0 += rtP . Mech0n [ 1 ] / rtP . Mech0d [ 0 ] * rtX . cizfoddkjl [ 1
] ; rtB . abmatz0jsq = rtP . BackEMF0 * rtB . e55n1mwom0 ; rtB . is2oky5nmn =
0.0 ; rtB . is2oky5nmn += rtP . Mech1n [ 0 ] / rtP . Mech1d [ 0 ] * rtX .
lunpvzrzl4 [ 0 ] ; rtB . is2oky5nmn += rtP . Mech1n [ 1 ] / rtP . Mech1d [ 0
] * rtX . lunpvzrzl4 [ 1 ] ; rtB . nb55jqhq34 = rtP . BackEMF1 * rtB .
is2oky5nmn ; rtB . gl55e1oxq3 = rtP . Sens0 * rtB . jvcbsan3fm ; rtB .
lntm0zfacy = rtP . FB0 * rtB . gl55e1oxq3 ; rtB . chgqwipbrj =
muDoubleScalarAtan ( rtB . h32e0arsda ) - rtB . lntm0zfacy ; rtB . ohehgsdsa5
= rtP . PID0 [ 2 ] * rtB . chgqwipbrj ; rtB . fycvf3ohxx = rtX . pds5dexq0c ;
rtB . kpbled4wwr = rtB . ohehgsdsa5 - rtB . fycvf3ohxx ; rtB . nrvbbkpqfy =
rtP . ControllerQ0_N * rtB . kpbled4wwr ; rtB . bwejbx3gz4 = rtP . PID0 [ 1 ]
* rtB . chgqwipbrj ; rtB . izwwnicbg1 = rtX . b5onyiwttn ; rtB . esaxa4ejop =
rtP . PID0 [ 0 ] * rtB . chgqwipbrj ; rtB . lp0vniw2vg = ( rtB . esaxa4ejop +
rtB . izwwnicbg1 ) + rtB . nrvbbkpqfy ; rtB . net2l52ebc = rtP . Sens1 * rtB
. ifywyvlyix ; rtB . jnetxfptgr = rtP . FB1 * rtB . net2l52ebc ; rtB .
d1asgjubos = muDoubleScalarAtan ( rtB . l43aesz3q0 ) - rtB . jnetxfptgr ; rtB
. pbnfjx04cq = rtP . PID1 [ 2 ] * rtB . d1asgjubos ; rtB . nsfmqq4us5 = rtX .
ftfth001j0 ; rtB . ipvn2dlajm = rtB . pbnfjx04cq - rtB . nsfmqq4us5 ; rtB .
eefrdns3vo = rtP . ControllerQ1_N * rtB . ipvn2dlajm ; rtB . a1vmpy24k5 = rtP
. PID1 [ 1 ] * rtB . d1asgjubos ; rtB . pkzwaw50et = rtX . lloaupur3b ; rtB .
iullwlukrq = rtP . PID1 [ 0 ] * rtB . d1asgjubos ; rtB . aljytqlhqv = ( rtB .
iullwlukrq + rtB . pkzwaw50et ) + rtB . eefrdns3vo ; rtB . bfla2pij1s = 0.0 ;
rtB . bfla2pij1s += rtP . Amp0n / rtP . Amp0d * rtB . lp0vniw2vg ; rtB .
nl1yr2gtpd = 0.0 ; rtB . nl1yr2gtpd += rtP . Amp1n / rtP . Amp1d * rtB .
aljytqlhqv ; if ( ssIsSampleHit ( rtS , 1 , 0 ) ) { { if ( ( rtDW .
gchzjejcu3 . AQHandles || rtDW . gchzjejcu3 . SlioLTF ) && ssGetLogOutput (
rtS ) ) { sdiSlioSdiWriteSignal ( rtDW . gchzjejcu3 . AQHandles , rtDW .
gchzjejcu3 . SlioLTF , 0 , ssGetTaskTime ( rtS , 1 ) , ( void * ) &
iekvwvtqfd ) ; } } { if ( ( rtDW . egn21ix41f . AQHandles || rtDW .
egn21ix41f . SlioLTF ) && ssGetLogOutput ( rtS ) ) { sdiSlioSdiWriteSignal (
rtDW . egn21ix41f . AQHandles , rtDW . egn21ix41f . SlioLTF , 0 ,
ssGetTaskTime ( rtS , 1 ) , ( void * ) & rtB . boq4gsls3l [ 0 ] ) ; } } { if
( ( rtDW . ge33tuv1zo . AQHandles || rtDW . ge33tuv1zo . SlioLTF ) &&
ssGetLogOutput ( rtS ) ) { sdiSlioSdiWriteSignal ( rtDW . ge33tuv1zo .
AQHandles , rtDW . ge33tuv1zo . SlioLTF , 0 , ssGetTaskTime ( rtS , 1 ) , (
void * ) & jzpkgjtrth ) ; } } } if ( ssIsMajorTimeStep ( rtS ) ) { rtDW .
kmlhhcf3ls = rtB . bfla2pij1s >= rtP . AmpSat0 ? 1 : rtB . bfla2pij1s > - rtP
. AmpSat0 ? 0 : - 1 ; rtDW . ersxnvaxzt = rtB . nl1yr2gtpd >= rtP . AmpSat1 ?
1 : rtB . nl1yr2gtpd > - rtP . AmpSat1 ? 0 : - 1 ; } rtB . dhlo5n33b5 = rtDW
. kmlhhcf3ls == 1 ? rtP . AmpSat0 : rtDW . kmlhhcf3ls == - 1 ? - rtP .
AmpSat0 : rtB . bfla2pij1s ; rtB . nimsz2eln4 = rtDW . ersxnvaxzt == 1 ? rtP
. AmpSat1 : rtDW . ersxnvaxzt == - 1 ? - rtP . AmpSat1 : rtB . nl1yr2gtpd ;
rtB . imugtlsrnt = rtB . nimsz2eln4 - rtB . nb55jqhq34 ; rtB . emcqf0ggw0 =
rtB . dhlo5n33b5 - rtB . abmatz0jsq ; rtB . iv32nbz1dr = rtP . TConst0 * rtB
. imv2femxvj ; rtB . d0itolxywz = rtB . iv32nbz1dr ; rtB . cnmmc5tlzm = rtP .
TConst1 * rtB . oqaiej1ofv ; UNUSED_PARAMETER ( tid ) ; } void MdlOutputsTID2
( int_T tid ) { rtB . jfrwj2ywep = 1.0 / rtP . Distance ; rtB . jtzc3yh3vr =
1.0 / rtP . Distance ; UNUSED_PARAMETER ( tid ) ; } void MdlUpdate ( int_T
tid ) { real_T * lastU ; if ( ssIsSampleHit ( rtS , 1 , 0 ) ) { rtDW .
edqnr03j4o [ 0 ] = rtB . boq4gsls3l [ 0 ] ; rtDW . edqnr03j4o [ 1 ] = rtB .
boq4gsls3l [ 1 ] ; rtDW . hi3zk3zli4 = rtB . cnomiivfhs ; rtDW . euclalwh11 =
rtB . d2rjutehif ; } if ( rtDW . beg153xvlk == ( rtInf ) ) { rtDW .
beg153xvlk = ssGetT ( rtS ) ; lastU = & rtDW . mcbn5gls5g ; } else if ( rtDW
. cnpublhlg5 == ( rtInf ) ) { rtDW . cnpublhlg5 = ssGetT ( rtS ) ; lastU = &
rtDW . h545t5oyoc ; } else if ( rtDW . beg153xvlk < rtDW . cnpublhlg5 ) {
rtDW . beg153xvlk = ssGetT ( rtS ) ; lastU = & rtDW . mcbn5gls5g ; } else {
rtDW . cnpublhlg5 = ssGetT ( rtS ) ; lastU = & rtDW . h545t5oyoc ; } * lastU
= rtB . mv5es2qqht ; if ( ssIsSampleHit ( rtS , 1 , 0 ) ) { rtDW . lgcrmtnzbq
= rtB . ezjo2kpzef ; } UNUSED_PARAMETER ( tid ) ; } void MdlUpdateTID2 (
int_T tid ) { UNUSED_PARAMETER ( tid ) ; } void MdlDerivatives ( void ) {
XDot * _rtXdot ; _rtXdot = ( ( XDot * ) ssGetdX ( rtS ) ) ; _rtXdot ->
ngucjqsbmh = 0.0 ; _rtXdot -> ngucjqsbmh += - rtP . Elec0d [ 1 ] / rtP .
Elec0d [ 0 ] * rtX . ngucjqsbmh ; _rtXdot -> ngucjqsbmh += rtB . emcqf0ggw0 ;
_rtXdot -> f1vfx1wka5 = 0.0 ; _rtXdot -> f1vfx1wka5 += - rtP . Elec1d [ 1 ] /
rtP . Elec1d [ 0 ] * rtX . f1vfx1wka5 ; _rtXdot -> f1vfx1wka5 += rtB .
imugtlsrnt ; _rtXdot -> gucrjwde45 = rtB . e55n1mwom0 ; _rtXdot -> mwebrdpwdq
= rtB . is2oky5nmn ; _rtXdot -> aijhcipwoo [ 0 ] = rtB . lkpyinhslc [ 0 ] ;
_rtXdot -> cizfoddkjl [ 0 ] = 0.0 ; _rtXdot -> cizfoddkjl [ 0 ] += - rtP .
Mech0d [ 1 ] / rtP . Mech0d [ 0 ] * rtX . cizfoddkjl [ 0 ] ; _rtXdot ->
aijhcipwoo [ 1 ] = rtB . lkpyinhslc [ 1 ] ; _rtXdot -> cizfoddkjl [ 1 ] = 0.0
; _rtXdot -> cizfoddkjl [ 0 ] += - rtP . Mech0d [ 2 ] / rtP . Mech0d [ 0 ] *
rtX . cizfoddkjl [ 1 ] ; _rtXdot -> cizfoddkjl [ 1 ] += rtX . cizfoddkjl [ 0
] ; _rtXdot -> cizfoddkjl [ 0 ] += rtB . d0itolxywz ; _rtXdot -> lunpvzrzl4 [
0 ] = 0.0 ; _rtXdot -> lunpvzrzl4 [ 0 ] += - rtP . Mech1d [ 1 ] / rtP .
Mech1d [ 0 ] * rtX . lunpvzrzl4 [ 0 ] ; _rtXdot -> lunpvzrzl4 [ 1 ] = 0.0 ;
_rtXdot -> lunpvzrzl4 [ 0 ] += - rtP . Mech1d [ 2 ] / rtP . Mech1d [ 0 ] *
rtX . lunpvzrzl4 [ 1 ] ; _rtXdot -> lunpvzrzl4 [ 1 ] += rtX . lunpvzrzl4 [ 0
] ; _rtXdot -> lunpvzrzl4 [ 0 ] += rtB . cnmmc5tlzm ; _rtXdot -> pds5dexq0c =
rtB . nrvbbkpqfy ; _rtXdot -> b5onyiwttn = rtB . bwejbx3gz4 ; _rtXdot ->
ftfth001j0 = rtB . eefrdns3vo ; _rtXdot -> lloaupur3b = rtB . a1vmpy24k5 ; }
void MdlProjection ( void ) { } void MdlZeroCrossings ( void ) { real_T tmp ;
ZCV * _rtZCSV ; _rtZCSV = ( ( ZCV * ) ssGetSolverZcSignalVector ( rtS ) ) ;
_rtZCSV -> bukeava42g = rtB . py2taxmodw [ 0 ] - rtP . NomI0 ; _rtZCSV ->
m0oxry41b5 = rtB . py2taxmodw [ 1 ] - rtP . NomI1 ; _rtZCSV -> invnk02rur [ 0
] = rtB . imv2femxvj ; _rtZCSV -> invnk02rur [ 1 ] = rtB . oqaiej1ofv ; tmp =
rtB . lkpyinhslc [ 0 ] ; if ( rtDW . jm5cialsp2 [ 0 ] == 1 ) { tmp = rtB .
grvfia1xdu [ 0 ] ; } _rtZCSV -> afsh3g3tfz [ 0 ] = muDoubleScalarMax ( rtB .
grvfia1xdu [ 0 ] , rtB . lkpyinhslc [ 0 ] ) - tmp ; tmp = rtB . lkpyinhslc [
1 ] ; if ( rtDW . jm5cialsp2 [ 1 ] == 1 ) { tmp = rtB . grvfia1xdu [ 1 ] ; }
_rtZCSV -> afsh3g3tfz [ 1 ] = muDoubleScalarMax ( rtB . grvfia1xdu [ 1 ] ,
rtB . lkpyinhslc [ 1 ] ) - tmp ; _rtZCSV -> p2shvbu40q = rtB . boq4gsls3l [ 0
] - rtP . StallI0 ; _rtZCSV -> o2dm1ntt40 = rtB . boq4gsls3l [ 1 ] - rtP .
StallI1 ; _rtZCSV -> i53gputbkx = rtB . ciuxkrwmvl - rtP . JntSat1 ; _rtZCSV
-> hmtnudz2kc = rtB . ciuxkrwmvl - ( - rtP . JntSat1 ) ; _rtZCSV ->
cu1bj5dhux = rtB . fl4jmkviqg - rtP . CompareToConstant_const ; if ( rtB .
jvi3aujz2y > rtB . d0ywb4iifr ) { if ( rtDW . njpfo0txij == 0 ) { _rtZCSV ->
imyyq1fqyh = rtB . jvi3aujz2y - rtB . jvi3aujz2y ; } else { _rtZCSV ->
imyyq1fqyh = rtB . jvi3aujz2y - rtB . d0ywb4iifr ; } } else if ( rtDW .
njpfo0txij == 0 ) { _rtZCSV -> imyyq1fqyh = rtB . d0ywb4iifr - rtB .
jvi3aujz2y ; } else { _rtZCSV -> imyyq1fqyh = rtB . d0ywb4iifr - rtB .
d0ywb4iifr ; } _rtZCSV -> kshqrlmyl0 = rtB . kqxihv51s2 ; _rtZCSV ->
goizezbp5o = rtB . hwswxdjz2o ; if ( rtB . cnomiivfhs > rtB . ezjo2kpzef ) {
if ( rtDW . ofvw1urmo2 == 0 ) { _rtZCSV -> nwjyd3eond = rtB . cnomiivfhs -
rtB . cnomiivfhs ; } else { _rtZCSV -> nwjyd3eond = rtB . cnomiivfhs - rtB .
ezjo2kpzef ; } } else if ( rtDW . ofvw1urmo2 == 0 ) { _rtZCSV -> nwjyd3eond =
rtB . ezjo2kpzef - rtB . cnomiivfhs ; } else { _rtZCSV -> nwjyd3eond = rtB .
ezjo2kpzef - rtB . ezjo2kpzef ; } _rtZCSV -> cz5sbsx2wk = rtB . bfla2pij1s -
rtP . AmpSat0 ; _rtZCSV -> btiqwemaem = rtB . bfla2pij1s - ( - rtP . AmpSat0
) ; _rtZCSV -> dbdjaizn11 = rtB . nl1yr2gtpd - rtP . AmpSat1 ; _rtZCSV ->
m0mliu0lgx = rtB . nl1yr2gtpd - ( - rtP . AmpSat1 ) ; } void MdlTerminate (
void ) { { if ( rtDW . ihyfkimqv5 . AQHandles ) { sdiTerminateStreaming ( &
rtDW . ihyfkimqv5 . AQHandles ) ; } if ( rtDW . ihyfkimqv5 . SlioLTF ) {
rtwDestructAccessorPointer ( rtDW . ihyfkimqv5 . SlioLTF ) ; } } { if ( rtDW
. gchzjejcu3 . AQHandles ) { sdiTerminateStreaming ( & rtDW . gchzjejcu3 .
AQHandles ) ; } if ( rtDW . gchzjejcu3 . SlioLTF ) {
rtwDestructAccessorPointer ( rtDW . gchzjejcu3 . SlioLTF ) ; } } { if ( rtDW
. egn21ix41f . AQHandles ) { sdiTerminateStreaming ( & rtDW . egn21ix41f .
AQHandles ) ; } if ( rtDW . egn21ix41f . SlioLTF ) {
rtwDestructAccessorPointer ( rtDW . egn21ix41f . SlioLTF ) ; } } { if ( rtDW
. ge33tuv1zo . AQHandles ) { sdiTerminateStreaming ( & rtDW . ge33tuv1zo .
AQHandles ) ; } if ( rtDW . ge33tuv1zo . SlioLTF ) {
rtwDestructAccessorPointer ( rtDW . ge33tuv1zo . SlioLTF ) ; } } if (
rt_slioCatalogue ( ) != ( NULL ) ) { void * * slioCatalogueAddr =
rt_slioCatalogueAddr ( ) ; rtwSaveDatasetsToMatFile (
rtwGetPointerFromUniquePtr ( rt_slioCatalogue ( ) ) ,
rt_GetMatSigstreamLoggingFileName ( ) ) ; rtwTerminateSlioCatalogue (
slioCatalogueAddr ) ; * slioCatalogueAddr = NULL ; } } void
MdlInitializeSizes ( void ) { ssSetNumContStates ( rtS , 14 ) ;
ssSetNumPeriodicContStates ( rtS , 0 ) ; ssSetNumY ( rtS , 0 ) ; ssSetNumU (
rtS , 0 ) ; ssSetDirectFeedThrough ( rtS , 0 ) ; ssSetNumSampleTimes ( rtS ,
2 ) ; ssSetNumBlocks ( rtS , 111 ) ; ssSetNumBlockIO ( rtS , 66 ) ;
ssSetNumBlockParams ( rtS , 65 ) ; } void MdlInitializeSampleTimes ( void ) {
ssSetSampleTime ( rtS , 0 , 0.0 ) ; ssSetSampleTime ( rtS , 1 , 0.0 ) ;
ssSetOffsetTime ( rtS , 0 , 0.0 ) ; ssSetOffsetTime ( rtS , 1 , 1.0 ) ; }
void raccel_set_checksum ( ) { ssSetChecksumVal ( rtS , 0 , 2691800636U ) ;
ssSetChecksumVal ( rtS , 1 , 3910809806U ) ; ssSetChecksumVal ( rtS , 2 ,
2654587771U ) ; ssSetChecksumVal ( rtS , 3 , 2193301241U ) ; }
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
laser_InitializeDataMapInfo ( ) ; ssSetIsRapidAcceleratorActive ( rtS , true
) ; ssSetRootSS ( rtS , rtS ) ; ssSetVersion ( rtS , SIMSTRUCT_VERSION_LEVEL2
) ; ssSetModelName ( rtS , "laser" ) ; ssSetPath ( rtS , "laser" ) ;
ssSetTStart ( rtS , 0.0 ) ; ssSetTFinal ( rtS , 10.0 ) ; { static RTWLogInfo
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
ssSolverInfo slvrInfo ; static boolean_T contStatesDisabled [ 14 ] ; static
real_T absTol [ 14 ] = { 1.0E-6 , 1.0E-6 , 1.0E-6 , 1.0E-6 , 1.0E-6 , 1.0E-6
, 1.0E-6 , 1.0E-6 , 1.0E-6 , 1.0E-6 , 1.0E-6 , 1.0E-6 , 1.0E-6 , 1.0E-6 } ;
static uint8_T absTolControl [ 14 ] = { 0U , 0U , 0U , 0U , 0U , 0U , 0U , 0U
, 0U , 0U , 0U , 0U , 0U , 0U } ; static uint8_T zcAttributes [ 19 ] = { (
ZC_EVENT_ALL ) , ( ZC_EVENT_ALL ) , ( ZC_EVENT_ALL ) , ( ZC_EVENT_ALL ) , (
ZC_EVENT_ALL ) , ( ZC_EVENT_ALL ) , ( ZC_EVENT_ALL ) , ( ZC_EVENT_ALL ) , (
ZC_EVENT_ALL ) , ( ZC_EVENT_ALL ) , ( ZC_EVENT_ALL ) , ( ZC_EVENT_ALL ) , (
ZC_EVENT_ALL ) , ( ZC_EVENT_ALL ) , ( ZC_EVENT_ALL ) , ( ZC_EVENT_ALL ) , (
ZC_EVENT_ALL ) , ( ZC_EVENT_ALL ) , ( ZC_EVENT_ALL ) } ; ssSetSolverRelTol (
rtS , 0.001 ) ; ssSetStepSize ( rtS , 0.0 ) ; ssSetMinStepSize ( rtS , 0.0 )
; ssSetMaxNumMinSteps ( rtS , - 1 ) ; ssSetMinStepViolatedError ( rtS , 0 ) ;
ssSetMaxStepSize ( rtS , 0.2 ) ; ssSetSolverMaxOrder ( rtS , 5 ) ;
ssSetSolverRefineFactor ( rtS , 1 ) ; ssSetOutputTimes ( rtS , ( NULL ) ) ;
ssSetNumOutputTimes ( rtS , 0 ) ; ssSetOutputTimesOnly ( rtS , 0 ) ;
ssSetOutputTimesIndex ( rtS , 0 ) ; ssSetZCCacheNeedsReset ( rtS , 1 ) ;
ssSetDerivCacheNeedsReset ( rtS , 0 ) ; ssSetNumNonContDerivSigInfos ( rtS ,
0 ) ; ssSetNonContDerivSigInfos ( rtS , ( NULL ) ) ; ssSetSolverInfo ( rtS ,
& slvrInfo ) ; ssSetSolverName ( rtS , "ode15s" ) ; ssSetVariableStepSolver (
rtS , 1 ) ; ssSetSolverConsistencyChecking ( rtS , 0 ) ;
ssSetSolverAdaptiveZcDetection ( rtS , 0 ) ; ssSetSolverRobustResetMethod (
rtS , 0 ) ; ssSetAbsTolVector ( rtS , absTol ) ; ssSetAbsTolControlVector (
rtS , absTolControl ) ; ssSetSolverAbsTol_Obsolete ( rtS , absTol ) ;
ssSetSolverAbsTolControl_Obsolete ( rtS , absTolControl ) ;
ssSetSolverStateProjection ( rtS , 0 ) ; ssSetSolverMassMatrixType ( rtS , (
ssMatrixType ) 0 ) ; ssSetSolverMassMatrixNzMax ( rtS , 0 ) ;
ssSetModelOutputs ( rtS , MdlOutputs ) ; ssSetModelLogData ( rtS ,
rt_UpdateTXYLogVars ) ; ssSetModelLogDataIfInInterval ( rtS ,
rt_UpdateTXXFYLogVars ) ; ssSetModelUpdate ( rtS , MdlUpdate ) ;
ssSetModelDerivatives ( rtS , MdlDerivatives ) ; ssSetSolverZcSignalAttrib (
rtS , zcAttributes ) ; ssSetSolverNumZcSignals ( rtS , 19 ) ;
ssSetModelZeroCrossings ( rtS , MdlZeroCrossings ) ;
ssSetSolverConsecutiveZCsStepRelTol ( rtS , 2.8421709430404007E-13 ) ;
ssSetSolverMaxConsecutiveZCs ( rtS , 1000 ) ; ssSetSolverConsecutiveZCsError
( rtS , 2 ) ; ssSetSolverMaskedZcDiagnostic ( rtS , 1 ) ;
ssSetSolverIgnoredZcDiagnostic ( rtS , 1 ) ; ssSetSolverMaxConsecutiveMinStep
( rtS , 1 ) ; ssSetSolverShapePreserveControl ( rtS , 2 ) ; ssSetTNextTid (
rtS , INT_MIN ) ; ssSetTNext ( rtS , rtMinusInf ) ; ssSetSolverNeedsReset (
rtS ) ; ssSetNumNonsampledZCs ( rtS , 19 ) ; ssSetContStateDisabled ( rtS ,
contStatesDisabled ) ; ssSetSolverMaxConsecutiveMinStep ( rtS , 1 ) ; }
ssSetChecksumVal ( rtS , 0 , 2691800636U ) ; ssSetChecksumVal ( rtS , 1 ,
3910809806U ) ; ssSetChecksumVal ( rtS , 2 , 2654587771U ) ; ssSetChecksumVal
( rtS , 3 , 2193301241U ) ; { static const sysRanDType rtAlwaysEnabled =
SUBSYS_RAN_BC_ENABLE ; static RTWExtModeInfo rt_ExtModeInfo ; static const
sysRanDType * systemRan [ 3 ] ; gblRTWExtModeInfo = & rt_ExtModeInfo ;
ssSetRTWExtModeInfo ( rtS , & rt_ExtModeInfo ) ;
rteiSetSubSystemActiveVectorAddresses ( & rt_ExtModeInfo , systemRan ) ;
systemRan [ 0 ] = & rtAlwaysEnabled ; systemRan [ 1 ] = & rtAlwaysEnabled ;
systemRan [ 2 ] = & rtAlwaysEnabled ; rteiSetModelMappingInfoPtr (
ssGetRTWExtModeInfo ( rtS ) , & ssGetModelMappingInfo ( rtS ) ) ;
rteiSetChecksumsPtr ( ssGetRTWExtModeInfo ( rtS ) , ssGetChecksums ( rtS ) )
; rteiSetTPtr ( ssGetRTWExtModeInfo ( rtS ) , ssGetTPtr ( rtS ) ) ; } return
rtS ; }
#if defined(_MSC_VER)
#pragma optimize( "", on )
#endif
const int_T gblParameterTuningTid = 2 ; void MdlOutputsParameterSampleTime (
int_T tid ) { MdlOutputsTID2 ( tid ) ; }
