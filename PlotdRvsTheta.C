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

float magnitude(float x, float y){
    return sqrt( pow(x,2)+pow(y,2));
}



void PlotdRvsTheta(){
    
    Int_t R[] = {4};
    Int_t N[] = {3};
    int nR=1;
    int nN=1; //XCone
    
    int nPoints = 3;
    
    TCut CutsR[] = {
        "sqrt(pow(deltaPhi(phi3,phi2),2.)+pow(eta2-eta3,2.))>0.8 && sqrt(pow(deltaPhi(phi3,phi2),2.)+pow(eta2-eta3,2.))<1.0",
        "sqrt(pow(deltaPhi(phi3,phi2),2.)+pow(eta2-eta3,2.))>1.0 && sqrt(pow(deltaPhi(phi3,phi2),2.)+pow(eta2-eta3,2.))<1.2",
        "sqrt(pow(deltaPhi(phi3,phi2),2.)+pow(eta2-eta3,2.))>1.2 && sqrt(pow(deltaPhi(phi3,phi2),2.)+pow(eta2-eta3,2.))<1.6",
        
    };
    
    TCut CutSeePull[] = {"pt1>190 && pt3>70 && acos(cos(phi1-phi2))>2*TMath::Pi()/3 " };
    TCut centrality = "0 < hiBin/2 && hiBin/2 < 30";
    
    //;&& acos((pull_y3*pull_y2+pull_phi3*pull_phi2)/(sqrt(pow(pull_y3,2.)+pow(pull_phi3,2.))*sqrt(pow(pull_y2,2.)+pow(pull_phi2,2.))))>TMath::Pi()/2"};
    
    Double_t X[]={0.9,1.1,1.4};
    Double_t Xerr[]={0.01,0.01,0.01};
    
    
    
    int nFiles = 4;
    TString Files[] = {
        "root://eoscms//eos/cms/store/group/cmst3/user/dgulhan/MultiJetSkims/20160720/PbPbMCpthat80+pullHiForestAOD_ALL.root",
        "/afs/cern.ch/work/e/eruizvel/public/PbPbDataHIHardProbes+pullHiForest_ALL.root",
        "root://eoscms//eos/cms/store/group/cmst3/user/dgulhan/MultiJetSkims/20160720/ppMCpthat80+pullHiForestAOD_ALL.root",
        "root://eoscms//eos/cms/store/group/cmst3/user/dgulhan/MultiJetSkims/20160726/ppDataHighPt80+pullHiForest_ALL.root"
    };

    
    TTree *tree[nFiles];
    TFile *file[nFiles];
    TGraphErrors * gr[nFiles];
    
    Double_t Y[nFiles][nPoints];
    Double_t Yerr[nFiles][nPoints];
    
    Double_t CountTheta[nPoints][nFiles];
    Double_t ErrCountTheta[nPoints][nFiles];
    
    int Color [] = { kRed , kBlue, kGreen, kMagenta };
    
    TH1D * Hist[nFiles][nPoints];
    
    
    Double_t Ntheta[nFiles][nPoints];
    Double_t Nall[nFiles][nPoints];
    for ( int iFile = 0 ; iFile < nFiles ; iFile ++){
        
        
        cout<<"loading file:"<<Files[iFile].Data()<<endl;
        file[iFile] = TFile::Open( Files[iFile].Data() );
        tree[iFile] = (TTree*)file[iFile]->Get(Form("xc_R4_N3_PF",R[0],N[0]));
        tree[iFile]->SetAlias( "theta23" , "acos((pullEta2*(eta3-eta2)+pullPhi2*deltaPhi(phi3,phi2))/( magnitude(pullEta2,pullPhi2)*magnitude(eta3-eta2,deltaPhi(phi3,phi2)) ))");
        tree[iFile]->SetAlias( "theta32" , "acos((pullEta3*(eta2-eta3)+pullPhi3*deltaPhi(phi2,phi3))/( magnitude(pullEta3,pullPhi3)*magnitude(eta2-eta3,deltaPhi(phi2,phi3)) ))");
        
        
        for ( int iPoint = 0 ; iPoint< nPoints ; iPoint++){
            
            
            Hist[iFile][iPoint] = new TH1D(Form("h%i%i",iFile,iPoint),"",50,0,3.5);
            
            if (iFile == 0 || iFile ==1 )
            {
                tree[iFile]->Draw(Form("theta23>>h%i%i",iFile,iPoint),CutSeePull[0] && CutsR[iPoint] && centrality);
            }
            if (iFile == 2 || iFile == 3 )
            {
                tree[iFile]->Draw(Form("theta23>>h%i%i",iFile,iPoint),CutSeePull[0] && CutsR[iPoint]);
            }
            
            Ntheta[iFile][iPoint] = Hist[iFile][iPoint]->Integral( Hist[iFile][iPoint]->FindBin(0.) , Hist[iFile][iPoint]->FindBin(TMath::Pi()/2.) );
            
            Nall[iFile][iPoint] = Hist[iFile][iPoint]->Integral( Hist[iFile][iPoint]->FindBin(0) , Hist[iFile][iPoint]->FindBin( TMath::Pi() ) );
            
            CountTheta[iFile][iPoint] = Ntheta[iFile][iPoint]/Nall[iFile][iPoint] ;
            ErrCountTheta[iFile][iPoint] = (Ntheta[iFile][iPoint] /Nall[iFile][iPoint])*(sqrt((1./Ntheta[iFile][iPoint])+ (1./Nall[iFile][iPoint]) ) ) ;
            
            
            //Y[iFile][iPoint] = Hist[iFile][iPoint]->GetMean();
            
            cout<<"Ratio: "<<CountTheta[iFile][iPoint]<<endl;
            //Yerr[iFile][iPoint] = Hist[iFile][iPoint]->GetMeanError();
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
        gr[iFile] = new TGraphErrors(nPoints,X,CountTheta[iFile],Xerr,ErrCountTheta[iFile]);
        gr[iFile]->SetFillColor(Color[iFile]);
        gr[iFile]->SetLineColor(Color[iFile]);
        if (iFile == 0) {
            gr[iFile]->GetXaxis()->SetTitle("#Delta R_{2,3} Cut");
            gr[iFile]->GetYaxis()->SetTitleOffset(2.4);
            gr[iFile]->SetMinimum(0.34);
            gr[iFile]->SetMaximum(1.23);
            gr[iFile]->GetYaxis()->SetTitle("#theta_{2,3}^{Pull}[0,#pi/2]/ #theta_{2,3}^{Pull}[#pi/2,#pi] ");
            
            gr[iFile]->Draw();
        }
        else{
            gr[iFile]->Draw("SAME");
        }
        
        t3->AddEntry(gr[iFile],LabelGraph[iFile],"l");
    }
    
    Double_t RatioPoints[2][nPoints];
    Double_t ErrRatioPoints[2][nPoints];

    for (int iPoint = 0 ; iPoint<nPoints ; iPoint ++ ){
        RatioPoints[0][iPoint] = CountTheta[0][iPoint]/CountTheta[2][iPoint];
        ErrRatioPoints[0][iPoint] = (ErrCountTheta[0][iPoint]*CountTheta[2][iPoint] + ErrCountTheta[2][iPoint]*CountTheta[0][iPoint])/pow(CountTheta[2][iPoint],2.0);

        RatioPoints[1][iPoint] = CountTheta[1][iPoint]/CountTheta[3][iPoint];
        ErrRatioPoints[1][iPoint] = (ErrCountTheta[1][iPoint]*CountTheta[3][iPoint] + ErrCountTheta[3][iPoint]*CountTheta[1][iPoint])/pow(CountTheta[3][iPoint],2.0);
        
        cout<<"bla: "<<RatioPoints[0][iPoint]<<"+- "<<ErrRatioPoints[0][iPoint]<<endl;
        cout<<"bla bla: "<<RatioPoints[1][iPoint]<<"+- "<<ErrRatioPoints[1][iPoint]<<endl;
    }
    
    TGraphErrors * rat[2];

    rat[0] = new TGraphErrors(nPoints,X,RatioPoints[0],Xerr,ErrRatioPoints[0]);
    rat[1] = new TGraphErrors(nPoints,X,RatioPoints[1],Xerr,ErrRatioPoints[1]);
    rat[0]->SetFillColor(kBlue-2);
    rat[0]->SetLineColor(kBlue-2);
    rat[1]->SetFillColor(kOrange+1);
    rat[1]->SetLineColor(kOrange+1);
    
    t3->AddEntry(rat[0],"PYTHIA + HYDJET / PYTHIA","l");
    t3->AddEntry(rat[1],"PbPb Data / pp Data","l");
    rat[0]->Draw("SAME");
    rat[1]->Draw("SAME");
    
    
    t3->Draw("SAME");
    drawText("CMS Preliminary",0.12,0.85,23);
    drawText("p_{T,1}>190 GeV  p_{T,2}>70 GeV p_{T,3}>70 GeV",0.13,0.82,16);
    drawText("|#Delta#phi_{2,3}|>2#pi/3 |#Delta#eta_{2,3}|>0.2",0.13,0.78,16);
    drawText("0 -30% Centrality",0.13,0.74,16);
    
    
    
    
    //c2->SaveAs("meanpull.png");
    //c2->SaveAs("meanpull.pdf");
    //c2->SaveAs("meanpull.gif");
    
    
    
    
    
    
    
}


