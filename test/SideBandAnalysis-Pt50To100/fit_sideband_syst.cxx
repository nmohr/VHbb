#include "../../interface/fitInfo.hpp"
#include "../../interface/controlRegions.h"
#include "sampleSideBand.h"
#include <iostream> 
#include <fstream>
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

  std::string DYL = "ZjL";
  std::string DYC = "ZjC";
  std::string DYB = "ZjH";
  std::string TTbar = "TT";
  
  if(argc < 2)
    {
      std::cout << "Usage:\n  fit_sideband_syst [syst]" << std::endl;
      std::cout << "Possible syst:\n btag_up \n btag_down \n mistag_up \n mistag_down \n jer_up \n jer_down \n jec_up \n jec_down \n " << std::endl;
      exit(1);
    }

  bool debug_=false;
  bool fitSys = true;
  bool fitMC = false;
  bool getSFfromFile = true;

  std::string btag_up = "btag_up";
  std::string btag_down = "btag_down";
  std::string mistag_up = "mistag_up";
  std::string mistag_down = "mistag_down";
  std::string jec_up = "jec_up";
  std::string jec_down = "jec_down";
  std::string jer_up = "jer_up";
  std::string jer_down = "jer_down";
  std::string syst_string(argv[1]);
  cout << syst_string << endl;
  // systematics suffix is needed for the shape effect
  std::string s_suffix_Zbb_SB = "$";
  std::string s_suffix_Zlight_SB = "$";
  std::string s_suffix_ttbar_SB = "$";
  std::string s_sysprefix_Zbb = "BDT";

  if(syst_string == btag_up){ s_suffix_Zlight_SB = "SystUP$";  }
  if(syst_string == btag_down){ s_suffix_Zlight_SB = "SystDOWN$";  }
  if(syst_string == mistag_up){ s_suffix_Zlight_SB = "SystFUP$";  }
  if(syst_string == mistag_down){ s_suffix_Zlight_SB = "SystFDOWN$";  }

  if(syst_string == jec_up){ s_suffix_Zbb_SB = "SystUP$"; }
  if(syst_string == jec_down){ s_suffix_Zbb_SB = "SystDOWN$"; }
  if(syst_string == jer_up){ s_suffix_Zbb_SB = "SystJERUP$"; }
  if(syst_string == jer_down){ s_suffix_Zbb_SB = "SystJERDOWN$"; }

//   if(syst_string == jec_up){ s_suffix_Zbb_SB = "SystUP$";  s_sysprefix_Zbb = "SystJecUPBDT";  }
//   if(syst_string == jec_down){ s_suffix_Zbb_SB = "SystDOWN$"; s_sysprefix_Zbb = "SystJecDOWNBDT"; }
//   if(syst_string == jer_up){ s_suffix_Zbb_SB = "SystJERUP$"; s_sysprefix_Zbb = "SystJerUPBDT"; }
//   if(syst_string == jer_down){ s_suffix_Zbb_SB = "SystJERDOWN$"; s_sysprefix_Zbb = "SystJerDOWNBDT"; }

  if(debug_)
    std::cout << "Init the sample" << std::endl;
 
  std::vector<Sample> s = histos();

  Sample data(1,"fake data","S1.root",0,true,1000);

  if(debug_)
    std::cout << "Init the data sample" << std::endl;
  for(size_t i=0;i< s.size();i++) if(s[i].data) {data=s[i];break;}

  if(debug_)
    std::cout << "Ls data sample" << std::endl;
  data.file()->ls(); 

  if(debug_)
    std::cout << "Init the mc sample" << std::endl;
  for(size_t i=0;i< s.size();i++) s[i].dump(1);

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


  std::string s_channel = "HZcomb";
  //  std::string s_channel = "HZee";
  std::string s_prefix = "BDT";
  // systematics prefix is needed for the yields effect
  //  std::string s_sysprefix = "SystBtagUPBDT"; //BDTSystJecDOWN, BDTSystBtagFDOWN 
  std::string s_sysprefix = "BDT";
  std::string s_region_Zbb_SB = "SideBand"; // SideBand
  std::string s_var_Zbb_SB = "ZH_dPhi";  //HiggsPt
  std::string s_region_ttbar_SB = "TTbarControl";
  std::string s_var_ttbar_SB = "MET_et"; // one addjet required  
  std::string s_region_Zlight_SB = "SideBand";
  std::string s_var_Zlight_SB = "SimpleJet1_bTag";

  if(debug_)
    std::cout << " filling the fit info " << std::endl;

  fitInfos.push_back( new fitInfo(s_region_Zbb_SB,s_var_Zbb_SB,s_prefix,s_sysprefix_Zbb,s_suffix_Zbb_SB,s_channel,0,4) );
  fitInfos.push_back( new fitInfo(s_region_ttbar_SB,s_var_ttbar_SB,s_prefix,s_sysprefix,s_suffix_ttbar_SB,s_channel,0,150) );
  fitInfos.push_back( new fitInfo(s_region_Zlight_SB,s_var_Zlight_SB,s_prefix,s_sysprefix,s_suffix_Zlight_SB,s_channel,0.,1) );

  std::string signalString = s_sysprefix+"SignalRegion"+s_channel+"/HiggsMass"+s_sysprefix+"SignalRegion"+s_channel+"$";
  for(int i=0; i<fitInfos.size(); ++i){
    fitInfos.at(i)->setSignalRegion(signalString);
    cout << fitInfos.at(i)->s_regionForSyst << endl;
    crToFit.push_back( new controlRegion );
  }

  if(debug_)
    std::cout << " filled the fit info " << std::endl;
 
  Options o;
  double SF[] = {1.0,1.0,1.0}; // SF for scaling

  //here I need to get the SF from the file
  std::ifstream SFfile;
  std::string line;
  if(getSFfromFile){
    SFfile.open("Pt50To100SFupdate.txt");
    if (SFfile.is_open()){
      while ( getline(SFfile,line) ){
	size_t pos_point = line.find('.'); // decimal of the double
	istringstream tokenizer(line.substr(pos_point-1));
	if(line.find(DYL,0)!=string::npos) tokenizer >> SF[0];
	//	if(line.find(DYC,0)!=string::npos) tokenizer >> SF[1];
	if(line.find(DYB,0)!=string::npos) tokenizer >> SF[1];
	if(line.find(TTbar,0)!=string::npos) tokenizer >> SF[2];
      }
      SFfile.close();
    }
  }

  cout << "Scale factors applied to DYL, DYC, DYB, TTbar" << endl;
  cout << SF[0]  << endl << SF[1] << endl << SF[2] << endl << endl;
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
	    h->Scale(s[j].scale(data.lumi(),SF));
	  for( int r=0; r<fitInfos.size(); ++r ){
	    if( n.Contains(TRegexp((fitInfos.at(r)->s_regionString).c_str())) ){ // normal histos
	      if(debug_) std::cout << "Filling fitting region " << (fitInfos.at(r)->s_regionString).c_str() << std::endl;
	      crToFit.at(r)->fillFromHisto(s[j], *h, 1 , h->GetNbinsX() );
	    }
	    if( n.Contains(TRegexp((fitInfos.at(r)->s_regionForSyst).c_str())) ){ // histos with systematics variations
	      if(debug_) std::cout << "Filling systematics template region " << (fitInfos.at(r)->s_regionForSyst).c_str() << std::endl;
	      fitInfos.at(r)->cr->fillFromHisto(s[j], *h, 1 , h->GetNbinsX() ); // no under/overflow considered
	    }
	    if( n.Contains(TRegexp((fitInfos.at(r)->s_signalRegion).c_str())) ) // signal region. FIXME:  Really needed here for syst?
	      fitInfos.at(r)->cr_signal->fillFromHisto(s[j], *h ,1 , h->GetNbinsX() ); // no under/overflow considered
	    
	  } // fitinfo loop
	} // sample loop
    } //name loop
  
  delete h;

  for(int i=0; i<fitInfos.size(); ++i){
    if(fitSys == true && fitMC ==  true){
      std::cout << " ==== Fitting MC ====" << std::endl;
      fitInfos.at(i)->fillHistoToFit( *crToFit.at(i)->hTotal() );
    }
    else{
      std::cout << " ==== Fitting Data ====" << std::endl;
      fitInfos.at(i)->fillHistoToFit( *crToFit.at(i)->hData() );
    }
  }    

  std::string zlightTemplate = "DYL+DYC";
  //  std::string zcharmTemplate = "DYC";
  std::string zbbTemplate = "DYB";
  std::string ttbarTemplate = "TTbar";
  std::string stTemplate = "ST";
  std::string vvTemplate = "VV";

  std::vector<std::string> templateNames;
  std::vector<std::string> fixedTemplateNames;

  templateNames.push_back(zlightTemplate);
  //  templateNames.push_back(zcharmTemplate);
  templateNames.push_back(zbbTemplate);
  templateNames.push_back(ttbarTemplate);
  fixedTemplateNames.push_back(stTemplate);
  fixedTemplateNames.push_back(vvTemplate);

  std::vector<double> sf_fixed( fixedTemplateNames.size() ,1.0);
  std::vector<double> sf( templateNames.size() ,1.0);
  std::vector<RooRealVar*> f_vars;
  for(int i=0; i<fixedTemplateNames.size(); ++i) //fixed templates
    f_vars.push_back( new RooRealVar(("f_"+fixedTemplateNames.at(i)).c_str(),("f_"+fixedTemplateNames.at(i)).c_str(), sf_fixed.at(i) ) );
  for(int i=0; i<templateNames.size(); ++i) // variable templates
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

   RooFitResult * fitRes = simPdf.fitTo(combData,SumW2Error(1),Save());

   std::cout << " ==== Scale Factor ==== " << std::endl;
   for(int i=0; i<f_vars.size(); ++i)
     std::cout << "Name = " << f_vars.at(i)->GetName() << "; Value = " << f_vars.at(i)->getVal() << "; Error = " << f_vars.at(i)->getError() << " + " << f_vars.at(i)->getAsymErrorHi() << " - " << f_vars.at(i)->getAsymErrorLo()  << std::endl;

  DYL = "f_DYL+DYC";
  DYC = "f_DYC";
  DYB = "f_DYB";
  TTbar = "f_TTbar";

   std::ofstream errorfile;
   errorfile.open ("SFErrors_Pt50To100.txt", ios::app);
   for(int i=0; i<f_vars.size(); ++i)
   if( f_vars.at(i)->GetName() == DYL ||
       f_vars.at(i)->GetName() == DYC ||
       f_vars.at(i)->GetName() == DYB ||
       f_vars.at(i)->GetName() == TTbar )
     errorfile << f_vars.at(i)->GetName() << " " << syst_string + " syst error = " << TMath::Abs(1-f_vars.at(i)->getVal()) << std::endl;
   errorfile.close();  

   //cleaning
   std::cout << "Cleaning" << std::endl;
   for(int i=0; i<(fixedTemplateNames.size()+templateNames.size()); ++i)
     delete f_vars.at(i); 
   for(int i=0; i<crToFit.size();++i)
     delete crToFit.at(i);
   for(int i=0; i<fitInfos.size(); ++i)
     delete fitInfos.at(i);
   std::cout << "Cleaned" << std::endl;

  return 0;
}
