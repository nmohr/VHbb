#include "../../interface/fitInfo.hpp"
#include "../../interface/controlRegions.h"
#include "sampleSideBand.h"
#include <iostream> 
#include <TCanvas.h>
#include <TLine.h>
#include <TRegexp.h>
#include <TLegend.h>
#include <THStack.h>
#include <TROOT.h>
#include "TLatex.h"
#include "TPaveText.h"
#include "TGraphErrors.h"
#include "TAxis.h"
#include <TH1.h>
#include <TFractionFitter.h>
#include <TFile.h>

#include "TObjArray.h"
#include "RooAbsReal.h"
#include "RooRealVar.h"
#include "RooArgList.h"
#include "RooFitResult.h"
#include "RooDataHist.h"
#include "RooDataSet.h"
#include "RooHistPdf.h"
#include "RooAddPdf.h"
#include "RooPlot.h"
#include "RooSimultaneous.h"
#include "RooCategory.h"


int main(int argc, char **argv){

  using namespace RooFit;

  double fa = 0.46502;
  double fb = 0.53498;
  bool debug_=true;

  if(debug_)
    std::cout << "Init the sample" << std::endl;
 
  std::vector<Sample> s = Nov10SideBandHistos();
  //std::vector<Sample> s = Nov10Fall1160MTopSlimSideBandHistos();

  Sample data(1,"fake data","S1.root",0,true,1000);

  if(debug_)
    std::cout << "Init the data sample" << std::endl;
  for(size_t i=0;i< s.size();i++) if(s[i].data) {data=s[i];break;}

  if(debug_)
    std::cout << "Ls data sample" << std::endl;
  data.file()->ls(); 

  if(debug_)
    std::cout << "Init the mc sample" << std::endl;
  for(size_t i=0;i< s.size();i++) s[i].dump(1,fa,fb);

  std::vector<std::string> names;

  if(debug_)
    std::cout << "Get List of Keys" << std::endl;
  TList * subs = data.file()->GetListOfKeys();
  for(size_t i=0;i< subs->GetSize();i++)
    {
      TString nn = subs->At(i)->GetName();
      if( nn.Contains(TRegexp("Count*")) )
	continue;
      if(debug_)
	std::cout << "Get List of Keys in subdirs" << std::endl;
      TList * objs = ((TDirectoryFile *)data.file()->Get(subs->At(i)->GetName()))->GetListOfKeys();
      for(size_t j=0;j< objs->GetSize();j++)
	{
	  if(debug_)
	    std::cout << "Name = " << subs->At(i)->GetName()+std::string("/")  + objs->At(j)->GetName() << std::endl;
	  names.push_back(subs->At(i)->GetName()+std::string("/")  + objs->At(j)->GetName());	 
	}
    }

  std::vector<fitInfo *> fitInfos;
  std::vector<controlRegion*> crToFit;  

  bool fitSys = false;
  std::string s_channel = "HZcombSB";
  //  std::string s_channel = "HZeeSB";
  std::string s_prefix = "BDT";
  // systematics prefix is needed for the yields effect
  //std::string s_sysprefix = "SystBtagFUPBDT"; //BDTSystJecDOWN, BDTSystBtagFDOWN 
  std::string s_sysprefix = "BDT";
  // systematics suffix is needed for the shape effect
  //std::string s_suffix_Zbb_SB = "$";
  std::string s_suffix_Zbb_SB = "$";
  //std::string s_suffix_Zlight_SB = "$";
  std::string s_suffix_Zlight_SB = "$";
  std::string s_suffix_ttbar_SB = "$";
  //  std::string s_suffix_ttbar_SB = "SystDOWN$";
  std::string s_region_Zbb_SB = "SideBand"; // Zbb sideband
  std::string s_var_Zbb_SB = "HiggsMass"; 
  std::string s_region_ttbar_SB = "TTbarControl";
  std::string s_var_ttbar_SB = "MET_et"; // one addjet required  
  std::string s_region_Zlight_SB = "SideBand";
  std::string s_var_Zlight_SB = "SimpleJet1_bTag";

  if(debug_)
    std::cout << " fillinf the fit info " << std::endl;

  fitInfos.push_back( new fitInfo(s_region_Zbb_SB,s_var_Zbb_SB,s_prefix,s_sysprefix,s_suffix_Zbb_SB,s_channel,0,250) );
  fitInfos.push_back( new fitInfo(s_region_ttbar_SB,s_var_ttbar_SB,s_prefix,s_sysprefix,s_suffix_ttbar_SB,s_channel,0,150) );
  fitInfos.push_back( new fitInfo(s_region_Zlight_SB,s_var_Zlight_SB,s_prefix,s_sysprefix,s_suffix_Zlight_SB,s_channel,0,1) );

  std::string signalString = s_sysprefix+"SignalRegion"+s_channel+"/HiggsMass"+s_sysprefix+"SignalRegion"+s_channel+"$";
  for(int i=0; i<fitInfos.size(); ++i){
    fitInfos.at(i)->setSignalRegion(signalString);
    crToFit.push_back( new controlRegion );
  }

  if(debug_)
    std::cout << " filled the fit info " << std::endl;
 
  Options o;
  double SF[] = {1.0,1.0,1.0}; // SF for scaling
  TH1F * h = new TH1F;
  h->Sumw2();

  for(size_t i = 0 ; i < names.size() ; i++) 
    {
      TString n=names[i];
      for(size_t j=0;j< s.size() ;j++) 
	{ 
	  TString sampleName=s[j].name;
	  h = ((TH1F*)s[j].file()->Get(names[i].c_str()));
	  if(!s[j].data)
	    h->Scale(s[j].scale(data.lumi(),fa,fb,SF));
	  for( int r=0; r<fitInfos.size(); ++r ){
	    if( n.Contains(TRegexp((fitInfos.at(r)->s_regionString).c_str())) ){
	      //	      if(debug_) std::cout << "Filling fitting region " << (fitInfos.at(r)->s_regionString).c_str() << std::endl;
	      crToFit.at(r)->fillFromHisto(s[j], *h, 1 , h->GetNbinsX() );
	    }
	    if( n.Contains(TRegexp((fitInfos.at(r)->s_regionForSyst).c_str())) ){
	      //	      if(debug_) std::cout << "Filling template region " << (fitInfos.at(r)->s_regionForSyst).c_str() << std::endl;
	      fitInfos.at(r)->cr->fillFromHisto(s[j], *h, 1 , h->GetNbinsX() ); // no under/overflow considered
	    }
	    if( n.Contains(TRegexp((fitInfos.at(r)->s_signalRegion).c_str())) )
	      fitInfos.at(r)->cr_signal->fillFromHisto(s[j], *h ,1 , h->GetNbinsX() ); // no under/overflow considered
	    
	  } // fitinfo loop
	} // sample loop
    } //name loop
  
  delete h;

  for(int i=0; i<fitInfos.size(); ++i){
    if(fitSys) fitInfos.at(i)->fillHistoToFit( *crToFit.at(i)->hTotal() );
    else  fitInfos.at(i)->fillHistoToFit( *crToFit.at(i)->hData() );
  }    

  std::string zlightTemplate = "DYL";
  std::string zcharmTemplate = "DYC";
  std::string zbbTemplate = "DYB";
  std::string ttbarTemplate = "TTbar";
  std::string stTemplate = "ST";
  std::string vvTemplate = "VV";

  std::vector<std::string> templateNames;
  std::vector<std::string> fixedTemplateNames;

  templateNames.push_back(zlightTemplate);
  templateNames.push_back(zcharmTemplate);
  templateNames.push_back(zbbTemplate);
  templateNames.push_back(ttbarTemplate);
  fixedTemplateNames.push_back(stTemplate);
  fixedTemplateNames.push_back(vvTemplate);

  std::vector<double> sf_fixed( fixedTemplateNames.size() ,1.);
  std::vector<double> sf( templateNames.size() ,1.);
  std::vector<RooRealVar*> f_vars;
  for(int i=0; i<fixedTemplateNames.size(); ++i)
    //    f_vars.push_back( new RooRealVar(("f_"+fixedTemplateNames.at(i)).c_str(),("f_"+fixedTemplateNames.at(i)).c_str(), fitInfos.at(0)->cr_signal->count(fixedTemplateNames.at(i)) ) );
    f_vars.push_back( new RooRealVar(("f_"+fixedTemplateNames.at(i)).c_str(),("f_"+fixedTemplateNames.at(i)).c_str(), sf_fixed.at(i) ) );
  for(int i=0; i<templateNames.size(); ++i)
    //    f_vars.push_back( new RooRealVar(("f_"+templateNames.at(i)).c_str(),("f_"+templateNames.at(i)).c_str(), fitInfos.at(0)->cr_signal->count(templateNames.at(i)), 0.5*fitInfos.at(0)->cr_signal->count(templateNames.at(i)) , 2.*fitInfos.at(0)->cr_signal->count(templateNames.at(i))) );
    f_vars.push_back( new RooRealVar(("f_"+templateNames.at(i)).c_str(),("f_"+templateNames.at(i)).c_str(), sf.at(i) , 0.5*sf.at(i) , 200.*sf.at(i) ) );

  for(int i=0; i<f_vars.size(); ++i)
    std::cout << "Var at " << i << " name = " << f_vars.at(i)->GetName() << " Value = " << f_vars.at(i)->getVal() << std::endl;
 
  bool sf_bool = true;
  for(int i=0; i<fitInfos.size(); ++i)
    fitInfos.at(i)->create_variable(templateNames,fixedTemplateNames,f_vars, sf_bool); //

  RooCategory varToFit("varToFit","varToFit");
  
  for( int r=0; r<fitInfos.size(); ++r ){
    std::cout << " ------  "<< fitInfos.at(r)->regionName() <<"  ------ " << std::endl;
    fitInfos.at(r)->cr->dump();
    varToFit.defineType(fitInfos.at(r)->var->GetName());
  }
  std::cout << " ------  "<< "Signal region (region where values are evaluated)" <<"  ------ " << std::endl;
  fitInfos.at(0)->cr_signal->dump();
  
   std::cout << "Generatign var To Fit ............ " << std::endl;
   
   if(debug_){
     for(int t = 0; t < templateNames.size() ; ++t){
       std::cout << "Couting region : " << fitInfos.at(0)->cr->count(templateNames.at(t)) << "  " << templateNames.at(t) << std::endl; 
       std::cout << "Couting signal region : " << fitInfos.at(0)->cr_signal->count(templateNames.at(t)) << "  " << templateNames.at(t) << std::endl; 
     }
     std::cout << "-------------------------------------------" << std::endl;
     for( int r=0; r<fitInfos.size(); ++r ){
       std::cout << "Error = " <<   (*fitInfos.at(r)->var).getError() << std::endl;
       std::cout << "Var to fit = " <<   fitInfos.at(r)->var->GetName() << std::endl;
       std::cout << "Template for the fit name = " <<   (*fitInfos.at(r)->templates.at(fixedTemplateNames.size()+templateNames.size()-1)).GetName() << std::endl;
       std::cout << "Template for the fit entries = " <<   (*fitInfos.at(r)->templates.at(fixedTemplateNames.size()+templateNames.size()-1)).sumEntries() << std::endl;
       std::cout << "Hist to fit with under/overflow entries = " <<   fitInfos.at(r)->h_data->sum(0) << std::endl;
       //       std::cout << "Hist to fit without under/overflow entries = " <<   fitInfos.at(r)->h_data->Integral(1,fitInfos.at(r)->cr->hTotal()->GetNbinsX()) << std::endl;
       std::cout << "Hist to fit with under/overflow entries = " <<   fitInfos.at(r)->cr->hTotal()->Integral() << std::endl;
       std::cout << "Hist to fit without under/overflow entries = " <<   fitInfos.at(r)->cr->hTotal()->Integral(1,fitInfos.at(r)->cr->hTotal()->GetNbinsX()) << std::endl;
       std::cout << "Data with under/overflow entries = " <<   fitInfos.at(r)->cr->hData()->Integral() << std::endl;
       std::cout << "Data without under/overflow entries = " <<   fitInfos.at(r)->cr->hData()->Integral(1,fitInfos.at(r)->cr->hTotal()->GetNbinsX()) << std::endl;

     }
   }

   std::cout << "Generatign combData ............ " << std::endl;

   RooDataHist combData("combData","combined data",
			RooArgSet( *fitInfos.at(0)->var ,
				   *fitInfos.at(1)->var ,
				   *fitInfos.at(2)->var ),
			Index(varToFit),
			Import(fitInfos.at(0)->var->GetName(),*fitInfos.at(0)->h_data),
			Import(fitInfos.at(1)->var->GetName(),*fitInfos.at(1)->h_data),
			Import(fitInfos.at(2)->var->GetName(),*fitInfos.at(2)->h_data));

  
   std::cout << "Generatign RooSimultaneous ............ " << std::endl;
   RooSimultaneous simPdf("simPdf","simPdf",varToFit);
   for(int i=0; i<fitInfos.size(); ++i)
     simPdf.addPdf(*fitInfos.at(i)->model,fitInfos.at(i)->var->GetName());

   std::cout << "FITTING  ............ " << std::endl;

   RooFitResult * fitRes = simPdf.fitTo(combData,SumW2Error(1));


   std::cout << " ==== Scale Factor ==== " << std::endl;
   for(int i=0; i<templateNames.size(); ++i){
     fitInfos.at(i)->var->Print();
   }

   // Plot data and PDF overlaid
   //ttbar
   RooPlot* TTbarVar_frame((*fitInfos.at(1)->var).frame(Title(""))) ;
   (*fitInfos.at(1)->h_data).plotOn(TTbarVar_frame) ;
   (*fitInfos.at(1)->model).plotOn(TTbarVar_frame) ;
   for(int i = 0; i < templateNames.size(); ++i){
     (*fitInfos.at(1)->model).plotOn(TTbarVar_frame,Components( *fitInfos.at(1)->pdfs.at(i) ) ,LineColor(i+1),LineStyle(kDotted));
   }
   TCanvas * c_TTbarVar = new TCanvas("TTbarVar fit","TTbarVar_fit",600,600) ;
   gPad->SetLeftMargin(0.15) ; TTbarVar_frame->GetYaxis()->SetTitleOffset(1.4) ; TTbarVar_frame->Draw() ;
   c_TTbarVar->Print("fromFitdev_TTbarVar","pdf");

   //zlight
   RooPlot* ZlightVar_frame((*fitInfos.at(0)->var).frame(Title(""))) ;
   (*fitInfos.at(0)->h_data).plotOn(ZlightVar_frame) ;
   (*fitInfos.at(0)->model).plotOn(ZlightVar_frame) ;
   for(int i = 0; i < templateNames.size(); ++i){
     (*fitInfos.at(0)->model).plotOn(ZlightVar_frame,Components( *fitInfos.at(0)->pdfs.at(i) ) ,LineColor(i+1),LineStyle(kDotted));
   }
   TCanvas * c_ZlightVar = new TCanvas("ZlightVar fit","ZlightVar_fit",600,600) ;
   gPad->SetLeftMargin(0.15) ; ZlightVar_frame->GetYaxis()->SetTitleOffset(1.4) ; ZlightVar_frame->Draw() ;
   c_ZlightVar->Print("fromFitdev_ZlightVar","pdf");

   //zlight
   RooPlot* ZbbVar_frame((*fitInfos.at(2)->var).frame(Title(""))) ;
   (*fitInfos.at(2)->h_data).plotOn(ZbbVar_frame) ;
   (*fitInfos.at(2)->model).plotOn(ZbbVar_frame) ;
   for(int i = 0; i < templateNames.size(); ++i){
     (*fitInfos.at(2)->model).plotOn(ZbbVar_frame,Components( *fitInfos.at(2)->pdfs.at(i) ) ,LineColor(i+1),LineStyle(kDotted));
   }
   TCanvas * c_ZbbVar = new TCanvas("ZbbVar fit","ZbbVar_fit",600,600) ;
   gPad->SetLeftMargin(0.15) ; ZbbVar_frame->GetYaxis()->SetTitleOffset(1.4) ; ZbbVar_frame->Draw() ;
   c_ZbbVar->Print("fromFitdev_ZbbVar","pdf");


   //cleaning
   std::cout << "Cleaning" << std::endl;
   for(int i=0; i<(fixedTemplateNames.size()+templateNames.size()); ++i)
     delete f_vars.at(i); 
   for(int i=0; i<crToFit.size();++i)
     delete crToFit.at(i);
   for(int i=0; i<fitInfos.size(); ++i)
     delete fitInfos.at(i);
   delete c_TTbarVar;
   delete c_ZlightVar;
   delete c_ZbbVar;
   delete TTbarVar_frame;
   delete ZlightVar_frame;
   delete ZbbVar_frame;
   std::cout << "Cleaned" << std::endl;

  return 0;
}
