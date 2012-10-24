#include <sampleSideBand.h>
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
#include "../../plugins/setTDRStyle.C"
//#include "../../plugins/Ratio.h"
#include "../../plugins/customize.h"


void plottingmacro()
{

  bool debug_ = false;
  bool getSFfromFile = false;

  std::string path("Plots_lowBtag/");

  if(debug_)
    std::cout << "Init the style form setTDRStyle" << std::endl;
  setTDRStyle();
  gStyle->SetErrorX(0.5);
  gROOT->ForceStyle();
  initOptions();
  
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
	  //      std::cout << subs->At(i)->GetName() << "/"  << objs->At(j)->GetName() << std::endl;
	  //TODO: select plots via regexp
	}
    }


  if(debug_)
    std::cout << "Starting plotting" << std::endl;

  std::string process;

  for(size_t i = 0 ; i < names.size() ; i++) 
    {
      
      std::map<std::string,TH1F *> grouped;
      TString n=names[i];

      // do not plot the systematics
      //      if( n.Contains(TRegexp("Syst")) || !n.Contains(TRegexp("HZee")) ) continue;
      //      if( n.Contains(TRegexp("Syst")) || !n.Contains(TRegexp("HZmm")) ) continue;
      if( n.Contains(TRegexp("Syst")) || !n.Contains(TRegexp("HZcomb")) ) continue;

      //      if(!n.Contains(TRegexp("^BDTZlightControlRegionHZee"))) continue;
      //      if(!n.Contains(TRegexp("^BDTZbbControlRegionHZee"))) continue;
      //      if(!n.Contains(TRegexp("^BDTTTbarControlRegionHZcomb"))) continue;
      //      if(!n.Contains(TRegexp("^BDTSideBandRegionHZcomb"))) continue;
      //      if(!n.Contains(TRegexp("^BDTSideBandRegion_noBTagHZcomb"))) continue;
      //      if(!n.Contains(TRegexp("BDTSideBandRegionHZcombSystFUP"))) continue;
      //if(!n.Contains(TRegexp("^BDTSignalRegionHZee"))) continue;
      //      if(!n.Contains(TRegexp("^BDTTrainingRegionHZcomb"))) continue;

      if(n.Contains(TRegexp("RegionHZcomb")))
	process = "Z(l^{+}l^{-})H(b#bar{b})";
      if(n.Contains(TRegexp("RegionHZmm")))
	process = "Z(#mu^{+}#mu^{-})H(b#bar{b})";
      if(n.Contains(TRegexp("RegionHZee")))
	process = "Z(e^{+}e^{-})H(b#bar{b})";

      if(debug_)
	std::cout << "Creating the Canvas" << std::endl;

      TCanvas *c = new TCanvas();
      c->SetFillStyle(4000);
      c->SetLogy(false);
      c->SetTitle(names[i].c_str());

      if(debug_)
	std::cout << "Creating histograms" << std::endl;
  
      TH1F *hd = ((TH1F*)data.file()->Get(names[i].c_str()));
      hd->Sumw2();
      Options o=options[names[i]];
      //      hd->Rebin(o.rebin);
      hd->SetMarkerStyle(20);
      hd->GetXaxis()->SetLabelOffset(99);
      hd->SetYTitle(o.yaxis.c_str());
      double nbin = hd->GetNbinsX();
      double min_bin = hd->GetXaxis()->GetXmin();
      double max_bin = hd->GetXaxis()->GetXmax();
      TH1F *hmc = new TH1F("hmc","hmc", nbin, min_bin, max_bin);
      hmc->SetFillColor(kWhite);
      hmc->Sumw2();
      //      hmc->Rebin(o.rebin);

      if(debug_)
	std::cout << "Creating the THStack and Legend" << std::endl;
      //      std::vector<TH1F*> v_hist;  v_hist.clear();
      THStack * sta = new THStack("sta",hd->GetTitle());
      TLegend * l = new TLegend(o.legendx1,o.legendy1,o.legendx2,o.legendy2); //0.7,0.1,0.9,0.6);
      l->SetFillColor(kWhite);
      l->SetBorderSize(0);
      l->SetTextFont(62);
      l->SetTextSize(0.03);
      if(debug_)
	std::cout << "Adding data to the legend" << std::endl;  
      l->AddEntry(hd, "Data","P");
      if(debug_)
	std::cout << "Adding MC to the THStack" << std::endl;  

      //scale factors {DYL, TTBar, , DYC, DYB}
      //      double SF[] = {1.00,1.00,1.00,1.00}; //
      double SF[] = {1.00,1.00,1.00}; //

      //here I get the SF from the file
      if(getSFfromFile){
	std::string DYL = "ZjL";
	std::string DYC = "ZjC";
	std::string DYB = "ZjH";
	std::string TTbar = "TT";
	std::ifstream SFfile;
	std::string line;
	SFfile.open("../Pt50To100SFupdate.txt");
	if (SFfile.is_open()){
	  while ( getline(SFfile,line) ){
	    size_t pos_point = line.find('.'); // decimal of the double
	    istringstream tokenizer(line.substr(pos_point-1));
	    if(line.find(DYL,0)!=string::npos) tokenizer >> SF[0];
	    //	    if(line.find(DYC,0)!=string::npos) tokenizer >> SF[1];
	    if(line.find(DYB,0)!=string::npos) tokenizer >> SF[1];
	    if(line.find(TTbar,0)!=string::npos) tokenizer >> SF[2];
	  }
	  SFfile.close();
	}
      }

      for(int i = 0; i< 3; ++i)
	std::cout << "SF [" << i << "] = " << SF[i] << std::endl;

//       TCanvas * c2 = new TCanvas("Normalized_plots","Normalized_plots",600,600);
//       hd->DrawNormalized();

      double mcIntegral=0;
      for(size_t j=0;j< s.size() ;j++) 
	{ 
	  if(!s[j].data) 
	    {
	      if(debug_)
		std::cout << "Creating TH1F from file " << s[j].name << std::endl;  
	      TH1F * h = ((TH1F*)s[j].file()->Get(names[i].c_str()));
	      h->Sumw2();
	      if(debug_){
		std::cout << "TH1F created from file " << s[j].name << std::endl;  
		std::cout << "Scaling : " << s[j].scale(data.lumi()) << std::endl;  
		std::cout << "Scaling with SF : " << s[j].scale(data.lumi()) << std::endl;  
		std::cout << "Histo integral before scaling = " << h->Integral() << std::endl;
	      }
	      h->Scale(s[j].scale(data.lumi(),SF ));
	      if(debug_){
		std::cout << "Histo integral after scaling = " << h->Integral() << std::endl;
		std::cout << "Managing style... " << std::endl;  
	      }
	      h->SetLineWidth(1.);
	      h->SetFillColor(s[j].color);
	      h->SetLineColor(s[j].color);
	      //	      h->Rebin(options[names[i]].rebin);
	      if(debug_)
		std::cout << "Cloning and update legend " << std::endl;  
	      if(grouped.find(s[j].name) == grouped.end()){
		l->AddEntry(h,s[j].name.c_str(),"F");
		//		h->SetLineColor(kBlack);
	      }
	      std::cout << "Sample : " << s[j].name << " - Integral for plot " << names[i] << " = " << h->Integral(-10000,10000) << std::endl;
	      mcIntegral += h->Integral();
	      sta->Add(h);
	      hmc->Add(h);

	      // for normalized plots
	      if(grouped.find(s[j].name) != grouped.end())
		grouped[s[j].name]->Add((TH1F *)h->Clone(("_"+names[i]).c_str()));
	      else
		grouped[s[j].name]=(TH1F *)h->Clone(("_"+names[i]).c_str());
	      grouped[s[j].name]->SetLineColor(s[j].color);
	    }
	}
      
      if(debug_){
	std::cout << "Data total = " << hd->Integral() << std::endl;
	std::cout << "MC = " << mcIntegral << std::endl;
	std::cout << "Data/MC = " << hd->Integral()/mcIntegral << std::endl;
      }

      TPad * TopPad = new TPad("TopPad","Top Pad",0.,0.3,1.,1. ) ;
      TPad * BtmPad = new TPad("BtmPad","Bottom Pad",0.,0.,1.,0.313 ) ;
      TopPad->SetBottomMargin(0.02);
      BtmPad->SetTopMargin(0.0);
      BtmPad->SetFillStyle(4000);
      TopPad->SetFillStyle(4000);
      BtmPad->SetFillColor(0);
      BtmPad->SetBottomMargin(0.35);
      TopPad->Draw() ;
      BtmPad->Draw() ;
      std::cout << "hd maximum = " << hd->GetMaximum() << "  sta maximum = " << sta->GetMaximum() << std::endl;
      double maxY;
      if(hd->GetMaximum() > sta->GetMaximum()) maxY = (hd->GetMaximum())*1.5;
      else maxY = (sta->GetMaximum())*1.5;
      TopPad->cd();
      hd->Draw("E1X0");
      sta->Draw("sameHIST");
      hmc->Draw("sameE2");
      hmc->SetFillColor(kGray+3);
      hmc->SetMarkerSize(0);
      hmc->SetFillStyle(3013);
      hd->Draw("E1X0same");
      l->Draw("same");
      TopPad->RedrawAxis();
      std::cout << "Set Maximum to = " << maxY << std::endl;
      hd->GetYaxis()->SetRangeUser(0.,maxY);
      hd->GetXaxis()->SetRangeUser(options[names[i]].min,options[names[i]].max);

      BtmPad->cd();
      std::cout << "Division" << std::endl;

      TH1D * divisionErrorBand = (TH1D*)(hmc)->Clone("divisionErrorBand");
      divisionErrorBand->Sumw2();
      divisionErrorBand->Divide(hmc);
      divisionErrorBand->Draw("E2");      
      divisionErrorBand->SetMaximum(2.49);
      divisionErrorBand->SetMinimum(0);
      divisionErrorBand->SetMarkerStyle(20);
      divisionErrorBand->SetMarkerSize(0.55);
      std::string xtitle = hd->GetTitle();
      xtitle = xtitle.substr(0,xtitle.find("("));
      divisionErrorBand->GetXaxis()->SetTitle( xtitle.c_str() );
      divisionErrorBand->GetXaxis()->SetTitleOffset(1.0); // 1.12
      divisionErrorBand->GetXaxis()->SetLabelSize(0.12);
      divisionErrorBand->GetXaxis()->SetTitleSize(0.12); //0.5
      divisionErrorBand->GetYaxis()->SetTitle("Data/MC");
      divisionErrorBand->GetYaxis()->SetLabelSize(0.12);
      divisionErrorBand->GetYaxis()->SetTitleSize(0.12);
      divisionErrorBand->GetYaxis()->SetTitleOffset(0.40);
      divisionErrorBand->GetYaxis()->SetNdivisions(505);
      //divisionErrorBand->UseCurrentStyle();
      divisionErrorBand->SetFillColor(kGray+3);
      //      divisionErrorBand->SetFillStyle(3001);
      divisionErrorBand->SetFillStyle(3013);
      divisionErrorBand->SetMarkerSize(0.);

      TH1D * divisionSystErrorBand = (TH1D*)(hmc)->Clone("divisionErrorBand");
      divisionSystErrorBand->Sumw2();
      std::vector<double> syst(divisionSystErrorBand->GetNbinsX(),1.);
      std::vector<double> syst_err(divisionSystErrorBand->GetNbinsX(), 0.15 );
      for(int i=0; i<divisionSystErrorBand->GetNbinsX();++i){
	if(hmc->GetBinContent(i+1) > 0. ){
	  divisionSystErrorBand->SetBinContent( i+1, syst.at(i) );
	  divisionSystErrorBand->SetBinError( i+1, syst_err.at(i) );
	}
      }
      divisionSystErrorBand->Draw("E2 same");      
      divisionSystErrorBand->SetMaximum(2.49);
      divisionSystErrorBand->SetMinimum(0);
      divisionSystErrorBand->SetMarkerStyle(20);
      divisionSystErrorBand->SetMarkerSize(0.55);
      divisionSystErrorBand->SetFillColor(kYellow);
      divisionSystErrorBand->SetFillStyle(1001);
      divisionSystErrorBand->SetMarkerSize(0.);

      //redraw to make it visible
      divisionErrorBand->Draw("E2 same"); 
      BtmPad->RedrawAxis(); 


      TH1D * division = (TH1D*)(hd)->Clone("division");
      division->Sumw2();
      division->Divide(hmc);
//       division->SetMaximum(2.5);
//       division->SetMinimum(0);
//       division->SetMarkerStyle(20);
//       division->SetMarkerSize(0.55);
//       division->GetXaxis()->SetLabelSize(0.12);
//       division->GetXaxis()->SetTitleSize(0.14);
//       division->GetYaxis()->SetLabelSize(0.10);
//       division->GetYaxis()->SetTitleSize(0.10);
//      division->GetYaxis()->SetTitle("Data/MC");
      Double_t min = division->GetXaxis()->GetXmin();
      Double_t max = division->GetXaxis()->GetXmax();
      division->Draw("E1X0same");

//form Niklas coolRatio
//       coolRatio * ratio = new coolRatio;
//       TH1D * division = new (TH1D*)
// 	(ratio.make_rebinned_ratios(hd, hmc, 0.2, true).at(0));

      TLine *line = new TLine(min, 1.0, max, 1.0);
      //      line->SetLineColor(kRed);
      line->SetLineStyle(2); //dashed
      line->Draw("same");
      
      TLegend * leg3 =new TLegend(0.50,0.86,0.69,0.96);
      leg3->AddEntry(divisionErrorBand,"MC uncert. (stat.)","f");
      leg3->SetFillColor(0);
      leg3->SetLineColor(0);
      leg3->SetShadowColor(0);
      leg3->SetTextFont(62);
      leg3->SetTextSize(0.06);
      leg3->Draw();

      TLegend * leg4 =new TLegend(0.69,0.86,0.88,0.96);
      leg4->AddEntry(divisionSystErrorBand,"MC uncert. (syst.)","f");
      leg4->SetFillColor(0);
      leg4->SetLineColor(0);
      leg4->SetShadowColor(0);
      leg4->SetTextFont(62);
      leg4->SetTextSize(0.06);
      leg4->Draw();

      TPaveText *pave = new TPaveText(0.15,0.85,0.32,0.96,"brNDC");
      pave->SetTextAlign(12);
      pave->SetLineColor(0);
      pave->SetFillColor(0);
      pave->SetShadowColor(0);
      //TText *text = pave->AddText(Form("#chi_{#nu}^{2} = %.3f, K_{s} = %.3f",histDt->Chi2Test(histCopyMC5,"UWCHI2/NDF"),histDt->KolmogorovTest(histCopyMC5))); // stat + sys
      TText *text = pave->AddText(Form("#chi_{#nu}^{2} = %.3f, K_{s} = %.3f",hd->Chi2Test(hmc,"UWCHI2/NDF"),hd->KolmogorovTest(hmc))); // stat only
      text->SetTextFont(62);
      text->SetTextSize(0.08);
      pave->Draw();

      TopPad->cd();
      TLatex latex;
      latex.SetNDC();
      latex.SetTextAlign(12);
      latex.SetTextSize(0.052);
      latex.DrawLatex(0.17,0.89,"CMS Preliminary");
      latex.SetTextSize(0.04);
      latex.DrawLatex(0.17,0.84,"#sqrt{s} = 8 TeV, L = 12.1 fb^{-1}");
      latex.DrawLatex(0.17,0.79,process.c_str());

      c->Update();
      std::string cName= hd->GetName();
      if(getSFfromFile)
	cName += "_SF.pdf";
      else
	cName += "_bare.pdf";
      cName = path+cName;
      c->Print(cName.c_str(),"pdf");

      delete c;

      //NORMALIZED plots

      TCanvas *c_norm = new TCanvas();
      c_norm->SetFillStyle(4000);
      c_norm->SetLogy(false);
      c_norm->SetTitle(names[i].c_str());

      TLegend * nl = new TLegend(o.legendx1,o.legendy1,o.legendx2,o.legendy2); //0.7,0.1,0.9,0.6);
      nl->SetFillColor(kWhite);
      nl->SetBorderSize(0);
      nl->SetTextFont(62);
      nl->SetTextSize(0.03);

      bool drawed = false;
      bool keepSample=false;  
      double maxYnorm = 0;
      std::vector<TString> sampleToKeep;
      sampleToKeep.push_back("DY*");
      sampleToKeep.push_back("ZH");
      sampleToKeep.push_back("TTbar");

      //getMaximum for drawing
      for( std::map<std::string,TH1F*>::iterator it=grouped.begin(); it!=grouped.end();++it ){
	keepSample = false;
	TString sampleName=(*it).first;
	for(unsigned int ss=0; ss<sampleToKeep.size(); ++ss)
	  if( (sampleName.Contains(TRegexp(sampleToKeep.at(ss)))) ) keepSample = true;
	if(!keepSample) continue;
	if( (*it).second->GetMaximum()/(*it).second->Integral() > maxYnorm ) maxYnorm = (*it).second->GetMaximum()/(*it).second->Integral();
      }

      //Now draw it!
      for( std::map<std::string,TH1F*>::iterator it=grouped.begin(); it!=grouped.end();++it ){
	keepSample = false;
	std::cout << "Normalized sample = " << (*it).first << std::endl;
	TString sampleName=(*it).first;
	for(unsigned int ss=0; ss<sampleToKeep.size(); ++ss)
	  if( (sampleName.Contains(TRegexp(sampleToKeep.at(ss)))) ) keepSample = true;
	if(!keepSample) continue;
	nl->AddEntry((*it).second, (*it).first.c_str() , "F");
	(*it).second->SetFillStyle(0);
	(*it).second->SetLineWidth(2.);
	(*it).second->GetYaxis()->SetRangeUser(0. , (*it).second->Integral()*maxYnorm*1.5 ); // you need to give the unscaled range...
	if( drawed == false ){
	  std::string xtitle = (*it).second->GetTitle();
	  xtitle = xtitle.substr(0,xtitle.find("("));
	  (*it).second->GetXaxis()->SetTitle( xtitle.c_str() );
	  (*it).second->GetXaxis()->SetTitleOffset(1.0); // 1.12
	  (*it).second->GetXaxis()->SetLabelSize(0.04);
	  (*it).second->GetXaxis()->SetTitleSize(0.04); //0.5
	  (*it).second->GetYaxis()->SetTitle("Normlized Entries");
	  (*it).second->GetYaxis()->SetTitleOffset(1.5); // 1.12
	  (*it).second->GetYaxis()->SetLabelSize(0.04);
	  (*it).second->GetYaxis()->SetTitleSize(0.04); //0.5

	  (*it).second->DrawNormalized("HIST") ;  
	  drawed = true; 
	}
      	else (*it).second->DrawNormalized("HIST same"); 
      }


      nl->Draw("same");	
      latex.SetNDC();
      latex.SetTextAlign(12);
      latex.SetTextSize(0.052);
      latex.DrawLatex(0.17,0.89,"CMS Preliminary");
      latex.SetTextSize(0.04);
      latex.DrawLatex(0.17,0.84,"#sqrt{s} = 8 TeV");
      latex.DrawLatex(0.17,0.79,process.c_str());
      std::string cName_norm= hd->GetName();

      c_norm->Update();
      cName_norm += "_norm.pdf";
      cName_norm = path+cName_norm;
      c_norm->Print(cName_norm.c_str(),"pdf");

      delete c_norm;

    }

}
