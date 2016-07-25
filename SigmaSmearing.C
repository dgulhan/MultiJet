#include "utilities.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TStyle.h"
#include "TColor.h"
#define sign(a) ( ( (a) < 0 )  ?  -1   : ( (a) > 0 ) )

float magnitude(float x, float y){
    
    return sqrt(pow(x,2.0)+pow(y,2.0));
    
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
    
    
    for (int iFile = 0; iFile < nFiles ; iFile++ ) {
        
        file[iFile] = TFile::Open( Files[iFile].Data() );
        tree[iFile] = (TTree*)file[iFile]->Get("xc_R4_N3_PF");
        hist[iFile] =  new TH1D(Form("hist%i",iFile),"",50,-0.025,0.025);
        tree[iFile]->Draw(Form("magnitude(pullEta,pullPhi)-magnitude(refPullEta,refPullPhi)>>hist%i",iFile),Cut[iFile]);
        hist[iFile]->Fit("gaus");
        
        func[iFile] = (TF1*)hist[iFile]->GetFunction("gaus");
        func[iFile]->SetLineColor(Color[iFile]);
        hist[iFile]->SetLineColor(Color[iFile]);
        cout<<"fit"<<endl;
    }
    
    
    TCanvas *c1 = new TCanvas("c1","",600,600);
    
    int iFile = 0;
    //func[iFile]->Draw("SAME");
    hist[iFile]->Draw("SAME");
    
    
    
    
    
    
    
}