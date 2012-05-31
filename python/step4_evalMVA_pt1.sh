path=/scratch/May23sys/
mkdir $path/MVAout
./evaluateMVA.py $path RTight_ZH110_may,RTight_ZH115_may,RTight_ZH120_may,RTight_ZH125_may,RTight_ZH130_may,RTight_ZH135_may,RMed_ZH110_may,RMed_ZH115_may,RMed_ZH120_may,RMed_ZH125_may,RMed_ZH130_may,RMed_ZH135_may WW,WZ,ZZ,TT,ST_s,ST_t,ST_tW,STbar_s,STbar_t,STbar_tW,ZH110,ZH115 1
#./evaluateMVA.py $path RTight_ZH110_may,RTight_ZH115_may,RTight_ZH120_may,RTight_ZH125_may,RTight_ZH130_may,RMed_ZH110_may,RMed_ZH115_may,RMed_ZH120_may,RMed_ZH125_may,RMed_ZH130_may ZZ 0
./showinfo.py $path/MVAout
