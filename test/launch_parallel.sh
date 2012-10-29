#!/bin/bash

if [ $# -lt 3 ]
    then
    echo "ERROR: You passed " $# "arguments while the script needs at least 3 arguments."
    echo "Exiting..."
    echo " ---------------------------------- "
    echo " Usage : ./launch_parallel.sh sample_name sample_type working_dir"
    echo " ---------------------------------- "
    exit
fi


cd $3

echo `pwd`
cd $CMSSW_BASE/src/
source /swshare/psit3/etc/profile.d/cms_ui_env.sh
export SCRAM_ARCH="slc5_amd64_gcc462"
source $VO_CMS_SW_DIR/cmsset_default.sh
eval `scramv1 runtime -sh`
export LD_LIBRARY_PATH=/swshare/glite/d-cache/dcap/lib/:$LD_LIBRARY_PATH
cd -

SAMPLENAME=$1
SAMPLETYPE=$2

./make_histos_parallel $SAMPLENAME $SAMPLETYPE