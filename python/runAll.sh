sample=$1
cd /shome/nmohr/CMSSW_5_2_4_patch4/src/
source /swshare/psit3/etc/profile.d/cms_ui_env.sh
export SCRAM_ARCH="slc5_amd64_gcc462"
source $VO_CMS_SW_DIR/cmsset_default.sh
eval `scramv1 runtime -sh`
unset TMP
unset TMPDIR
pathAna=/shome/nmohr/VHbbAnalysis/EDMNtuple_step2/Jun18/
execute=/shome/nmohr/CMSSW_5_2_4_patch4/src/UserCode/VHbb/python/
mkdir $pathAna/env/sys
cd $execute
./write_regression_systematics.py $pathAna/env/ $sample
mkdir $pathAna/env/sys/MVAout
./evaluateMVA.py $pathAna/env/sys/ RTight_ZH110_may,RTight_ZH115_may,RTight_ZH120_may,RTight_ZH125_may,RTight_ZH130_may,RTight_ZH135_may,RMed_ZH110_may,RMed_ZH115_may,RMed_ZH120_may,RMed_ZH125_may,RMed_ZH130_may,RMed_ZH135_may $sample 0
./showinfo.py $pathAna/env/sys
