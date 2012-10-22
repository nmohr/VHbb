#g++ -q -o make_histos_Pt100 SideBandAnalysis-Pt100/make_histos_sideband.cxx -I $ROOTSYS/include -I $ROOTSYS/include/TMVA -l TMVA -L $ROOTSYS/lib `root-config --glibs`
g++ -std=c++0x -o make_histos_Pt50To100 SideBandAnalysis-Pt50To100/make_histos_sideband.cxx -I $ROOTSYS/include -lMathMore -I $ROOTSYS/include/TMVA -l TMVA -L $ROOTSYS/lib `root-config --glibs`
#g++ -o make_histos_Basic Basic/make_histos.cxx -I $ROOTSYS/include -I $ROOTSYS/include/TMVA -l TMVA -L $ROOTSYS/lib `root-config --glibs`
#g++ -q -o make_histos_CnC-Pt50To100 CnC-Pt50To100/make_histos.cxx -I $ROOTSYS/include -I $ROOTSYS/include/TMVA -l TMVA -L $ROOTSYS/lib `root-config --glibs`
#g++ -o make_histos_CnC CnC/make_histos.cxx -I $ROOTSYS/include -I $ROOTSYS/include/TMVA -l TMVA -L $ROOTSYS/lib `root-config --glibs`
#g++ -q -o cutFlow cutFlow.cxx -I $ROOTSYS/include -I $ROOTSYS/include/TMVA -l TMVA -L $ROOTSYS/lib `root-config --glibs`
#g++ -q -o fit_VHbb fit_VHbb.cxx -I $ROOTSYS/include -l RooFit -l RooFitCore -L $ROOTSYS/lib `root-config --glibs`
#g++ -q -o fit_sideband_pt100 SideBandAnalysis-Pt100/fit_sideband.cxx -I $ROOTSYS/include -l RooFit -l RooFitCore -L $ROOTSYS/lib `root-config --glibs`
g++ -o fit_sideband_pt50To100 SideBandAnalysis-Pt50To100/fit_sideband.cxx -I $ROOTSYS/include -lMathMore -I $ROOFITSYS/include -L $ROOFITSYS/lib -l RooFit -l RooFitCore -L $ROOTSYS/lib `root-config --glibs`
#g++ -q -o fit_sideband_syst_pt100 SideBandAnalysis-Pt100/fit_sideband_syst.cxx -I $ROOTSYS/include -l RooFit -l RooFitCore -L $ROOTSYS/lib `root-config --glibs`
g++ -o fit_sideband_syst_pt50To100 SideBandAnalysis-Pt50To100/fit_sideband_syst.cxx -I $ROOTSYS/include -lMathMore -I $ROOFITSYS/include -L $ROOFITSYS/lib -l RooFit -l RooFitCore -L $ROOTSYS/lib `root-config --glibs`