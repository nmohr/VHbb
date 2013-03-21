#!/bin/bash
#====================================================================
#
#        FILE: runAll.sh
#
#       USAGE: runAll.sh sample energy task
#
# DESCRIPTION: Script to be launched in the batch system.
#              Can also be used, with some careful, to run locally.
#
#      AUTHOR: VHbb team
#              ETH Zurich
#
#=====================================================================

#Input argument:
sample=$1           # sample you want to run on. It has to match the naming in sample.info.
energy=$2           # sqrt(s) you want to run
task=$3             # the task 
job_id=$4           # needed for train optimisation. @TO FIX: it does not have a unique meaning
additional_arg=$5   # needed for train optimisation. @TO FIX: it does not have a unique meaning

#-------------------------------------------------
# Check the number of input arguments
#-------------------------------------------------
if [ $# -lt 3 ]
    then
    echo "ERROR: You passed " $# "arguments while the script needs at least 3 arguments."
    echo "Exiting..."
    echo " ---------------------------------- "
    echo " Usage : ./runAll.sh sample energy task"
    echo " ---------------------------------- "
    exit
fi

#------------------------------------------------
# get the log dir from the config and create it
#------------------------------------------------
logpath=`python << EOF 
import os
from myutils import BetterConfigParser
config = BetterConfigParser()
config.read('./${energy}config/paths')
print config.get('Directories','logpath')
EOF`
if [ ! -d $logpath ]
    then
    mkdir $logpath
fi

#-------------------------------------------------
#Set the environment for the batch job execution
#-------------------------------------------------
cd $CMSSW_BASE/src/
source /swshare/psit3/etc/profile.d/cms_ui_env.sh
export SCRAM_ARCH="slc5_amd64_gcc462"
source $VO_CMS_SW_DIR/cmsset_default.sh
eval `scramv1 runtime -sh`
#export LD_PRELOAD="libglobus_gssapi_gsi_gcc64pthr.so.0":${LD_PRELOAD}
export LD_LIBRARY_PATH=/swshare/glite/globus/lib/:/swshare/glite/d-cache/dcap/lib64/:$LD_LIBRARY_PATH
export LD_PRELOAD="libglobus_gssapi_gsi_gcc64pthr.so.0:${LD_PRELOAD}"
mkdir $TMPDIR

cd -   #back to the working dir

MVAList=`python << EOF 
import os
from myutils import BetterConfigParser
config = BetterConfigParser()
config.read('./${energy}config/training')
print config.get('MVALists','List_for_submitscript')
EOF`


#----------------------------------------------
# load from the paths the configs to be used
#----------------------------------------------
input_configs=`python << EOF 
import os
from myutils import BetterConfigParser
config = BetterConfigParser()
config.read('./${energy}config/paths')
print config.get('Configuration','List')
EOF`
required_number_of_configs=7                                             # set the number of required cconfig
input_configs_array=( $input_configs )                                   # create an array to count the number of elements
if [ ${#input_configs_array[*]} -ne $required_number_of_configs ]        # check if the list contains the right number of configs
    then 
    echo "@ERROR : The number of the elements in the config list is not correct"
    exit
fi
configList=${input_configs// / -C ${energy}config\/}                     # replace the spaces with ' -C '
echo "@LOG : The config list you are using is"
echo ${configList}


#------------------------------------
#Run the scripts
#------------------------------------

if [ $task = "prep" ]; then
    ./prepare_environment_with_config.py --samples $sample --config ${energy}config/${configList}
fi
if [ $task = "sys" ]; then
    ./write_regression_systematics.py --samples $sample --config ${energy}config/${configList}
fi
if [ $task = "eval" ]; then
    ./evaluateMVA.py --discr $MVAList --samples $sample --config ${energy}config/${configList}
fi
if [ $task = "syseval" ]; then
    ./write_regression_systematics.py --samples $sample --config ${energy}config/${configList}
    ./evaluateMVA.py --discr $MVAList --samples $sample --config ${energy}config/${configList}
fi
if [ $task = "train" ]; then
    ./train.py --training $sample --config ${energy}config/${configList} --local True
fi
if [ $task = "plot" ]; then
    ./tree_stack.py --region $sample --config ${energy}config/${configList}
fi
if [ $task = "dc" ]; then
    ./workspace_datacard.py --variable $sample --config ${energy}config/${configList}
fi
if [ $task = "split" ]; then
    ./split_tree.py --samples $sample --config ${energy}config/${configList} --max-events $job_id
fi

if [ $task = "mva_opt" ]; then
    if [ $# -lt 5 ]
	then
	echo "@ERROR: You passed " $# "arguments while BDT optimisation needs at least 5 arguments."
	echo "Exiting..."
	echo " ---------------------------------- "
	echo " Usage : ./runAll.sh sample energy task jo_id bdt_factory_settings"
	echo " ---------------------------------- "
	exit
    fi
    echo "BDT factory settings"
    echo $additional_arg
    echo "Runnning"
    ./train.py --name ${sample} --training ${job_id} --config ${energy}config/${configList} --setting ${additional_arg} --local False
fi

rm -rf $TMPDIR
