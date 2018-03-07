#include "__cf_motor.h"
#ifndef RTW_HEADER_motor_h_
#define RTW_HEADER_motor_h_
#include <stddef.h>
#include <string.h>
#include "rtw_modelmap.h"
#ifndef motor_COMMON_INCLUDES_
#define motor_COMMON_INCLUDES_
#include <stdlib.h>
#include "sl_AsyncioQueue/AsyncioQueueCAPI.h"
#include "simtarget/slSimTgtSigstreamRTW.h"
#include "simtarget/slSimTgtSlioCoreRTW.h"
#include "simtarget/slSimTgtSlioClientsRTW.h"
#include "simtarget/slSimTgtSlioSdiRTW.h"
#include "rtwtypes.h"
#include "sl_fileio_rtw.h"
#include "simtarget/slSimTgtSlFileioRTW.h"
#include "sigstream_rtw.h"
#include "simstruc.h"
#include "fixedpoint.h"
#include "raccel.h"
#include "slsv_diagnostic_codegen_c_api.h"
#include "rt_logging.h"
#include "dt_info.h"
#include "ext_work.h"
#endif
#include "motor_types.h"
#include "multiword_types.h"
#include "mwmathutil.h"
#include "rt_defines.h"
#include "rtGetInf.h"
#include "rt_nonfinite.h"
#define MODEL_NAME motor
#define NSAMPLE_TIMES (4) 
#define NINPUTS (0)       
#define NOUTPUTS (0)     
#define NBLOCKIO (74) 
#define NUM_ZC_EVENTS (0) 
#ifndef NCSTATES
#define NCSTATES (17)   
#elif NCSTATES != 17
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
typedef struct { real_T ioc0okmkmy ; real_T o5y1y4cmrq ; real_T anujv4qdwd ;
real_T d3uyq13rzr ; real_T hjl5biokwy ; real_T i2zgpmdtdd ; real_T j1d4ade1zr
; real_T hnoyfag32g ; real_T agiv5am4pg ; real_T gmjwvr4my1 ; real_T
bs4j1hqktx ; real_T gterhc2ycg ; real_T jqe1l2xedg ; real_T jdxhpskhxu ;
real_T dn5v5kwhgm ; real_T jgwwnwtolk ; real_T amsfxvim15 ; real_T dngwxi52p3
; real_T paygzk0zoc ; real_T nkhyo2j0jl ; real_T no3lkd1xft ; real_T
el2gn1lphk ; real_T btapnh3csw ; real_T fhsc2gicgw ; real_T k4ktntecy5 ;
real_T e1pup3cj2f ; real_T ou2ycdjzh0 ; real_T o1ro1rhovm ; real_T puti2xcwwj
; real_T mtjjfm5fkq ; real_T bqokd1dwue ; real_T c133a0jqdk ; real_T
i51k3nx1do ; real_T n014xvirka ; real_T gucmiu55ed ; real_T m2egujefvv ;
real_T ozd5y1bdbm ; real_T l2d0v0tkwo ; real_T gjaaa2fhno ; real_T ccn2pszgjr
; real_T ke4p3coxhb ; real_T gxpiulydd2 ; real_T odkwwsipfi ; real_T
lksfqnpvfh ; real_T obo5lyqljg ; real_T gmkdc4mlzx ; real_T nv3h1alees ;
real_T fjewmqeu3b ; real_T etljz0mm2f ; real_T biwfzm5zhf ; real_T ntrwuhfs2g
; real_T g5rilccwnf ; real_T ciip4hb2p2 ; real_T f3xnhsznvk ; real_T
awmqggonyb ; real_T i2ml1fewle ; real_T eixzkkukbm ; real_T bnpnp05c3l ;
real_T cjp5mog4yq ; real_T jrm53acbhq ; real_T fixgevc5xe ; real_T lul5450swo
; real_T brgflil51h ; real_T jaj4esgdh0 ; real_T ioesu1dalb ; real_T
hxxkhd0gkz ; real_T kta0dglp1y ; real_T o3wu3v2g2b ; real_T ijsvvv0me4 ;
real_T kx4hloeszq ; boolean_T hryw525bko ; boolean_T lm0riqbmwp ; boolean_T
emy34hfzxp ; boolean_T avhiv2ojkj ; } B ; typedef struct { real_T jhudklf0yp
; real_T b2ftxry5zj ; struct { void * LoggedData ; } k2x5bpwds1 ; struct {
void * LoggedData ; } dqynkooqdd ; struct { void * LoggedData ; } ac3jpaqlsx
; struct { void * AQHandles ; void * SlioLTF ; } oc5c35nsjw ; struct { void *
LoggedData ; } gs4qgjd0pq ; struct { void * LoggedData ; } hxsublhkma ;
struct { void * LoggedData ; } o2qr3etmsw ; struct { void * LoggedData ; }
gvwjgwsvp4 ; struct { void * AQHandles ; void * SlioLTF ; } oy51qzwlsb ;
struct { void * AQHandles ; void * SlioLTF ; } odasxv14ku ; struct { void *
AQHandles ; void * SlioLTF ; } ix54ulvqvm ; struct { void * AQHandles ; void
* SlioLTF ; } jpmbni14kg ; struct { void * AQHandles ; void * SlioLTF ; }
ksnq4jprhj ; struct { void * AQHandles ; void * SlioLTF ; } bahcjcb1oc ;
struct { void * LoggedData ; } mukcwbq3ix ; struct { void * LoggedData ; }
hztccx0mly ; struct { void * LoggedData ; } hhe551hq4b ; struct { void *
LoggedData ; } iarjtt15q1 ; struct { void * LoggedData ; } ofevtcfiuw ;
struct { void * FilePtr ; } oqnegpzh1g ; struct { void * LoggedData ; }
copwekyj5z ; struct { void * LoggedData ; } lh1ujktmyi ; struct { void *
AQHandles ; void * SlioLTF ; } e3mw3kxdbw ; struct { void * AQHandles ; void
* SlioLTF ; } lltjwuok3g ; struct { void * AQHandles ; void * SlioLTF ; }
grojl3nk3g ; struct { void * FilePtr ; } lcl4opl5jx ; struct { void * FilePtr
; } lrc3gfcuvu ; struct { int_T Count ; int_T Decimation ; } j1xa3hpons ;
struct { int_T Count ; int_T Decimation ; } pjbkr2i3xx ; struct { int_T Count
; int_T Decimation ; } o51b0uerqu ; int_T if1ncvemx1 ; int_T pol4d4okmy ;
int_T fwwxv0t4om ; int_T mcsw1g0pr4 ; int_T ifrsgr5d25 ; int_T p4il5t3tsl ;
int_T l2sav3arsj ; int_T hnqwxnzjee ; int_T f3t0nzed5p ; int_T id1uld5v45 ;
int_T gjgazova4y ; int_T m0qklhvna2 ; int_T f2vrqerrls ; int_T lnlaljtbyn ;
int_T ep2uw1gbbk ; boolean_T abahn02ksw ; boolean_T dv104ugpzo ; boolean_T
dzorqaujrj ; boolean_T pjivo2ki1n ; boolean_T nqjspphkim ; } DW ; typedef
struct { real_T nvaocs00bc ; real_T pfcrbgvmdb ; real_T mjgnwkqw0t ; real_T
o2vdlc3lwj ; real_T lgupwhixdz ; real_T f3greldmrk [ 2 ] ; real_T bkgokwpcki
; real_T igwsihwpdp [ 2 ] ; real_T puo0nzqs35 ; real_T f3s5lse3uq ; real_T
hcazinuy1s ; real_T av5owbi5i4 ; real_T dihsnra40r ; real_T fkehg4zumr [ 2 ]
; } X ; typedef struct { real_T nvaocs00bc ; real_T pfcrbgvmdb ; real_T
mjgnwkqw0t ; real_T o2vdlc3lwj ; real_T lgupwhixdz ; real_T f3greldmrk [ 2 ]
; real_T bkgokwpcki ; real_T igwsihwpdp [ 2 ] ; real_T puo0nzqs35 ; real_T
f3s5lse3uq ; real_T hcazinuy1s ; real_T av5owbi5i4 ; real_T dihsnra40r ;
real_T fkehg4zumr [ 2 ] ; } XDot ; typedef struct { boolean_T nvaocs00bc ;
boolean_T pfcrbgvmdb ; boolean_T mjgnwkqw0t ; boolean_T o2vdlc3lwj ;
boolean_T lgupwhixdz ; boolean_T f3greldmrk [ 2 ] ; boolean_T bkgokwpcki ;
boolean_T igwsihwpdp [ 2 ] ; boolean_T puo0nzqs35 ; boolean_T f3s5lse3uq ;
boolean_T hcazinuy1s ; boolean_T av5owbi5i4 ; boolean_T dihsnra40r ;
boolean_T fkehg4zumr [ 2 ] ; } XDis ; typedef struct { real_T nvaocs00bc ;
real_T pfcrbgvmdb ; real_T mjgnwkqw0t ; real_T o2vdlc3lwj ; real_T lgupwhixdz
; real_T f3greldmrk [ 2 ] ; real_T bkgokwpcki ; real_T igwsihwpdp [ 2 ] ;
real_T puo0nzqs35 ; real_T f3s5lse3uq ; real_T hcazinuy1s ; real_T av5owbi5i4
; real_T dihsnra40r ; real_T fkehg4zumr [ 2 ] ; } CStateAbsTol ; typedef
struct { real_T d4cfarnuxg ; real_T dl2rec3iq5 ; real_T kvph4uuxhw ; real_T
ed2ukm5fft ; real_T linbijbzri ; real_T m5zd1wh33t ; real_T a3wuanjgmk ;
real_T js12ctyuwj ; real_T d3nt5octq5 ; real_T p0h3fuy3y5 ; real_T pcw4qfr235
; real_T gai1020gpf ; real_T fb1wk2ass1 ; real_T aadd3pfro1 ; real_T
dzmwbh1gyj ; real_T pzc0e4zttf ; real_T cuvi30r0xz ; real_T b04vdkrp0q ;
real_T dg3bgegovs ; real_T g3spp13qf2 ; real_T ayodvjrca5 ; real_T lkftuvlorw
; real_T d40bzasok5 ; real_T gcos3yfhmp ; real_T dsx4qmcx2h ; real_T
ehlrsyzdec ; real_T cae2rljtqz ; real_T ft22grzbnv ; } ZCV ; typedef struct {
rtwCAPI_ModelMappingInfo mmi ; } DataMapInfo ; struct P_ { real_T AmpSat1 ;
real_T BackEMF1 ; real_T Elec1d [ 2 ] ; real_T Elec1n ; real_T Mech1d [ 3 ] ;
real_T Mech1n [ 2 ] ; real_T NomCurrent ; real_T PWMConversion [ 5 ] ; real_T
StallCurrent ; real_T StaticFric ; real_T TConst1 ; real_T
StepResponseControl1_D ; real_T StepResponseControl_D ; real_T
StepResponseControl1_I ; real_T StepResponseControl_I ; real_T
StepResponseControl1_N ; real_T StepResponseControl_N ; real_T
StepResponseControl1_P ; real_T StepResponseControl_P ; real_T Integrator3_IC
; real_T Step_Time ; real_T Step_Y0 ; real_T Step_YFinal ; real_T
Integrator_IC ; real_T MaxCurrent1_UpperSat ; real_T MaxCurrent1_LowerSat ;
real_T Memory2_InitialCondition ; real_T Memory1_InitialCondition ; real_T
Conversion_Value ; real_T Quantizeto2pi1_Interval ; real_T
Integrator_IC_i2h5jsmjmj ; real_T Filter_IC ; real_T MaxDutyCycle2_UpperSat ;
real_T MaxDutyCycle2_LowerSat ; real_T NearestInt1_Interval ; real_T
Integrator1_IC ; real_T PWM_Time ; real_T PWM_Y0 ; real_T PWM_YFinal ; real_T
Integrator2_IC ; real_T Quantizeto2pi400_Interval ; real_T
DesiredAngleInput_Time ; real_T DesiredAngleInput_Y0 ; real_T
DesiredAngleInput_YFinal ; real_T Integrator_IC_hgnjre2kl0 ; real_T
Filter_IC_hkzbi0o3xl ; real_T MaxCurrent_UpperSat ; real_T
MaxCurrent_LowerSat ; real_T MaxDutyCycle1_UpperSat ; real_T
MaxDutyCycle1_LowerSat ; real_T NearestInt_Interval ; real_T u0to255_UpperSat
; real_T u0to255_LowerSat ; real_T u55to30_UpperSat ; real_T u55to30_LowerSat
; real_T Switch_Threshold ; uint8_T Constant_Value ; } ; extern const char *
RT_MEMORY_ALLOCATION_ERROR ; extern B rtB ; extern X rtX ; extern DW rtDW ;
extern P rtP ; extern const rtwCAPI_ModelMappingStaticInfo *
motor_GetCAPIStaticMap ( void ) ; extern SimStruct * const rtS ; extern const
int_T gblNumToFiles ; extern const int_T gblNumFrFiles ; extern const int_T
gblNumFrWksBlocks ; extern rtInportTUtable * gblInportTUtables ; extern const
char * gblInportFileName ; extern const int_T gblNumRootInportBlks ; extern
const int_T gblNumModelInputs ; extern const int_T gblInportDataTypeIdx [ ] ;
extern const int_T gblInportDims [ ] ; extern const int_T gblInportComplex [
] ; extern const int_T gblInportInterpoFlag [ ] ; extern const int_T
gblInportContinuous [ ] ; extern const int_T gblParameterTuningTid ; extern
size_t gblCurrentSFcnIdx ; extern DataMapInfo * rt_dataMapInfoPtr ; extern
rtwCAPI_ModelMappingInfo * rt_modelMapInfoPtr ; void MdlOutputs ( int_T tid )
; void MdlOutputsParameterSampleTime ( int_T tid ) ; void MdlUpdate ( int_T
tid ) ; void MdlTerminate ( void ) ; void MdlInitializeSizes ( void ) ; void
MdlInitializeSampleTimes ( void ) ; SimStruct * raccel_register_model ( void
) ;
#endif
