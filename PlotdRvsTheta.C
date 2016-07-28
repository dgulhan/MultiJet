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
    
    int nPoints = 5;
    
    TCut CutsR[] = {
        "sqrt(pow(deltaPhi(phi3,phi2),2.)+pow(eta2-eta3,2.))>0.4 && sqrt(pow(deltaPhi(phi3,phi2),2.)+pow(eta2-eta3,2.))<0.6",
        "sqrt(pow(deltaPhi(phi3,phi2),2.)+pow(eta2-eta3,2.))>0.6 && sqrt(pow(deltaPhi(phi3,phi2),2.)+pow(eta2-eta3,2.))<0.8",
        "sqrt(pow(deltaPhi(phi3,phi2),2.)+pow(eta2-eta3,2.))>0.8 && sqrt(pow(deltaPhi(phi3,phi2),2.)+pow(eta2-eta3,2.))<1.0",
        "sqrt(pow(deltaPhi(phi3,phi2),2.)+pow(eta2-eta3,2.))>1.0 && sqrt(pow(deltaPhi(phi3,phi2),2.)+pow(eta2-eta3,2.))<1.2",
        "sqrt(pow(deltaPhi(phi3,phi2),2.)+pow(eta2-eta3,2.))>1.2 && sqrt(pow(deltaPhi(phi3,phi2),2.)+pow(eta2-eta3,2.))<1.6",
        
    };
    
    TCut CutSeePull[] = {"pt1>140 && pt3>50 && acos(cos(phi1-phi2))>2*TMath::Pi()/3 " };
    TCut centrality = "0 < hiBin/2 && hiBin/2 < 30";
    
    //;&& acos((pull_y3*pull_y2+pull_phi3*pull_phi2)/(sqrt(pow(pull_y3,2.)+pow(pull_phi3,2.))*sqrt(pow(pull_y2,2.)+pow(pull_phi2,2.))))>TMath::Pi()/2"};
    
    double X[]={0.5,0.7,0.9,1.1,1.4};
    double Xerr[]={0.01,0.01,0.01,0.01,0.01};
    
    
    
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
    
    double Y[nFiles][nPoints];
    double Yerr[nFiles][nPoints];
    
    double CountTheta[nFiles][nPoints];
    double ErrCountTheta[nFiles][nPoints];
    
    int Color [] = { kRed , kBlue, kGreen, kMagenta };
    
    TH1D * Hist[nFiles][nPoints];
    
    
    double Ntheta[nFiles][nPoints];
    double Nall[nFiles][nPoints];
    for ( int iFile = 0 ; iFile < nFiles ; iFile ++){
        
        
        cout<<"loading file:"<<Files[iFile].Data()<<endl;
        file[iFile] = TFile::Open( Files[iFile].Data() );
        tree[iFile] = (TTree*)file[iFile]->Get("ak4PF");
        
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
            
            cout<<"Ratio: "<<CountTheta[iFile][iPoint]<<" +- "<<ErrCountTheta[iFile][iPoint]<<endl;
            //Yerr[iFile][iPoint] = Hist[iFile][iPoint]->GetMeanError();
        }
    }
    
    double RatioPoints[2][nPoints];
    double ErrRatioPoints[2][nPoints];
    
    for (int iPoint = 0 ; iPoint<nPoints ; iPoint ++ ){

        RatioPoints[0][iPoint] = CountTheta[0][iPoint]/CountTheta[2][iPoint];
        ErrRatioPoints[0][iPoint] = (ErrCountTheta[0][iPoint]*CountTheta[2][iPoint] + ErrCountTheta[2][iPoint]*CountTheta[0][iPoint])/pow(CountTheta[2][iPoint],2.0);

        RatioPoints[1][iPoint] = CountTheta[1][iPoint]/CountTheta[3][iPoint];
        ErrRatioPoints[1][iPoint] = (ErrCountTheta[1][iPoint]*CountTheta[3][iPoint] + ErrCountTheta[3][iPoint]*CountTheta[1][iPoint])/pow(CountTheta[3][iPoint],2.0);

        cout<<"pythia rat: "<<RatioPoints[0][iPoint]<<"+- "<<ErrRatioPoints[0][iPoint]<<endl;
        cout<<"data rat: "<<RatioPoints[1][iPoint]<<"+- "<<ErrRatioPoints[1][iPoint]<<endl;
    }
    

    
    
    TCanvas *c2 = new TCanvas ("c2","c2",610,600);
    c2->SetLeftMargin(0.2);
    
    
    TLegend *t3=new TLegend(0.55,0.64,0.88,0.77);
    t3->SetFillColor(0);
    t3->SetBorderSize(0);
    t3->SetFillStyle(0);
    t3->SetTextFont(43);
    t3->SetTextSize(16);
    TString LabelGraph[] = {"PbPb PYTHIA+HYDJET", "PbPb Data" , "pp PYTHIA", "pp Data"};
    
    
    for ( int iFile = 0 ; iFile < nFiles ; iFile ++){

        gr[iFile] = new TGraphErrors(nPoints,X,CountTheta[iFile],Xerr,ErrCountTheta[iFile]);
        gr[iFile]->SetFillColor(Color[iFile]);
        gr[iFile]->SetLineColor(Color[iFile]);
        if (iFile==0) {
            gr[iFile]->SetLineColor(kRed-7);
            gr[iFile]->SetLineStyle(9);
            gr[iFile]->GetXaxis()->SetTitle("#Delta R_{2,3} Cut");
            gr[iFile]->SetMinimum(0.3);
            gr[iFile]->SetMaximum(1.0);
            gr[iFile]->GetYaxis()->SetTitle("#theta_{2,3}^{Pull}[0,#pi/2]/ #theta_{2,3}^{Pull}[0,#pi] ");
            
            gr[iFile]->Draw();
        }

        if (iFile==1) {
            gr[iFile]->SetMarkerStyle(21);
            gr[iFile]->SetMarkerSize(1);
            gr[iFile]->SetMarkerColor(kRed);
            gr[iFile]->Draw("P SAME");

        }
        if (iFile==2) {
            gr[iFile]->SetLineColor(kBlue-7);
            gr[iFile]->SetLineStyle(9);
        }
        if (iFile==3) {
            gr[iFile]->SetMarkerStyle(21);
            gr[iFile]->SetMarkerColor(kBlue);
            gr[iFile]->SetMarkerSize(1);
            gr[iFile]->Draw("P SAME");

        }
      
        
        t3->AddEntry(gr[iFile],LabelGraph[iFile],"l");
    }
    t3->AddEntry(c2,"anti-k_{T} R=0.4","");
    t3->Draw("SAME");
    drawText("CMS Preliminary",0.22,0.85,23);
    drawText("p_{T,1}>140 GeV  p_{T,2}>50 GeV p_{T,3}>50 GeV",0.23,0.82,16);
    drawText("|#Delta#phi_{2,3}|>2#pi/3 |#Delta#eta_{2,3}|>0.2",0.23,0.78,16);
    drawText("0 -30% Centrality",0.23,0.74,16);

    /***
    
    TCanvas *c3 = new TCanvas("c3","c2",610,600);
    c3->SetLeftMargin(0.2);
    TGraphErrors * rat[2];

    TLegend *t4=new TLegend(0.55,0.64,0.88,0.77);
    t4->SetFillColor(0);
    t4->SetBorderSize(0);
    t4->SetFillStyle(0);
    t4->SetTextFont(43);
    t4->SetTextSize(16);
    
    
    rat[0] = new TGraphErrors(nPoints,X,RatioPoints[0],Xerr,ErrRatioPoints[0]);
    rat[1] = new TGraphErrors(nPoints,X,RatioPoints[1],Xerr,ErrRatioPoints[1]);
    rat[1]->SetFillColor(kBlue-2);
    rat[1]->SetLineColor(kBlue-2);
    rat[0]->SetFillColor(kOrange+1);
    rat[0]->SetLineColor(kOrange+1);
    
    
    rat[0]->SetMinimum(0.5);
    rat[0]->SetMaximum(1.6);
    rat[0]->Draw("SAME");
    rat[1]->Draw("SAME");
    drawText("CMS Preliminary",0.22,0.85,23);
    drawText("p_{T,1}>140 GeV  p_{T,2}>50 GeV p_{T,3}>50 GeV",0.23,0.82,16);
    drawText("|#Delta#phi_{2,3}|>2#pi/3 |#Delta#eta_{2,3}|>0.2",0.23,0.78,16);
    drawText("0 -30% Centrality",0.23,0.74,16);

    
    t4->AddEntry(rat[0],"PYTHIA + HYDJET / PYTHIA","l");
    t4->AddEntry(rat[1],"PbPb Data / pp Data","l");
    
    t4->Draw("SAME");
    
    
    ***/
    
    
    
    
    
    
    
    
    //c2->SaveAs("meanpull.png");
    //c2->SaveAs("meanpull.pdf");
    //c2->SaveAs("meanpull.gif");
    
    
    
    
    
    
    
}



