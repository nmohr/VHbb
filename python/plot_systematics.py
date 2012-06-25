#!/usr/bin/env python
import ROOT 
from ROOT import TFile
from Ratio import getRatio


#Abin='RMed4'
#mass='125'
#channel='Zee'
path='~/VHbb/Limits/ICHEP'
outpath='~/VHbb/Stacks/ICHEP/'

xMin=-1
xMax=1
#MC='ZjCF'
#syst='CMS_beff'

for mass in ['110','115','120','125','130','135']:
    for Abin in ['RMed4','RTight4']:
        for channel in ['Zee','Zmm']:

            input = TFile.Open(path+'/vhbb_TH_BDT'+Abin+'_M'+mass+'_'+channel+'.root','read')


            for MC in ['VH','ZjLF','ZjHF','VV','TT','s_Top']:
                for syst in ['JER','JEC','Btag','BtagFake']:
                #for syst in ['CMS_vhbb_stats_']:

                    ROOT.gROOT.SetStyle("Plain")
                    c = ROOT.TCanvas('canvas','canvas', 800, 700)
                    oben = ROOT.TPad('oben','oben',0,0.2 ,1.0,1.0,10)
                    unten = ROOT.TPad('unten','unten',0,0.05,1.0,0.2,10)
                    oben.Draw()
                    unten.Draw()
                    oben.cd()
                    ROOT.gPad.SetTicks(1,1)


                    Ntotal=input.Get(MC)
                    Utotal=input.Get(MC+syst+'Up')
                    #Utotal=input.Get(MC+syst+MC+'_'+channel+'Up')
                    Dtotal=input.Get(MC+syst+'Down')
                    #Dtotal=input.Get(MC+syst+MC+'_'+channel+'Down')
                    l = ROOT.TLegend(0.11, 0.89, 0.3, 0.7)
                    l.AddEntry(Ntotal,'nominal','PL')
                    l.AddEntry(Utotal,'up','PL')
                    l.AddEntry(Dtotal,'down','PL')
                    Ntotal.SetMarkerStyle(8)
                    Ntotal.SetLineColor(1)
                    Ntotal.SetStats(0)
                    Ntotal.SetTitle(MC +' '+syst)
                    Ntotal.Draw("P0")
                    Ntotal.Draw("same")
                    Utotal.SetLineColor(4)    
                    Utotal.SetLineStyle(4)
                    Utotal.SetLineWidth(2)        
                    Utotal.Draw("same hist")
                    Dtotal.SetLineColor(2)
                    Dtotal.SetLineStyle(3)
                    Dtotal.SetLineWidth(2)  
                    Dtotal.Draw("same hist")
                    l.SetFillColor(0)
                    l.SetBorderSize(0)
                    l.Draw()
                    
                    
                    unten.cd()
                    ROOT.gPad.SetTicks(1,1)

                    ratioU, errorU, ksScoreU, chiScoreU = getRatio(Utotal,Ntotal,xMin,xMax,"Ratio",10,True)
                    ratioD, errorD, ksScoreD, chiScoreD = getRatio(Dtotal,Ntotal,xMin,xMax,"Ratio",10,True)

                    ratioU.SetStats(0)
                    ratioU.GetYaxis().SetRangeUser(0.5,1.5)
                    ratioU.GetYaxis().SetNdivisions(502,0)
                    ratioU.GetYaxis().SetLabelSize(0.2)
                    ratioU.GetYaxis().SetTitleSize(0.2)
                    ratioU.GetYaxis().SetTitleOffset(0.2)
                    ratioU.GetXaxis().SetLabelColor(10)
                    ratioU.SetLineColor(4)    
                    ratioU.SetLineStyle(4)
                    ratioU.SetLineWidth(2)        
                    ratioU.Draw("hist")
                    ratioU.SetTitle("")
                    ratioD.SetStats(0)
                    ratioD.GetYaxis().SetRangeUser(0.5,1.5)
                    ratioD.GetYaxis().SetNdivisions(502,0)
                    ratioD.GetYaxis().SetLabelSize(0.2)
                    ratioD.GetYaxis().SetTitleSize(0.2)
                    ratioD.GetYaxis().SetTitleOffset(0.2)
                    ratioD.GetXaxis().SetLabelColor(10)
                    ratioD.SetLineColor(2)
                    ratioD.SetLineStyle(3)
                    ratioD.SetLineWidth(2)  
                    ratioD.Draw("hist same")
                    ratioD.SetTitle("")
                    m_one_line = ROOT.TLine(xMin,1,xMax,1)
                    m_one_line.SetLineStyle(7)
                    m_one_line.SetLineColor(4)
                    m_one_line.Draw("Same")

                    

                    #name = outpath+Abin+'_M'+mass+'_'+channel+'_'+MC+syst+'.png'
                    #c.Print(name)
                    name = outpath+Abin+'_M'+mass+'_'+channel+'_'+MC+syst+'.pdf'
                    c.Print(name)


            input.Close()