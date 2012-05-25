path=/scratch/May23
mkdir $path/env
ln -s $path/ZllH.May23.DataZ.root $path/ZllH.May23.DataZee.root
ln -s $path/ZllH.May23.DataZ.root $path/ZllH.May23.DataZmm.root
./prepare_environment.py $path $path/env/
./showinfo.py $path/env