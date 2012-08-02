#!/usr/bin/env python
import sys
import os
import ROOT 
from ROOT import TFile
from array import array
from math import sqrt
from copy import copy
#suppres the EvalInstace conversion warning bug
import warnings
warnings.filterwarnings( action='ignore', category=RuntimeWarning, message='creating converter.*' )
from BetterConfigParser import BetterConfigParser
from samplesclass import sample
from mvainfos import mvainfo
import pickle
from progbar import progbar
from printcolor import printc

#CONFIGURE

#load config
config = BetterConfigParser()
config.read('./config')

#get locations:
Wdir=config.get('Directories','Wdir')

MVAdir=config.get('Directories','MVAdir')

#systematics
systematics=config.get('systematics','systematics')
systematics=systematics.split(' ')

#TreeVar Array
#MVA_Vars={}
#for systematic in systematics:
#    MVA_Vars[systematic]=config.get('treeVars',systematic)
#    MVA_Vars[systematic]=MVA_Vars[systematic].split(' ')

######################
#Evaluate multi: Must Have same treeVars!!!

Apath=sys.argv[1]
arglist=sys.argv[2] #RTight_blavla,bsbsb

namelistIN=sys.argv[3]
namelist=namelistIN.split(',')

doinfo=bool(int(sys.argv[4]))

MVAlist=arglist.split(',')

#CONFIG
#factory
factoryname=config.get('factory','factoryname')
#MVA
#MVAnames=[]
#for MVA in MVAlist:
#    print MVA
#    MVAnames.append(config.get(MVA,'MVAname'))
#print Wdir+'/weights/'+factoryname+'_'+MVAname+'.info'
#MVAinfofiles=[]
MVAinfos=[]
for MVAname in MVAlist:
    MVAinfofile = open(Wdir+'/weights/'+factoryname+'_'+MVAname+'.info','r')
    MVAinfos.append(pickle.load(MVAinfofile))
    MVAinfofile.close()
    
treeVarSet=MVAinfos[0].varset
#variables
#TreeVar Array
MVA_Vars={}
for systematic in systematics:
    MVA_Vars[systematic]=config.get(treeVarSet,systematic)
    MVA_Vars[systematic]=MVA_Vars[systematic].split(' ')
#Spectators:
#spectators=config.get(treeVarSet,'spectators')
#spectators=spectators.split(' ')
#progbar quatsch
longe=40
#Workdir
workdir=ROOT.gDirectory.GetPath()
#os.mkdir(Apath+'/MVAout')

#Book TMVA readers: MVAlist=["MMCC_bla","CC5050_bla"]
readers=[]
for MVA in MVAlist:
    readers.append(ROOT.TMVA.Reader("!Color:!Silent"))

#define variables and specatators
MVA_var_buffer = []
MVA_var_buffer4 = []
for i in range(len( MVA_Vars['Nominal'])):
    MVA_var_buffer.append(array( 'f', [ 0 ] ))
    for reader in readers:
        reader.AddVariable( MVA_Vars['Nominal'][i],MVA_var_buffer[i])
#MVA_spectator_buffer = []
#for i in range(len(spectators)):
#    MVA_spectator_buffer.append(array( 'f', [ 0 ] ))
#    for reader in readers:
#        reader.AddSpectator(spectators[i],MVA_spectator_buffer[i])
#Load raeder
for i in range(0,len(readers)):
    readers[i].BookMVA(MVAinfos[i].MVAname,MVAinfos[i].getweightfile())
#--> Now the MVA is booked

#Apply samples
infofile = open(Apath+'/samples.info','r')
Ainfo = pickle.load(infofile)
infofile.close()

#eval
for job in Ainfo:
    if eval(job.active):
        if job.name in namelist:
            #get trees:
            input = TFile.Open(job.getpath(),'read')
            outfile = TFile.Open(job.path+'/'+MVAdir+job.prefix+job.identifier+'.root','recreate')
            input.cd()
            obj = ROOT.TObject
            for key in ROOT.gDirectory.GetListOfKeys():
                input.cd()
                obj = key.ReadObj()
                #print obj.GetName()
                if obj.GetName() == job.tree:
                    continue
                outfile.cd()
                #print key.GetName()
                obj.Write(key.GetName())
            tree = input.Get(job.tree)
            nEntries = tree.GetEntries()
            outfile.cd()
            newtree = tree.CloneTree(0)

            #MCs:
            if job.type != 'DATA':
                MVA_formulas={}
                MVA_formulas4={}
                for systematic in systematics: 
                    #print '\t\t - ' + systematic
                    MVA_formulas[systematic]=[]
                    MVA_formulas4[systematic]=[]
                    #create TTreeFormulas
                    for j in range(len( MVA_Vars['Nominal'])):
                        MVA_formulas[systematic].append(ROOT.TTreeFormula("MVA_formula%s_%s"%(j,systematic),MVA_Vars[systematic][j],tree))
                        MVA_formulas4[systematic].append(ROOT.TTreeFormula("MVA_formula4%s_%s"%(j,systematic),MVA_Vars['Nominal'][j]+'+('+MVA_Vars[systematic][j]+'-'+MVA_Vars['Nominal'][j]+')*4',tree))#HERE change
                outfile.cd()
                #Setup Branches
                MVAbranches=[]
                MVAbranches4=[]
                for i in range(0,len(readers)):
                    MVAbranches.append(array('f',[0]*9))
                    MVAbranches4.append(array('f',[0]*9))
                    newtree.Branch(MVAinfos[i].MVAname,MVAbranches[i],'nominal:JER_up:JER_down:JES_up:JES_down:beff_up:beff_down:bmis_up:bmis_down/F')
                    newtree.Branch(MVAinfos[i].MVAname+'_4',MVAbranches4[i],'nominal:JER_up:JER_down:JES_up:JES_down:beff_up:beff_down:bmis_up:bmis_down/F')
                print '\n--> ' + job.name +':'
                #progbar setup
                if nEntries >= longe:
                    step=int(nEntries/longe)
                    long=longe
                else:
                    long=nEntries
                    step = 1
                bar=progbar(long)
                #Fill event by event:
                for entry in range(0,nEntries):
                    if entry % step == 0:
                        bar.move()
                    #load entry
                    tree.GetEntry(entry)
                    for systematic in systematics:
                        for j in range(len( MVA_Vars['Nominal'])):
                            MVA_var_buffer[j][0] = MVA_formulas[systematic][j].EvalInstance()
                            
                        for j in range(0,len(readers)):
                            MVAbranches[j][systematics.index(systematic)] = readers[j].EvaluateMVA(MVAinfos[j].MVAname)
                            
                        for j in range(len( MVA_Vars['Nominal'])):
                            MVA_var_buffer[j][0] = MVA_formulas4[systematic][j].EvalInstance()
                            
                        for j in range(0,len(readers)):
                            MVAbranches4[j][systematics.index(systematic)] = readers[j].EvaluateMVA(MVAinfos[j].MVAname)
                    #Fill:
                    newtree.Fill()
                newtree.AutoSave()
                outfile.Close()
                
            #DATA:
            if job.type == 'DATA':
                #MVA Formulas
                MVA_formulas_Nominal = []
                #create TTreeFormulas
                for j in range(len( MVA_Vars['Nominal'])):
                    MVA_formulas_Nominal.append(ROOT.TTreeFormula("MVA_formula%s_Nominal"%j, MVA_Vars['Nominal'][j],tree))
                outfile.cd()
                MVAbranches=[]
                for i in range(0,len(readers)):
                    MVAbranches.append(array('f',[0]))
                    newtree.Branch(MVAinfos[i].MVAname,MVAbranches[i],'nominal/F') 
                    newtree.Branch(MVAinfos[i].MVAname+'_4',MVAbranches[i],'nominal/F') 
                #progbar           
                print '\n--> ' + job.name +':'
                if nEntries >= longe:
                    step=int(nEntries/longe)
                    long=longe
                else:
                    long=nEntries
                    step = 1
                bar=progbar(long)
                #Fill event by event:
                for entry in range(0,nEntries):
                    if entry % step == 0:
                        bar.move()
                    #load entry
                    tree.GetEntry(entry)
                    #nominal:
                    for j in range(len( MVA_Vars['Nominal'])):
                            MVA_var_buffer[j][0] = MVA_formulas_Nominal[j].EvalInstance()
                            
                    for j in range(0,len(readers)):
                        MVAbranches[j][0]= readers[j].EvaluateMVA(MVAinfos[j].MVAname)
                    newtree.Fill()
                newtree.AutoSave()
                outfile.Close()

print '\n'

#Update Info:
if doinfo:
    for job in Ainfo:        
        for MVAinfo in MVAinfos:
            job.addcomment('Added MVA %s'%MVAinfo.MVAname)
        job.addpath(MVAdir)
    infofile = open(Apath+MVAdir+'/samples.info','w')
    pickle.dump(Ainfo,infofile)
    infofile.close()


