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

/***
void SigmaSmearing(){
    
    TString Files[] = {"root://eoscms//eos/cms/store/group/cmst3/user/dgulhan/MultiJetSkims/20160720/PbPbMCpthat80+pullHiForestAOD_ALL.root",
        "root://eoscms//eos/cms/store/group/cmst3/user/dgulhan/MultiJetSkims/20160720/ppMCpthat80+pullHiForestAOD_ALL.root"
    };
    
    int  nFiles = 2;
    
    TFile *file[nFiles];
    TTree *tree[nFiles];
    
    TCut Cut[] = {"pt1>120 && pt3>50 && acos(cos(phi1-phi2))>2*TMath::Pi()/3 && abs(eta1-eta2)>0.2 && sqrt(pow(deltaPhi(phi3,phi2),2.)+pow(eta2-eta3,2.))<0.5",
        "pt1>100 && pt3>30 && acos(cos(phi1-phi2))>2*TMath::Pi()/3 && abs(eta1-eta2)>0.2 && sqrt(pow(deltaPhi(phi3,phi2),2.)+pow(eta2-eta3,2.))<0.5"
    };
    
    TCut CentralityBinsCuts[] = { " 50 < hiBin/2 && hiBin/2 < 100 ",
        " 30 < hiBin/2 && hiBin/2 < 50 " ,
        " 10 < hiBin/2 && hiBin/2 < 30 " ,
        " 0 < hiBin/2 && hiBin/2 < 10"
    };
    TString CentrText[] = {"Centr. 100-50%","Centr. 50-30%","Centr. 30-10%","Centr. 10-0%"};
    
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
        
        for (int iCentr=0; iCentr<nCentr; iCentr++) {
            
            hist[iFile][iCentr] =  new TH1D(Form("hist%i%i",iFile,iCentr),";|#theta_{2,3 raw}^{pull}|-|#theta_{2,3 ref}^{pull}|;Event Fraction",50,-TMath::Pi(),TMath::Pi());
            
            if (iFile==0)  tree[iFile]->Draw(Form("(theta23-reftheta23)>>hist%i%i",iFile,iCentr),Cut[iFile] && CentralityBinsCuts[iCentr]);
            if (iFile == 1) tree[iFile]->Draw( Form("(theta23-reftheta23)>>hist%i%i",iFile,iCentr),Cut[iFile] );
            
            hist[iFile][iCentr]->Scale(1.0/hist[iFile][iCentr]->Integral());
            hist[iFile][iCentr]->Fit("gaus");
            
            func[iFile][iCentr] = (TF1*)hist[iFile][iCentr]->GetFunction("gaus");
            func[iFile][iCentr]->SetLineColor(Color[iFile]);
            hist[iFile][iCentr]->SetLineColor(Color[iFile]);
            hist[iFile][iCentr]->SetStats(0);
            makePretty(hist[iFile][iCentr]);
            cout<<"fit"<<endl;
            SigmaFit[iFile][iCentr] = func[iFile][iCentr]->GetParameter(2);
            
            
            
        }
        
        
    }
    
    
    
    TCanvas *c5;
    
    c5 = new TCanvas(Form("c5%i",0),"",4*451,450);
    makeMultiPanelCanvas(c5,4,1,0.0,0.0,0.17,0.17,0.02);
    
    TLegend *t3=new TLegend(0.42,0.80,0.56,0.88);
    t3->SetFillColor(0);
    t3->SetBorderSize(0);
    t3->SetFillStyle(0);
    t3->SetTextFont(43);
    t3->SetTextSize(15);
    t3->SetTextAlign(13);
    
    for (int iFile = 0 ; iFile<nFiles; iFile++) {
        
        for (int iCentr = 0 ; iCentr < nCentr ; iCentr++) {
            
            c5->cd(iCentr+1);
            hist[iFile][iCentr]->Draw("SAME");
            hist[iFile][iCentr]->SetMaximum(0.2);
            
            TLegend *t2;
            
            if (iCentr == 0){
                t2=new TLegend(0.19,0.83,0.26,0.95);
                drawText(Form("#sigma_{diff}=%0.6f",sqrt(abs(pow(SigmaFit[0][iCentr],2.0)-pow(SigmaFit[1][0],2.0)))),0.18,0.80,18);
                
            }
            if (iCentr > 0){
                t2=new TLegend(0.015,0.83,0.03,0.95);
                drawText(Form("#sigma_{diff}=%0.6f",sqrt(abs(pow(SigmaFit[0][iCentr],2.0)-pow(SigmaFit[1][0],2.0)))),0.03,0.80,18);
            }
            
            t2->SetFillColor(0);
            t2->SetBorderSize(0);
            t2->SetFillStyle(0);
            t2->SetTextFont(43);
            t2->SetTextSize(19);
            t2->AddEntry(c5 ,CentrText[iCentr].Data(),"");
            
            
            t2->Draw("SAME");
            
            if (iCentr == 0){
                drawText("",0.20,0.93,23);
            }
            if (iCentr == 1) {
                drawText("p_{T,1}>120 GeV  p_{T,2}>50 GeV p_{T,3}>50 GeV",0.03,0.93,18);
            }
            if (iCentr == 2){
                drawText("#Delta#phi_{1,2}> 2#pi/3 |#Delta#eta_{1,2}|>0.2",0.03,0.93,18);
            }
            
            if (iCentr == nCentr-1) {
                if (iFile==0 )  t3->AddEntry(hist[iFile][iCentr],"XCone PYTHIA+HYDJET","l");
                if (iFile==1 )  t3->AddEntry(hist[iFile][iCentr],"XCone PYTHIA","l");
                t3->Draw("SAME");
                
            }
            
            cout<<"iFile "<<iFile<<"    iCentr"<<iCentr<<"  Sigma "<<SigmaFit[iFile][iCentr]<<endl;
            cout<<Form("#sigma_{diff}=%0.6f",sqrt(abs(pow(SigmaFit[0][iCentr],2.0)-pow(SigmaFit[1][0],2.0))))<<endl;
        }
        
    }
    
    c5->SaveAs("SigmaSmearingTheta.png");
    c5->SaveAs("SigmaSmearingTheta.eps");
    c5->SaveAs("SigmaSmearingTheta.gif");
    
 
  ***/
    
void SigmaSmearing(){
 
    TString Files[] = {"/afs/cern.ch/work/e/eruizvel/public/CutconstPbPbMCpthat80+pullHiForestAOD_ALL.root",
                       "root://eoscms//eos/cms/store/group/cmst3/user/dgulhan/MultiJetSkims/20160720/ppMCpthat80+pullHiForestAOD_ALL.root"
                      };
    
    int  nFiles = 2;
    
    TFile *file[nFiles];
    TTree *tree[nFiles];
    
    TCut Cut[] = {"pt1>120 && pt3>50 && acos(cos(phi1-phi2))>2*TMath::Pi()/3 && abs(eta1-eta2)>0.2 && sqrt(pow(deltaPhi(phi3,phi2),2.)+pow(eta2-eta3,2.))>0.8  && sqrt(pow(deltaPhi(phi3,phi2),2.)+pow(eta2-eta3,2.))>1.57079632679",
                  "pt1>120 && pt3>50 && acos(cos(phi1-phi2))>2*TMath::Pi()/3 && abs(eta1-eta2)>0.2 && sqrt(pow(deltaPhi(phi3,phi2),2.)+pow(eta2-eta3,2.))>0.8 && sqrt(pow(deltaPhi(phi3,phi2),2.)+pow(eta2-eta3,2.))>1.57079632679"
                 };
    
    TCut CentralityBinsCuts[] = { " 50 < hiBin/2 && hiBin/2 < 100 ",
                                  " 30 < hiBin/2 && hiBin/2 < 50 " ,
                                  " 10 < hiBin/2 && hiBin/2 < 30 " ,
                                  " 0 < hiBin/2 && hiBin/2 < 10"
                                };
    TString CentrText[] = {"Centr. 100-50%","Centr. 50-30%","Centr. 30-10%","Centr. 10-0%"};

    int nCentr = 4;
    
    TH1D *hist[nFiles][nCentr];
    TF1 *func[nFiles][nCentr];
    TF1 *f1[nFiles][nCentr];
	
    int Color[] = {kRed,kBlue};
    
    float SigmaFit[nFiles][nCentr];
    
    for (int iFile = 0; iFile < nFiles ; iFile++ ) {

    
        file[iFile] = TFile::Open( Files[iFile].Data() );
        tree[iFile] = (TTree*)file[iFile]->Get("xc_R4_N3_PF");
        
        tree[iFile]->SetAlias("dt","magnitude(pullEta,pullPhi)-magnitude(refPullEta,refPullPhi)");
        tree[iFile]->SetAlias( "theta23" , "acos((pullEta2*(eta3-eta2)+pullPhi2*deltaPhi(phi3,phi2))/( magnitude(pullEta2,pullPhi2)*magnitude(eta3-eta2,deltaPhi(phi3,phi2)) ))");
        tree[iFile]->SetAlias( "reftheta23" , "acos((refPullEta2*(refEta3-refEta2)+refPullPhi2*deltaPhi(refPhi3,refPhi2))/( magnitude(refPullEta2,refPullPhi2)*magnitude(refEta3-refEta2,deltaPhi(refPhi3,refPhi2)) ))");
        
        for (int iCentr=0; iCentr<nCentr; iCentr++) {
                
            hist[iFile][iCentr] =  new TH1D(Form("hist%i%i",iFile,iCentr),";|#vec{t}_{raw}|-|#vec{t}_{ref}|;Event Fraction",50,-0.01,0.01);
                
            if (iFile==0)  tree[iFile]->Draw(Form("dt>>hist%i%i",iFile,iCentr),Cut[iFile] && CentralityBinsCuts[iCentr]);
            if (iFile == 1) tree[iFile]->Draw( Form("dt>>hist%i%i",iFile,iCentr),Cut[iFile] );
                
            hist[iFile][iCentr]->Scale(1.0/hist[iFile][iCentr]->Integral());
            
			float maxBinCenter = hist[iFile][iCentr]->GetBinCenter(hist[iFile][iCentr]->GetMaximumBin());
			float histRMS = hist[iFile][iCentr]->GetRMS();
			
			if(iFile==0) func[iFile][iCentr] = new TF1(Form("func_%d_%d", iFile, iCentr),"gaus(0)", maxBinCenter - 2*histRMS, maxBinCenter + 2*histRMS);
			else func[iFile][iCentr] = new TF1(Form("func_%d_%d", iFile, iCentr),"gaus(0)", maxBinCenter - histRMS, maxBinCenter + histRMS);
			func[iFile][iCentr]->SetParameters(0.1,0.001,0.01);
			hist[iFile][iCentr]->Fit(func[iFile][iCentr],"R LL");
                
            // func[iFile][iCentr] = (TF1*)hist[iFile][iCentr]->GetFunction("gaus");
            func[iFile][iCentr]->SetLineColor(Color[iFile]);
            hist[iFile][iCentr]->SetLineColor(Color[iFile]);
            hist[iFile][iCentr]->SetStats(0);
            makePretty(hist[iFile][iCentr]);
            cout<<"fit"<<endl;
            SigmaFit[iFile][iCentr] = func[iFile][iCentr]->GetParameter(2);
            
            
    
        }
        

    }
    
    
    
    TCanvas *c5;
    
    c5 = new TCanvas(Form("c5%i",0),"",4*451,450);
    makeMultiPanelCanvas(c5,4,1,0.0,0.0,0.17,0.17,0.02);

    TLegend *t3=new TLegend(0.42,0.80,0.56,0.88);
    t3->SetFillColor(0);
    t3->SetBorderSize(0);
    t3->SetFillStyle(0);
    t3->SetTextFont(43);
    t3->SetTextSize(15);
    t3->SetTextAlign(13);
    
    for (int iFile = 0 ; iFile<nFiles; iFile++) {
        
        for (int iCentr = 0 ; iCentr < nCentr ; iCentr++) {
                
            c5->cd(iCentr+1);
            hist[iFile][iCentr]->Draw("SAME");
            hist[iFile][iCentr]->SetMaximum(0.25);
            
            TLegend *t2;
            
            if (iCentr == 0){
                t2=new TLegend(0.19,0.83,0.26,0.95);
                drawText(Form("#sigma_{diff}=%0.6f",sqrt(pow(SigmaFit[0][iCentr],2.0)-pow(SigmaFit[1][0],2.0))),0.18,0.80,18);
                
            }
            if (iCentr > 0){
                t2=new TLegend(0.015,0.83,0.03,0.95);
                drawText(Form("#sigma_{diff}=%0.6f",sqrt(pow(SigmaFit[0][iCentr],2.0)-pow(SigmaFit[1][0],2.0))),0.03,0.80,18);
            }
            
            t2->SetFillColor(0);
            t2->SetBorderSize(0);
            t2->SetFillStyle(0);
            t2->SetTextFont(43);
            t2->SetTextSize(19);
            t2->AddEntry(c5 ,CentrText[iCentr].Data(),"");
            
            
            t2->Draw("SAME");
            
            if (iCentr == 0){
                drawText("",0.20,0.93,23);
            }
            if (iCentr == 1) {
                drawText("p_{T,1}>120 GeV  p_{T,2}>50 GeV p_{T,3}>50 GeV",0.03,0.93,18);
            }
            if (iCentr == 2){
                drawText("#Delta#phi_{1,2}> 2#pi/3 |#Delta#eta_{1,2}|>0.2",0.03,0.93,18);
            }
                
            if (iCentr == nCentr-1) {
                if (iFile==0 )  t3->AddEntry(hist[iFile][iCentr],"XCone PYTHIA+HYDJET","l");
                if (iFile==1 )  t3->AddEntry(hist[iFile][iCentr],"XCone PYTHIA","l");
                t3->Draw("SAME");

            }
            
            cout<<"iFile "<<iFile<<"    iCentr"<<iCentr<<"  Sigma "<<SigmaFit[iFile][iCentr]<<endl;
            cout<<Form("#sigma_{diff}=%0.6f",sqrt(pow(SigmaFit[0][iCentr],2.0)-pow(SigmaFit[1][0],2.0)))<<endl;
        }
            
    }
   
    c5->SaveAs("SigmaSmearingPullVector.png");
    c5->SaveAs("SigmaSmearingPullVector.eps");
    c5->SaveAs("SigmaSmearingPullVector.gif");


    
    
    
    
    
    
    
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