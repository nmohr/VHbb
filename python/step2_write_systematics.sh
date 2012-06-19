path=/data1/nmohr/ichep8TeV/AddSample/env/
mkdir $path/sys
./write_regression_systematics.py $path ZH125
./showinfo.py $path/sys
