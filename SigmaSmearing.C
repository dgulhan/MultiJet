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

void SigmaSmearing(){
    
    TString Files[] = {"root://eoscms//eos/cms/store/group/cmst3/user/dgulhan/MultiJetSkims/20160720/PbPbMCpthat80+pullHiForestAOD_ALL.root",
                       "root://eoscms//eos/cms/store/group/cmst3/user/dgulhan/MultiJetSkims/20160720/ppMCpthat80+pullHiForestAOD_ALL.root"
                      };
    
    int  nFiles = 2;
    
    TFile *file[nFiles];
    TTree *tree[nFiles];
    
    TCut Cut[] = {"pt1>100 && pt3>30 && acos(cos(phi1-phi2))>2*TMath::Pi()/3 && abs(eta1-eta2)>0.2",
                  "pt1>100 && pt3>30 && acos(cos(phi1-phi2))>2*TMath::Pi()/3 && abs(eta1-eta2)>0.2"
                 };
    
    TH1D *hist[nFiles];
    TF1 *func[nFiles];
    TF1 f1("f1","gaus",-0.02,0.02);
    
    int Color[] = {kRed,kBlue};
    
    float SigmaFit[nFiles];

    for (int iFile = 0; iFile < nFiles ; iFile++ ) {
        
        file[iFile] = TFile::Open( Files[iFile].Data() );
        tree[iFile] = (TTree*)file[iFile]->Get("xc_R4_N3_PF");
        hist[iFile] =  new TH1D(Form("hist%i",iFile),"",50,-0.025,0.025);
        
        tree[iFile]->SetAlias("dt","magnitude(pullEta,pullPhi)-magnitude(refPullEta,refPullPhi)");
        tree[iFile]->SetAlias( "theta23" , "acos((pullEta2*(eta3-eta2)+pullPhi2*deltaPhi(phi3,phi2))/( magnitude(pullEta2,pullPhi2)*magnitude(eta3-eta2,deltaPhi(phi3,phi2)) ))");
        tree[iFile]->SetAlias( "reftheta23" , "acos((refPullEta2*(refEta3-refEta2)+refPullPhi2*deltaPhi(refPhi3,refPhi2))/( magnitude(refPullEta2,refPullPhi2)*magnitude(refEta3-refEta2,deltaPhi(refPhi3,refPhi2)) ))");
        
        tree[iFile]->Draw(Form("dt>>hist%i",iFile),Cut[iFile]);
        hist[iFile]->Scale(1.0/hist[iFile]->Integral());
        hist[iFile]->Fit("gaus");
        
        func[iFile] = (TF1*)hist[iFile]->GetFunction("gaus");
        func[iFile]->SetLineColor(Color[iFile]);
        hist[iFile]->SetLineColor(Color[iFile]);
        cout<<"fit"<<endl;
        SigmaFit[nFiles] = func[iFile]->GetParameter(2);
    }
    
    
    TCanvas *c1 = new TCanvas("c1","",600,600);
    
    for (int iFile = 0; iFile < nFiles ; iFile++ ) {
        hist[iFile]->Draw("SAME");
        
    }
    
    float SigmaDiff = sqrt( pow(SigmaFit[0],2.0) - pow(SigmaFit[1],2.0) );
    
    
    //////////// -------------------- 2D CORRELATION PLOTS ------------ //////////////
    
    
    TH2D *corr[nFiles];
    
    for (int iFile = 0; iFile < nFiles ; iFile++ ) {
        
        corr[iFile] = new TH2D (Form("corr%i",iFile),"",50,0,TMath::Pi(),50,0.0,0.02);
        tree[iFile]->Draw(Form("dt:(theta23-reftheta23)>>corr%i",iFile),Cut[iFile]);
        
        
    }
    
    
    TCanvas *c3 = new TCanvas("c3","",600,600);
    tree[0]->Draw("dt",Cut[0]);
    TCanvas *c4 = new TCanvas("c4","",600,600);
    tree[0]->Draw("theta23-reftheta23",Cut[0]);
    
    
    TCanvas *c2 = new TCanvas("c2","",600,600);
    
    corr[0]->Draw("COLZ");
    
    TCanvas *c3 = new TCanvas("c3","",600,600);
    
    corr[1]->Draw("COLZ");
    
    
    
    
    
    
    
    
}