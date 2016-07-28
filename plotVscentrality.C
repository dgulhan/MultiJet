#include "utilities.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TStyle.h"
#include "TColor.h"
#define sign(a) ( ( (a) < 0 )  ?  -1   : ( (a) > 0 ) )


void plotVscentrality(){
    
    Int_t R[] = {4};
    Int_t N[] = {3};
    int nR=1;
    int nN=1; //XCone
    int nAlgo=2;//XCone and antiKt
    
    int nBinsCentr = 4;
    TString CentralityBinsCuts[] = { "0 < hiBin/2 && hiBin/2 < 10 && pt3>0 ","10 < hiBin/2 && hiBin/2 < 30 && pt3>0","30 < hiBin/2 && hiBin/2 < 50 && pt3>0 " ,"50 < hiBin/2 && hiBin/2 < 100 && pt3>0" };
    
    int Color [] = { kRed , kBlue, kGreen, kMagenta };
    
    
    // the value 4 in this vectors goes for 2 datasets of Data and 2 of MC (pp,PbPb)
    Double_t X[nBinsCentr];
    Double_t Xerr[nBinsCentr];
    
    Double_t Y[nBinsCentr];
    Double_t Yerr[nBinsCentr];

    
    // Four files ppMC PbPbData ppData PbPbMC
    
    TString Files[] = {
        "root://eoscms//eos/cms/store/group/cmst3/user/dgulhan/MultiJetSkims/20160720/PbPbMCpthat80+pullHiForestAOD_ALL.root",
        "/afs/cern.ch/work/e/eruizvel/public/PbPbDataHIHardProbes+pullHiForest_ALL.root",
        "root://eoscms//eos/cms/store/group/cmst3/user/dgulhan/MultiJetSkims/20160720/ppMCpthat80+pullHiForestAOD_ALL.root",
        "root://eoscms//eos/cms/store/group/cmst3/user/dgulhan/MultiJetSkims/20160726/ppDataHighPt80+pullHiForest_ALL.root"
    };
    

   
    
    
    int nFiles = 4;
    
    TFile *file[nFiles];
    
    
    TGraphErrors * gr [nFiles];
    
    TCanvas *c1[nFiles];
   
    Double_t Xpp[] = {5.0,20.0,40,75} ;
    Double_t Xpperr[] = {0,0.0,0,0} ;
    for ( int iFile = 0 ; iFile < nFiles ; iFile ++){
        
        //c1[iFile] = new TCanvas(Form("c1%i",iFile),"",600,600);
        
        cout<<"loading file:"<<Files[iFile].Data()<<endl;
        file[iFile] = TFile::Open( Files[iFile].Data() );
        TH1D * histHiBin[nBinsCentr];
        TH1D * histNjet[nBinsCentr];
        TTree* tree[1];
        tree[0] = (TTree*)file[iFile]->Get(Form("xc_R%i_N%i_PF",R[0],N[0]));
        //tree[0] = (TTree*)file[iFile]->Get(Form("ak%iPF",R[0],N[0]));

      
        
        for (int iCentr = 0 ; iCentr < nBinsCentr ; iCentr++) {
            
            
            histHiBin[iCentr] = new TH1D(Form("histHiBin%i",iCentr),"",100,0,200);
            histNjet[iCentr] = new TH1D(Form("histNjet%i",iCentr),"",100,0,200);
            
            tree[0]->Draw(Form("hiBin>>histHiBin%i",iCentr),CentralityBinsCuts[iCentr].Data());
            tree[0]->Draw(Form("sqrt((pt1*cos(phi1)+pt2*cos(phi2)+pt3*cos(phi3))^2 + (pt1*sin(phi1)+pt2*sin(phi2)+pt3*sin(phi3))^2)/(pt1+pt2+pt3)>>histNjet%i",iCentr),CentralityBinsCuts[iCentr].Data());
            
            
            X[iCentr] = histHiBin[iCentr]->GetMean(1)/2.0;
            cout<<"mean x: "<<X[iCentr]<<endl;
            Xerr[iCentr] = histHiBin[iCentr]->GetMeanError()/2.0;
            Y[iCentr] = histNjet[iCentr]->GetMean();
            cout<<"mean y: "<<Y[iCentr]<<endl;
            Yerr[iCentr] = histNjet[iCentr]->GetMeanError();
            
        }
        if (X[0] == 0.0 ) { gr[iFile] = new TGraphErrors(nBinsCentr,Xpp,Y,Xpperr,Yerr);}
        if (X[0] > 0.0 ) { gr[iFile] = new TGraphErrors(nBinsCentr,X,Y,Xerr,Yerr); }

        //gr[iFile]->Draw();
        gr[iFile]->SetLineColor(Color[iFile]);
        
    }
    
    TCanvas *c2 = new TCanvas ("c2","",600,600);
    gr[1]->SetMinimum(-2);
    gr[1]->SetMaximum(50);
    gr[1]->GetXaxis()->SetLimits(0,80);
    gr[1]->GetXaxis()->SetTitle("% Centrality ");
    gr[1]->GetYaxis()->SetTitle("#LT N_{jet} #GT");

    gr[1]->Draw();
    gr[0]->Draw("SAME");
    gr[2]->Draw("SAME"); //pp data
    gr[3]->Draw("SAME"); //pp MC
    
    TLegend *t3=new TLegend(0.60,0.75,0.90,0.85);
    t3->SetFillColor(0);
    t3->SetBorderSize(0);
    t3->SetFillStyle(0);
    t3->SetTextFont(43);
    t3->SetTextSize(20);
    t3->AddEntry(gr[1],"PbPb Data","l");
    gr[1]->SetLineStyle(9);
    t3->AddEntry(gr[0],"PbPb MC","l");
    t3->AddEntry(gr[2],"pp Data","l");
    gr[2]->SetLineStyle(9);
    t3->AddEntry(gr[3],"pp MC","l");
    t3->Draw("SAME");
    
    
    c2->SaveAs("centrality.png");
    c2->SaveAs("centrality.pdf");
    c2->SaveAs("centrality.gif");
    
    
    

    

    
}