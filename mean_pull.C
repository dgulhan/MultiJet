//Compute the mean value of the pull vectors magnitude when varying R_23 distance.


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



void mean_pull(){
    int nPoints = 6;
    
    TCut CutsR[] = {"sqrt(pow(deltaPhi(phi3,phi2),2.)+pow(eta2-eta3,2.))<0.2",
                    "sqrt(pow(deltaPhi(phi3,phi2),2.)+pow(eta2-eta3,2.))<0.4",
                    "sqrt(pow(deltaPhi(phi3,phi2),2.)+pow(eta2-eta3,2.))<0.6",
                    "sqrt(pow(deltaPhi(phi3,phi2),2.)+pow(eta2-eta3,2.))<0.8",
                    "sqrt(pow(deltaPhi(phi3,phi2),2.)+pow(eta2-eta3,2.))<1.0",
                    "sqrt(pow(deltaPhi(phi3,phi2),2.)+pow(eta2-eta3,2.))<1.2",
        
    };
    
    TCut CutSeePull[] = {"pt1>180 && pt3>70 && acos(cos(phi1-phi2))>2*TMath::Pi()/3 && 0 < hiBin/2 && hiBin/2 < 30" }; //;&& acos((pull_y3*pull_y2+pull_phi3*pull_phi2)/(sqrt(pow(pull_y3,2.)+pow(pull_phi3,2.))*sqrt(pow(pull_y2,2.)+pow(pull_phi2,2.))))>TMath::Pi()/2"};
    
    Double_t X[]={0.2,0.4,0.6,0.8,1.0,1.2};
    Double_t Xerr[]={0.01,0.01,0.01,0.01,0.01,0.01};

    
    
    int nFiles = 4;
    TString Files[] = {"root://eoscms//eos/cms/store/group/cmst3/user/dgulhan/MultiJetSkims/20160720/PbPbMCpthat80+pullHiForestAOD_ALL.root",
                       "/afs/cern.ch/work/e/eruizvel/public/PbPbDataHIHardProbes+pullHiForest_ALL.root",
                       "root://eoscms//eos/cms/store/group/cmst3/user/dgulhan/MultiJetSkims/20160720/ppMCpthat80+pullHiForestAOD_ALL.root",
                        "root://eoscms//eos/cms/store/group/cmst3/user/dgulhan/MultiJetSkims/20160720/ppMCpthat80+pullHiForestAOD_ALL.root"};
    
    TTree *xc_R4_N3_PF[nFiles];
    TFile *file[nFiles];
    TGraphErrors * gr[nFiles];
    
    Double_t Y0[nPoints];
    Double_t Y0err[nPoints];
    Double_t Y1[nPoints];
    Double_t Y1err[nPoints];
    Double_t Y2[nPoints];
    Double_t Y2err[nPoints];
    Double_t Y3[nPoints];
    Double_t Y3err[nPoints];
    
    
    int Color[]={kRed,kBlue,kGreen,kMagenta};
    TH1D * h[nFiles][nPoints];
    

    int iFile;
    
    iFile=0;
    
    file[iFile] = TFile::Open(Files[iFile].Data());
    xc_R4_N3_PF[iFile]= (TTree*)file[iFile]->Get("xc_R4_N3_PF");

    for ( int iPoint = 0 ; iPoint< nPoints ; iPoint++){
        
        h[iFile][iPoint] = new TH1D(Form("h%i%i",iFile,iPoint),"",50,0,3.5);
        xc_R4_N3_PF[iFile]->Draw(Form("sqrt( pow(pullEta2,2.0) + pow(pullPhi2,2.0) )>>h%i%i",iFile,iPoint),CutSeePull[0] && CutsR[iPoint] );
        Y0[iPoint] = h[iFile][iPoint]->GetMean();
        cout<<h[iFile][iPoint]->GetMean()<<endl;
        Y0err[iPoint] = h[iFile][iPoint]->GetMeanError();
    }
    
    iFile=1;
    
    file[iFile] = TFile::Open(Files[iFile].Data());
    xc_R4_N3_PF[iFile]= (TTree*)file[iFile]->Get("xc_R4_N3_PF");
    
    for ( int iPoint = 0 ; iPoint< nPoints ; iPoint++){
        
        h[iFile][iPoint] = new TH1D(Form("h%i%i",iFile,iPoint),"",50,0,3.5);
        xc_R4_N3_PF[iFile]->Draw(Form("sqrt( pow(pullEta2,2.0) + pow(pullPhi2,2.0) )>>h%i%i",iFile,iPoint),CutSeePull[0] && CutsR[iPoint] );
        Y1[iPoint] = h[iFile][iPoint]->GetMean();
        cout<<h[iFile][iPoint]->GetMean()<<endl;
        Y1err[iPoint] = h[iFile][iPoint]->GetMeanError();
    }
    
    iFile=2;
    
    file[iFile] = TFile::Open(Files[iFile].Data());
    xc_R4_N3_PF[iFile]= (TTree*)file[iFile]->Get("xc_R4_N3_PF");
    
    for ( int iPoint = 0 ; iPoint< nPoints ; iPoint++){
        
        h[iFile][iPoint] = new TH1D(Form("h%i%i",iFile,iPoint),"",50,0,3.5);
        xc_R4_N3_PF[iFile]->Draw(Form("sqrt( pow(pullEta2,2.0) + pow(pullPhi2,2.0) )>>h%i%i",iFile,iPoint),CutSeePull[0] && CutsR[iPoint] );
        Y2[iPoint] = h[iFile][iPoint]->GetMean();
        cout<<h[iFile][iPoint]->GetMean()<<endl;
        Y2err[iPoint] = h[iFile][iPoint]->GetMeanError();
    }
    
    iFile=3;
    
    file[iFile] = TFile::Open(Files[iFile].Data());
    xc_R4_N3_PF[iFile]= (TTree*)file[iFile]->Get("xc_R4_N3_PF");
    
    for ( int iPoint = 0 ; iPoint< nPoints ; iPoint++){
        
        h[iFile][iPoint] = new TH1D(Form("h%i%i",iFile,iPoint),"",50,0,3.5);
        xc_R4_N3_PF[iFile]->Draw(Form("sqrt( pow(pullEta2,2.0) + pow(pullPhi2,2.0) )>>h%i%i",iFile,iPoint),CutSeePull[0] && CutsR[iPoint] );
        Y3[iPoint] = h[iFile][iPoint]->GetMean();
        cout<<h[iFile][iPoint]->GetMean()<<endl;
        Y3err[iPoint] = h[iFile][iPoint]->GetMeanError();
    }
    
        
    
    
    TCanvas *c2 = new TCanvas ("c2","",610,600);

    gr[0] = new TGraphErrors(nPoints,X,Y0,Xerr,Y0err);
    gr[0]->GetXaxis()->SetTitle("#Delta R_{2,3} Cut");
    gr[0]->GetYaxis()->SetTitleOffset(1.4);
    gr[0]->GetYaxis()->SetTitle("#LT | #vec{t} | #GT ");
    gr[0]->SetFillColor(Color[0]);
    gr[0]->SetLineColor(Color[0]);
    gr[0]->Draw();

    gr[1] = new TGraphErrors(nPoints,X,Y1,Xerr,Y1err);
    gr[1]->SetFillColor(Color[1]);
    gr[1]->SetLineColor(Color[1]);
    gr[1]->Draw("SAME");
    
    gr[2] = new TGraphErrors(nPoints,X,Y2,Xerr,Y2err);
    gr[2]->SetFillColor(Color[2]);
    gr[2]->SetLineColor(Color[2]);
    gr[2]->Draw("SAME");
    
    gr[3] = new TGraphErrors(nPoints,X,Y3,Xerr,Y3err);
    gr[3]->SetFillColor(Color[3]);
    gr[3]->SetLineColor(Color[3]);
    gr[3]->Draw("SAME");

    
    
    TLegend *t2=new TLegend(0.15,0.75,0.25,0.88);
    t2->SetFillColor(0);
    t2->SetBorderSize(0);
    t2->SetFillStyle(0);
    t2->SetTextFont(43);
    t2->SetTextSize(19);
    t2->AddEntry(gr[0],"PbPb PYTHIA+HYDJET","l");
    //t2->AddEntry(gr[1],"PbPb Data","l");
    t2->AddEntry(gr[2],"pp PYTHIA","l");
    //t2->AddEntry(gr[3],"pp Data","l");
    t2->Draw("SAME");
    drawText("p_{T,1}>180 GeV  p_{T,2}>70 GeV p_{T,3}>70 GeV |#Delta#phi_{1,2}|>2/3 #pi",0.25,0.20,15);


    
    
    

    
}



