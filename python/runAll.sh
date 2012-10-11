#!/bin/bash

#Input argument:
#sample you want to run on. It has to match the naming in sample.info.
sample=$1
#sqrt(s) you want to run
energy=$2

task=$3

if [ $# -lt 3 ]
    then
    echo "ERROR: You passed " $# "arguments while the script needs at least 3 arguments."
    echo "Exiting..."
    echo " ---------------------------------- "
    echo " Usage : ./runAll.sh sample energy task"
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
export LD_LIBRARY_PATH=/swshare/glite/d-cache/dcap/lib/:$LD_LIBRARY_PATH
#unset TMP
#unset TMPDIR

mkdir $TMPDIR

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

MVAList=`python << EOF 
import os
from BetterConfigParser import BetterConfigParser
config = BetterConfigParser()
config.read('./config$energy')
print config.get('MVALists','List_for_submitscript')
EOF`
configFile=config$energy


#Create subdirs where processed samples will be stored
if [ ! -d $pathAna/env ]
    then
    mkdir $pathAna/env
fi
if [ ! -d $pathAna/env/sys ]
    then
    mkdir $pathAna/env/sys
fi
if [ ! -d $pathAna/env/sys/MVAout ]
    then
    mkdir $pathAna/env/sys/MVAout
fi

#Run the scripts

if [ $task = "prep" ]; then
    ./prepare_environment_with_config.py -I $pathAna -O $pathAna/env/ -C ${energy}samples_nosplit.cfg
fi
if [ $task = "sys" ]; then
    ./write_regression_systematics.py -P $pathAna/env/ -S $sample -C $configFile -C pathConfig$energy
fi
if [ $task = "eval" ]; then
    ./evaluateMVA.py -P $pathAna/env/sys/ -D $MVAList -S $sample -U 0 -C ${configFile} -C pathConfig$energy
fi
if [ $task = "syseval" ]; then
    ./write_regression_systematics.py -P $pathAna/env/ -S $sample -C $configFile -C pathConfig$energy
    ./evaluateMVA.py -P $pathAna/env/sys/ -D $MVAList -S $sample -U 0 -C ${configFile} -C pathConfig$energy
fi
if [ $task = "plot" ]; then
    ./tree_stack.py -P $pathAna/env/sys/MVAout/ -C ${configFile} -C pathConfig$energy -R $sample
fi
if [ $task = "dc" ]; then
    ./workspace_datacard.py -P $pathAna/env/sys/MVAout/ -C ${configFile} -C pathConfig$energy -V $sample 
fi

rm -rf $TMPDIR
