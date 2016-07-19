//implemneting pull angle as in Atlas Paper.
#include "utilities.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TStyle.h"
#include "TMath.h"
#include "TColor.h"
#include <stdio.h>

float deltaPhi( float phi1, float phi2) {
    float dphi = phi1 - phi2;
    
    if ( dphi > 3.141592653589 ){
        dphi = dphi - 2. * 3.141592653589;
        cout<<"dphi > 3.14 "<< dphi<<endl;}
    if ( dphi <= -3.141592653589 ){
        dphi = dphi + 2. * 3.141592653589;
        cout<<"dphi <= -3.14 "<<dphi<<endl;}
    if ( TMath::Abs(dphi) > 3.141592653589 ) {
        cout<<"abs(dphi)"<<TMath::Abs(dphi)<<endl;
        cout << " commonUtility::getDPHI error!!! dphi is bigger than 3.141592653589 " << endl;
    }
    
    return dphi;
}

float mag(float x, float y){
    return sqrt( pow(x,2)+pow(y,2));
}

void PullAngle(){
    
    int nFiles = 1;
    
    TString Files[] = { "ppMCpthat80+pullHiForestAOD_ALL.root" };
    
    TFile *file[nFiles];
    TTree *xcR4N3PF[nFiles];
    
    TCut cut1 = "pt1>120 && pt3>30 && acos(cos(phi1-phi2))>2*TMath::Pi()/3 && sqrt(pow(deltaPhi(phi3,phi2),2.)+pow(eta2-eta3,2.))<0.7" ;
    
    
    TH1D *h[nFiles];
    int Colors[] = {kRed,kBlue};
    TCanvas * c2 = new TCanvas("c2","c2",750,750);
    makeMultiPanelCanvas(c2,1,1,0.0,0.0,0.17,0.17,0.02);
    for ( int iFile = 0 ; iFile < nFiles; iFile++ ) {
        
        file[iFile] = TFile::Open(Files[iFile].Data());
        xcR4N3PF[iFile] = (TTree*)file[iFile]->Get("xc_R5_N3_PF");
        h[iFile] = new TH1D(Form("h%i",iFile),"XConeR5N3delta230.7;#theta_{Pull 2,3};Event fraction",50,0,3.5);
        xcR4N3PF[iFile]->Draw(Form("acos((pullEta2*(eta3-eta2)+pullPhi2*deltaPhi(phi3,phi2))/( mag(pullEta2,pullPhi2)*mag(eta3-eta2,deltaPhi(phi3,phi2)) ))>>h%i",iFile),cut1);
        h[iFile]->Scale(1./h[iFile]->Integral());
        h[iFile]->SetLineColor(Colors[iFile]);
        makePretty(h[iFile]);
    }
    
    h[0]->Draw();
    //h[1]->Draw("SAME");
    
}












