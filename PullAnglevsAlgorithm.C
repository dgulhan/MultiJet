//implemneting pull angle as in Atlas Paper plot it
//for antiKt and XCone for centraliti 0 to 30.
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
        //cout<<"dphi > 3.14 "<< dphi<<endl;
    }
    if ( dphi <= -3.141592653589 ){
        dphi = dphi + 2. * 3.141592653589;
        //cout<<"dphi <= -3.14 "<<dphi<<endl;
    }
    if ( TMath::Abs(dphi) > 3.141592653589 ) {
        //cout<<"abs(dphi)"<<TMath::Abs(dphi)<<endl;
        cout << " commonUtility::getDPHI error!!! dphi is bigger than 3.141592653589 " << endl;
    }
    
    return dphi;
}

float mag(float x, float y){
    return sqrt( pow(x,2)+pow(y,2));
}

void PullAnglevsAlgorithm(){
    
    int nFiles = 1;
    
    TString Files[] = {"root://eoscms//eos/cms/store/group/cmst3/user/dgulhan/MultiJetSkims/20160720/PbPbMCpthat80+pullHiForestAOD_ALL.root"};
        //"root://eoscms//eos/cms/store/group/cmst3/user/dgulhan/MultiJetSkims/20160720/ppMCpthat80+pullHiForestAOD_ALL.root"};

    
    TFile *file[nFiles];
    
    TTree *xcR5N3PF[nFiles];
    TTree *akR5PF[nFiles];
    TTree *xcR4N4PF[nFiles];
    TTree *akR4PF[nFiles];
    
    TCut Cut1a = "pt1>100 && pt3>30 && acos(cos(phi1-phi2))>2*TMath::Pi()/3 && sqrt(pow(deltaPhi(phi3,phi2),2.)+pow(eta2-eta3,2.))<0.7 && 0 < hiBin/2 && hiBin/2 < 30" ;
    TCut Cut1b = "pt1>100 && pt3>30 && acos(cos(phi1-phi2))>2*TMath::Pi()/3 && sqrt(pow(deltaPhi(phi3,phi2),2.)+pow(eta2-eta3,2.))<0.7 && 0 < hiBin/2 && hiBin/2 < 30" ;
    TCut Cut1c = "pt1>100 && pt3>30 && acos(cos(phi1-phi2))>2*TMath::Pi()/3 && sqrt(pow(deltaPhi(phi3,phi2),2.)+pow(eta2-eta3,2.))<0.7 && 0 < hiBin/2 && hiBin/2 < 30" ;
    
    
    TH1D *h[nFiles][6];
    int Colors[] = {kMagenta,kGreen}; //kGreen for XCone kMagenta anit-kT
    
    TCanvas * c2 = new TCanvas("c2","c2",4*450,450);
    makeMultiPanelCanvas(c2,3,1,0.0,0.0,0.17,0.17,0.02);
    
    for ( int iFile = 0 ; iFile < nFiles; iFile++ ) {
        
        file[iFile] = TFile::Open(Files[iFile].Data());
        
        xcR5N3PF[iFile] = (TTree*)file[iFile]->Get("xc_R5_N3_PF");
        akR5PF[iFile] = (TTree*)file[iFile]->Get("ak5PF");
        xcR4N4PF[iFile] = (TTree*)file[iFile]->Get("xc_R4_N4_PF");
        akR4PF[iFile] = (TTree*)file[iFile]->Get("ak4PF");
        
        h[iFile][0] = new TH1D(Form("h0%i",iFile),";#theta_{Pull 2,3};Event fraction",25,0,3.5);
        xcR5N3PF[iFile]->Draw(Form("acos((pullEta2*(eta3-eta2)+pullPhi2*deltaPhi(phi3,phi2))/( mag(pullEta2,pullPhi2)*mag(eta3-eta2,deltaPhi(phi3,phi2)) ))>>h0%i",iFile),Cut1a);
        h[iFile][0]->Scale(1./h[iFile][0]->Integral());
        h[iFile][0]->SetLineColor(Colors[0]);
        makePretty(h[iFile][0]);
        
        
        h[iFile][1] = new TH1D(Form("h1%i",iFile),";#theta_{Pull 2,3};Event fraction",25,0,3.5);
        akR5PF[iFile]->Draw(Form("acos((pullEta2*(eta3-eta2)+pullPhi2*deltaPhi(phi3,phi2))/( mag(pullEta2,pullPhi2)*mag(eta3-eta2,deltaPhi(phi3,phi2)) ))>>h1%i",iFile),Cut1a);
        h[iFile][1]->Scale(1./h[iFile][1]->Integral());
        h[iFile][1]->SetLineColor(Colors[1]);
        makePretty(h[iFile][1]);
        
        
        h[iFile][2] = new TH1D(Form("h2%i",iFile),";#theta_{Pull 2,3};Event fraction",25,0,3.5);
        xcR4N4PF[iFile]->Draw(Form("acos((pullEta2*(eta3-eta2)+pullPhi2*deltaPhi(phi3,phi2))/( mag(pullEta2,pullPhi2)*mag(eta3-eta2,deltaPhi(phi3,phi2)) ))>>h2%i",iFile),Cut1b);
        h[iFile][2]->Scale(1./h[iFile][2]->Integral());
        h[iFile][2]->SetLineColor(Colors[0]);
        makePretty(h[iFile][2]);
        
        
        h[iFile][3] = new TH1D(Form("h3%i",iFile),";#theta_{Pull 2,3};Event fraction",25,0,3.5);
        akR4PF[iFile]->Draw(Form("acos((pullEta2*(eta3-eta2)+pullPhi2*deltaPhi(phi3,phi2))/( mag(pullEta2,pullPhi2)*mag(eta3-eta2,deltaPhi(phi3,phi2)) ))>>h3%i",iFile),Cut1b);
        h[iFile][3]->Scale(1./h[iFile][3]->Integral());
        h[iFile][3]->SetLineColor(Colors[1]);
        makePretty(h[iFile][3]);
        
        
        h[iFile][4] = new TH1D(Form("h4%i",iFile),";#theta_{Pull 2,3};Event fraction",25,0,3.5);
        xcR4N4PF[iFile]->Draw(Form("acos((pullEta2*(rawEta[3]-eta2)+pullPhi2*deltaPhi(rawPhi[3],phi2))/( mag(pullEta2,pullPhi2)*mag(rawEta[3]-eta2,deltaPhi(rawPhi[3],phi2)) ))>>h4%i",iFile),Cut1c);
        h[iFile][4]->Scale(1./h[iFile][4]->Integral());
        h[iFile][4]->SetLineColor(Colors[0]);
        makePretty(h[iFile][4]);
        
        
        h[iFile][5] = new TH1D(Form("h5%i",iFile),";#theta_{Pull 2,3};Event fraction",25,0,3.5);
        akR4PF[iFile]->Draw(Form("acos((pullEta2*(rawEta[3]-eta2)+pullPhi2*deltaPhi(rawPhi[3],phi2))/( mag(pullEta2,pullPhi2)*mag(rawEta[3]-eta2,deltaPhi(rawPhi[3],phi2)) ))>>h5%i",iFile),Cut1c);
        h[iFile][5]->Scale(1./h[iFile][5]->Integral());
        h[iFile][5]->SetLineColor(Colors[1]);
        makePretty(h[iFile][5]);
        
        
    }
    
    int iFile=0;
    c2->cd(1);
    
    h[iFile][0]->SetStats(0);
    h[iFile][1]->SetStats(0);

    h[iFile][0]->Draw();
    h[iFile][1]->Draw("SAME");
    
    c2->cd(2);
    h[iFile][2]->SetStats(0);
    h[iFile][3]->SetStats(0);
    h[iFile][2]->Draw();
    h[iFile][3]->Draw("SAME");

    c2->cd(3);
    h[iFile][4]->SetStats(0);
    h[iFile][5]->SetStats(0);
    h[iFile][4]->Draw();
    h[iFile][5]->Draw("SAME");



}












