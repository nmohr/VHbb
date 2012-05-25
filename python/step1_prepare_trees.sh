# Also edit ./prepare_environment.py !!!
path=/scratch/May23Like
mkdir $path/env
ln -s $path/ZllH.May23Likelihood.DataZ.root $path/ZllH.May23Likelihood.DataZee.root
ln -s $path/ZllH.May23Likelihood.DataZ.root $path/ZllH.May23Likelihood.DataZmm.root
./prepare_environment.py $path $path/env/
./showinfo.py $path/env
