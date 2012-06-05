#include <TH1F.h>
#include <TFile.h>
#include <TGraph.h>
#include <vector>
#include <iostream>
#include <TSpline.h>
#include "Math/Interpolator.h"
#define MAXPOINTS 200

class BTagShape 
{
 public: 
   BTagShape(const char * file) : m_file(file)
   {
     m_hb = (TH1F *) m_file.Get("hb");
     m_hc = (TH1F *) m_file.Get("hc");
     m_hl = (TH1F *) m_file.Get("hl");
  }

    
  std::vector<std::pair<float,float> > computeEquivalentCuts( TH1F * h ,const std::vector<std::pair<float, float> > & cutsAndSF )
  {
    std::vector<std::pair<float,float> > equivalents;
    int lastbin =2001;
    float integral =  h->Integral(-1,lastbin);
    for(unsigned int i =0;i<cutsAndSF.size(); i++)
    {
      float oldCut=cutsAndSF[i].first;
      float sf=cutsAndSF[i].second;
      float originalIntegral = h->Integral(h->FindBin(oldCut),lastbin);
      float originalLowEdge = h->GetBinLowEdge(h->FindBin(oldCut));
      std::cout << std::endl<<    " Scale Factor : " << sf << std::endl;
//      float target=originalIntegral/sf;
      float target=originalIntegral*sf;
      std::cout << " Target " << target << " orig " << originalIntegral << std::endl;
      for(int j=lastbin; j> -1; j--)
      {
        if(h->Integral(j,lastbin)>= target)
          {
             //equivalents.push_back(std::pair<float,float>(originalLowEdge,h->GetBinLowEdge(j))); 
             equivalents.push_back(std::pair<float,float>(h->GetBinLowEdge(j),originalLowEdge)); 
	     std::cout << "Found at " << j << " was " << h->FindBin(oldCut) <<  std::endl;
	     std::cout << h->GetBinLowEdge(j) << " was " << originalLowEdge << " cut: " << oldCut <<  std::endl;
             break;
          }
      }
 
    }
   return equivalents;
  }
  TGraph * makeGraph(TH1F * h,const std::vector<std::pair<float, float> > & cutsAndSF)
  {
      std::vector<std::pair<float, float> > eq = computeEquivalentCuts(h,cutsAndSF);
      float x[MAXPOINTS],y[MAXPOINTS];
      for(unsigned int i  = 1 ; i < MAXPOINTS-2 && i <= eq.size(); i++)
      {
         std::cout << " i " << i << std::endl;
         x[eq.size()-i+1]=eq[i-1].first;
         y[eq.size()-i+1]=eq[i-1].second;
      }
      //Boundary conditions for CSV
      x[0]=0;
      y[0]=0;
      x[eq.size()+1]=1.001;
      y[eq.size()+1]=1.001;

     return new TGraph(eq.size()+2,x,y);
  }

  ROOT::Math::Interpolator * makeInterpolator(TH1F * h,const std::vector<std::pair<float, float> > & cutsAndSF)
  {
      std::vector<std::pair<float, float> > eq = computeEquivalentCuts(h,cutsAndSF);
      std::vector<double> x;
      std::vector<double> y;
      x.push_back(0.);
      y.push_back(0.);
      for(unsigned int i  = 0 ; i < eq.size(); i++)
      {
          x.push_back(eq[eq.size()-i-1].first);
          y.push_back(eq[eq.size()-i-1].second);
      }
      x.push_back(1.001);
      y.push_back(1.001);

     return new ROOT::Math::Interpolator(x,y,ROOT::Math::Interpolation::kLINEAR);
  }

  void computeFunctions(float uncert=0., float uncertL = 0., int lineStyle=0, int markerStyle=21, const char * opts = "")
  {
    std::vector<std::pair<float, float> > cutsAndSFB,cutsAndSFC,cutsAndSFL;
  /*  cutsAndSFB.push_back(std::pair<float, float>(0.898,1));
    cutsAndSFB.push_back(std::pair<float, float>(0.65,1));
    cutsAndSFB.push_back(std::pair<float, float>(0.24,1));
    cutsAndSFC.push_back(std::pair<float, float>(0.898,1));
    cutsAndSFC.push_back(std::pair<float, float>(0.65,1));
    cutsAndSFC.push_back(std::pair<float, float>(0.24,1));
    cutsAndSFL.push_back(std::pair<float, float>(0.898,1));
    cutsAndSFL.push_back(std::pair<float, float>(0.65,1));
    cutsAndSFL.push_back(std::pair<float, float>(0.24,1));
   cutsAndSFB.push_back(std::pair<float, float>(0.898,0.94+uncert*0.1));
    cutsAndSFB.push_back(std::pair<float, float>(0.679,0.96+uncert*0.1));
    cutsAndSFB.push_back(std::pair<float, float>(0.244,1.00+uncert*0.1));*/
    cutsAndSFB.push_back(std::pair<float, float>(0.898,0.96+uncert*0.04));
    cutsAndSFB.push_back(std::pair<float, float>(0.679,0.97+uncert*0.04));
    cutsAndSFB.push_back(std::pair<float, float>(0.244,1.01+uncert*0.04));

  
    cutsAndSFC.push_back(std::pair<float, float>(0.898,0.94+uncert*0.1));
    cutsAndSFC.push_back(std::pair<float, float>(0.679,0.96+uncert*0.1));
    cutsAndSFC.push_back(std::pair<float, float>(0.24,1.00+uncert*0.1));

    cutsAndSFL.push_back(std::pair<float, float>(0.898,1.10+uncertL*0.22)); //10
    cutsAndSFL.push_back(std::pair<float, float>(0.679,1.08+uncertL*0.13));//8
    cutsAndSFL.push_back(std::pair<float, float>(0.244,1.07+uncertL*0.11)); //7

    ib= makeInterpolator(m_hb,cutsAndSFB);
    ic= makeInterpolator(m_hc,cutsAndSFC);
    il= makeInterpolator(m_hl,cutsAndSFL);


    TGraph *gb= makeGraph(m_hb,cutsAndSFB);
    TGraph *gc= makeGraph(m_hc,cutsAndSFC);
    TGraph *gl= makeGraph(m_hl,cutsAndSFL);
    gb->SetMarkerStyle(markerStyle);
    gc->SetMarkerStyle(markerStyle);
    gl->SetMarkerStyle(markerStyle);
    sb= new TSpline3("b",gb);
    sc= new TSpline3("c",gc);
    sl= new TSpline3("l",gl);
    sb->SetLineStyle(lineStyle);
    sc->SetLineStyle(lineStyle);
    sl->SetLineStyle(lineStyle);
    sb->SetLineColor(kRed);
    sc->SetLineColor(kGreen);
    sl->SetLineColor(kBlue);
    gb->SetMarkerColor(kRed);
    gc->SetMarkerColor(kGreen);
    gl->SetMarkerColor(kBlue);

    /*sb->Draw(opts);
    sc->Draw("same");
    sl->Draw("same");
    gb->Draw("P");
    gc->Draw("P");
    gl->Draw("P");*/
  }

  std::vector<std::pair<float, float> > m_cutsAndSF;
  std::vector<float> m_equivalents;
  TFile m_file;
  TH1F * m_hb;
  TH1F * m_hc;
  TH1F * m_hl;
ROOT::Math::Interpolator * ib;
  ROOT::Math::Interpolator * ic;
  ROOT::Math::Interpolator * il;

  TSpline3 * sb;
  TSpline3 * sc;
  TSpline3 * sl;
  

};

