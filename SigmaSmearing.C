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
    
    TString Files[] = {"root://eoscms//eos/cms/store/group/cmst3/user/dgulhan/MultiJetSkims/20160712/PbPbPy8hat80HiForestAOD_ALL.root",
                       "root://eoscms//eos/cms/store/group/cmst3/user/dgulhan/MultiJetSkims/20160716/ppPy8hat80HiForestAOD_ALL.root"
                      };
    
    int  nFiles = 2;
    
    TFile *file[nFiles];
    TTree *tree[nFiles];
    
    TCut Cut[] = {"pt1>100 && pt3>30 && acos(cos(phi1-phi2))>2*TMath::Pi()/3 && abs(eta1-eta2)>0.2",
                  "pt1>100 && pt3>30 && acos(cos(phi1-phi2))>2*TMath::Pi()/3 && abs(eta1-eta2)>0.2"
                 };
    
    TH1D *hist[nFiles];
    
    for (int iFile = 0; iFile < nFiles ; iFile++ ) {
        cout<<"read file"<<endl;
        
        file[iFile] = TFile::Open( Files[iFile].Data() );
        
        cout<<"load tree"<<endl;
        tree[iFile] = (TTree*)file[iFile]->Get("xc_R4_N3_P");
        cout<<"load histo"<<endl;
        hist[iFile] =  new TH1D(Form("hist%i",iFile),"",50,-4.0,4.0);
        cout<<"def histo"<<endl;
        tree[iFile]->Draw(Form("pullEta>>hist%i",iFile),Cut[iFile]);
        cout<<"proj histo"<<endl;
        hist[iFile]->Fit("gaus");
        cout<<"fit"<<endl;
    }
    
    
    
    
    
    
}