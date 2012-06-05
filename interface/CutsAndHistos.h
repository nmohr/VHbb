#ifndef CUTSANDHISTOS_H
#define CUTSANDHISTOS_H
#include <string>
#include <sstream>
#include <vector>
#include <TROOT.h>
#include <TFile.h>
#include "ntupleReader.hpp"
#include "samples.hpp"

enum  VType{ Zmm, Zee, Wmn, Wen, Znn } iType;

class Histos {
public:
   virtual void book(TFile &f, std::string suffix) = 0;
   virtual void fill( ntupleReader &event, float w) = 0;
//   virtual Histos * clone() =0;
};

class Cut {
 public:
  virtual bool pass( ntupleReader &event ) = 0;
   virtual std::string name() = 0;
   virtual bool operator()(ntupleReader &event) {return pass(event); }
};

class CutSample : public Cut {
 public:
  virtual bool pass( ntupleReader &event ) = 0;
  virtual bool pass( ntupleReader &event, Sample &sample ) = 0;
  virtual double weight( ntupleReader &event, Sample &sample ) = 0;
   virtual std::string name() = 0;
   virtual bool operator()(ntupleReader &event) {return pass(event); }
};

class NoCut : public Cut {
 public:
  virtual bool pass( ntupleReader &event )  { return true;}
   virtual std::string name() {return "NoCut"; }
};

/// One parameter cut class
class PCut : public Cut
{
 public:
  PCut(){}
 PCut(float cut) : m_cut(cut) {}
 PCut(float minCut, float maxCut) : m_cut(minCut), M_cut(maxCut) {}
  void setCut(float cut) {m_cut=cut;}
  void setCut(float minCut, float maxCut) {m_cut=minCut; M_cut=maxCut;}
  std::string cutValueString()
    {
      std::stringstream s;
      s << m_cut;
      return s.str();
    } 
  float m_cut;
  float M_cut; 
};

class CutSet : public Cut {
 public:
 void add(Cut *c) {cuts.push_back(c);}
 void drop(Cut *c) { pastes.push_back(c);}  
 int size(){ return cuts.size(); }
 bool pass(ntupleReader &event) {
  bool result=true;
  for(size_t i=0; i< cuts.size() ; i++)
    if( ! (cuts.at(i)->pass(event)) ) 
      result=false;
  for(size_t i=0; i< pastes.size() ; i++)
    if( (pastes.at(i)->pass(event)) ) 
      result=true;
  return result;
 } 
 std::string name() {
   std::stringstream s;
   for(size_t i=0; i< cuts.size() ; i++) {
     s << "_" << cuts.at(i)->name();
   }
 return s.str();
 }

private:
 std::vector<Cut *> cuts;
 std::vector<Cut *> pastes;
 
};


///CutSet of PCut, with scanning functions
// to be implemented still
class PCutSet : public Cut {
 public:
 void add(PCut *c) {cuts.push_back(c);}
 void drop(PCut *c) { pastes.push_back(c);}  
 int size(){ return cuts.size(); }
 bool pass(ntupleReader &event) {
  bool result=true;
  for(size_t i=0; i< cuts.size(); i++)
    if( ! (cuts.at(i)->pass(event)) )
      result=false;
  for(size_t i=0; i< pastes.size() ; i++)
    if( (pastes.at(i)->pass(event)) ) 
      result=true;
  return result;
 }
 bool pass(ntupleReader &event, int n) {
  bool result=true;
  for(size_t i=0; i< n; i++){
    if( ! (cuts.at(i)->pass(event)) )
      result=false;
    for(size_t i=0; i< pastes.size() ; i++)
      if( (pastes.at(i)->pass(event)) ) 
	result=true;
  }
  return result;
 }
 std::string name() {
   std::stringstream s;
   for(size_t i=0; i< cuts.size(); i++) {
     s << "_" << cuts.at(i)->name();
   }
 return s.str();
 }
 PCut * getCut( int i ) { return cuts.at(i); }

private:
 std::vector<PCut *> cuts;
 std::vector<PCut *> pastes;

};



class CutsAndHistos {
public:
  CutsAndHistos() {}
  CutsAndHistos(CutSample * c, std::vector<Histos *> & h):
    cutS(c),
    histos(h) {
      suffix=cutS->name(); }
  CutsAndHistos(CutSample * c, Histos * h):
    cutS(c) {
       histos.push_back(h);
       suffix=cutS->name(); }
  CutsAndHistos(Cut * c, std::vector<Histos *> & h):
    cut(c),
    histos(h) {
      suffix=cut->name(); }
  CutsAndHistos(Cut * c, Histos * h):
    cut(c) {
       histos.push_back(h);
       suffix=cut->name();
   }

  //TODO: implement destructor for all pointers received
  
  void book(TFile &f) {
    for(size_t i=0; i< histos.size(); i++) 
      histos.at(i)->book(f,suffix);
  }
  
  void process(ntupleReader &event, float w)
  {
    if(cutS->pass(event))
      for(size_t i=0; i< histos.size(); i++) 
	histos.at(i)->fill(event,w);
  }
  
  void process(ntupleReader &event, float w, Sample &s)
  {
    if(cutS->pass(event,s))
      for(size_t i=0; i< histos.size(); i++) 
	histos.at(i)->fill(event, (w * cutS->weight(event,s)) );
  }

  Cut * cut;
  CutSample * cutS;
  std::vector<Histos *> histos;

 private:
  std::string suffix;    
};

#endif

