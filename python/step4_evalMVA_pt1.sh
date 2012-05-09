path=/scratch/May08/env/sys/
mkdir $path/MVAout
./evaluateMVA.py $path RTight_ZH110_may,RTight_ZH115_may,RTight_ZH120_may,RTight_ZH125_may,RTight_ZH130_may,RMed_ZH110_may,RMed_ZH115_may,RMed_ZH120_may,RMed_ZH125_may,RMed_ZH130_may 0 12 1
./showinfo.py $path/MVAout
