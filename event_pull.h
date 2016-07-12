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


float deltaPhi( float phi1, float phi2) {
    float dphi = phi1 - phi2;
    
    if ( dphi > 3.141592653589 )
        dphi = dphi - 2. * 3.141592653589;
    if ( dphi <= -3.141592653589 )
        dphi = dphi + 2. * 3.141592653589;
    
    if ( TMath::Abs(dphi) > 3.141592653589 ) {
        cout << " commonUtility::getDPHI error!!! dphi is bigger than 3.141592653589 " << endl;
    }
    
    return dphi;
}



float Pull1_i( float Jy , float Jphi, float JpT, float pY, float pphi, float ppT  ){
    // input is Jy (pseudorapidity of Jet)
    //          Jphi (phi angle of Jet)
    //          JpT (pT of jet)
    //          and same for p stands for particle.
    // RETRUNS i_PULL. Need to sum over all i pulls one for each particle insinde jet
    // is a 2D vector
    float w_ratio = ppT* sqrt(pow((pY-Jy),2) + pow((pphi - Jphi),2) )/ JpT ;
    float t_i1 = w_ratio*(pY-Jy);
    return t_i1;
}
float Pull2_i( float Jy , float Jphi, float JpT, float pY, float pphi, float ppT  ){
    // input is Jy (pseudorapidity of Jet)
    //          Jphi (phi angle of Jet)
    //          JpT (pT of jet)
    //          and same for p stands for particle.
    // RETRUNS i_PULL. Need to sum over all i pulls one for each particle insinde jet
    // is a 2D vector
    float w_ratio = ppT* sqrt(pow((pY-Jy),2) + pow((deltaPhi(pphi,Jphi)),2) )/ JpT ;
    float t_i2 = w_ratio*(pphi-Jphi);
    return t_i2;
}


float w_ratio_i( float Jy , float Jphi, float JpT, float pY, float pphi, float ppT  ){
    //this only computes the ratio tu verifiy that it is always <1
    return ppT* sqrt(pow((pY-Jy),2.) + pow((deltaPhi(pphi,Jphi)),2.) )/ JpT ;
    
}





struct Jet{
public :
  float pt;
  float eta;
  float phi;
  float refpt; 
  float refeta; 
  float refphi;
  // pull
  float pull_y;
  float pull_phi;
    // pull
  float refpull_y;
  float refpull_phi;
  
  void reset(){
    pt = eta = phi = -99;
	refpt = refeta = refphi = -99;
    pull_y = pull_phi = -99;
    refpull_y = refpull_phi = -99;
  }
  Jet(float pt, float eta, float phi, float pull_y = -99, float pull_phi = -99, float refpt = -99, float refeta = -99, float refphi = -99, float refpull_y = -99 , float refpull_phi = -99){
    reset();
    this->pt = pt; 
	this->eta = eta;
	this->phi = phi;
      this->pull_y = pull_y;
      this->pull_phi = pull_phi;
    this->refpt = refpt; 
	this->refeta = refeta;
	this->refphi = refphi;
      this->refpull_y = refpull_y;
      this->refpull_phi = refpull_phi;
  }

public:
  bool operator < (const Jet& rhs) {
   if(this->pt < rhs.pt) return true;
   else return false;
  }
};


struct newEvent{
public :
   bool           doGen;
   
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
   //pull for leading, subleading and third jet.
    float          pull_y1;
    float          pull_phi1;
    float          pull_y2;
    float          pull_phi2;
    float          pull_y3;
    float          pull_phi3;
   float          refpt1;
   float          refpt2;
   float          refpt3;
   float          refeta1;
   float          refeta2;
   float          refeta3;
   float          refphi1;
   float          refphi2;
   float          refphi3;
    float          refpull_y1;
    float          refpull_phi1;
    float          refpull_y2;
    float          refpull_phi2;
    float          refpull_y3;
    float          refpull_phi3;
   float          genpt1;
   float          genpt2;
   float          genpt3;
   float          geneta1;
   float          geneta2;
   float          geneta3;
   float          genphi1;
   float          genphi2;
   float          genphi3;
    float          genpull_y1;
    float          genpull_phi1;
    float          genpull_y2;
    float          genpull_phi2;
    float          genpull_y3;
    float          genpull_phi3;
   int            nref;
   float          rawpt[100]; 
   float          rawphi[100]; 
   float          raweta[100]; 
   float          refpt[100]; 
   float          refphi[100]; 
   float          refeta[100]; 
   int            ngen;
   float          genpt[100]; 
   float          genphi[100]; 
   float          geneta[100];
    float           genpull_y[100];
    float           genpull_phi[100];
    float           refpull_y[100];
    float           refpull_phi[100];
   //variables for pull(x,y)
    float          pull_y[100];
    float          pull_phi[100];
    
   void reset(){
    evt = lumi = run = -99;
 	pt1 = pt2 = pt3 = eta1 = eta2 = eta3 = phi1 = phi2 = phi3 = pthat = -99;
	refpt1 = refpt2 = refpt3 = refeta1 = refeta2 = refeta3 = refphi1 = refphi2 = refphi3 = -99;
	genpt1 = genpt2 = genpt3 = geneta1 = geneta2 = geneta3 = genphi1 = genphi2 = genphi3 = -99;
	nref = -99;
	ngen = -99;
       
       pull_y1 = pull_phi1 = -99;
       pull_y1 = pull_phi1 = -99;
       pull_y1 = pull_phi1 = -99;

       
       refpull_y1 = refpull_phi1 = -99;
       refpull_y2 = refpull_phi2 = -99;
       refpull_y3 = refpull_phi3 = -99;
       
       genpull_y1 = genpull_phi1 = -99;
       genpull_y1 = genpull_phi1 = -99;
       genpull_y1 = genpull_phi1 = -99;
    
    for(int i = 0; i < 100; i++){
     rawpt[i] = -99;
     rawphi[i] = -99;
     raweta[i] = -99;
     refpt[i] = -99;
     refphi[i] = -99;
     refeta[i] = -99;
        
    //PUll
     pull_y[i] = -99;
     pull_phi[i] = -99;
        refpull_y[i] = -99;
        refpull_phi[i] = -99;
    }
    for(int i = 0; i < 100; i++){
     genpt[i] = -99;
     genphi[i] = -99;
     geneta[i] = -99;
        genpull_y[i] = -99;
        genpull_phi[i] = -99;
    }
   }
   newEvent(bool doGen){
    this->doGen = doGen;
    reset();
   }
   
  
  void setEvent(int run, int lumi, int evt, int hiBin, std::vector<Jet> * jets, std::vector<Jet> * genjets){
    this->run = run; 
    this->lumi = lumi; 
    this->evt = evt; 
    this->hiBin = hiBin; 
    nref = jets->size();
	for(int i = 0; i < nref; i++){
	  rawpt[i] = jets->at(i).pt;
	  raweta[i] = jets->at(i).eta;
	  rawphi[i] = jets->at(i).phi;
        pull_y[i] = jets->at(i).pull_y;
        pull_phi[i] = jets->at(i).pull_phi;
	  refpt[i] = jets->at(i).refpt;
	  refeta[i] = jets->at(i).refeta;
	  refphi[i] = jets->at(i).refphi;
        refpull_y[i] = jets->at(i).refpull_y;
        refpull_phi[i] = jets->at(i).refpull_phi;
	}
	std::sort(jets->begin(), jets->end());
	if(nref > 0){
      pt1 = jets->at(nref-1).pt;
      eta1 = jets->at(nref-1).eta;
      phi1 = jets->at(nref-1).phi;
	  refpt1 = jets->at(nref-1).refpt;
	  refeta1 = jets->at(nref-1).refeta;
	  refphi1 = jets->at(nref-1).refphi;
        pull_y1 = jets->at(nref-1).pull_y;
        pull_phi1 = jets->at(nref-1).pull_phi;
        refpull_y1 = jets->at(nref-1).refpull_y;
        refpull_phi1 = jets->at(nref-1).refpull_phi;
        
	  if(nref > 1){
        pt2 = jets->at(nref-2).pt;
        eta2 = jets->at(nref-2).eta;
        phi2 = jets->at(nref-2).phi;
        refpt2 = jets->at(nref-2).refpt;
        refeta2 = jets->at(nref-2).refeta;
        refphi2 = jets->at(nref-2).refphi;
          pull_y2 = jets->at(nref-2).pull_y;
          pull_phi2 = jets->at(nref-2).pull_phi;
          refpull_y2 = jets->at(nref-2).refpull_y;
          refpull_phi2 = jets->at(nref-2).refpull_phi;
          
	    if(nref > 2){
          pt3 = jets->at(nref-3).pt;
          eta3 = jets->at(nref-3).eta;
          phi3 = jets->at(nref-3).phi;
          refpt3 = jets->at(nref-3).refpt;
          refeta3 = jets->at(nref-3).refeta;
          refphi3 = jets->at(nref-3).refphi;
            pull_y3 = jets->at(nref-3).pull_y;
            pull_phi3 = jets->at(nref-3).pull_phi;
            refpull_y3 = jets->at(nref-3).refpull_y;
            refpull_phi3 = jets->at(nref-3).refpull_phi;
	    }
	  }
	}

      
      
	if(doGen){
	  ngen = genjets->size();
	  for(int i = 0; i < ngen; i++){
	    genpt[i] = genjets->at(i).pt;
	    geneta[i] = genjets->at(i).eta;
	    genphi[i] = genjets->at(i).phi;
        genpull_y[i] = genjets->at(i).pull_y;
        genpull_phi[i] = genjets->at(i).pull_phi;
	  }
      std::sort(genjets->begin(), genjets->end());
	  if(ngen > 0){
        genpt1 = genjets->at(ngen-1).pt;
        geneta1 = genjets->at(ngen-1).eta;
        genphi1 = genjets->at(ngen-1).phi;
        genpull_phi1 = genjets->at(ngen-1).pull_phi;
        genpull_y1 = genjets->at(ngen-1).pull_y;

	    if(ngen > 1){
          genpt2 = genjets->at(ngen-2).pt;
          geneta2 = genjets->at(ngen-2).eta;
          genphi2 = genjets->at(ngen-2).phi;
            genpull_phi2 = genjets->at(ngen-2).pull_phi;
            genpull_y2 = genjets->at(ngen-2).pull_y;
	      if(ngen > 2){
            genpt3 = genjets->at(ngen-3).pt;
            geneta3 = genjets->at(ngen-3).eta;
            genphi3 = genjets->at(ngen-3).phi;
              genpull_phi3 = genjets->at(ngen-3).pull_phi;
              genpull_y3 = genjets->at(ngen-3).pull_y;
	      }
	    }
	  }
	}
  }
};
