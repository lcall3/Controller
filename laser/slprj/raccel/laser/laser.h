#include "__cf_laser.h"
#ifndef RTW_HEADER_laser_h_
#define RTW_HEADER_laser_h_
#include <stddef.h>
#include <string.h>
#include "rtw_modelmap.h"
#ifndef laser_COMMON_INCLUDES_
#define laser_COMMON_INCLUDES_
#include <stdlib.h>
#include "sl_AsyncioQueue/AsyncioQueueCAPI.h"
#include "simtarget/slSimTgtSigstreamRTW.h"
#include "simtarget/slSimTgtSlioCoreRTW.h"
#include "simtarget/slSimTgtSlioClientsRTW.h"
#include "simtarget/slSimTgtSlioSdiRTW.h"
#include "rtwtypes.h"
#include "sigstream_rtw.h"
#include "simstruc.h"
#include "fixedpoint.h"
#include "raccel.h"
#include "slsv_diagnostic_codegen_c_api.h"
#include "rt_logging.h"
#include "dt_info.h"
#include "ext_work.h"
#endif
#include "laser_types.h"
#include "multiword_types.h"
#include "rtGetInf.h"
#include "rt_nonfinite.h"
#include "mwmathutil.h"
#include "rt_defines.h"
#define MODEL_NAME laser
#define NSAMPLE_TIMES (3) 
#define NINPUTS (0)       
#define NOUTPUTS (0)     
#define NBLOCKIO (66) 
#define NUM_ZC_EVENTS (0) 
#ifndef NCSTATES
#define NCSTATES (14)   
#elif NCSTATES != 14
#error Invalid specification of NCSTATES defined in compiler command
#endif
#ifndef rtmGetDataMapInfo
#define rtmGetDataMapInfo(rtm) (*rt_dataMapInfoPtr)
#endif
#ifndef rtmSetDataMapInfo
#define rtmSetDataMapInfo(rtm, val) (rt_dataMapInfoPtr = &val)
#endif
#ifndef IN_RACCEL_MAIN
#endif
typedef struct { real_T hbmlhug0bx [ 2 ] ; real_T py2taxmodw [ 2 ] ; real_T
imv2femxvj ; real_T oqaiej1ofv ; real_T lkpyinhslc [ 2 ] ; real_T grvfia1xdu
[ 2 ] ; real_T boq4gsls3l [ 2 ] ; real_T jvcbsan3fm ; real_T muyocrskli ;
real_T ciuxkrwmvl ; real_T ifywyvlyix ; real_T df2qekfpqc ; real_T fl4jmkviqg
; real_T oog2f0orgs ; real_T pw553ih11r ; real_T jvi3aujz2y ; real_T
d0ywb4iifr ; real_T cnomiivfhs ; real_T mv5es2qqht ; real_T kqxihv51s2 ;
real_T hwswxdjz2o ; real_T ezjo2kpzef ; real_T cborkiagpq ; real_T d2rjutehif
; real_T jfrwj2ywep ; real_T jtzc3yh3vr ; real_T h32e0arsda ; real_T
l43aesz3q0 ; real_T e55n1mwom0 ; real_T abmatz0jsq ; real_T is2oky5nmn ;
real_T nb55jqhq34 ; real_T gl55e1oxq3 ; real_T lntm0zfacy ; real_T chgqwipbrj
; real_T ohehgsdsa5 ; real_T fycvf3ohxx ; real_T kpbled4wwr ; real_T
nrvbbkpqfy ; real_T bwejbx3gz4 ; real_T izwwnicbg1 ; real_T esaxa4ejop ;
real_T lp0vniw2vg ; real_T net2l52ebc ; real_T jnetxfptgr ; real_T d1asgjubos
; real_T pbnfjx04cq ; real_T nsfmqq4us5 ; real_T ipvn2dlajm ; real_T
eefrdns3vo ; real_T a1vmpy24k5 ; real_T pkzwaw50et ; real_T iullwlukrq ;
real_T aljytqlhqv ; real_T bfla2pij1s ; real_T nl1yr2gtpd ; real_T dhlo5n33b5
; real_T nimsz2eln4 ; real_T imugtlsrnt ; real_T emcqf0ggw0 ; real_T
iv32nbz1dr ; real_T d0itolxywz ; real_T cnmmc5tlzm ; real_T iik1kdrydb [ 2 ]
; real_T imnwnfgdra [ 2 ] ; boolean_T nblejb4ulo ; } B ; typedef struct {
real_T edqnr03j4o [ 2 ] ; real_T hi3zk3zli4 ; real_T euclalwh11 ; real_T
beg153xvlk ; real_T mcbn5gls5g ; real_T cnpublhlg5 ; real_T h545t5oyoc ;
real_T lgcrmtnzbq ; struct { void * AQHandles ; void * SlioLTF ; } ihyfkimqv5
; struct { void * LoggedData ; } bv0zhgyp5k ; struct { void * AQHandles ;
void * SlioLTF ; } gchzjejcu3 ; struct { void * AQHandles ; void * SlioLTF ;
} egn21ix41f ; struct { void * AQHandles ; void * SlioLTF ; } ge33tuv1zo ;
int_T frnbyss1yt [ 2 ] ; int_T jm5cialsp2 [ 2 ] ; int_T hoivdwve1d ; int_T
njpfo0txij ; int_T d1vwwr4s1r ; int_T icn2tg3hl2 ; int_T ofvw1urmo2 ; int_T
kmlhhcf3ls ; int_T ersxnvaxzt ; int8_T lufveoz2ya ; int8_T fnfpq0xxhm ;
int8_T f0ckmjw1gj ; boolean_T kylvmh4w13 ; boolean_T kbqz5luorh ; boolean_T
ekvz540vhq ; boolean_T eplu0qlvkz ; boolean_T ih4snyf23z ; } DW ; typedef
struct { real_T aijhcipwoo [ 2 ] ; real_T ngucjqsbmh ; real_T f1vfx1wka5 ;
real_T gucrjwde45 ; real_T mwebrdpwdq ; real_T cizfoddkjl [ 2 ] ; real_T
lunpvzrzl4 [ 2 ] ; real_T pds5dexq0c ; real_T b5onyiwttn ; real_T ftfth001j0
; real_T lloaupur3b ; } X ; typedef struct { real_T aijhcipwoo [ 2 ] ; real_T
ngucjqsbmh ; real_T f1vfx1wka5 ; real_T gucrjwde45 ; real_T mwebrdpwdq ;
real_T cizfoddkjl [ 2 ] ; real_T lunpvzrzl4 [ 2 ] ; real_T pds5dexq0c ;
real_T b5onyiwttn ; real_T ftfth001j0 ; real_T lloaupur3b ; } XDot ; typedef
struct { boolean_T aijhcipwoo [ 2 ] ; boolean_T ngucjqsbmh ; boolean_T
f1vfx1wka5 ; boolean_T gucrjwde45 ; boolean_T mwebrdpwdq ; boolean_T
cizfoddkjl [ 2 ] ; boolean_T lunpvzrzl4 [ 2 ] ; boolean_T pds5dexq0c ;
boolean_T b5onyiwttn ; boolean_T ftfth001j0 ; boolean_T lloaupur3b ; } XDis ;
typedef struct { real_T aijhcipwoo [ 2 ] ; real_T ngucjqsbmh ; real_T
f1vfx1wka5 ; real_T gucrjwde45 ; real_T mwebrdpwdq ; real_T cizfoddkjl [ 2 ]
; real_T lunpvzrzl4 [ 2 ] ; real_T pds5dexq0c ; real_T b5onyiwttn ; real_T
ftfth001j0 ; real_T lloaupur3b ; } CStateAbsTol ; typedef struct { real_T
bukeava42g ; real_T m0oxry41b5 ; real_T invnk02rur [ 2 ] ; real_T afsh3g3tfz
[ 2 ] ; real_T p2shvbu40q ; real_T o2dm1ntt40 ; real_T i53gputbkx ; real_T
hmtnudz2kc ; real_T cu1bj5dhux ; real_T imyyq1fqyh ; real_T kshqrlmyl0 ;
real_T goizezbp5o ; real_T nwjyd3eond ; real_T cz5sbsx2wk ; real_T btiqwemaem
; real_T dbdjaizn11 ; real_T m0mliu0lgx ; } ZCV ; typedef struct {
rtwCAPI_ModelMappingInfo mmi ; } DataMapInfo ; struct P_ { real_T Amp0d ;
real_T Amp0n ; real_T Amp1d ; real_T Amp1n ; real_T AmpSat0 ; real_T AmpSat1
; real_T BackEMF0 ; real_T BackEMF1 ; real_T Distance ; real_T Elec0d [ 2 ] ;
real_T Elec0n ; real_T Elec1d [ 2 ] ; real_T Elec1n ; real_T FB0 ; real_T FB1
; real_T JntSat1 ; real_T Mech0d [ 3 ] ; real_T Mech0n [ 2 ] ; real_T Mech1d
[ 3 ] ; real_T Mech1n [ 2 ] ; real_T NomI0 ; real_T NomI1 ; real_T PID0 [ 3 ]
; real_T PID1 [ 3 ] ; real_T Sens0 ; real_T Sens1 ; real_T StallI0 ; real_T
StallI1 ; real_T TConst0 ; real_T TConst1 ; real_T ControllerQ0_N ; real_T
ControllerQ1_N ; real_T CompareToConstant_const ; real_T Integrator_IC ;
real_T Memory2_InitialCondition ; real_T IntegratorQ0_IC ; real_T
IntegratorQ1_IC ; real_T SineWave_Amp ; real_T SineWave_Bias ; real_T
SineWave_Freq ; real_T SineWave_Phase ; real_T SineWave1_Amp ; real_T
SineWave1_Bias ; real_T SineWave1_Freq ; real_T SineWave1_Phase ; real_T
Memory1_InitialCondition ; real_T Memory3_InitialCondition ; real_T
Memory4_InitialCondition ; real_T Filter_IC ; real_T Integrator_IC_itl5ymsq54
; real_T Filter_IC_kyn4kgm3f4 ; real_T Integrator_IC_bz3z1grlau ; uint8_T
Constant_Value ; } ; extern const char * RT_MEMORY_ALLOCATION_ERROR ; extern
B rtB ; extern X rtX ; extern DW rtDW ; extern P rtP ; extern const
rtwCAPI_ModelMappingStaticInfo * laser_GetCAPIStaticMap ( void ) ; extern
SimStruct * const rtS ; extern const int_T gblNumToFiles ; extern const int_T
gblNumFrFiles ; extern const int_T gblNumFrWksBlocks ; extern rtInportTUtable
* gblInportTUtables ; extern const char * gblInportFileName ; extern const
int_T gblNumRootInportBlks ; extern const int_T gblNumModelInputs ; extern
const int_T gblInportDataTypeIdx [ ] ; extern const int_T gblInportDims [ ] ;
extern const int_T gblInportComplex [ ] ; extern const int_T
gblInportInterpoFlag [ ] ; extern const int_T gblInportContinuous [ ] ;
extern const int_T gblParameterTuningTid ; extern size_t gblCurrentSFcnIdx ;
extern DataMapInfo * rt_dataMapInfoPtr ; extern rtwCAPI_ModelMappingInfo *
rt_modelMapInfoPtr ; void MdlOutputs ( int_T tid ) ; void
MdlOutputsParameterSampleTime ( int_T tid ) ; void MdlUpdate ( int_T tid ) ;
void MdlTerminate ( void ) ; void MdlInitializeSizes ( void ) ; void
MdlInitializeSampleTimes ( void ) ; SimStruct * raccel_register_model ( void
) ;
#endif
