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
    TH1D::SetDefaultSumw2();

    TString Files[] = { "root://eoscms//eos/cms/store/group/cmst3/user/dgulhan/MultiJetSkims/20160720/PbPbMCpthat80+pullHiForestAOD_ALL.root",
                        "/afs/cern.ch/work/e/eruizvel/public/PbPbDataHIHardProbes+pullHiForest_ALL.root",
                        "root://eoscms//eos/cms/store/group/cmst3/user/dgulhan/MultiJetSkims/20160720/ppMCpthat80+pullHiForestAOD_ALL.root",
                        "root://eoscms//eos/cms/store/group/cmst3/user/dgulhan/MultiJetSkims/20160726/ppDataHighPt80+pullHiForest_ALL.root"
    };
    
    int nFiles=4;
    
    
    TFile *file[nFiles];
    TTree *tree[nFiles][2];
    
    TCut Cut[] = {
        "pt1>140 && pt3>50 && acos(cos(phi1-phi2))>2*TMath::Pi()/3 && abs(eta1-eta2)>0.2 && sqrt(pow(deltaPhi(phi3,phi2),2.)+pow(eta2-eta3,2.))>0.8 && sqrt(pow(deltaPhi(phi3,phi2),2.)+pow(eta2-eta3,2.))<(TMath::Pi()/2)",
                  "pt1>140 && pt3>50 && acos(cos(phi1-phi2))>2*TMath::Pi()/3 && abs(eta1-eta2)>0.2 && sqrt(pow(deltaPhi(phi3,phi2),2.)+pow(eta2-eta3,2.))>0.8 && sqrt(pow(deltaPhi(phi3,phi2),2.)+pow(eta2-eta3,2.))<(TMath::Pi()/2)",
                  "pt1>140 && pt3>50 && acos(cos(phi1-phi2))>2*TMath::Pi()/3 && abs(eta1-eta2)>0.2 && sqrt(pow(deltaPhi(phi3,phi2),2.)+pow(eta2-eta3,2.))>0.8 && sqrt(pow(deltaPhi(phi3,phi2),2.)+pow(eta2-eta3,2.))<(TMath::Pi()/2)",
                  "pt1>140 && pt3>50 && acos(cos(phi1-phi2))>2*TMath::Pi()/3 && abs(eta1-eta2)>0.2 && sqrt(pow(deltaPhi(phi3,phi2),2.)+pow(eta2-eta3,2.))>0.8 && sqrt(pow(deltaPhi(phi3,phi2),2.)+pow(eta2-eta3,2.))<(TMath::Pi()/2)"
    };
    
    TCut CentralityBinsCuts[] = { " 0 < hiBin/2 && hiBin/2 < 30"  };
    TString CentrText[] = { "Centr. 30-0%" };
    
    
    TH1D *hist[nFiles][2];
    
    
    int Color[] = {kRed,kRed,kBlue,kBlue};
    
    
    
    for (int iFile = 0; iFile < nFiles ; iFile++ ) {
        file[iFile] = TFile::Open( Files[iFile].Data() );
        for (int iAlgo=0; iAlgo<2 ; iAlgo++)
        {
            if (iAlgo==0) tree[iFile][iAlgo] = (TTree*)file[iFile]->Get("xc_R4_N3_PF");
            if (iAlgo==1) tree[iFile][iAlgo] = (TTree*)file[iFile]->Get("ak4PF");

        
        
            tree[iFile][iAlgo]->SetAlias( "theta23" , "acos((pullEta2*(eta3-eta2)+pullPhi2*deltaPhi(phi3,phi2))/( magnitude(pullEta2,pullPhi2)*magnitude(eta3-eta2,deltaPhi(phi3,phi2)) ))");
            
            tree[iFile][iAlgo]->SetAlias( "theta32" , "acos((pullEta3*(eta2-eta3)+pullPhi3*deltaPhi(phi2,phi3))/( magnitude(pullEta3,pullPhi3)*magnitude(eta2-eta3,deltaPhi(phi2,phi3)) ))");
            
            //tree[iFile][iAlgo]->SetAlias("t2","magnitude(pullEta2,pullPhi2)");
            //tree[iFile][iAlgo]->SetAlias("t3","magnitude(pullEta3,pullPhi3)");


            hist[iFile][iAlgo] =  new TH1D(Form("hist%i%i",iFile,iAlgo),";|#vec{t}_{3}|#theta_{3,2}^{pull};Event Fraction",20,0,0.04001);
        
            if (iFile == 0 || iFile ==1 )tree[iFile][iAlgo]->Draw(Form("magnitude(pullEta3,pullPhi3)*theta32>>hist%i%i",iFile,iAlgo),Cut[iFile] && CentralityBinsCuts[0] && "theta32<TMath::Pi()/2");
            if (iFile == 2 || iFile ==3 )tree[iFile][iAlgo]->Draw(Form("magnitude(pullEta3,pullPhi3)*theta32>>hist%i%i",iFile,iAlgo),Cut[iFile] && "theta32<TMath::Pi()/2" );

            hist[iFile][iAlgo]->Scale(1.0/hist[iFile][iAlgo]->Integral());
       
            hist[iFile][iAlgo]->SetStats(0);
            makePretty(hist[iFile][iAlgo]);
        }
    }
   
    cout<<"out of here 0"<<endl;
    
    TCanvas *c5;
    
    c5 = new TCanvas("c5","",2*451,450);
    makeMultiPanelCanvas(c5,2,1,0.0,0.0,0.17,0.17,0.02);
    
    TLegend *t3=new TLegend(0.47,0.80,0.61,0.90);
    t3->SetFillColor(0);
    t3->SetBorderSize(0);
    t3->SetFillStyle(0);
    t3->SetTextFont(43);
    t3->SetTextSize(15);
    t3->SetTextAlign(13);
    
    TString Label[] = { "PbPb PYTHIA+HYDJET" , "PbPb Data",  "pp PYTHIA" ,"pp Data" };
    TString LabelMode[] = { "f" , "p" , "f", "p"};
    
    cout<<"out of here 1"<<endl;

    for (int iFile = 0 ; iFile<nFiles; iFile++) {
        
        for (int iAlgo=0; iAlgo<2; iAlgo++) {
    
       
            cout<<"out of here 2"<<endl;

            c5->cd(iAlgo+1);
            hist[iFile][iAlgo]->SetMaximum(1.0);
        
            if (iFile == 0 || iFile == 2) {
                if (iFile == 0) hist[iFile][iAlgo]->SetFillStyle(3005);
                if (iFile == 2) hist[iFile][iAlgo]->SetFillStyle(3004);
                hist[iFile][iAlgo]->SetLineColor(Color[iFile]);
                hist[iFile][iAlgo]->SetFillColorAlpha(Color[iFile],0.35);
                //hist[iFile][iAlgo]->Draw("SAME HIST");
                cout<<"out of here 3"<<endl;

            }
            if (iFile == 1 || iFile == 3) {
                hist[iFile][iAlgo]->SetMarkerStyle(20);
                hist[iFile][iAlgo]->SetMarkerSize(1.5);
                hist[iFile][iAlgo]->SetMarkerColor(Color[iFile]);
                hist[iFile][iAlgo]->SetLineColor(Color[iFile]);
                if (iFile==1) hist[iFile][iAlgo]->Draw();
                if (iFile==3) hist[iFile][iAlgo]->Draw("SAME");
                cout<<"out of here 4"<<endl;

            }
            cout<<"out of here 5"<<endl;

            
            if (iAlgo==0) {
                drawText("XCone",0.19,0.93,19);
                drawText("p_{T,1}>140 GeV  p_{T,2}>50 GeV p_{T,3}>50 GeV",0.18,0.87,18);
                drawText("#Delta#phi_{1,2}> 2#pi/3 |#Delta#eta_{1,2}|>0.2 #Delta R_{2,3}<#pi/2 #Delta R_{2,3}>0.8",0.18,0.82,18);
                drawText("#theta_{3,2}^{pull}<#pi/2",0.18,0.77,18);
            }
            if (iAlgo==1) drawText("anti-k_{T}",0.03,0.93,19);


        }
        if (iFile == 1 || iFile == 3) t3->AddEntry(hist[iFile][1],Label[iFile].Data(),LabelMode[iFile].Data());
        cout<<"out of here 6"<<endl;
    }
    cout<<"out of here 7"<<endl;

    
    t3->Draw("SAME");
    cout<<"out of here 8"<<endl;

}