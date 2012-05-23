#!/usr/bin/env python
from copytree import copytree
from printcolor import printc
from samplesclass import sample
import pickle
import sys

prefix='ZllH.May23.'

lumi=4980

#pathIN='/scratch/May08/'
#pathOUT='/scratch/May08/env/'

pathIN=sys.argv[1]
pathOUT=sys.argv[2]

weightexpression='((0.46502*PUweight+0.53498*PUweight2011B)*weightTrig)'

#this is only to speed it up, remove for final trees!
Precut='& V.pt > 50 & V.mass > 75. & V.mass < 105 & hJet_pt[0] > 20. & hJet_pt[1] > 20. & abs(hJet_eta[0]) < 2.4 & abs(hJet_eta[1]) < 2.4'



#Montecarlos
InFiles0 = ['WW_TuneZ2_7TeV_pythia6_tauola', 'WZ_TuneZ2_7TeV_pythia6_tauola','ZZ_TuneZ2_7TeV_pythia6_tauola','TTJets_TuneZ2_7TeV-madgraph-tauola','T_TuneZ2_s-channel_7TeV-powheg-tauola','T_TuneZ2_t-channel_7TeV-powheg-tauola', 'T_TuneZ2_tW-channel-DR_7TeV-powheg-tauola','Tbar_TuneZ2_s-channel_7TeV-powheg-tauola','Tbar_TuneZ2_t-channel_7TeV-powheg-tauola', 'Tbar_TuneZ2_tW-channel-DR_7TeV-powheg-tauola','ZH_ZToLL_HToBB_M-110_7TeV-powheg-herwigpp','ZH_ZToLL_HToBB_M-115_7TeV-powheg-herwigpp','ZH_ZToLL_HToBB_M-120_7TeV-powheg-herwigpp','ZH_ZToLL_HToBB_M-125_7TeV-powheg-herwigpp','ZH_ZToLL_HToBB_M-130_7TeV-powheg-herwigpp']
samplenames0 =['WW','WZ','ZZ','TT','ST_s','ST_t','ST_tW','STbar_s','STbar_t','STbar_tW','ZH110','ZH115','ZH120','ZH125','ZH130']
sampletypes0 =['BKG','BKG','BKG','BKG','BKG','BKG','BKG','BKG','BKG','BKG','SIG','SIG','SIG','SIG','SIG']
samplesgroup0=['VV','VV','VV','TT','ST','ST','ST','ST','ST','ST','ZH','ZH','ZH','ZH','ZH']
xsecs0 = [42.9, 18.3, 5.9, 165, 3.19, 41.92, 7.87, 1.44, 22.65, 7.87, 0.4721*0.100974*0.745, 0.4107*0.100974*0.704, 0.3598*0.100974*0.648, 0.3158*0.100974*0.577, 0.2778*0.100974*0.493]
SF0=[1.0,1.0,1.0,1.04,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0,1.0]
Aprefix0 = ['']
cut0 = ['(Vtype == 1 || Vtype == 0) && EVENT.json && hbhe']

#split DY in flavours
#genZpt < 120
InFiles1 = ['DYJetsToLL_TuneZ2_M-50_7TeV-madgraph-tauola']*3
samplenames1 =['Zudsg','Zbb','Zcc']
sampletypes1 =['BKG']*3
samplesgroup1=['DYlight','DYb','DYc']
xsecs1 = [3048]*3
SF1=[1.00,0.95,1.24]
Aprefix1 = ['udsg_120_', 'b_120_','c_120_']
cut1 = ['(Vtype == 1 || Vtype == 0) & EVENT.json & hbhe & eventFlav != 5 & eventFlav != 4 & genZpt <= 120.','(Vtype == 1 || Vtype == 0) & EVENT.json & hbhe & eventFlav == 5 & genZpt <= 120.','(Vtype == 1 || Vtype == 0) & EVENT.json & hbhe & eventFlav == 4 & genZpt <= 120.']

#genZpt > 120
InFiles2 = ['DYJetsToLL_PtZ-100_TuneZ2_7TeV-madgraph-tauola']*3
samplenames2 =['Zudsg_pt120','Zbb_pt120','Zcc_pt120']
sampletypes2 =['BKG']*3
samplesgroup2=['DYlight','DYb','DYc']
xsecs2 = [30]*3
SF2=[1.00,0.95,1.24]
Aprefix2 = ['udsg_120_', 'b_120_','c_120_']
cut2 = ['(Vtype == 1 || Vtype == 0) & EVENT.json & hbhe & eventFlav != 5 & eventFlav != 4 & genZpt > 120.','(Vtype == 1 || Vtype == 0) & EVENT.json & hbhe & eventFlav == 5 & genZpt > 120.','(Vtype == 1 || Vtype == 0) & EVENT.json & hbhe & eventFlav == 4 & genZpt > 120.']

#The Data
dataFiles = ['DataZee', 'DataZmm']
datanames =['Zee','Zmm']
datatypes =['DATA','DATA']
datagroup=['DATA','DATA']
AdataPrefix = ['']
datacuts=['(Vtype==1 && EVENT.json && hbhe) && (triggerFlags[5] | triggerFlags[6])','(Vtype==0 && EVENT.json && hbhe)&&((EVENT.run<173198 && (triggerFlags[0]>0 || triggerFlags[13]>0 || triggerFlags[14]>0 || triggerFlags[20]>0 || triggerFlags[21]>0)) || (EVENT.run>=173198 && EVENT.run<175832  && (triggerFlags[13]>0 ||triggerFlags[14]>0 || triggerFlags[22]>0 || triggerFlags[23]>0))|| (EVENT.run>=175832 && EVENT.run<178390 && (triggerFlags[13]>0 ||triggerFlags[14]>0 ||triggerFlags[15]>0 || triggerFlags[21]>0 || triggerFlags[22]>0 || triggerFlags[23]>0)) || (EVENT.run>=178390 && (triggerFlags[14]>0 ||triggerFlags[15]>0 || triggerFlags[21]>0 || triggerFlags[22]>0 || triggerFlags[23]>0 || triggerFlags[24]>0 || triggerFlags[25]>0 || triggerFlags[26]>0 || triggerFlags[27]>0)))']





info = []

#prepare the files:

# i>1 because no WW sample!!! only temporary fix

for i in range(0,len(InFiles0)):
    #copytree(pathIN,pathOUT,prefix,InFiles0[i],Aprefix0[0],cut0[0]+Precut)
    info.append(sample(samplenames0[i],sampletypes0[i]))
    info[-1].path=pathOUT
    info[-1].identifier=Aprefix0[0]+InFiles0[i]
    info[-1].weightexpression=weightexpression
    info[-1].group=samplesgroup0[i]
    info[-1].lumi=lumi
    info[-1].prefix=prefix
    info[-1].xsec=xsecs0[i]
    info[-1].sf=SF0[i]
    info[-1].addtreecut(cut0[0])

for i in range(3):
    #copytree(pathIN,pathOUT,prefix,InFiles1[i],Aprefix1[i],cut1[i]+Precut)
    info.append(sample(samplenames1[i],sampletypes1[i]))
    info[-1].path=pathOUT
    info[-1].identifier=Aprefix1[i]+InFiles1[i]
    info[-1].weightexpression=weightexpression
    info[-1].group=samplesgroup1[i]
    info[-1].lumi=lumi
    info[-1].prefix=prefix
    info[-1].xsec=xsecs1[i]
    info[-1].sf=SF1[i]
    info[-1].addtreecut(cut1[i])
    
for i in range(3):
    #copytree(pathIN,pathOUT,prefix,InFiles2[i],Aprefix2[i],cut2[i]+Precut)
    info.append(sample(samplenames2[i],sampletypes2[i]))
    info[-1].path=pathOUT
    info[-1].identifier=Aprefix2[i]+InFiles2[i]
    info[-1].weightexpression=weightexpression
    info[-1].group=samplesgroup2[i]
    info[-1].lumi=lumi
    info[-1].prefix=prefix
    info[-1].xsec=xsecs2[i]
    info[-1].sf=SF2[i]
    info[-1].addtreecut(cut2[i])
 
for i in range(0,len(dataFiles)):
    copytree(pathIN,pathOUT,prefix,dataFiles[i],AdataPrefix[0],datacuts[i]+Precut)
    info.append(sample(datanames[i],datatypes[i]))
    info[-1].path=pathOUT
    info[-1].identifier=AdataPrefix[0]+dataFiles[i]
    info[-1].group=datagroup[i]
    info[-1].lumi=lumi
    info[-1].prefix=prefix
    info[-1].addtreecut(datacuts[i])


#dump info   
infofile = open(pathOUT+'/samples.info','w')
pickle.dump(info,infofile)
infofile.close()
