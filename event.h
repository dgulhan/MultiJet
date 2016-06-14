#include <algorithm> 
#include <functional> 
#include <cctype>
// #include <locale>
#include <iostream>
// #include <string>
// #include <fstream>
// #include <sstream>
#include <vector>
#include <cmath>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
// #include <time.h>

struct Jet{
public :
  float pt;
  float eta;
  float phi;
  void reset(){
    pt = eta = phi = -99;
  }
  Jet(float pt, float eta, float phi){
    this->pt = pt; 
	this->eta = eta;
	this->phi = phi;
  }

public:
  bool operator < (const Jet& rhs) {
   if(this->pt < rhs.pt) return true;
   else return false;
  }
};


struct newEvent{
public :
   int            run;
   int            lumi;
   int            evt;
   int            hiBin;
   float          pthat;
   float          pt1;
   float          pt2;
   float          pt3;
   float          eta1;
   float          eta2;
   float          eta3;
   float          phi1;
   float          phi2;
   float          phi3;
   int            nref;
   float          rawpt[100]; 
   float          rawphi[100]; 
   float          raweta[100]; 
   void reset(){
    evt = lumi = run = -99;
 	pt1 = pt2 = pt3 = eta1 = eta2 = eta3 = phi1 = phi2 = phi3 = pthat = -99;
	nref = -99;
    for(int i = 0; i < 100; i++){
     rawpt[i] = -99;
     rawphi[i] = -99;
     raweta[i] = -99;
    }
   }
   newEvent(){
    reset();
   }
   
  
  void setEvent(int run, int lumi, int evt, int hiBin, std::vector<Jet> * jets){
    this->run = run; 
    this->lumi = lumi; 
    this->evt = evt; 
    this->hiBin = hiBin; 
    nref = jets->size();
	for(int i = 0; i < nref; i++){
	  rawpt[i] = jets->at(i).pt;
	  raweta[i] = jets->at(i).eta;
	  rawphi[i] = jets->at(i).phi;
	}
	std::sort(jets->begin(), jets->end());
	if(nref > 0){
      pt1 = jets->at(nref-1).pt;
      eta1 = jets->at(nref-1).eta;
      phi1 = jets->at(nref-1).phi;
	  if(nref > 1){
        pt2 = jets->at(nref-2).pt;
        eta2 = jets->at(nref-2).eta;
        phi2 = jets->at(nref-2).phi;
	    if(nref > 2){
          pt3 = jets->at(nref-3).pt;
          eta3 = jets->at(nref-3).eta;
          phi3 = jets->at(nref-3).phi;
	    }
	  }
	}
  }
};
