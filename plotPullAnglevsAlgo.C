#include "utilities.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TStyle.h"
#include "TMath.h"
#include "TColor.h"
#include <stdio.h>
#define sign(a) ( ( (a) < 0 )  ?  -1   : ( (a) > 0 ) )


float deltaPhi( float phi1, float phi2) {
    float dphi = phi1 - phi2;
    
    if ( dphi > 3.141592653589 ){
        dphi = dphi - 2. * 3.141592653589;}
    if ( dphi <= -3.141592653589 ){
        dphi = dphi + 2. * 3.141592653589;}
    if ( TMath::Abs(dphi) > 3.141592653589 ) {
        cout << " commonUtility::getDPHI error!!! dphi is bigger than 3.141592653589 " << endl;
    }
    
    return dphi;
}

float mag(float x, float y){
    return sqrt( pow(x,2)+pow(y,2));
}



void plotPullAnglevsAlgo(){
    TH1D::SetDefaultSumw2();
    
    int nFiles = 4;
    
    TString Files[] = {"root://eoscms//eos/cms/store/group/cmst3/user/dgulhan/MultiJetSkims/20160720/PbPbMCpthat80+pullHiForestAOD_ALL.root",
        "/afs/cern.ch/work/e/eruizvel/public/PbPbDataHIHardProbes+pullHiForest_ALL.root",
        "root://eoscms//eos/cms/store/group/cmst3/user/dgulhan/MultiJetSkims/20160720/ppMCpthat80+pullHiForestAOD_ALL.root",
        "root://eoscms//eos/cms/store/group/cmst3/user/dgulhan/MultiJetSkims/20160720/ppMCpthat80+pullHiForestAOD_ALL.root"};
    
    int Color[]={kRed,kBlue};

    TFile *file[nFiles];
    TH1D *h[nFiles];
    TTree *tree[nFiles];
    
    TCut cut = "pt1>180 && pt3>70 && acos(cos(phi1-phi2))>2*TMath::Pi()/3 && sqrt(pow(deltaPhi(phi3,phi2),2.)+pow(eta2-eta3,2.))<0.5";
    TCut CutCentr = "0 < hiBin/2 && hiBin/2 < 30";


    
    for (int iFile=0; iFile<nFiles ; iFile++ ){
        
        file[iFile] = TFile::Open(Files[iFile].Data());
        
        tree[iFile]= (TTree*)file[iFile]->Get(Form("xc_R4_N3"));
        
        h[iFile] = TH1D(Form("h%i",iFile),";#theta_{2,3}^{Pull};EventFraction",50,0,TMath::Pi());
        tree[iFile]->Draw(Form("acos((pullEta2*(eta3-eta2)+pullPhi2*deltaPhi(phi3,phi2))/( mag(pullEta2,pullPhi2)*mag(eta3-eta2,deltaPhi(phi3,phi2)) ))>>h%i",iFile), cut && CutCentr);
        h[iFile]->Scale(1./h[iFile]->Integral());
        makePretty(h[iFile]);
        
        if (iFile == 0) {
            h[iFile]->SetLineColor(Color[0]);
            h[iFile]->SetFillStyle(3005);
            h[iFile]->SetFillColorAlpha(Color[0],0.35);

        }
        if (iFile==1) {
            h[iFile]->SetMarkerStyle(20);
            h[iFile]->SetMarkerSize(0.5);
            h[iFile]->SetMarkerColor(Color[0]);
            h[iFile]->SetLineColor(Color[0]);
        }
        
        if (iFile == 2) {
            h[iFile]->SetLineColor(Color[1]);
            h[iFile]->SetFillStyle(3004);
            h[iFile]->SetFillColorAlpha(Color[1],0.35);
            
        }
        if (iFile==3) {
            h[iFile]->SetMarkerStyle(20);
            h[iFile]->SetMarkerSize(0.5);
            h[iFile]->SetMarkerColor(Color[1]);
            h[iFile]->SetLineColor(Color[1]);
        }
        
        
        
        
        
        
    }
    
    TCanvas * c2 = new TCanvas("c2","c2",550,450);
    makeMultiPanelCanvas(c2,1,1,-0.12,0.0,0.15,0.16,0.02);
    
    c2->cd(1);
    TLegend *t3=new TLegend(0.17,0.77,0.27,0.92);
    t3->SetFillColor(0);
    t3->SetBorderSize(0);
    t3->SetFillStyle(0);
    t3->SetTextFont(43);
    t3->SetTextSize(15);
    t3->SetTextAlign(13);
    t3->AddEntry(h[0] ,"XCone PbPb PYTHIA+HYDJET","f");
    t3->AddEntry(h[1] ,"XCone PbPb Data","p");
    t3->AddEntry(h[2] ,"XCone pp PYTHIA","f");
    t3->AddEntry(h[3] ,"XCone pp Data","p");
    h[0]->Draw();
    h[1]->Draw("SAME");
    h[2]->Draw("SAME");
    h[3]->Draw("SAME");
    t3->Draw();
    drawText("CMS Preliminary",0.17,0.93,23);
    drawText("p_{T,1}>180 GeV  p_{T,2}>70 GeV p_{T,3}>70 GeV",0.18,0.74,16);
    drawText("Centr. 30 - 0 %",0.18,0.70,16);
    
    
}
   