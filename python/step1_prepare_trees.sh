# Also edit ./prepare_environment.py !!!
path=/data1/VHbbAnalysis/EDMNtuple_step2/V12/5May12/Dilepton/
mkdir $path/env
./prepare_environment_with_config.py -I $path -O $path/env/ -C 7TeVsamples_ZZ.cfg
./showinfo.py $path/env
