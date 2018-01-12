  function targMap = targDataMap(),

  ;%***********************
  ;% Create Parameter Map *
  ;%***********************
      
    nTotData      = 0; %add to this count as we go
    nTotSects     = 2;
    sectIdxOffset = 0;
    
    ;%
    ;% Define dummy sections & preallocate arrays
    ;%
    dumSection.nData = -1;  
    dumSection.data  = [];
    
    dumData.logicalSrcIdx = -1;
    dumData.dtTransOffset = -1;
    
    ;%
    ;% Init/prealloc paramMap
    ;%
    paramMap.nSections           = nTotSects;
    paramMap.sectIdxOffset       = sectIdxOffset;
      paramMap.sections(nTotSects) = dumSection; %prealloc
    paramMap.nTotData            = -1;
    
    ;%
    ;% Auto data (rtP)
    ;%
      section.nData     = 52;
      section.data(52)  = dumData; %prealloc
      
	  ;% rtP.Amp0d
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% rtP.Amp0n
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 1;
	
	  ;% rtP.Amp1d
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 2;
	
	  ;% rtP.Amp1n
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 3;
	
	  ;% rtP.AmpSat0
	  section.data(5).logicalSrcIdx = 4;
	  section.data(5).dtTransOffset = 4;
	
	  ;% rtP.AmpSat1
	  section.data(6).logicalSrcIdx = 5;
	  section.data(6).dtTransOffset = 5;
	
	  ;% rtP.BackEMF0
	  section.data(7).logicalSrcIdx = 6;
	  section.data(7).dtTransOffset = 6;
	
	  ;% rtP.BackEMF1
	  section.data(8).logicalSrcIdx = 7;
	  section.data(8).dtTransOffset = 7;
	
	  ;% rtP.Distance
	  section.data(9).logicalSrcIdx = 8;
	  section.data(9).dtTransOffset = 8;
	
	  ;% rtP.Elec0d
	  section.data(10).logicalSrcIdx = 9;
	  section.data(10).dtTransOffset = 9;
	
	  ;% rtP.Elec0n
	  section.data(11).logicalSrcIdx = 10;
	  section.data(11).dtTransOffset = 11;
	
	  ;% rtP.Elec1d
	  section.data(12).logicalSrcIdx = 11;
	  section.data(12).dtTransOffset = 12;
	
	  ;% rtP.Elec1n
	  section.data(13).logicalSrcIdx = 12;
	  section.data(13).dtTransOffset = 14;
	
	  ;% rtP.FB0
	  section.data(14).logicalSrcIdx = 13;
	  section.data(14).dtTransOffset = 15;
	
	  ;% rtP.FB1
	  section.data(15).logicalSrcIdx = 14;
	  section.data(15).dtTransOffset = 16;
	
	  ;% rtP.JntSat1
	  section.data(16).logicalSrcIdx = 15;
	  section.data(16).dtTransOffset = 17;
	
	  ;% rtP.Mech0d
	  section.data(17).logicalSrcIdx = 16;
	  section.data(17).dtTransOffset = 18;
	
	  ;% rtP.Mech0n
	  section.data(18).logicalSrcIdx = 17;
	  section.data(18).dtTransOffset = 21;
	
	  ;% rtP.Mech1d
	  section.data(19).logicalSrcIdx = 18;
	  section.data(19).dtTransOffset = 23;
	
	  ;% rtP.Mech1n
	  section.data(20).logicalSrcIdx = 19;
	  section.data(20).dtTransOffset = 26;
	
	  ;% rtP.NomI0
	  section.data(21).logicalSrcIdx = 20;
	  section.data(21).dtTransOffset = 28;
	
	  ;% rtP.NomI1
	  section.data(22).logicalSrcIdx = 21;
	  section.data(22).dtTransOffset = 29;
	
	  ;% rtP.PID0
	  section.data(23).logicalSrcIdx = 22;
	  section.data(23).dtTransOffset = 30;
	
	  ;% rtP.PID1
	  section.data(24).logicalSrcIdx = 23;
	  section.data(24).dtTransOffset = 33;
	
	  ;% rtP.Sens0
	  section.data(25).logicalSrcIdx = 24;
	  section.data(25).dtTransOffset = 36;
	
	  ;% rtP.Sens1
	  section.data(26).logicalSrcIdx = 25;
	  section.data(26).dtTransOffset = 37;
	
	  ;% rtP.StallI0
	  section.data(27).logicalSrcIdx = 26;
	  section.data(27).dtTransOffset = 38;
	
	  ;% rtP.StallI1
	  section.data(28).logicalSrcIdx = 27;
	  section.data(28).dtTransOffset = 39;
	
	  ;% rtP.TConst0
	  section.data(29).logicalSrcIdx = 28;
	  section.data(29).dtTransOffset = 40;
	
	  ;% rtP.TConst1
	  section.data(30).logicalSrcIdx = 29;
	  section.data(30).dtTransOffset = 41;
	
	  ;% rtP.ControllerQ0_N
	  section.data(31).logicalSrcIdx = 30;
	  section.data(31).dtTransOffset = 42;
	
	  ;% rtP.ControllerQ1_N
	  section.data(32).logicalSrcIdx = 31;
	  section.data(32).dtTransOffset = 43;
	
	  ;% rtP.CompareToConstant_const
	  section.data(33).logicalSrcIdx = 32;
	  section.data(33).dtTransOffset = 44;
	
	  ;% rtP.Integrator_IC
	  section.data(34).logicalSrcIdx = 33;
	  section.data(34).dtTransOffset = 45;
	
	  ;% rtP.Memory2_InitialCondition
	  section.data(35).logicalSrcIdx = 34;
	  section.data(35).dtTransOffset = 46;
	
	  ;% rtP.IntegratorQ0_IC
	  section.data(36).logicalSrcIdx = 35;
	  section.data(36).dtTransOffset = 47;
	
	  ;% rtP.IntegratorQ1_IC
	  section.data(37).logicalSrcIdx = 36;
	  section.data(37).dtTransOffset = 48;
	
	  ;% rtP.SineWave_Amp
	  section.data(38).logicalSrcIdx = 37;
	  section.data(38).dtTransOffset = 49;
	
	  ;% rtP.SineWave_Bias
	  section.data(39).logicalSrcIdx = 38;
	  section.data(39).dtTransOffset = 50;
	
	  ;% rtP.SineWave_Freq
	  section.data(40).logicalSrcIdx = 39;
	  section.data(40).dtTransOffset = 51;
	
	  ;% rtP.SineWave_Phase
	  section.data(41).logicalSrcIdx = 40;
	  section.data(41).dtTransOffset = 52;
	
	  ;% rtP.SineWave1_Amp
	  section.data(42).logicalSrcIdx = 41;
	  section.data(42).dtTransOffset = 53;
	
	  ;% rtP.SineWave1_Bias
	  section.data(43).logicalSrcIdx = 42;
	  section.data(43).dtTransOffset = 54;
	
	  ;% rtP.SineWave1_Freq
	  section.data(44).logicalSrcIdx = 43;
	  section.data(44).dtTransOffset = 55;
	
	  ;% rtP.SineWave1_Phase
	  section.data(45).logicalSrcIdx = 44;
	  section.data(45).dtTransOffset = 56;
	
	  ;% rtP.Memory1_InitialCondition
	  section.data(46).logicalSrcIdx = 45;
	  section.data(46).dtTransOffset = 57;
	
	  ;% rtP.Memory3_InitialCondition
	  section.data(47).logicalSrcIdx = 46;
	  section.data(47).dtTransOffset = 58;
	
	  ;% rtP.Memory4_InitialCondition
	  section.data(48).logicalSrcIdx = 47;
	  section.data(48).dtTransOffset = 59;
	
	  ;% rtP.Filter_IC
	  section.data(49).logicalSrcIdx = 48;
	  section.data(49).dtTransOffset = 60;
	
	  ;% rtP.Integrator_IC_itl5ymsq54
	  section.data(50).logicalSrcIdx = 49;
	  section.data(50).dtTransOffset = 61;
	
	  ;% rtP.Filter_IC_kyn4kgm3f4
	  section.data(51).logicalSrcIdx = 50;
	  section.data(51).dtTransOffset = 62;
	
	  ;% rtP.Integrator_IC_bz3z1grlau
	  section.data(52).logicalSrcIdx = 51;
	  section.data(52).dtTransOffset = 63;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(1) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% rtP.Constant_Value
	  section.data(1).logicalSrcIdx = 52;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      paramMap.sections(2) = section;
      clear section
      
    
      ;%
      ;% Non-auto Data (parameter)
      ;%
    

    ;%
    ;% Add final counts to struct.
    ;%
    paramMap.nTotData = nTotData;
    


  ;%**************************
  ;% Create Block Output Map *
  ;%**************************
      
    nTotData      = 0; %add to this count as we go
    nTotSects     = 2;
    sectIdxOffset = 0;
    
    ;%
    ;% Define dummy sections & preallocate arrays
    ;%
    dumSection.nData = -1;  
    dumSection.data  = [];
    
    dumData.logicalSrcIdx = -1;
    dumData.dtTransOffset = -1;
    
    ;%
    ;% Init/prealloc sigMap
    ;%
    sigMap.nSections           = nTotSects;
    sigMap.sectIdxOffset       = sectIdxOffset;
      sigMap.sections(nTotSects) = dumSection; %prealloc
    sigMap.nTotData            = -1;
    
    ;%
    ;% Auto data (rtB)
    ;%
      section.nData     = 65;
      section.data(65)  = dumData; %prealloc
      
	  ;% rtB.hbmlhug0bx
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% rtB.py2taxmodw
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 2;
	
	  ;% rtB.imv2femxvj
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 4;
	
	  ;% rtB.oqaiej1ofv
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 5;
	
	  ;% rtB.lkpyinhslc
	  section.data(5).logicalSrcIdx = 4;
	  section.data(5).dtTransOffset = 6;
	
	  ;% rtB.grvfia1xdu
	  section.data(6).logicalSrcIdx = 5;
	  section.data(6).dtTransOffset = 8;
	
	  ;% rtB.boq4gsls3l
	  section.data(7).logicalSrcIdx = 6;
	  section.data(7).dtTransOffset = 10;
	
	  ;% rtB.jvcbsan3fm
	  section.data(8).logicalSrcIdx = 7;
	  section.data(8).dtTransOffset = 12;
	
	  ;% rtB.muyocrskli
	  section.data(9).logicalSrcIdx = 8;
	  section.data(9).dtTransOffset = 13;
	
	  ;% rtB.ciuxkrwmvl
	  section.data(10).logicalSrcIdx = 9;
	  section.data(10).dtTransOffset = 14;
	
	  ;% rtB.ifywyvlyix
	  section.data(11).logicalSrcIdx = 10;
	  section.data(11).dtTransOffset = 15;
	
	  ;% rtB.df2qekfpqc
	  section.data(12).logicalSrcIdx = 11;
	  section.data(12).dtTransOffset = 16;
	
	  ;% rtB.fl4jmkviqg
	  section.data(13).logicalSrcIdx = 12;
	  section.data(13).dtTransOffset = 17;
	
	  ;% rtB.oog2f0orgs
	  section.data(14).logicalSrcIdx = 13;
	  section.data(14).dtTransOffset = 18;
	
	  ;% rtB.pw553ih11r
	  section.data(15).logicalSrcIdx = 14;
	  section.data(15).dtTransOffset = 19;
	
	  ;% rtB.jvi3aujz2y
	  section.data(16).logicalSrcIdx = 15;
	  section.data(16).dtTransOffset = 20;
	
	  ;% rtB.d0ywb4iifr
	  section.data(17).logicalSrcIdx = 16;
	  section.data(17).dtTransOffset = 21;
	
	  ;% rtB.cnomiivfhs
	  section.data(18).logicalSrcIdx = 17;
	  section.data(18).dtTransOffset = 22;
	
	  ;% rtB.mv5es2qqht
	  section.data(19).logicalSrcIdx = 18;
	  section.data(19).dtTransOffset = 23;
	
	  ;% rtB.kqxihv51s2
	  section.data(20).logicalSrcIdx = 19;
	  section.data(20).dtTransOffset = 24;
	
	  ;% rtB.hwswxdjz2o
	  section.data(21).logicalSrcIdx = 20;
	  section.data(21).dtTransOffset = 25;
	
	  ;% rtB.ezjo2kpzef
	  section.data(22).logicalSrcIdx = 21;
	  section.data(22).dtTransOffset = 26;
	
	  ;% rtB.cborkiagpq
	  section.data(23).logicalSrcIdx = 22;
	  section.data(23).dtTransOffset = 27;
	
	  ;% rtB.d2rjutehif
	  section.data(24).logicalSrcIdx = 23;
	  section.data(24).dtTransOffset = 28;
	
	  ;% rtB.jfrwj2ywep
	  section.data(25).logicalSrcIdx = 24;
	  section.data(25).dtTransOffset = 29;
	
	  ;% rtB.jtzc3yh3vr
	  section.data(26).logicalSrcIdx = 25;
	  section.data(26).dtTransOffset = 30;
	
	  ;% rtB.h32e0arsda
	  section.data(27).logicalSrcIdx = 26;
	  section.data(27).dtTransOffset = 31;
	
	  ;% rtB.l43aesz3q0
	  section.data(28).logicalSrcIdx = 27;
	  section.data(28).dtTransOffset = 32;
	
	  ;% rtB.e55n1mwom0
	  section.data(29).logicalSrcIdx = 28;
	  section.data(29).dtTransOffset = 33;
	
	  ;% rtB.abmatz0jsq
	  section.data(30).logicalSrcIdx = 29;
	  section.data(30).dtTransOffset = 34;
	
	  ;% rtB.is2oky5nmn
	  section.data(31).logicalSrcIdx = 30;
	  section.data(31).dtTransOffset = 35;
	
	  ;% rtB.nb55jqhq34
	  section.data(32).logicalSrcIdx = 31;
	  section.data(32).dtTransOffset = 36;
	
	  ;% rtB.gl55e1oxq3
	  section.data(33).logicalSrcIdx = 32;
	  section.data(33).dtTransOffset = 37;
	
	  ;% rtB.lntm0zfacy
	  section.data(34).logicalSrcIdx = 33;
	  section.data(34).dtTransOffset = 38;
	
	  ;% rtB.chgqwipbrj
	  section.data(35).logicalSrcIdx = 34;
	  section.data(35).dtTransOffset = 39;
	
	  ;% rtB.ohehgsdsa5
	  section.data(36).logicalSrcIdx = 35;
	  section.data(36).dtTransOffset = 40;
	
	  ;% rtB.fycvf3ohxx
	  section.data(37).logicalSrcIdx = 36;
	  section.data(37).dtTransOffset = 41;
	
	  ;% rtB.kpbled4wwr
	  section.data(38).logicalSrcIdx = 37;
	  section.data(38).dtTransOffset = 42;
	
	  ;% rtB.nrvbbkpqfy
	  section.data(39).logicalSrcIdx = 38;
	  section.data(39).dtTransOffset = 43;
	
	  ;% rtB.bwejbx3gz4
	  section.data(40).logicalSrcIdx = 39;
	  section.data(40).dtTransOffset = 44;
	
	  ;% rtB.izwwnicbg1
	  section.data(41).logicalSrcIdx = 40;
	  section.data(41).dtTransOffset = 45;
	
	  ;% rtB.esaxa4ejop
	  section.data(42).logicalSrcIdx = 41;
	  section.data(42).dtTransOffset = 46;
	
	  ;% rtB.lp0vniw2vg
	  section.data(43).logicalSrcIdx = 42;
	  section.data(43).dtTransOffset = 47;
	
	  ;% rtB.net2l52ebc
	  section.data(44).logicalSrcIdx = 43;
	  section.data(44).dtTransOffset = 48;
	
	  ;% rtB.jnetxfptgr
	  section.data(45).logicalSrcIdx = 44;
	  section.data(45).dtTransOffset = 49;
	
	  ;% rtB.d1asgjubos
	  section.data(46).logicalSrcIdx = 45;
	  section.data(46).dtTransOffset = 50;
	
	  ;% rtB.pbnfjx04cq
	  section.data(47).logicalSrcIdx = 46;
	  section.data(47).dtTransOffset = 51;
	
	  ;% rtB.nsfmqq4us5
	  section.data(48).logicalSrcIdx = 47;
	  section.data(48).dtTransOffset = 52;
	
	  ;% rtB.ipvn2dlajm
	  section.data(49).logicalSrcIdx = 48;
	  section.data(49).dtTransOffset = 53;
	
	  ;% rtB.eefrdns3vo
	  section.data(50).logicalSrcIdx = 49;
	  section.data(50).dtTransOffset = 54;
	
	  ;% rtB.a1vmpy24k5
	  section.data(51).logicalSrcIdx = 50;
	  section.data(51).dtTransOffset = 55;
	
	  ;% rtB.pkzwaw50et
	  section.data(52).logicalSrcIdx = 51;
	  section.data(52).dtTransOffset = 56;
	
	  ;% rtB.iullwlukrq
	  section.data(53).logicalSrcIdx = 52;
	  section.data(53).dtTransOffset = 57;
	
	  ;% rtB.aljytqlhqv
	  section.data(54).logicalSrcIdx = 53;
	  section.data(54).dtTransOffset = 58;
	
	  ;% rtB.bfla2pij1s
	  section.data(55).logicalSrcIdx = 54;
	  section.data(55).dtTransOffset = 59;
	
	  ;% rtB.nl1yr2gtpd
	  section.data(56).logicalSrcIdx = 55;
	  section.data(56).dtTransOffset = 60;
	
	  ;% rtB.dhlo5n33b5
	  section.data(57).logicalSrcIdx = 56;
	  section.data(57).dtTransOffset = 61;
	
	  ;% rtB.nimsz2eln4
	  section.data(58).logicalSrcIdx = 57;
	  section.data(58).dtTransOffset = 62;
	
	  ;% rtB.imugtlsrnt
	  section.data(59).logicalSrcIdx = 58;
	  section.data(59).dtTransOffset = 63;
	
	  ;% rtB.emcqf0ggw0
	  section.data(60).logicalSrcIdx = 59;
	  section.data(60).dtTransOffset = 64;
	
	  ;% rtB.iv32nbz1dr
	  section.data(61).logicalSrcIdx = 60;
	  section.data(61).dtTransOffset = 65;
	
	  ;% rtB.d0itolxywz
	  section.data(62).logicalSrcIdx = 61;
	  section.data(62).dtTransOffset = 66;
	
	  ;% rtB.cnmmc5tlzm
	  section.data(63).logicalSrcIdx = 62;
	  section.data(63).dtTransOffset = 67;
	
	  ;% rtB.iik1kdrydb
	  section.data(64).logicalSrcIdx = 63;
	  section.data(64).dtTransOffset = 68;
	
	  ;% rtB.imnwnfgdra
	  section.data(65).logicalSrcIdx = 64;
	  section.data(65).dtTransOffset = 70;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(1) = section;
      clear section
      
      section.nData     = 1;
      section.data(1)  = dumData; %prealloc
      
	  ;% rtB.nblejb4ulo
	  section.data(1).logicalSrcIdx = 65;
	  section.data(1).dtTransOffset = 0;
	
      nTotData = nTotData + section.nData;
      sigMap.sections(2) = section;
      clear section
      
    
      ;%
      ;% Non-auto Data (signal)
      ;%
    

    ;%
    ;% Add final counts to struct.
    ;%
    sigMap.nTotData = nTotData;
    


  ;%*******************
  ;% Create DWork Map *
  ;%*******************
      
    nTotData      = 0; %add to this count as we go
    nTotSects     = 5;
    sectIdxOffset = 2;
    
    ;%
    ;% Define dummy sections & preallocate arrays
    ;%
    dumSection.nData = -1;  
    dumSection.data  = [];
    
    dumData.logicalSrcIdx = -1;
    dumData.dtTransOffset = -1;
    
    ;%
    ;% Init/prealloc dworkMap
    ;%
    dworkMap.nSections           = nTotSects;
    dworkMap.sectIdxOffset       = sectIdxOffset;
      dworkMap.sections(nTotSects) = dumSection; %prealloc
    dworkMap.nTotData            = -1;
    
    ;%
    ;% Auto data (rtDW)
    ;%
      section.nData     = 8;
      section.data(8)  = dumData; %prealloc
      
	  ;% rtDW.edqnr03j4o
	  section.data(1).logicalSrcIdx = 0;
	  section.data(1).dtTransOffset = 0;
	
	  ;% rtDW.hi3zk3zli4
	  section.data(2).logicalSrcIdx = 1;
	  section.data(2).dtTransOffset = 2;
	
	  ;% rtDW.euclalwh11
	  section.data(3).logicalSrcIdx = 2;
	  section.data(3).dtTransOffset = 3;
	
	  ;% rtDW.beg153xvlk
	  section.data(4).logicalSrcIdx = 3;
	  section.data(4).dtTransOffset = 4;
	
	  ;% rtDW.mcbn5gls5g
	  section.data(5).logicalSrcIdx = 4;
	  section.data(5).dtTransOffset = 5;
	
	  ;% rtDW.cnpublhlg5
	  section.data(6).logicalSrcIdx = 5;
	  section.data(6).dtTransOffset = 6;
	
	  ;% rtDW.h545t5oyoc
	  section.data(7).logicalSrcIdx = 6;
	  section.data(7).dtTransOffset = 7;
	
	  ;% rtDW.lgcrmtnzbq
	  section.data(8).logicalSrcIdx = 7;
	  section.data(8).dtTransOffset = 8;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(1) = section;
      clear section
      
      section.nData     = 5;
      section.data(5)  = dumData; %prealloc
      
	  ;% rtDW.ihyfkimqv5.AQHandles
	  section.data(1).logicalSrcIdx = 8;
	  section.data(1).dtTransOffset = 0;
	
	  ;% rtDW.bv0zhgyp5k.LoggedData
	  section.data(2).logicalSrcIdx = 9;
	  section.data(2).dtTransOffset = 1;
	
	  ;% rtDW.gchzjejcu3.AQHandles
	  section.data(3).logicalSrcIdx = 10;
	  section.data(3).dtTransOffset = 2;
	
	  ;% rtDW.egn21ix41f.AQHandles
	  section.data(4).logicalSrcIdx = 11;
	  section.data(4).dtTransOffset = 3;
	
	  ;% rtDW.ge33tuv1zo.AQHandles
	  section.data(5).logicalSrcIdx = 12;
	  section.data(5).dtTransOffset = 4;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(2) = section;
      clear section
      
      section.nData     = 9;
      section.data(9)  = dumData; %prealloc
      
	  ;% rtDW.frnbyss1yt
	  section.data(1).logicalSrcIdx = 13;
	  section.data(1).dtTransOffset = 0;
	
	  ;% rtDW.jm5cialsp2
	  section.data(2).logicalSrcIdx = 14;
	  section.data(2).dtTransOffset = 2;
	
	  ;% rtDW.hoivdwve1d
	  section.data(3).logicalSrcIdx = 15;
	  section.data(3).dtTransOffset = 4;
	
	  ;% rtDW.njpfo0txij
	  section.data(4).logicalSrcIdx = 16;
	  section.data(4).dtTransOffset = 5;
	
	  ;% rtDW.d1vwwr4s1r
	  section.data(5).logicalSrcIdx = 17;
	  section.data(5).dtTransOffset = 6;
	
	  ;% rtDW.icn2tg3hl2
	  section.data(6).logicalSrcIdx = 18;
	  section.data(6).dtTransOffset = 7;
	
	  ;% rtDW.ofvw1urmo2
	  section.data(7).logicalSrcIdx = 19;
	  section.data(7).dtTransOffset = 8;
	
	  ;% rtDW.kmlhhcf3ls
	  section.data(8).logicalSrcIdx = 20;
	  section.data(8).dtTransOffset = 9;
	
	  ;% rtDW.ersxnvaxzt
	  section.data(9).logicalSrcIdx = 21;
	  section.data(9).dtTransOffset = 10;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(3) = section;
      clear section
      
      section.nData     = 3;
      section.data(3)  = dumData; %prealloc
      
	  ;% rtDW.lufveoz2ya
	  section.data(1).logicalSrcIdx = 22;
	  section.data(1).dtTransOffset = 0;
	
	  ;% rtDW.fnfpq0xxhm
	  section.data(2).logicalSrcIdx = 23;
	  section.data(2).dtTransOffset = 1;
	
	  ;% rtDW.f0ckmjw1gj
	  section.data(3).logicalSrcIdx = 24;
	  section.data(3).dtTransOffset = 2;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(4) = section;
      clear section
      
      section.nData     = 5;
      section.data(5)  = dumData; %prealloc
      
	  ;% rtDW.kylvmh4w13
	  section.data(1).logicalSrcIdx = 25;
	  section.data(1).dtTransOffset = 0;
	
	  ;% rtDW.kbqz5luorh
	  section.data(2).logicalSrcIdx = 26;
	  section.data(2).dtTransOffset = 1;
	
	  ;% rtDW.ekvz540vhq
	  section.data(3).logicalSrcIdx = 27;
	  section.data(3).dtTransOffset = 2;
	
	  ;% rtDW.eplu0qlvkz
	  section.data(4).logicalSrcIdx = 28;
	  section.data(4).dtTransOffset = 3;
	
	  ;% rtDW.ih4snyf23z
	  section.data(5).logicalSrcIdx = 29;
	  section.data(5).dtTransOffset = 4;
	
      nTotData = nTotData + section.nData;
      dworkMap.sections(5) = section;
      clear section
      
    
      ;%
      ;% Non-auto Data (dwork)
      ;%
    

    ;%
    ;% Add final counts to struct.
    ;%
    dworkMap.nTotData = nTotData;
    


  ;%
  ;% Add individual maps to base struct.
  ;%

  targMap.paramMap  = paramMap;    
  targMap.signalMap = sigMap;
  targMap.dworkMap  = dworkMap;
  
  ;%
  ;% Add checksums to base struct.
  ;%


  targMap.checksum0 = 2691800636;
  targMap.checksum1 = 3910809806;
  targMap.checksum2 = 2654587771;
  targMap.checksum3 = 2193301241;

