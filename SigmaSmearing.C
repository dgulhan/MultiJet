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
    
    TCut Cut[] = {"pt1>100 && pt3>30 && acos(cos(phi1-phi2))>2*TMath::Pi()/3 && abs(eta1-eta2)>0.2 && sqrt(pow(deltaPhi(phi3,phi2),2.)+pow(eta2-eta3,2.))<0.5",
                  "pt1>100 && pt3>30 && acos(cos(phi1-phi2))>2*TMath::Pi()/3 && abs(eta1-eta2)>0.2 && sqrt(pow(deltaPhi(phi3,phi2),2.)+pow(eta2-eta3,2.))<0.5"
                 };
    
    TCut CentralityBinsCuts[] = { " 50 < hiBin/2 && hiBin/2 < 100 ",
                                  " 30 < hiBin/2 && hiBin/2 < 50 " ,
                                  " 10 < hiBin/2 && hiBin/2 < 30 " ,
                                  " 0 < hiBin/2 && hiBin/2 < 10"
                                };
    int nCentr = 4;
    
    TH1D *hist[nFiles][nCentr];
    TF1 *func[nFiles][nCentr];
    TF1 f1("f1","gaus",-0.02,0.02);
    
    int Color[] = {kRed,kBlue};
    
    float SigmaFit[nFiles][nCentr];

    for (int iFile = 0; iFile < nFiles ; iFile++ ) {
        
        file[iFile] = TFile::Open( Files[iFile].Data() );
        tree[iFile] = (TTree*)file[iFile]->Get("xc_R4_N3_PF");
        
        tree[iFile]->SetAlias("dt","magnitude(pullEta,pullPhi)-magnitude(refPullEta,refPullPhi)");
        tree[iFile]->SetAlias( "theta23" , "acos((pullEta2*(eta3-eta2)+pullPhi2*deltaPhi(phi3,phi2))/( magnitude(pullEta2,pullPhi2)*magnitude(eta3-eta2,deltaPhi(phi3,phi2)) ))");
        tree[iFile]->SetAlias( "reftheta23" , "acos((refPullEta2*(refEta3-refEta2)+refPullPhi2*deltaPhi(refPhi3,refPhi2))/( magnitude(refPullEta2,refPullPhi2)*magnitude(refEta3-refEta2,deltaPhi(refPhi3,refPhi2)) ))");
        
        if (iFile==0) {
            for (int iCentr=0; iCentr<nCentr; iCentr++) {
                
                hist[iFile][iCentr] =  new TH1D(Form("hist%i%i",iFile,iCentr),"",50,-0.025,0.025);
                
                tree[iFile]->Draw(Form("dt>>hist%i%i",iFile,iCentr),Cut[iFile] && CentralityBinsCuts[iCentr]);
                
                hist[iFile][iCentr]->Scale(1.0/hist[iFile][iCentr]->Integral());
                hist[iFile][iCentr]->Fit("gaus");
                
                func[iFile][iCentr] = (TF1*)hist[iFile][iCentr]->GetFunction("gaus");
                func[iFile][iCentr]->SetLineColor(Color[iFile]);
                hist[iFile][iCentr]->SetLineColor(Color[iFile]);
                cout<<"fit"<<endl;
                SigmaFit[nFiles][iCentr] = func[iFile][iCentr]->GetParameter(2);
                
            }
            
        }
        if (iFile == 1) {
            int iCentr=0
            hist[iFile][iCentr] =  new TH1D(Form("hist%i%i",iFile,iCentr),"",50,-0.025,0.025);
            
            tree[iFile][iCentr]->Draw( Form("dt>>hist%i%i",iFile,iCentr),Cut[iFile] );
            hist[iFile][iCentr]->Scale(1.0/hist[iFile][iCentr]->Integral());
            hist[iFile][iCentr]->Fit("gaus");
            
            func[iFile][iCentr] = (TF1*)hist[iFile][iCentr]->GetFunction("gaus");
            func[iFile][iCentr]->SetLineColor(Color[iFile]);
            hist[iFile][iCentr]->SetLineColor(Color[iFile]);
            cout<<"fit"<<endl;
            SigmaFit[nFiles][iCentr] = func[iFile][iCentr]->GetParameter(2);

        }

    }
    
    
    
    TCanvas *c5[nFiles];
    
    for (int iFile = 0 ; iFile<nFiles; iFile++) {
        if (iFile==0) {
            c5[iFile] = new TCanvas(Form("c5%i",iFile),"",4*600,600);
            makeMultiPanelCanvas(c5[iFile],4,1,0.0,0.0,0.17,0.17,0.02);
            
            
            for (int iCentr = 0 ; iCentr < nCentr ; iCentr++) {
                
                c5[iFile]->cd(iCentr+1);
                hist[iFile][iCentr]->Draw("COLZ");
                
                
            }
            
        }
        if (iFile==1) {
            c5[iFile] = new TCanvas(Form("c5%i",iFile),"",600,600);
            
            hist[iFile][0]->Draw("COLZ");
        }
    }

    
    
    
    
    
    
    
    /***
    
    
    
    TCanvas *c1 = new TCanvas("c1","",600,600);
    
    for (int iFile = 0; iFile < nFiles ; iFile++ ) {
        hist[iFile]->Draw("SAME");
        
    }
    
    float SigmaDiff = sqrt( pow(SigmaFit[0],2.0) - pow(SigmaFit[1],2.0) );
    
    
    //////////// -------------------- 2D CORRELATION PLOTS ------------ //////////////
    
    
    TH2D *corr[nFiles][nCentr];
    
    for (int iFile = 0; iFile < nFiles ; iFile++ ) {
        for (int iCentr = 0 ; iCentr < nCentr ; iCentr++) {
            corr[iFile][iCentr] = new TH2D (Form("corr%i%i",iFile,iCentr),"",50,-TMath::Pi(),TMath::Pi(),50,-0.02,0.02);
            if (iFile==0) tree[iFile]->Draw(Form("dt:(theta23-reftheta23)>>corr%i%i",iFile,iCentr),Cut[iFile] && CentralityBinsCuts[iCentr]);
            if (iFile==1) tree[iFile]->Draw(Form("dt:(theta23-reftheta23)>>corr%i%i",iFile,iCentr),Cut[iFile]);

                }
        
    }
    
    
    TCanvas *c3 = new TCanvas("c3","",600,600);
    tree[0]->Draw("dt",Cut[0] && "dt>-20");
    TCanvas *c31 = new TCanvas("c31","",600,600);
    tree[1]->Draw("dt",Cut[1] && "dt>-20");

    
    TCanvas *c4 = new TCanvas("c4","",600,600);
    tree[0]->Draw("theta23-reftheta23",Cut[0]);
    TCanvas *c41 = new TCanvas("c41","",600,600);
    tree[1]->Draw("theta23-reftheta23",Cut[1]);

    
    TCanvas *c5[nFiles];

    for (int iFile = 0 ; iFile<nFiles; iFile++) {
        if (iFile==0) {
            c5[iFile] = new TCanvas(Form("c5%i",iFile),"",4*600,600);
            makeMultiPanelCanvas(c5[iFile],4,1,0.0,0.0,0.17,0.17,0.02);
            
            
            for (int iCentr = 0 ; iCentr < nCentr ; iCentr++) {
                
                c5[iFile]->cd(iCentr+1);
                corr[iFile][iCentr]->Draw("COLZ");
                
                
            }

        }
        if (iFile==1) {
            c5[iFile] = new TCanvas(Form("c5%i",iFile),"",600,600);
            
            corr[iFile][0]->Draw("COLZ");
        }
    }

    


    ***/
    
    
    
    
    
    
    
}