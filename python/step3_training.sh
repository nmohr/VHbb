#!/bin/bash
#Tight
var=''
./train.py RTight${var}_ZH110_may silent
./train.py RTight${var}_ZH115_may silent
./train.py RTight${var}_ZH120_may silent
./train.py RTight${var}_ZH125_may silent
./train.py RTight${var}_ZH130_may silent
./train.py RTight${var}_ZH135_may silent
#Med
./train.py RMed${var}_ZH110_may silent
./train.py RMed${var}_ZH115_may silent
./train.py RMed${var}_ZH120_may silent
./train.py RMed${var}_ZH125_may silent
./train.py RMed${var}_ZH130_may silent
./train.py RMed${var}_ZH135_may silent
