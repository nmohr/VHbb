#!/bin/bash

#Input argument:
#sample you want to run on. It has to match the naming in sample.info.
sample=$1
#sqrt(s) you want to run
energy=$2

if [ $# -lt 2 ]
    then
    echo "ERROR: You passed " $# "arguments while the script needs at least 2 arguments."
    echo "Exiting..."
    echo " ---------------------------------- "
    echo " Usage : ./runAll.sh sample energy"
    echo " ---------------------------------- "
    exit
fi

#Set the environment for the batch job execution

#cd /shome/peller/CMSSW_5_2_4_patch4/src/
# this doesnt work for me..?
cd $CMSSW_BASE/src/
source /swshare/psit3/etc/profile.d/cms_ui_env.sh
export SCRAM_ARCH="slc5_amd64_gcc462"
source $VO_CMS_SW_DIR/cmsset_default.sh
eval `scramv1 runtime -sh`
unset TMP
unset TMPDIR

#Path where the script write_regression_systematic.py and evaluateMVA.py are stored
#execute=$PWD/UserCode/VHbb/python/
#execute=/shome/peller/UserCode/VHbb/python/
#cd $execute

#back to the working dir
cd -

#Parsing the path form the config
pathAna=`python << EOF 
import os
from BetterConfigParser import BetterConfigParser
config = BetterConfigParser()
config.read('./pathConfig$energy')
print config.get('Directories','samplepath')
EOF`
echo $pathAna
configFile=config$energy

#Create subdirs where processed samples will be stored
if [ ! -d $pathAna/env/sys ]
    then
    mkdir $pathAna/env/sys
fi
if [ ! -d $pathAna/env/sys/MVAout ]
    then
    mkdir $pathAna/env/sys/MVAout
fi

#Create the link to th sample information in the new sudfolders
if [ ! -f $pathAna/env/sys/samples.info ]
    then
    ln -s $pathAna/env/samples.info  $pathAna/env/sys/samples.info
fi
if [ ! -f $pathAna/sys/MVAout/samples.info ]
    then
    ln -s $pathAna/env/samples.info $pathAna/env/sys/MVAout/samples.info
fi

#Run the scripts
#./step1_prepare_trees.sh 
#./write_regression_systematics.py -P $pathAna/env/ -S $sample -C $configFile -C pathConfig$energy
./evaluateMVA.py -P $pathAna/env/sys/ -D RTight_ZH110_may,RTight_ZH115_may,RTight_ZH120_may,RTight_ZH125_may,RTight_ZH130_may,RTight_ZH135_may,RMed_ZH110_may,RMed_ZH115_may,RMed_ZH120_may,RMed_ZH125_may,RMed_ZH130_may,RMed_ZH135_may,RPt50_ZZ_may,RIncl_ZZ_may -S $sample -U 0 -C ${configFile} -C pathConfig$energy
#./showinfo.py $pathAna/env/sys
#./evaluateMVA.py -P $pathAna/env/sys/ -D RTight_ZH110_may,RTight_ZH115_may,RTight_ZH120_may,RTight_ZH125_may,RTight_ZH130_may,RTight_ZH135_may,RMed_ZH110_may,RMed_ZH115_may,RMed_ZH120_may,RMed_ZH125_may,RMed_ZH130_may,RMed_ZH135_may -S $sample -U 0 -C ${configFile} -C pathConfig$energy
