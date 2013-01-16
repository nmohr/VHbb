#ifndef GENERIC_PLOTTER_H
#define GENERIC_PLOTTER_H

#include <stdio.h>
#include <iostream>
#include <vector>
#include <string>
#include <TLegend.h>
#include <TAxis.h>
#include <TH1.h>
#include <math.h>

struct coolRatio {
    //coolRatio() :  
    
  // User must clean up the created ratio histograms.
  //TH1 make_rebinned_ratios(TH1* theHist, TH1* theReference, double maxUncertainty);
  //static double ratioError2(double numerator, double numeratorError2, double denominator, double denominatorError2);



TH1* make_rebinned_ratios(TH1* theHist, TH1* theReference, double maxUncertainty, bool useReferenceError = false, const int number = 0)
{
  std::vector<TH1*> hist;
  std::vector<TH1*> ratios;
  hist.push_back(theHist);
  hist.push_back(theReference);
  const int reference = 1;
   
  const int             numHistograms   = int(hist.size());
  assert(numHistograms >= 2);
  ratios.clear();

  // Find nonzero range
  const TH1*            denominator     = hist[reference];
  const TAxis*          rebinAxis       = denominator->GetXaxis();
  const int             binBound        = rebinAxis->GetNbins() + 1;  // overflow
  int                   firstBin        = 0;
  for (bool allEmpty = true; allEmpty && ++firstBin < binBound;)
    for (int i = 0; allEmpty && i < numHistograms; ++i)
      allEmpty         &= (hist[i] == 0 || hist[i]->GetBinContent(firstBin) == 0);
  int                   lastBin         = binBound;
  for (bool allEmpty = true; allEmpty && --lastBin > 0;)
    for (int i = 0; allEmpty && i < numHistograms; ++i)
      allEmpty         &= (hist[i] == 0 || hist[i]->GetBinContent(lastBin) == 0);
  if (lastBin <= firstBin)  return theHist;     // no content


  // Partition bins in range
  std::vector<double>   binEdges;
  if (firstBin > 1)     binEdges.push_back(rebinAxis->GetBinLowEdge(1));
  double                previousEdge    = rebinAxis->GetBinLowEdge(firstBin);
  std::vector<double>                   zeros     (numHistograms,0);
  std::vector<std::vector<double> >     sumNum    (1, zeros);
  std::vector<std::vector<double> >     sumNumErr2(1, zeros);
  std::vector<double>                   sumDen    (1, 0);
  std::vector<double>                   sumDenErr2(1, 0);

  ////std::cout << std::endl << rebinAxis->GetXmin() << " ( " << rebinAxis->GetBinLowEdge(firstBin) << " , ";
  ////std::cout << rebinAxis->GetBinUpEdge(lastBin) << " ) " << rebinAxis->GetXmax() << std::endl;
  for (int bin = firstBin; bin <= lastBin; ++bin) {
    // Find a filled block
    sumDen    .back()  += denominator->GetBinContent(bin);
    sumDenErr2.back()  += pow(denominator->GetBinError(bin), 2);
    bool                aboveThreshold  = (sumDen.back() != 0); // denominator must not vanish

    for (int iHist = 0; iHist < numHistograms; ++iHist) {
      if (iHist == reference)           continue;
      if (hist[iHist] == 0)             continue;
      double            num             = hist[iHist]->GetBinContent(bin);
      double            numErr2         = pow(hist[iHist]->GetBinError(bin), 2);
      sumNum    .back()[iHist]         += num;
      sumNumErr2.back()[iHist]         += numErr2;

      const double      error2          = ratioError2(sumNum.back()[iHist],sumNumErr2.back()[iHist],sumDen.back(),sumDenErr2.back(),useReferenceError);
      aboveThreshold   &= (sqrt(error2) * sumDen.back() < maxUncertainty * sumNum.back()[iHist]);
      if (maxUncertainty > 100.) aboveThreshold = true;
    } // end loop over histograms

    if (aboveThreshold && bin < lastBin) {
      //std::cout << " + [" << previousEdge << " , " << rebinAxis->GetBinUpEdge(bin) << "] = " << sumDen.back() << std::endl;
      binEdges.push_back(previousEdge);
      sumNum  .push_back(zeros);        sumNumErr2.push_back(zeros);
      sumDen  .push_back(0);            sumDenErr2.push_back(0);
      previousEdge      = rebinAxis->GetBinUpEdge(bin);
    }
  } // end loop over bins in reference

  if (binEdges.empty() || binEdges.back()!=previousEdge)  binEdges.push_back(previousEdge);
                                                          binEdges.push_back(rebinAxis->GetBinUpEdge (lastBin ));
  if (lastBin < binBound - 1)                             binEdges.push_back(rebinAxis->GetBinLowEdge(binBound));

  ////for (unsigned i=0; i<binEdges.size(); ++i)  std::cout << " " << binEdges[i];  std::cout << std::endl;
  ////for (unsigned i=0; i<sumDen.size(); ++i)    std::cout << " " << sumDen[i];    std::cout << std::endl;


  // Make ratios according to new bin edges
  ratios.reserve(numHistograms - 1);
  const unsigned        numBins         = binEdges.size() - 1u;
  const unsigned        numContent      = sumNum.size();
  assert(numBins >= numContent);


  for (int iHist = 0; iHist < numHistograms; ++iHist) {
    if (iHist == reference)             continue;
    if (hist[iHist] == 0)               continue;
    TH1*                ratio           = static_cast<TH1*>(hist[iHist]->Clone("Ratio"));
    TH1*                refError   = static_cast<TH1*>(hist[iHist]->Clone("RefError"));
    ratio->Reset    ();
    ratio->SetBins  (numBins, &(binEdges[0]));
    refError->Reset    ();
    refError->SetBins  (numBins, &(binEdges[0]));
    if (ratio->GetSumw2N() == 0)        ratio->Sumw2();
    if (refError->GetSumw2N() == 0)        refError->Sumw2();
    TArrayD*            error2          = ratio->GetSumw2();
    TArrayD*            refError2          = refError->GetSumw2();
    for (unsigned index = 0, bin = 1 + (firstBin > 1); index < numContent; ++index, ++bin) {
      if (sumDen[index] == 0)           continue;
      ratio ->SetBinContent(bin, sumNum[index][iHist] / sumDen[index]);
      error2->SetAt(ratioError2(sumNum[index][iHist],sumNumErr2[index][iHist],sumDen[index],sumDenErr2[index],useReferenceError), bin);
      if (sumNum[index][iHist] == 0 && sumDen[index] == 0){
        refError ->SetBinContent(bin, 0.);
        refError2->SetAt(0., bin);
      }
      else{
        refError ->SetBinContent(bin, 1.);
        refError2->SetAt(ratio1Error2(sumDen[index],sumDenErr2[index]), bin);
      }
    } // end loop over bins
    ratios.push_back(ratio);
    ratios.push_back(refError);
  } // end loop over histograms
  return ratios[number];
}

private:
double ratio1Error2(double denominator, double denominatorError2)
{
  if (denominator == 0) return 0;
  return  (denominatorError2/denominator/denominator );
}
double ratioError2(double numerator, double numeratorError2, double denominator, double denominatorError2,bool useDenominatorError=true)
{
  if (numerator   == 0) return 0;
  if (denominator == 0) return 0;
  if (!useDenominatorError) denominatorError2 = 0;
  const double          ratio           = numerator / denominator;
  return  ratio*ratio*( numeratorError2/numerator/numerator + denominatorError2/denominator/denominator );
}

};

#endif
