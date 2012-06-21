#!/bin/bash
path=/shome/nmohr/VHbbAnalysis/EDMNtuple_step2/ichepApp1/
sys="4"
sys=""
en="8TeV"
# RTight EE
./workspace_datacard.py $path RTight${sys}_ZH110_EE_${en}
./workspace_datacard.py $path RTight${sys}_ZH115_EE_${en}
./workspace_datacard.py $path RTight${sys}_ZH120_EE_${en}
./workspace_datacard.py $path RTight${sys}_ZH125_EE_${en}
./workspace_datacard.py $path RTight${sys}_ZH130_EE_${en}
#./workspace_datacard.py $path RTight${sys}_ZH135_EE_${en}
## RTight MM
./workspace_datacard.py $path RTight${sys}_ZH110_MM_${en}
./workspace_datacard.py $path RTight${sys}_ZH115_MM_${en}
./workspace_datacard.py $path RTight${sys}_ZH120_MM_${en}
./workspace_datacard.py $path RTight${sys}_ZH125_MM_${en}
./workspace_datacard.py $path RTight${sys}_ZH130_MM_${en}
#./workspace_datacard.py $path RTight${sys}_ZH135_MM_${en}
## RMed EE
./workspace_datacard.py $path RMed${sys}_ZH110_EE_${en}
./workspace_datacard.py $path RMed${sys}_ZH115_EE_${en}
./workspace_datacard.py $path RMed${sys}_ZH120_EE_${en}
./workspace_datacard.py $path RMed${sys}_ZH125_EE_${en}
./workspace_datacard.py $path RMed${sys}_ZH130_EE_${en}
#./workspace_datacard.py $path RMed${sys}_ZH135_EE_${en}
## RMed MM
./workspace_datacard.py $path RMed${sys}_ZH110_MM_${en}
./workspace_datacard.py $path RMed${sys}_ZH115_MM_${en}
./workspace_datacard.py $path RMed${sys}_ZH120_MM_${en}
./workspace_datacard.py $path RMed${sys}_ZH125_MM_${en}
./workspace_datacard.py $path RMed${sys}_ZH130_MM_${en}
#./workspace_datacard.py $path RMed${sys}_ZH135_MM_${en}
