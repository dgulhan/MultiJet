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
    
    Int_t R[] = {4};
    Int_t N[] = {3};
    int nR=1;
    int nN=1; //XCone
    
    int nPoints = 6;
    
    TCut CutsR[] = {"sqrt(pow(acos(cos(phi3-phi2)),2.)+pow(eta2-eta3,2.))<0.2",
                    "sqrt(pow(deltaPhi(phi3,phi2),2.)+pow(eta2-eta3,2.))<0.4",
                    "sqrt(pow(deltaPhi(phi3,phi2),2.)+pow(eta2-eta3,2.))<0.6",
                    "sqrt(pow(deltaPhi(phi3,phi2),2.)+pow(eta2-eta3,2.))<0.8",
                    "sqrt(pow(deltaPhi(phi3,phi2),2.)+pow(eta2-eta3,2.))<1.0",
                    "sqrt(pow(deltaPhi(phi3,phi2),2.)+pow(eta2-eta3,2.))<1.2",
        
    };
    
    TCut CutSeePull[] = {"pt1>180 && pt3>70 && acos(cos(phi1-phi2))>2*TMath::Pi()/3 " };
    TCut centrality = "0 < hiBin/2 && hiBin/2 < 30";
    
    //;&& acos((pull_y3*pull_y2+pull_phi3*pull_phi2)/(sqrt(pow(pull_y3,2.)+pow(pull_phi3,2.))*sqrt(pow(pull_y2,2.)+pow(pull_phi2,2.))))>TMath::Pi()/2"};
    
    Double_t X[]={0.2,0.4,0.6,0.8,1.0,1.2};
    Double_t Xerr[]={0.01,0.01,0.01,0.01,0.01,0.01};

    
    
    int nFiles = 4;
    TString Files[] = {"root://eoscms//eos/cms/store/group/cmst3/user/dgulhan/MultiJetSkims/20160720/PbPbMCpthat80+pullHiForestAOD_ALL.root",
                       "/afs/cern.ch/work/e/eruizvel/public/PbPbDataHIHardProbes+pullHiForest_ALL.root",
                       "root://eoscms//eos/cms/store/group/cmst3/user/dgulhan/MultiJetSkims/20160720/ppMCpthat80+pullHiForestAOD_ALL.root",
                       "root://eoscms//eos/cms/store/group/cmst3/user/dgulhan/MultiJetSkims/20160720/ppMCpthat80+pullHiForestAOD_ALL.root"};
    
    TTree *tree[nFiles];
    TFile *file[nFiles];
    TGraphErrors * gr[nFiles];
    
    Double_t Y[nFiles][nPoints];
    Double_t Yerr[nFiles][nPoints];
    
    int Color [] = { kRed , kBlue, kGreen, kMagenta };
    
    TH1D * Hist[nFiles][nPoints];

    
    for ( int iFile = 0 ; iFile < nFiles ; iFile ++){
        
        
        cout<<"loading file:"<<Files[iFile].Data()<<endl;
        file[iFile] = TFile::Open( Files[iFile].Data() );
        tree[iFile] = (TTree*)file[iFile]->Get(Form("xc_R%i_N%i_PF",R[0],N[0]));
        
        for ( int iPoint = 0 ; iPoint< nPoints ; iPoint++){
            
            Hist[iFile][iPoint] = new TH1D(Form("h%i%i",iFile,iPoint),"",50,0,3.5);
            
            if (iFile == 0 || iFile ==1 )
            {
                tree[iFile]->Draw(Form("sqrt( pow(pullEta2,2.0) + pow(pullPhi2,2.0) )>>h%i%i",iFile,iPoint),CutSeePull[0] && CutsR[iPoint] && centrality);
            }
            if (iFile == 2 || iFile == 3 )
            {
                tree[iFile]->Draw(Form("sqrt( pow(pullEta2,2.0) + pow(pullPhi2,2.0) )>>h%i%i",iFile,iPoint),CutSeePull[0] && CutsR[iPoint]);
            }
            
            Y[iFile][iPoint] = Hist[iFile][iPoint]->GetMean();

            cout<<"Mean: "<<Y[iFile][iPoint]<<endl;
            Yerr[iFile][iPoint] = Hist[iFile][iPoint]->GetMeanError();
        }
    }
    
    
    
    TCanvas *c2 = new TCanvas ("c2","",610,600);
    TLegend *t3=new TLegend(0.50,0.64,0.83,0.77);
    t3->SetFillColor(0);
    t3->SetBorderSize(0);
    t3->SetFillStyle(0);
    t3->SetTextFont(43);
    t3->SetTextSize(18);
    TString LabelGraph[] = {"PbPb PYTHIA+HYDJET", "PbPb Data" , "pp PYTHIA", "pp Data"};
    
    
    for ( int iFile = 0 ; iFile < nFiles ; iFile ++){
        gr[iFile] = new TGraphErrors(nPoints,X,Y[iFile],Xerr,Yerr[iFile]);
        gr[iFile]->SetFillColor(Color[iFile]);
        gr[iFile]->SetLineColor(Color[iFile]);
        if (iFile == 0) {
            gr[iFile]->GetXaxis()->SetTitle("#Delta R_{2,3} Cut");
            gr[iFile]->GetYaxis()->SetTitleOffset(2.4);
            gr[iFile]->SetMinimum(0.0);
            gr[iFile]->SetMaximum(0.0055);
            gr[iFile]->GetYaxis()->SetTitle("#LT | #vec{t} | #GT ");
            gr[iFile]->SetMinimum(0.11);
            gr[iFile]->SetMaximum(0.30);
            gr[iFile]->Draw();
        }
        else{
            gr[iFile]->Draw("SAME");
        }
        
        t3->AddEntry(gr[iFile],LabelGraph[iFile],"l");
    }

    t3->Draw("SAME");
    drawText("CMS Preliminary",0.12,0.85,23);
    drawText("p_{T,1}>180 GeV  p_{T,2}>70 GeV p_{T,3}>70 GeV",0.13,0.82,16);
    drawText("|#Delta#phi_{2,3}|>2#pi/3 |#Delta#eta_{2,3}|>0.2",0.13,0.78,16);
    
    
    
    
    c2->SaveAs("totbalvscentrality.png");
    c2->SaveAs("totbalvscentrality.pdf");
    c2->SaveAs("totbalvscentrality.gif");
    
    

    
    

    
}



