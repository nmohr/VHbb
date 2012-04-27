countExpDYL=SFLight*countSignalCCDYL;
countExpTTbar=SFTTbar*countSignalCCTTbar;
countExpDYB=SFHeavy*countSignalCCDYB;

errorExpDYL=Sqrt[ D[countExpDYL, SFLight]^2 * errorSFLight + D[countExpDYL,countSignalCCDYL]^2 * errorSignalCCDYL ];
errorExpTTbar=Sqrt[ D[countExpTTbar, SFTTbar]^2 * errorSFTTbar + D[countExpTTbar,countSignalCCTTbar]^2 * errorSignalCCTTbar ];
errorExpDYB=Sqrt[ D[countExpDYB, SFHeavy]^2 * errorSFHeavy + D[countExpDYB,countSignalCCDYB]^2 * errorSignalCCDYB ];

countBackExp=SFLight*countSignalCCDYL + SFTTbar*countSignalCCTTbar + SFHeavy*countSignalCCDYB + countSignalCCVV + countSignalCCST;

errorBackExp= Sqrt[( D[countBackExp,SFLight]^2 * errorSFLight^2 +
		     D[countBackExp,countSignalCCDYL]^2 * errorSignalCCDYL^2 +
		     D[countBackExp,SFTTbar]^2 * errorSFTTbar^2 +
		     D[countBackExp,countSignalCCTTbar]^2 * errorSignalCCTTbar^2 +
		     D[countBackExp,SFHeavy]^2 * errorSFHeavy^2 +
		     D[countBackExp,countSignalCCDYB]^2 * errorSignalCCDYB^2 +
		     D[countBackExp,countSignalCCVV]^2 * errorSignalCCVV^2 +
		     D[countBackExp,countSignalCCST]^2 * errorSignalCCST^2 +
		     2*D[countBackExp,SFLight]*D[countBackExp,SFTTbar]*covSFLightSFTTbar +
		     2*D[countBackExp,SFLight]*D[countBackExp,SFHeavy]*covSFLightSFHeavy +
		     2*D[countBackExp,SFHeavy]*D[countBackExp,SFTTbar]*covSFHeavySFTTbar ) ];

errorBackExpNoCorr= Sqrt[( D[countBackExp,SFLight]^2 * errorSFLight^2 +
			   D[countBackExp,countSignalCCDYL]^2 * errorSignalCCDYL^2 +
			   D[countBackExp,SFTTbar]^2 * errorSFTTbar^2 +
			   D[countBackExp,countSignalCCTTbar]^2 * errorSignalCCTTbar^2 +
			   D[countBackExp,SFHeavy]^2 * errorSFHeavy^2 +
			   D[countBackExp,countSignalCCDYB]^2 * errorSignalCCDYB^2 +
			   D[countBackExp,countSignalCCVV]^2 * errorSignalCCVV^2 +
			   D[countBackExp,countSignalCCST]^2 * errorSignalCCST^2 ) ];


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

  (*final full dataset?*)

countLightCCDYL = 4550.49
countLightCCDYB = 271.631
countLightCCTTbar = 6.07884
countLightCCRest = 4910
errorLightCCDYL = 35.8009
errorLightCCDYB = 8.58789
errorLightCCTTbar = 1.37668
errorLightCCRest = 74.6632
countTTbarCCDYL = 1.14358
countTTbarCCDYB = 8.3694
countTTbarCCTTbar = 228.569
countTTbarCCRest = 245.482
errorTTbarCCDYL = 0.832678
errorTTbarCCDYB = 1.66034
errorTTbarCCTTbar = 8.21455
errorTTbarCCRest = 16.2178
countHeavyCCDYL = 21.7475
countHeavyCCDYB = 165.785
countHeavyCCTTbar = 19.1879
countHeavyCCRest = 206.161
errorHeavyCCDYL = 3.40526
errorHeavyCCDYB = 9.08026
errorHeavyCCTTbar = 2.43568
errorHeavyCCRest = 14.6818

  (*final full Fall11 OK*)

countLightCCDYL = 4560.88
countLightCCDYB = 281.724
countLightCCTTbar = 5.39248
countLightCCRest = 4909.71
errorLightCCDYL = 35.1472
errorLightCCDYB = 8.83566
errorLightCCTTbar = 1.20267
errorLightCCRest = 74.6862
countTTbarCCDYL = 0.253396
countTTbarCCDYB = 6.23054
countTTbarCCTTbar = 233.483
countTTbarCCRest = 246.313
errorTTbarCCDYL = 0.180352
errorTTbarCCDYB = 1.19805
errorTTbarCCTTbar = 7.9731
errorTTbarCCRest = 16.1734
countHeavyCCDYL = 21.5395
countHeavyCCDYB = 161.798
countHeavyCCTTbar = 20.2059
countHeavyCCRest = 205.904
errorHeavyCCDYL = 3.47153
errorHeavyCCDYB = 8.8569
errorHeavyCCTTbar = 2.36065
errorHeavyCCRest = 14.6874
countSignalCCDYL = 1.38
countSignalCCDYB = 3.56478
countSignalCCTTbar = 0.965476
countSignalCCRest = 7.27111
errorSignalCCDYL = 0.665461
errorSignalCCDYB = 0.879099
errorSignalCCTTbar = 0.489464
errorSignalCCRest = 2.83961

(* with new electrons efficiency*)
countLightCCDYL = 4483.13
countLightCCDYB = 277.1
countLightCCTTbar = 5.50526
countLightCCRest = 4910.8
errorLightCCDYL = 34.5085
errorLightCCDYB = 8.67965
errorLightCCTTbar = 0.423406
errorLightCCRest = 74.561
countTTbarCCDYL = 0.251084
countTTbarCCDYB = 6.14393
countTTbarCCTTbar = 227.549
countTTbarCCRest = 246.455
errorTTbarCCDYL = 0.17867
errorTTbarCCDYB = 1.18279
errorTTbarCCTTbar = 2.68855
errorTTbarCCRest = 16.1647
countHeavyCCDYL = 20.9866
countHeavyCCDYB = 158.218
countHeavyCCTTbar = 19.9432
countHeavyCCRest = 206.031
errorHeavyCCDYL = 3.37895
errorHeavyCCDYB = 8.6525
errorHeavyCCTTbar = 0.7942
errorHeavyCCRest = 14.6821

 
  Print[TraditionalForm["SFLight = "],SFLight,TraditionalForm[" +- "], errorSFLight]
  Print[TraditionalForm["SFTTbar = "],SFTTbar,TraditionalForm[" +- "], errorSFTTbar]
  Print[TraditionalForm["SFHeavy = "],SFHeavy,TraditionalForm[" +- "], errorSFHeavy]

  Print[TraditionalForm["Cov(SFLight,SFTTbar)"],Vy[[2,1]]]
  Print[TraditionalForm["Cov(SFLight,SFHeavy)"],Vy[[3,1]]]
  Print[TraditionalForm["Cov(SFTTbar,SFHeavy)"],Vy[[2,3]]]

  Print[TraditionalForm["ZLight = "], countExpDYL ,TraditionalForm[" +- "], errorExpDYL ]
  Print[TraditionalForm["TTbar = "], countExpTTbar ,TraditionalForm[" +- "], errorExpTTbar ]
  Print[TraditionalForm["ZHeavy = "], countExpDYB ,TraditionalForm[" +- "], errorExpDYB ]
  Print[TraditionalForm["ST = "], countSignalCCST ,TraditionalForm[" +- "], errorSignalCCST ]
  Print[TraditionalForm["VV = "], countSignalCCVV ,TraditionalForm[" +- "], errorSignalCCVV ]
  Print[TraditionalForm["MCtotal = "],countBackExp,TraditionalForm[" +- "], errorBackExp]

  Print[TraditionalForm["MCtotal without correlation = "],countBackExp,TraditionalForm[" +- "], errorBackExpNoCorr]

