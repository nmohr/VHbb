#ifndef CONTROLREGION_H
#define CONTROLREGION_H

#include "samples.hpp"
#include "ntupleReader.hpp"
#include "CutsAndHistos.h"
#include "TH1.h"
#include <string>

class controlRegion{

 public:
  controlRegion(){ init(); };
 controlRegion( double lumi_, double f_a, double f_b )
   :lumi(lumi_), fa(f_a), fb(f_b){ init(); };
  ~controlRegion() {};

  void setName(std::string name_){ name = name_; }
  std::string getName(){ return name; }

  double sqrtSum( double ex, double ey ){
    if(ex != 0 || ey != 0)
      return sqrt(ex*ex + ey*ey) ;
    else 
      return 0;
  }

  double cData(){return data;}  
  double cSignal(){return signal;}
  double cDYL(){return dyl;}
  double cDYC(){return dyc;}
  double cDYB(){return dyb;}
  double cTTbar(){return ttbar;}
  double cVV(){return vv;}
  double cST(){return st;}
  double cWJETS(){return wjets;}
  double cOthers(){return others;}
  double cRest(){ return ( data-(vv+st+wjets+others) );}
  double cTotal(){return dyl+dyc+dyb+ttbar+vv+st+wjets+others;}

  TH1F * hData(){ hdata = new TH1F(*(TH1F*)(list_data->At(0))); hdata->Reset(); hdata->Merge(list_data); return hdata;}  
  TH1F * hSignal(){ hsignal = new TH1F(*(TH1F*)(list_signal->At(0))); hsignal->Reset(); hsignal->Merge(list_signal); return hsignal;}
  TH1F * hDYL(){ hdyl = new TH1F(*(TH1F*)(list_dyl->At(0))); hdyl->Reset(); hdyl->Merge(list_dyl); return hdyl;}
  TH1F * hDYC(){ hdyc = new TH1F(*(TH1F*)(list_dyc->At(0))); hdyc->Reset(); hdyc->Merge(list_dyc); return hdyc;}
  TH1F * hDYB(){ hdyb = new TH1F(*(TH1F*)(list_dyb->At(0))); hdyb->Reset(); hdyb->Merge(list_dyb); return hdyb;}
  TH1F * hTTbar(){ httbar = new TH1F(*(TH1F*)(list_ttbar->At(0))); httbar->Reset(); httbar->Merge(list_ttbar); return httbar;}
  TH1F * hVV(){ hvv = new TH1F(*(TH1F*)(list_vv->At(0))); hvv->Reset(); hvv->Merge(list_vv); return hvv;}
  TH1F * hST(){ hst = new TH1F(*(TH1F*)(list_st->At(0))); hst->Reset(); hst->Merge(list_st);  return hst;}
  TH1F * hWJETS(){hwjets = new TH1F(*(TH1F*)(list_wjets->At(0))); hwjets->Reset(); hwjets->Merge(list_wjets); return hwjets;}
  TH1F * hOthers(){ hothers = new TH1F(*(TH1F*)(list_others->At(0))); hothers->Reset(); hothers->Merge(list_others); return hothers;}
  TH1F * hTotal(){ htotal = new TH1F(*(TH1F*)(list_total->At(0))); htotal->Reset(); htotal->Merge(list_total); return htotal;}

  double eData(){if(data > 0) err_data = sqrt(data); return err_data;}  
  double eSignal(){return err_signal;}
  double eDYL(){return err_dyl;}
  double eDYC(){return err_dyc;}
  double eDYB(){return err_dyb;}
  double eTTbar(){return err_ttbar;}
  double eVV(){return err_vv = sqrtSum( err_vv, 0.3*vv );}
  double eST(){return err_st = sqrtSum( err_st, 0.3*st );}
  double eWJETS(){return err_wjets;}
  double eOthers(){return err_others;}
  double eRest(){ return sqrt( eData()*eData() + eVV()*eVV() + eST()*eST() + eWJETS()*eWJETS() + eOthers()*eOthers() );}
  double eTotal(){ return sqrt( eDYL()*eDYL() + eDYC()*eDYC() + eDYB()*eDYB() + eTTbar()*eTTbar() + eVV()*eVV() + eST()*eST() + eWJETS()*eWJETS() + eOthers()*eOthers() );}

  double count( std::string type ){
    if( ((int)type.find("+")) > 0 ) return combinedCount( type );
    if( type == Run2011A_s || type == Run2011B_s ){ return cData(); }
    else{
      if(type == Signal_s){ return cSignal(); }
      else if(type == DYL_s ){ return cDYL(); }
      else if(type == DYC_s ){ return cDYC(); }
      else if(type == DYB_s ){  return cDYB(); }
      else if(type == TTbar_s){  return cTTbar(); }
      else if(type == VV_s){ return cVV(); }
      else if(type == ST_s){ return cST();  }
      else if(type == WJETS_s){ return cWJETS();  }
      else{  return cOthers();  }
    }
  }
  double combinedCount( std::string type ){
    count_comb = 0;
    std::vector<std::string> types;
    size_t pos = type.size();
    while ( (int)pos > 0){
      std::cout << type << " has size = " << (int)pos << std::endl; 
      pos = type.rfind("+");
      std::cout << type << " has size = " << (int)pos << std::endl; 
      if( (int)pos > 0){
	types.push_back( type.substr(pos+1) ); 
	type.resize(pos);
      }
      else
	types.push_back( type );
    }
    for(size_t t=0; t<types.size(); ++t){
      std::cout << types.at(t) << std::endl;
      count_comb += count( types.at(t) );
    }
    return count_comb;
  }

  TH1F * histo( std::string type ){
    if( ((int)type.find("+")) > 0 ) return combinedHistos( type );    
    if( type == Run2011A_s || type == Run2011B_s ){ return hData(); }
    else{
      if(type == Signal_s){ return hSignal(); }
      else if(type == DYL_s ){ return hDYL(); }
      else if(type == DYC_s ){ return hDYC(); }
      else if(type == DYB_s ){  return hDYB(); }
      else if(type == TTbar_s){  return hTTbar(); }
      else if(type == VV_s){ return hVV(); }
      else if(type == ST_s){ return hST();  }
      else if(type == WJETS_s){ return hWJETS();  }
      else{  return hOthers();  }
    }
  }

  TH1F * combinedHistos( std::string type ){
    std::cout << "Combine histos " << std::endl;
    std::vector<std::string> types;
    size_t pos = type.size();
    while ((int)pos > 0){
      std::cout << type << " has size = " << (int)pos << std::endl; 
      pos = type.rfind("+");
      std::cout << type << " has size = " << (int)pos << std::endl; 
      if( (int)pos > 0 ){
	types.push_back( type.substr(pos+1) ); 
	type.resize(pos);
      }
      else
	types.push_back( type );
    }
    for(size_t t=0; t<types.size(); ++t)
      list_comb->Add( histo(types.at(t)) );
    h_comb = new TH1F(*(TH1F*)(list_comb->At(0))); h_comb->Reset(); h_comb->Merge(list_comb);  return h_comb;
  }

  void dump(){
    std::cout << "Data            = " << cData() << std::endl;
    std::cout << "Signal          = " << cSignal() << std::endl;
    std::cout << "DrellYann light = " << cDYL() << std::endl;
    std::cout << "DrellYann charm = " << cDYC() << std::endl;
    std::cout << "DrellYann b     = " << cDYB() << std::endl;
    std::cout << "TTbar           = " << cTTbar() << std::endl;
    std::cout << "Diboson         = " << cVV() << std::endl;
    std::cout << "Single Top      = " << cST() << std::endl;
    std::cout << "Wjets           = " << cWJETS() << std::endl;
    std::cout << "Others          = " << cOthers() << std::endl;
    std::cout << "Total MC        = " << cTotal() << std::endl;
  }


  void fillFromHisto( Sample & sample, TH1F & histo, double min=-1e10, double max=1e10 ){
    if(sample.data){
      data += histo.Integral(min,max);
      list_data->Add(&histo);
    }
    else{
      if(sample.name == Signal_s){
	signal = histo.Integral(min,max);
	list_signal->Add(&histo);
	bcsignal=0;
	err_signal = sqrtSum( err_signal, TMath::Sqrt(signal) );
      }
      else{
	list_total->Add(&histo);
	if(sample.name == DYL_s ){
	  dyl += histo.Integral(min,max);
	  list_dyl->Add(&histo);
	  bcdyl=0;
	  err_dyl = sqrtSum( err_dyl, TMath::Sqrt(dyl) );
	}
	else if(sample.name == DYC_s ){
	  dyc += histo.Integral(min,max);
	  list_dyc->Add(&histo);
	  bcdyc=0;
	  err_dyc = sqrtSum( err_dyl, TMath::Sqrt(dyc) );
	}
	else if(sample.name == DYB_s ){
	  dyb += histo.Integral(min,max);
	  list_dyb->Add(&histo);
	  bcdyb=0;
	  err_dyb = sqrtSum( err_dyl, TMath::Sqrt(dyb) );
	}
	else if(sample.name == TTbar_s){
	  ttbar += histo.Integral(min,max);
	  list_ttbar->Add(&histo);
	  bcttbar=0;
	  err_ttbar = sqrtSum( err_ttbar, TMath::Sqrt(ttbar) );
	}
	else if(sample.name == VV_s){
	  vv +=  histo.Integral(min,max);
	  list_vv->Add(&histo);
	  bcvv=0;
	  err_vv = sqrtSum( err_vv, TMath::Sqrt(vv) );
	}
	else if(sample.name == ST_s){
	  st +=  histo.Integral(min,max);
	  list_st->Add(&histo);
	  bcst=0;
	  err_st = sqrtSum( err_st, TMath::Sqrt(st) );
	}
	else if(sample.name == WJETS_s){
	  wjets +=  histo.Integral(min,max);
	  list_wjets->Add(&histo);
	  bcwjets=0;
	  err_wjets = sqrtSum( err_wjets, TMath::Sqrt(wjets) );
	}
	else{
	  std::cout << "WARNING: Others counter non zero!" << std::endl;
	  others +=  histo.Integral(min,max);
	  list_others->Add(&histo);
	  bcothers=0;
	  err_others = sqrtSum( err_others, TMath::Sqrt(others) );
	}
      }
    }
  }


  void fill( Sample &sample, CutSample &cut, PCutSet &addCut, int n, ntupleReader &ev){
    bool ok = cut.pass( ev, sample );
    bool addOk = addCut.pass( ev, n );
    double scale = sample.scale(lumi,fa,fb);
    double weight = sample.scale(lumi,fa,fb) * cut.weight( ev , sample );
    if(!ok || !addOk)
      return;
    else{
      if(sample.data)
	data++;
      else{
	if(sample.name == Signal_s){
	  signal += weight;
	  bcsignal++;
	  err_signal = sqrtSum( err_signal, weight );
	}
	else if(sample.name == DY_s || sample.name == DYBOOSTED_s){
	  if( TMath::Abs(ev.eventFlav) < 4){
	    dyl += weight;
	    bcdyl++;
	    err_dyl = sqrtSum( err_dyl, weight );
	  }
	  else if( TMath::Abs(ev.eventFlav) == 4){
	    dyc += weight;
	    bcdyc++;
	    err_dyc = sqrtSum( err_dyc, weight );
	  }
	  else if( TMath::Abs(ev.eventFlav) == 5){
	    dyb += weight;
	    bcdyb++;
	    err_dyb = sqrtSum( err_dyb, weight );
	  }
	}
	else if(sample.name == TTbar_s){
	  ttbar += weight;
	  bcttbar++;
	  err_ttbar = sqrtSum( err_ttbar, weight );
	}
	else if(sample.name == VV_s){
	  vv += weight;
	  bcvv++;
	  err_vv = sqrtSum( err_vv, weight );
	}
	else if(sample.name == ST_s){
	  st += weight;
	  bcst++;
	  err_st = sqrtSum( err_st, weight );
	}
	else if(sample.name == WJETS_s){
	  wjets += weight;
	  bcwjets++;
	  err_wjets = sqrtSum( err_wjets, weight );
	}
	else{
	  std::cout << "WARNING: Others counter non zero!" << std::endl;
	  others += weight;
	  bcothers++;
	  err_others = sqrtSum( err_others, weight );
	}
      }
    }
  }

  void fill( Sample &sample, CutSample &cut,  ntupleReader &ev){
    bool ok = cut.pass( ev, sample );
    double scale = sample.scale(lumi,fa,fb);
    double weight = sample.scale(lumi,fa,fb) * cut.weight( ev , sample );
    if(!ok)
      return;
    else{
      if(sample.data)
	data++;
      else{
	if(sample.name == Signal_s){
	  signal += weight;
	  bcsignal++;
	  err_signal = sqrtSum( err_signal, weight );
	}
	else if(sample.name == DY_s || sample.name == DYBOOSTED_s){
	  if( TMath::Abs(ev.eventFlav) < 4){
	    dyl += weight;
	    bcdyl++;
	    err_dyl = sqrtSum( err_dyl, weight );
	  }
	  else if( TMath::Abs(ev.eventFlav) == 4){
	    dyc += weight;
	    bcdyc++;
	    err_dyc = sqrtSum( err_dyc, weight );
	  }
	  else if( TMath::Abs(ev.eventFlav) == 5){
	    dyb += weight;
	    bcdyb++;
	    err_dyb = sqrtSum( err_dyb, weight );
	  }
	}
	else if(sample.name == TTbar_s){
	  ttbar += weight;
	  bcttbar++;
	  err_ttbar = sqrtSum( err_ttbar, weight );
	}
	else if(sample.name == VV_s){
	  vv += weight;
	  bcvv++;
	  err_vv = sqrtSum( err_vv, weight );
	}
	else if(sample.name == ST_s){
	  st += weight;
	  bcst++;
	  err_st = sqrtSum( err_st, weight );
	}
	else if(sample.name == WJETS_s){
	  wjets += weight;
	  bcwjets++;
	  err_wjets = sqrtSum( err_wjets, weight );
	}
	else{
	  std::cout << "WARNING: Others counter non zero!" << std::endl;
	  others += weight;
	  bcothers++;
	  err_others = sqrtSum( err_others, weight );
	}
      }
    }
  }


  void fill( Sample& sample, double entries){
    double weight = entries;
    if(sample.data)
      data++;
    else{
      if(sample.name == Signal_s){
	signal += weight;
	bcsignal++;
	err_signal = sqrtSum( err_signal, weight );
      }
      else if(sample.name == DYL_s ){
	dyl += weight;
	bcdyl++;
	err_dyl = sqrtSum( err_dyl, weight );
      }
      else if(sample.name == DYC_s ){
	dyc += weight;
	bcdyc++;
	err_dyc = sqrtSum( err_dyc, weight );
      }
      else if(sample.name == DYB_s ){
	dyb += weight;
	bcdyb++;
	err_dyb = sqrtSum( err_dyb, weight );
      }
      else if(sample.name == TTbar_s){
	ttbar += weight;
	bcttbar++;
	err_ttbar = sqrtSum( err_ttbar, weight );
      }
      else if(sample.name == VV_s){
	vv += weight;
	bcvv++;
	err_vv = sqrtSum( err_vv, weight );
      }
      else if(sample.name == ST_s){
	st += weight;
	bcst++;
	err_st = sqrtSum( err_st, weight );
      }
      else if(sample.name == WJETS_s){
	wjets += weight;
	bcwjets++;
	err_wjets = sqrtSum( err_wjets, weight );
      }
      else{
	std::cout << "WARNING: Others counter non zero!" << std::endl;
	others += weight;
	bcothers++;
	err_others = sqrtSum( err_others, weight );
      }
    }
  }

  
  void init(){

    list_data = new TList;
    list_signal = new TList;
    list_dyl = new TList;
    list_dyc = new TList;
    list_dyb = new TList;
    list_ttbar = new TList;
    list_vv = new TList;
    list_st = new TList;
    list_wjets = new TList;
    list_others = new TList;
    list_total = new TList;
    list_comb = new TList;

   data=0;  
   signal=0;
   dyl=0;
   dyc=0;
   dyb=0;
   ttbar=0;
   vv=0;
   st=0;
   wjets=0;
   others=0;

   bcdata=0;  
   bcsignal=0;
   bcdyl=0;
   bcdyc=0;
   bcdyb=0;
   bcttbar=0;
   bcvv=0;
   bcst=0;
   bcwjets=0;
   bcothers=0;

   err_data=0;  
   err_signal=0;
   err_dyl=0;
   err_dyc=0;
   err_dyb=0;
   err_ttbar=0;
   err_vv=0;
   err_st=0;
   err_wjets=0;
   err_others=0;
   
   Run2011A_s = "Run2011A";
   Run2011B_s = "Run2011B";
   Signal_s = "ZH";
   DYL_s = "DYL";
   DYC_s = "DYC";
   DYB_s = "DYB";
   DY_s = "DY";
   DYBOOSTED_s = "DYBOOSTED";
   TTbar_s = "TTbar";
   VV_s = "VV";
   ST_s = "ST";
   WJETS_s = "WJ";

  }
  
 private:

  double lumi;
  double fa;
  double fb;
  std::string name;

  std::string Run2011A_s;
  std::string Run2011B_s;
  std::string Signal_s;
  std::string DYL_s;
  std::string DYC_s;
  std::string DYB_s;
  std::string DY_s;
  std::string DYBOOSTED_s;
  std::string TTbar_s;
  std::string VV_s;
  std::string ST_s;
  std::string WJETS_s;

  double data;  
  double signal;
  double dyl;
  double dyc;
  double dyb;
  double ttbar;
  double vv;
  double st;
  double wjets;
  double others;
  double count_comb;

  double bcdata;  
  double bcsignal;
  double bcdyl;
  double bcdyc;
  double bcdyb;
  double bcttbar;
  double bcvv;
  double bcst;
  double bcwjets;
  double bcothers;

  TH1F * hdata;  
  TH1F * hsignal;
  TH1F * hdyl;
  TH1F * hdyc;
  TH1F * hdyb;
  TH1F * httbar;
  TH1F * hvv;
  TH1F * hst;
  TH1F * hwjets;
  TH1F * hothers;
  TH1F * htotal;
  TH1F * h_comb;

  TList * list_data;  
  TList * list_signal;
  TList * list_dyl;
  TList * list_dyc;
  TList * list_dyb;
  TList * list_ttbar;
  TList * list_vv;
  TList * list_st;
  TList * list_wjets;
  TList * list_others;
  TList * list_total;
  TList * list_comb;

  double err_data;  
  double err_signal;
  double err_dyl;
  double err_dyc;
  double err_dyb;
  double err_ttbar;
  double err_vv;
  double err_st;
  double err_wjets;
  double err_others;


};


#endif
