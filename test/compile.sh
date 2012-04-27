g++ -q -o make_histos_step2 make_histos_step2.cxx -I $ROOTSYS/include -I $ROOTSYS/include/TMVA -l TMVA -L $ROOTSYS/lib `root-config --glibs`
g++ -q -o makeSystematicsForSF makeSystematicsForSF.cxx -I $ROOTSYS/include -I $ROOTSYS/include/TMVA -l TMVA -L $ROOTSYS/lib `root-config --glibs`
g++ -q -o cutFlow cutFlow.cxx -I $ROOTSYS/include -I $ROOTSYS/include/TMVA -l TMVA -L $ROOTSYS/lib `root-config --glibs`
g++ -q -o TMVAClassification TMVAClassification.cxx -I $ROOTSYS/include -I $ROOTSYS/include/TMVA -l TMVA -L $ROOTSYS/lib `root-config --glibs`
g++ -q -o make_histos_step2_v2 make_histos_step2_v2.cxx -I $ROOTSYS/include -I $ROOTSYS/include/TMVA -l TMVA -L $ROOTSYS/lib `root-config --glibs`
g++ -q -o fit_VHbb fit_VHbb.cxx -I $ROOTSYS/include -l RooFit -l RooFitCore -L $ROOTSYS/lib `root-config --glibs`
g++ -q -o Efficiency Efficiency.cxx -I $ROOTSYS/include -L $ROOTSYS/lib `root-config --glibs`
