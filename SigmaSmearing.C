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
    
    TString Files[] = {};
    int  nFiles =  ;
    
    TFile *file[nFiles];
    TTree *tree[nFiles];
    
    TCut Cut[] = {};
    
    TH1D *hist[nFiles];
    
    for (int iFile = 0; iFile < nFiles ; iFile++ ) {
        file[iFile] = TFile::Open( Files[iFile].Data() );
        tree[iFile] = (*TTree)file[iFile]->Get("xc_R4_N3_P");
        
        hist[iFile] =  new TH1D(Form("hist%i",iFile),"",50,-4.0,4.0);
        
        tree[iFile]->Draw(Form("magnitude(pullEta,pullPhi)-magnitude(refpullEta,refpullPhi)>>hist%i",iFile),Cut[iFile])
        
        
    }
    
    
    
    
    
    
}