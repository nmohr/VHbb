#ifndef samples_h
#define samples_h

#include <string>
#include <vector>
#include <TFile.h>
#include <TH1F.h>
#include <TTree.h>
#include <iostream>
#include <sstream>
#include "TMath.h"
#include <TCut.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct Sample {
  Sample();
Sample( float xs, std::string n, std::string f, int c, bool isdata, float datalumi=-1., float nEvents=-1 )
: xsec(xs),luminosity(datalumi),name(n),filename(f),color(c),data(isdata),f(0),nevents(nEvents) {}

  float lumi() {  if(data) return luminosity; else return numberOfEvents()/xsec; }
  float lumi(double fA, double fB) {  if(data) return luminosity; else return numberOfEvents(fA,fB)/xsec; }
  float scale(float l) { if(lumi()>0) return l/lumi(); else return 0;}
  float scale(float l, double *SF) { 
    std::string DYL("DYL");
    std::string DYC("DYC");
    std::string DYNoB("DYNoB");
    std::string DYB("DYB");
    std::string TTbar("TTbar");
    if(lumi()>0){
      if(name == DYL || name == DYC || name == DYNoB)
	return SF[0]*l/lumi();
      else if(name == DYB)
	return SF[1]*l/lumi();
      else if(name == TTbar) 
	return SF[2]*l/lumi(); 
      else
	return scale(l);
    }
    else 
      return 0; }

  float scale(float l, double fA, double fB) { if(lumi(fA,fB)>0) return l/lumi(fA,fB); else return 0;}
  float scale(float l, double fA, double fB, double *SF) { 
    std::string DYL("DYL");
    std::string DYC("DYC");
    std::string DYNoB("DYNoB");
    std::string DYB("DYB");
    std::string TTbar("TTbar");
    if(lumi(fA,fB)>0){
      if(name == DYL || name == DYC || name == DYNoB)
	return SF[0]*l/lumi(fA,fB);
      else if(name == TTbar) 
	return SF[1]*l/lumi(fA,fB); 
      else if(name == DYB)
	return SF[2]*l/lumi(fA,fB);
      else
	return scale(l,fA,fB);
    }
    else 
      return 0; }
  TFile * file() { if(f) return f; else return f=TFile::Open(filename.c_str());}
  float numberOfEvents( double fA, double fB ) 
  {
    if(data) return luminosity;
    double CountWithPU,CountWithPU2011B;
    double nOfEvents;
    if(nevents !=-1) return nevents;
    else
      {
       CountWithPU = ((TH1F*)file()->Get("CountWithPU"))->GetBinContent(1);
       CountWithPU2011B = ((TH1F*)file()->Get("CountWithPU2011B"))->GetBinContent(1);
       nOfEvents = fA*CountWithPU + fB*CountWithPU2011B;
       return nOfEvents;
      }
  }  

  float numberOfEvents() 
  {
    if(data) return luminosity;
    if(nevents !=-1) return nevents;
    else
      {
	//	return ((TH1F*)file()->Get("Count"))->GetBinContent(1);
	return  ((TH1F*)file()->Get("CountWithPU"))->GetBinContent(1);
      }
  }  

  void dump(float l)
  {
    std::cout << name <<  "\t& " << xsec << "\t& " <<  lumi()/1000 << "/fb \t& " << scale(l) << "\t& " << numberOfEvents() << std::endl;
    //     std::cout << name <<  "\t& " << xsec << "\t& " <<  lumi()/1000 << "/fb \t& " << scale(l) << std::endl;
    //     std::cout << name <<  "\t& " << xsec << "\t& " <<  lumi()/1000 << std::endl;
  }

  void dump(float l, double fa, double fb)
  {
    std::cout << name <<  "\t& " << xsec << "\t& " <<  lumi(fa,fb)/1000 << "/fb \t& " << scale(l,fa,fb) << "\t& " << numberOfEvents(fa,fb) << std::endl;
    //     std::cout << name <<  "\t& " << xsec << "\t& " <<  lumi()/1000 << "/fb \t& " << scale(l) << std::endl;
    //     std::cout << name <<  "\t& " << xsec << "\t& " <<  lumi()/1000 << std::endl;
  }
  
  float bareCount(TCut iCut){
    float NpassedEvents = 0;
    file()->cd();
    NpassedEvents = ((TTree*)file()->Get("tree"))->Draw("H.dPhi", iCut, "goff");
    return NpassedEvents;
  }
  
  float bareCount(TCut iWeight, TCut iCut){
    float NpassedEvents = 0;
    file()->cd();
    NpassedEvents = ((TTree*)file()->Get("tree"))->Draw("H.dPhi", iWeight * iCut, "goff");
    return NpassedEvents;
  }

  float bareCountError(TCut iCut){ bareCountError_ = 0; if(bareCount(iCut)>0) bareCountError_ = TMath::Sqrt(bareCount(iCut)); return bareCountError_; }
  
  float count(TCut iCut){
    float NweightedEvents = 0;
    if(data)
      return bareCount(iCut);
    else{
      TH1F* histo;
      ((TTree*)file()->Get("tree"))->Draw("H.dPhi>>histo", iCut, "goff");
      histo = (TH1F*)gDirectory->Get("histo");
      NweightedEvents = histo->Integral()/lumi();
      return NweightedEvents;
    }
  }

  float count(TCut iWeight, TCut iCut){
    float NweightedEvents = 0;
    if(data)
      return bareCount(iCut);
    else{
      TH1F* histo;
      ((TTree*)file()->Get("tree"))->Draw("H.dPhi>>histo", iWeight*iCut, "goff");
      histo = (TH1F*)gDirectory->Get("histo");
      NweightedEvents = histo->Integral()/lumi();
      return NweightedEvents;
    }
  }

  float count(TCut iCut, double fA, double fB){
    float NweightedEvents = 0;
    if(data)
      return bareCount(iCut);
    else{
      TH1F* histo;
      ((TTree*)file()->Get("tree"))->Draw("H.dPhi>>histo", iCut, "goff");
      histo = (TH1F*)gDirectory->Get("histo");
      NweightedEvents = histo->Integral()/lumi(fA, fB);
      return NweightedEvents;
    }
  }

  float count(TCut iWeight, TCut iCut, double fA, double fB){
    float NweightedEvents = 0;
    if(data)
      return bareCount(iCut);
    else{
      TH1F* histo;
      std::stringstream oss;
      srand( time(NULL) );
      int num = rand() % 10000 + 1;
      oss << num;
      std::string var("H.dPhi>>");
      std::string histoName("histo");
      histoName=histoName+name+oss.str();
      ((TTree*)file()->Get("tree"))->Draw((var+histoName).c_str(), iWeight*iCut, "goff");
      histo = (TH1F*)gDirectory->Get(histoName.c_str());
      NweightedEvents = histo->Integral()/lumi(fA, fB);
      return NweightedEvents;
    }
  }

  float countError(TCut iCut){ countError_ = count(iCut)/bareCountError(iCut); return countError_; }

  float countError(TCut iWeight, TCut iCut, double fA, double fB){ countError_ = 0; if(bareCountError(iCut)>0) countError_ = count(iWeight,iCut,fA, fB)/bareCountError(iCut); return countError_; }

  float countError(TCut iCut, float systematicError ){
    float totalError=0;
    if(systematicError < 1)
      totalError = TMath::Sqrt( TMath::Power(count(iCut)/bareCountError(iCut),2) + TMath::Power( systematicError*count(iCut),2) );
    else
      std::cout << "Systematic error has to be espressed in %" << std::endl;
    return totalError;
  }
  
  float addSysError( float error, float systematicError ){ return TMath::Sqrt( TMath::Power(error,2) + TMath::Power( systematicError,2) ); }
  
  void setCountError( float newCountError ){
    countError_ = newCountError;
  }
  

  float countError_;
  float bareCountError_;
  float nevents;
  float xsec;
  float luminosity;
  std::string name;
  std::string filename;
  int color;
  bool data;
  TFile * f;
  
}; 

#endif
