#include "utilities.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TStyle.h"
#include "TColor.h"
#define sign(a) ( ( (a) < 0 )  ?  -1   : ( (a) > 0 ) )

float magnitude(float x, float y){
    
    return sqrt(pow(x,2.0)+pow(y,2.0));
    
}

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


void PlotThetaPull(){
    
    TString Files[] = { "root://eoscms//eos/cms/store/group/cmst3/user/dgulhan/MultiJetSkims/20160726/PbPbDataHIHardProbes+pullHiForest_ALL.root",
                        "root://eoscms//eos/cms/store/group/cmst3/user/dgulhan/MultiJetSkims/20160726/PbPbDataHIHardProbes+pullHiForest_ALL.root",
                        "root://eoscms//eos/cms/store/group/cmst3/user/dgulhan/MultiJetSkims/20160726/ppDataHighPt80+pullHiForest_ALL.root",
                        "root://eoscms//eos/cms/store/group/cmst3/user/dgulhan/MultiJetSkims/20160726/ppDataHighPt80+pullHiForest_ALL.root"
    };
    
    int nFiles=4;
    
    
    TFile *file[nFiles];
    TTree *tree[nFiles];
    
    TCut Cut[] = {"pt1>120 && pt3>50 && acos(cos(phi1-phi2))>2*TMath::Pi()/3 && abs(eta1-eta2)>0.2 && sqrt(pow(deltaPhi(phi3,phi2),2.)+pow(eta2-eta3,2.))<0.5",
                  "pt1>100 && pt3>30 && acos(cos(phi1-phi2))>2*TMath::Pi()/3 && abs(eta1-eta2)>0.2 && sqrt(pow(deltaPhi(phi3,phi2),2.)+pow(eta2-eta3,2.))<0.5",
                  "pt1>100 && pt3>30 && acos(cos(phi1-phi2))>2*TMath::Pi()/3 && abs(eta1-eta2)>0.2 && sqrt(pow(deltaPhi(phi3,phi2),2.)+pow(eta2-eta3,2.))<0.5",
                  "pt1>100 && pt3>30 && acos(cos(phi1-phi2))>2*TMath::Pi()/3 && abs(eta1-eta2)>0.2 && sqrt(pow(deltaPhi(phi3,phi2),2.)+pow(eta2-eta3,2.))<0.5"
    };
    
    TCut CentralityBinsCuts[] = { " 0 < hiBin/2 && hiBin/2 < 30"  };
    TString CentrText[] = { "Centr. 30-0%" };
    
    
    TH1D *hist[nFiles];
    
    
    int Color[] = {kRed,kRed,kBlue,kBlue};
    
    
    
    for (int iFile = 0; iFile < nFiles ; iFile++ ) {
        file[iFile] = TFile::Open( Files[iFile].Data() );
        tree[iFile] = (TTree*)file[iFile]->Get("xc_R4_N3_PF");
        
        tree[iFile]->SetAlias( "theta23" , "acos((pullEta2*(eta3-eta2)+pullPhi2*deltaPhi(phi3,phi2))/( magnitude(pullEta2,pullPhi2)*magnitude(eta3-eta2,deltaPhi(phi3,phi2)) ))");

        hist[iFile] =  new TH1D(Form("hist%i",iFile),";#theta_{2,3}^{pull};Event Fraction",50,0,TMath::Pi());
        
        tree[iFile]->Draw(Form("theta23>>hist%i",iFile),Cut[iFile] && CentralityBinsCuts[0]);
        hist[iFile]->Scale(1.0/hist[iFile]->Integral());
       
        hist[iFile]->SetStats(0);
        makePretty(hist[iFile]);
        
    }
    
    
    TCanvas *c5;
    
    c5 = new TCanvas(Form("c",0),"",451,450);
    makeMultiPanelCanvas(c5,1,1,0.0,0.0,0.17,0.17,0.02);
    
    TLegend *t3=new TLegend(0.42,0.80,0.56,0.88);
    t3->SetFillColor(0);
    t3->SetBorderSize(0);
    t3->SetFillStyle(0);
    t3->SetTextFont(43);
    t3->SetTextSize(15);
    t3->SetTextAlign(13);
    
    TString Label[] = { "PbPb PYTHIA+HYDJET" , "PbPb Data",  "pp PYTHIA" ,"pp Data" };
    TString LabelMode[] = { "f" , "p" , "f", "p"};
    for (int iFile = 0 ; iFile<nFiles; iFile++) {
        
        c5->cd(1);
        hist[iFile]->SetMaximum(0.2);
        
        if (iFile == 0 || iFile == 2) {
            if (iFile == 0) hist[iFile]->SetFillStyle(3005);
            if (iFile == 2) hist[iFile]->SetFillStyle(3004);
            hist[iFile]->SetLineColor(Color[iFile]);
            hist[iFile]->SetFillColorAlpha(Color[iFile],0.35);
            hist[iFile]->Draw("SAME HIST");

        }
        if (iFile == 1 || iFile == 3) {
            hist[iFile]->SetMarkerStyle(20);
            hist[iFile]->SetMarkerSize(0.5);
            hist[iFile]->SetMarkerColor(Color[iFile]);
            hist[iFile]->SetLineColor(ColorAK[iFile]);
            hist[iFile]->Draw("SAME HIST");

        }
        
        t3->AddEntry(hist[iFile],Label[iFile].Data(),LabelMode[iFile].Data())
        

    }
    drawText("p_{T,1}>120 GeV  p_{T,2}>50 GeV p_{T,3}>50 GeV",0.03,0.93,18);
    drawText("#Delta#phi_{1,2}> 2#pi/3 |#Delta#eta_{1,2}|>0.2",0.03,0.93,18);
    t3->Draw("SAME");
}