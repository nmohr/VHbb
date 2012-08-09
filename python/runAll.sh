sample=$1
cd /shome/nmohr/CMSSW_5_3_2/src/
source /swshare/psit3/etc/profile.d/cms_ui_env.sh
export SCRAM_ARCH="slc5_amd64_gcc462"
source $VO_CMS_SW_DIR/cmsset_default.sh
eval `scramv1 runtime -sh`
unset TMP
unset TMPDIR
pathAna=/shome/nmohr/VHbbAnalysis/EDMNtuple_step2/May5/
execute=/shome/nmohr/CMSSW_5_3_2/src/UserCode/VHbb/python/
config=config7TeV
mkdir $pathAna/env/sys
cd $execute
./write_regression_systematics.py $pathAna/env/ $sample -C ${config}
mkdir $pathAna/env/sys/MVAout
./evaluateMVA.py $pathAna/env/sys/ RTight_ZH110_may,RTight_ZH115_may,RTight_ZH120_may,RTight_ZH125_may,RTight_ZH130_may,RTight_ZH135_may,RMed_ZH110_may,RMed_ZH115_may,RMed_ZH120_may,RMed_ZH125_may,RMed_ZH130_may,RMed_ZH135_may $sample 0 -C ${config}
./showinfo.py $pathAna/env/sys
