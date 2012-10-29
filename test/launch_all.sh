#!/bin/bash

if [ ! -f launch_parallel.sh ]
    then
    echo "ERROR: No launch_parallel.sh script found"
    exit -1
fi

qsub -cwd -V -q all.q -N TT -e TT.err -o TT.out ./launch_parallel.sh  TTJets_Merged.root TTbar `pwd`
qsub -cwd -V -q all.q -N DYinc -e DYinc.err -o DYinc.out ./launch_parallel.sh  DYJetsToLL_M-50_TuneZ2Star_8TeV-madgraph-tarball.root DY `pwd`
qsub -cwd -V -q all.q -N DY5070 -e DY5070.err -o DY5070.out ./launch_parallel.sh  DYJetsToLL_PtZ-50To70_TuneZ2star_8TeV-madgraph-tarball.root DY `pwd`
qsub -cwd -V -q all.q -N DY70100 -e DY70100.err -o DY70100.out ./launch_parallel.sh  DYJetsToLL_PtZ-70To100_TuneZ2star_8TeV-madgraph-tarball.root DY `pwd`
qsub -cwd -V -q all.q -N DY100 -e DY100.err -o DY100.out ./launch_parallel.sh  DYJetsToLL_PtZ-100_TuneZ2star_8TeV-madgraph.root DY `pwd`
qsub -cwd -V -q all.q -N DY1 -e DY1.err -o DY1.out ./launch_parallel.sh  DY1JetsToLL_M-50_TuneZ2Star_8TeV-madgraph.root DY `pwd`
qsub -cwd -V -q all.q -N DY2 -e DY2.err -o DY2.out ./launch_parallel.sh  DY2JetsToLL_M-50_TuneZ2Star_8TeV-madgraph.root DY `pwd`
qsub -cwd -V -q all.q -N DY3 -e DY3.err -o DY3.out ./launch_parallel.sh  DY3JetsToLL_M-50_TuneZ2Star_8TeV-madgraph.root DY `pwd`
qsub -cwd -V -q all.q -N DY4 -e DY4.err -o DY4.out ./launch_parallel.sh  DY4JetsToLL_M-50_TuneZ2Star_8TeV-madgraph.root  DY `pwd`
qsub -cwd -V -q all.q -N DYHT24 -e DYHT24.err -o DYHT24.out ./launch_parallel.sh  DYJetsToLL_HT-200To400_TuneZ2Star_8TeV-madgraph.root DY `pwd`
qsub -cwd -V -q all.q -N DYHT4 -e DYHT4.err -o DYHT4.out ./launch_parallel.sh  DYJetsToLL_HT-400ToInf_TuneZ2Star_8TeV-madgraph.root DY `pwd`
qsub -cwd -V -q all.q -N ZZ -e ZZ.err -o ZZ.out ./launch_parallel.sh  ZZ_TuneZ2star_8TeV_pythia6_tauola.root VV `pwd`
qsub -cwd -V -q all.q -N ZZ2 -e ZZ2.err -o ZZ2.out ./launch_parallel.sh  ZZJetsTo2L2Q_TuneZ2star_8TeV-madgraph-tauola.root VV `pwd`
qsub -cwd -V -q all.q -N WZ -e WZ.err -o WZ.out ./launch_parallel.sh  WZ_TuneZ2star_8TeV_pythia6_tauola.root VV `pwd`
qsub -cwd -V -q all.q -N WW -e WW.err -o WW.out ./launch_parallel.sh  WW_TuneZ2star_8TeV_pythia6_tauola.root VV `pwd`
qsub -cwd -V -q all.q -N Ts -e Ts.err -o Ts.out ./launch_parallel.sh  T_s-channel_TuneZ2star_8TeV-powheg-tauola.root ST  `pwd`
qsub -cwd -V -q all.q -N Tt -e Tt.err -o Tt.out ./launch_parallel.sh  T_t-channel_TuneZ2star_8TeV-powheg-tauola.root ST `pwd`
qsub -cwd -V -q all.q -N Ttw -e Ttw.err -o Ttw.out ./launch_parallel.sh  T_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola.root ST `pwd`
qsub -cwd -V -q all.q -N Tbs -e Tbs.err -o Tbs.out ./launch_parallel.sh  Tbar_s-channel_TuneZ2star_8TeV-powheg-tauola.root ST `pwd`
qsub -cwd -V -q all.q -N Tbt -e Tbt.err -o Tbt.out ./launch_parallel.sh  Tbar_t-channel_TuneZ2star_8TeV-powheg-tauola.root ST `pwd`
qsub -cwd -V -q all.q -N Tbtw -e Tbtw.err -o Tbtw.out ./launch_parallel.sh  Tbar_tW-channel-DR_TuneZ2star_8TeV-powheg-tauola.root ST `pwd`
qsub -cwd -V -q all.q -N dataF -e dataF.err -o dataF.out ./launch_parallel.sh  DataZ.root data `pwd`
qsub -cwd -V -q all.q -N dataE -e dataE.err -o dataE.out ./launch_parallel.sh  DataZee.root data `pwd`
qsub -cwd -V -q all.q -N dataM -e dataM.err -o dataM.out ./launch_parallel.sh  DataZmm.root data `pwd`
