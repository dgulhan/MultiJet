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

float deltaR( float eta1, float phi1, float eta2, float phi2){
    float theDphi = deltaPhi( phi1, phi2);
    float theDeta = eta1 - eta2;
    return sqrt( theDphi*theDphi + theDeta*theDeta);
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
  float refPt; 
  float refEta; 
  float refPhi;
  //!pull
  float pullEta;
  float pullPhi;
  float refPullEta;
  float refPullPhi;
  //!matching to reco jet
  bool matched;
  int refIndex;
  
  void reset(){
    pt = eta = phi = -99;
	refPt = refEta = refPhi = -99;
    pullEta = pullPhi = -99;
    refPullEta = refPullPhi = -99;
	refIndex = -99;
	matched = false;
  }

  Jet(float pt, float eta, float phi, float pullEta = -99, float pullPhi = -99, bool matched = false, float refPt = -99, float refEta = -99, float refPhi = -99, float refPullEta = -99 , float refPullPhi = -99, int refIndex = -99){
    reset();
    this->pt = pt; 
	this->eta = eta;
	this->phi = phi;
    this->pullEta = pullEta;
    this->pullPhi = pullPhi;
    this->refPt = refPt; 
	this->refEta = refEta;
	this->refPhi = refPhi;
    this->refPullEta = refPullEta;
    this->refPullPhi = refPullPhi;
	this->matched = matched;
	this->refIndex = refIndex;
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
   
   //!reconstructed properties
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
    float          pullEta1;
    float          pullPhi1;
    float          pullEta2;
    float          pullPhi2;
    float          pullEta3;
    float          pullPhi3;
	
   //! matched properties
   float          refPt1;
   float          refPt2;
   float          refPt3;
   float          refEta1;
   float          refEta2;
   float          refEta3;
   float          refPhi1;
   float          refPhi2;
   float          refPhi3;
    float          refPullEta1;
    float          refPullPhi1;
    float          refPullEta2;
    float          refPullPhi2;
    float          refPullEta3;
    float          refPullPhi3;
	
	
	//!gen properties
   float          genPt1;
   float          genPt2;
   float          genPt3;
   float          genEta1;
   float          genEta2;
   float          genEta3;
   float          genPhi1;
   float          genPhi2;
   float          genPhi3;
   float          genPullEta1;
   float          genPullPhi1;
   float          genPullEta2;
   float          genPullPhi2;
   float          genPullEta3;
   float          genPullPhi3;
   //!inclusive jets
   int            nref;
   float          rawPt[100]; 
   float          rawPhi[100]; 
   float          rawEta[100]; 
   float          pullEta[100];
   float          pullPhi[100];
   float          refPt[100]; 
   float          refPhi[100]; 
   float          refEta[100]; 
   float          refPullEta[100];
   float          refPullPhi[100];
   int            ngen;
   float          genPt[100]; 
   float          genPhi[100]; 
   float          genEta[100];
   float          genPullEta[100];
   float          genPullPhi[100];
   //variables for pull(x,y)
    
   void reset(){
    evt = lumi = run = -99;
 	pt1 = pt2 = pt3 = eta1 = eta2 = eta3 = phi1 = phi2 = phi3 = pthat = -99;
	refPt1 = refPt2 = refPt3 = refEta1 = refEta2 = refEta3 = refPhi1 = refPhi2 = refPhi3 = -99;
	genPt1 = genPt2 = genPt3 = genEta1 = genEta2 = genEta3 = genPhi1 = genPhi2 = genPhi3 = -99;
	nref = -99;
	ngen = -99;
       
    pullEta1 = pullPhi1 = -99;
    pullEta1 = pullPhi1 = -99;
    pullEta1 = pullPhi1 = -99;

       
    refPullEta1 = refPullPhi1 = -99;
    refPullEta2 = refPullPhi2 = -99;
    refPullEta3 = refPullPhi3 = -99;
       
    genPullEta1 = genPullPhi1 = -99;
    genPullEta1 = genPullPhi1 = -99;
    genPullEta1 = genPullPhi1 = -99;
    
    for(int i = 0; i < 100; i++){
     rawPt[i] = -99;
     rawPhi[i] = -99;
     rawEta[i] = -99;
	 pullEta[i] = -99;
     pullPhi[i] = -99;
	 
     refPt[i] = -99;
     refPhi[i] = -99;
     refEta[i] = -99;       
     refPullEta[i] = -99;
     refPullPhi[i] = -99;
    
     genPt[i] = -99;
     genPhi[i] = -99;
     genEta[i] = -99;
     genPullEta[i] = -99;
     genPullPhi[i] = -99;
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
	  rawPt[i] = jets->at(i).pt;
	  rawEta[i] = jets->at(i).eta;
	  rawPhi[i] = jets->at(i).phi;
      pullEta[i] = jets->at(i).pullEta;
      pullPhi[i] = jets->at(i).pullPhi;
	  refPt[i] = jets->at(i).refPt;
	  refEta[i] = jets->at(i).refEta;
	  refPhi[i] = jets->at(i).refPhi;
      refPullEta[i] = jets->at(i).refPullEta;
      refPullPhi[i] = jets->at(i).refPullPhi;
	  
	}
	std::sort(jets->begin(), jets->end());
	if(nref > 0){
      pt1 = jets->at(nref-1).pt;
      eta1 = jets->at(nref-1).eta;
      phi1 = jets->at(nref-1).phi;
	  pullEta1 = jets->at(nref-1).pullEta;
      pullPhi1 = jets->at(nref-1).pullPhi;
	  
	  refPt1 = jets->at(nref-1).refPt;
	  refEta1 = jets->at(nref-1).refEta;
	  refPhi1 = jets->at(nref-1).refPhi;
      refPullEta1 = jets->at(nref-1).refPullEta;
      refPullPhi1 = jets->at(nref-1).refPullPhi;
      
        
	  if(nref > 1){
        pt2 = jets->at(nref-2).pt;
        eta2 = jets->at(nref-2).eta;
        phi2 = jets->at(nref-2).phi;
        pullEta2 = jets->at(nref-2).pullEta;
        pullPhi2 = jets->at(nref-2).pullPhi;
        
		refPt2 = jets->at(nref-2).refPt;
        refEta2 = jets->at(nref-2).refEta;
        refPhi2 = jets->at(nref-2).refPhi;
        refPullEta2 = jets->at(nref-2).refPullEta;
        refPullPhi2 = jets->at(nref-2).refPullPhi;
       	
	    if(nref > 2){
          pt3 = jets->at(nref-3).pt;
          eta3 = jets->at(nref-3).eta;
          phi3 = jets->at(nref-3).phi;
          pullEta3 = jets->at(nref-3).pullEta;
          pullPhi3 = jets->at(nref-3).pullPhi;
		  
          refPt3 = jets->at(nref-3).refPt;
          refEta3 = jets->at(nref-3).refEta;
          refPhi3 = jets->at(nref-3).refPhi;
          refPullEta3 = jets->at(nref-3).refPullEta;
          refPullPhi3 = jets->at(nref-3).refPullPhi;
		             
	    }
	  }
	}

      
      
	if(doGen){
	  ngen = genjets->size();
	  for(int i = 0; i < ngen; i++){
	    genPt[i] = genjets->at(i).pt;
	    genEta[i] = genjets->at(i).eta;
	    genPhi[i] = genjets->at(i).phi;
        genPullEta[i] = genjets->at(i).pullEta;
        genPullPhi[i] = genjets->at(i).pullPhi;
	  }
      std::sort(genjets->begin(), genjets->end());
	  if(ngen > 0){
        genPt1 = genjets->at(ngen-1).pt;
        genEta1 = genjets->at(ngen-1).eta;
        genPhi1 = genjets->at(ngen-1).phi;
        genPullPhi1 = genjets->at(ngen-1).pullPhi;
        genPullEta1 = genjets->at(ngen-1).pullEta;

	    if(ngen > 1){
          genPt2 = genjets->at(ngen-2).pt;
          genEta2 = genjets->at(ngen-2).eta;
          genPhi2 = genjets->at(ngen-2).phi;
            genPullPhi2 = genjets->at(ngen-2).pullPhi;
            genPullEta2 = genjets->at(ngen-2).pullEta;
	      if(ngen > 2){
            genPt3 = genjets->at(ngen-3).pt;
            genEta3 = genjets->at(ngen-3).eta;
            genPhi3 = genjets->at(ngen-3).phi;
              genPullPhi3 = genjets->at(ngen-3).pullPhi;
              genPullEta3 = genjets->at(ngen-3).pullEta;
	      }
	    }
	  }
	}
  }
};
