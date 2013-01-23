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
export LD_PRELOAD="libglobus_gssapi_gsi_gcc64pthr.so.0":${LD_PRELOAD}

mkdir $TMPDIR

#back to the working dir
cd -

MVAList=`python << EOF 
import os
from myutils import BetterConfigParser
config = BetterConfigParser()
config.read('./${energy}config/training')
print config.get('MVALists','List_for_submitscript')
EOF`

#Run the scripts

if [ $task = "prep" ]; then
    ./prepare_environment_with_config.py -C ${energy}config/samples_nosplit.cfg -C ${energy}config/paths
fi
if [ $task = "sys" ]; then
    ./write_regression_systematics.py -S $sample -C ${energy}config/general -C ${energy}config/paths
fi
if [ $task = "eval" ]; then
    ./evaluateMVA.py -D $MVAList -S $sample -C ${energy}config/general -C ${energy}config/paths -C ${energy}config/cuts -C ${energy}config/training
fi
if [ $task = "syseval" ]; then
    ./write_regression_systematics.py -S $sample -C ${energy}config/general -C ${energy}config/paths
    ./evaluateMVA.py -D $MVAList -S $sample -C ${energy}config/general -C ${energy}config/paths -C ${energy}config/cuts -C ${energy}config/training
fi
if [ $task = "plot" ]; then
    ./tree_stack.py -R $sample -C ${energy}config/general -C ${energy}config/paths -C ${energy}config/cuts -C ${energy}config/plots
fi
if [ $task = "dc" ]; then
    ./workspace_datacard.py -V $sample -C ${energy}config/general -C ${energy}config/paths -C ${energy}config/cuts -C ${energy}config/datacards
fi

rm -rf $TMPDIR
