countBackExp=SFLight*countSignal115DYL + SFTTbar*countSignal115TTbar + SFHeavy*countSignal115DYB + countSignal115VV + countSignal115ST

errorBackExp= ( D[countBackExp,SFLight]^2 * errorSFLight^2 +
                D[countBackExp,countSignal115DYL]^2 * errorSignal115DYL^2 +

						    D[countBackExp,SFTTbar]^2 * errorSFTTbar^2 +
                D[countBackExp,countSignal115TTbar]^2 * errorSignal115TTbar^2 +

                D[countBackExp,SFHeavy]^2 * errorSFHeavy^2 +
                D[countBackExp,countSignal115DYB]^2 * errorSignal115DYB^2 +

                D[countBackExp,countSignal115VV]^2 * errorSignal115VV^2 +
                D[countBackExp,countSignal115ST]^2 * errorSignal115ST^2 +

                2*D[countBackExp,SFLight]*D[countBackExp,SFTTbar]*covSFLightSFTTbar +
                2*D[countBackExp,SFLight]*D[countBackExp,SFHeavy]*covSFLightSFHeavy +
                2*D[countBackExp,SFHeavy]*D[countBackExp,SFTTbar]*covSFHeavySFTTbar )

m = { { countLightCCDYL   , countLightCCTTbar   , countLightCCDYB   },
      { countTTbarCCDYL   , countTTbarCCTTbar   , countTTbarCCDYB   },
      { countHeavyCCDYL   , countHeavyCCTTbar   , countHeavyCCDYB   } };

r = {  countLightCCRest ,
       countTTbarCCRest ,
       countHeavyCCRest  };

SFLight = LinearSolve[m, r][[1]];
SFTTbar = LinearSolve[m, r][[2]];
SFHeavy = LinearSolve[m, r][[3]];

A={{  D[SFLight, countLightCCDYL]   ,
       D[SFLight, countLightCCTTbar] ,
       D[SFLight, countLightCCDYB]   ,
       D[SFLight, countTTbarCCDYL]   ,
       D[SFLight, countTTbarCCTTbar] ,
       D[SFLight, countTTbarCCDYB]   ,
       D[SFLight, countHeavyCCDYL]   ,
       D[SFLight, countHeavyCCTTbar] ,
       D[SFLight, countHeavyCCDYB]   ,
       D[SFLight, countLightCCRest]  ,
       D[SFLight, countTTbarCCRest]  ,
       D[SFLight, countHeavyCCRest]  } ,
    {  D[SFTTbar, countLightCCDYL]   ,
       D[SFTTbar, countLightCCTTbar] ,
       D[SFTTbar, countLightCCDYB]   ,
       D[SFTTbar, countTTbarCCDYL]   ,
       D[SFTTbar, countTTbarCCTTbar] ,
       D[SFTTbar, countTTbarCCDYB]   ,
       D[SFTTbar, countHeavyCCDYL]   ,
       D[SFTTbar, countHeavyCCTTbar] ,
       D[SFTTbar, countHeavyCCDYB]   ,
       D[SFTTbar, countLightCCRest]  ,
       D[SFTTbar, countTTbarCCRest]  ,
       D[SFTTbar, countHeavyCCRest]  } ,
    {  D[SFHeavy, countLightCCDYL]   ,
       D[SFHeavy, countLightCCTTbar] ,
       D[SFHeavy, countLightCCDYB]   ,
       D[SFHeavy, countTTbarCCDYL]   ,
       D[SFHeavy, countTTbarCCTTbar] ,
       D[SFHeavy, countTTbarCCDYB]   ,
       D[SFHeavy, countHeavyCCDYL]   ,
       D[SFHeavy, countHeavyCCTTbar] ,
       D[SFHeavy, countHeavyCCDYB]   ,
       D[SFHeavy, countLightCCRest]  ,
       D[SFHeavy, countTTbarCCRest]  ,
       D[SFHeavy, countHeavyCCRest]  }}
Vx=DiagonalMatrix[ { errorLightCCDYL^2   ,
                     errorLightCCTTbar^2 ,
                     errorLightCCDYB^2   ,
                     errorTTbarCCDYL^2   ,
                     errorTTbarCCTTbar^2 ,
                     errorTTbarCCDYB^2   ,
                     errorHeavyCCDYL^2   ,
                     errorHeavyCCTTbar^2 ,
                     errorHeavyCCDYB^2   ,
                     errorLightCCRest^2  ,
                     errorTTbarCCRest^2  ,
                     errorHeavyCCRest^2  } ]

Vy=A.Vx.Transpose[A]

covSFLightSFTTbar = Vy[[2,1]]
covSFLightSFHeavy = Vy[[3,1]]
covSFHeavySFTTbar = Vy[[2,3]]

errorSFLight = Sqrt[Vy[[1,1]]]
errorSFTTbar = Sqrt[Vy[[2,2]]]
errorSFHeavy = Sqrt[Vy[[3,3]]]


(*UPDATED WITHOUT JET ID*)
countTTbarCCDYL = 0.58
errorTTbarCCDYL = 0.49
countTTbarCCTTbar  = 243.02
errorTTbarCCTTbar  = 7.54
countTTbarCCDYB  = 6.35
errorTTbarCCDYB  = 1.33
countTTbarCCRest  = 303.00 - (0.42 + 0.10 + 0.00 + 9.61)
errorTTbarCCRest  = Sqrt[ (Sqrt[303.00]^2 + 0.05^2 + 0.07^2 + 0.00^2 + 0.70^2)]

countLightCCDYL = 5457.46
errorLightCCDYL = 34.87
countLightCCTTbar  = 2.13
errorLightCCTTbar  = 0.71
countLightCCDYB  = 315.89
errorLightCCDYB  = 8.40
countLightCCRest  = 5514.00 - (29.73 + 1.10 + 48.99 + 0.55)
errorLightCCRest  = Sqrt[ (Sqrt[5514.00]^2 + 0.46^2 + 0.24^2 + 1.03^2 + 0.17^2 )]
     
countHeavyCCDYL = 22.71
errorHeavyCCDYL = 3.06
countHeavyCCTTbar  = 24.63
errorHeavyCCTTbar  = 2.40
countHeavyCCDYB  = 205.85
errorHeavyCCDYB  = 9.10
countHeavyCCRest  = 248.00 - (6.19 + 0.07 + 0.12 + 0.70)
errorHeavyCCRest  = Sqrt[ (Sqrt[248.00]^2 + 0.21^2 + 0.06^2 + 0.05^2 + 0.19^2 )]
 
  Print[TraditionalForm["SFLight = "],SFLight,TraditionalForm[" +- "], errorSFLight]
  Print[TraditionalForm["SFTTbar = "],SFTTbar,TraditionalForm[" +- "], errorSFTTbar]
  Print[TraditionalForm["SFHeavy = "],SFHeavy,TraditionalForm[" +- "], errorSFHeavy]

  Print[TraditionalForm["Cov(SFLight,SFTTbar)"],Vy[[2,1]]]
  Print[TraditionalForm["Cov(SFLight,SFHeavy)"],Vy[[3,1]]]
  Print[TraditionalForm["Cov(SFTTbar,SFHeavy)"],Vy[[2,3]]]
