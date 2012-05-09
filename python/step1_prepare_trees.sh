path=/scratch/May08
mkdir $path/env
ln -s $path/ZllH.May8Reg.DataZ.root $path/ZllH.May8Reg.DataZee.root
ln -s $path/ZllH.May8Reg.DataZ.root $path/ZllH.May8Reg.DataZmm.root
./prepare_environment.py
./showinfo.py $path/env
