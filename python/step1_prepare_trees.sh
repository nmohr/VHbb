# Also edit ./prepare_environment.py !!!
path=/shome/peller/DATA/HCP/
mkdir $path/env
./prepare_environment_with_config.py -I $path -O $path/env/ -C 8TeVsamples_nosplit.cfg
./showinfo.py $path/env
