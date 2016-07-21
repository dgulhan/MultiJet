#include "utilities.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TStyle.h"
#include "TColor.h"
#define sign(a) ( ( (a) < 0 )  ?  -1   : ( (a) > 0 ) )


void plot_vs_centrality(){
    
    Int_t R[] = {4};
    Int_t N[] = {3};
    int nR=1;
    int nN=1; //XCone

    
    int nBinsCentr = 4;
    
    TCut CentralityBinsCuts[] = { "0 < hiBin/2 && hiBin/2 < 10","10 < hiBin/2 && hiBin/2 < 30 ","30 < hiBin/2 && hiBin/2 < 50" ,"50 < hiBin/2 && hiBin/2 < 100" };
    TCut Cut[] = {};
    
    int Color [] = { kRed , kBlue, kGreen, kYellow };
    
    int nFiles = 4;
    TFile *file[nFiles];
    TString Files[] = {
        "root://eoscms//eos/cms/store/group/cmst3/user/dgulhan/MultiJetSkims/20160712/PbPbPy8hat80HiForestAOD_ALL.root",
        "root://eoscms//eos/cms/store/group/cmst3/user/dgulhan/MultiJetSkims/20160712/MJSkim_PbPb_data.root",
        "root://eoscms//eos/cms/store/group/cmst3/user/dgulhan/MultiJetSkims/20160716/ppPy8hat80HiForestAOD_ALL.root" ,
        "root://eoscms//eos/cms/store/group/cmst3/user/dgulhan/MultiJetSkims/20160716/ppDatahat80HiForest_ALL.root"};

    
    TGraphErrors * gr [nFiles];
    
    Double_t X[] = {5.0 , 20. , 30.0 , 75.0 };
    Double_t Xerr = { 0.1 , 0.1 , 0.1 , 0.1 };
    
    Double_t Y[nFiles][nBinsCentr];
    Double_t Yerr[nFiles][nBinsCentr];

    TH1D * HistTotBal[nFiles][nBinsCentr];
    TTree * tree[nFiles];
    
    
    TCanvas *c = new TCanvas ("c","",600,600);
    makeMultiPanelCanvas(c,1,1,-0.12,0.0,0.15,0.16,0.02);
    
    TLegend *t3=new TLegend(0.60,0.75,0.90,0.85);
    t3->SetFillColor(0);
    t3->SetBorderSize(0);
    t3->SetFillStyle(0);
    t3->SetTextFont(43);
    t3->SetTextSize(20);
    TString LabelGraph[] = {"PbPb PYTHIA+HYDJET", "PbPb Data" , "pp PYTHIA", "pp Data"};
    
    c->cd(1);

    for ( int iFile = 0 ; iFile < nFiles ; iFile ++){
        
        
        cout<<"loading file:"<<Files[iFile].Data()<<endl;
        file[iFile] = TFile::Open( Files[iFile].Data() );
        tree[iFile] = (TTree*)file[iFile]->Get(Form("xc_R%i_N%i_PF",R[0],N[0]));
        
        for (int iCentr = 0 ; iCentr < nBinsCentr ; iCentr++) {

            HistTotBal[iFile][iCentr] = new TH1D(Form("TotBal%i%i",iFile,iCentr),"",100,0,200);
            if (iFile == 0 || iFile ==1 ) {
                tree[iFile]->Draw(Form("(sqrt((pt1*cos(phi1)+pt2*cos(phi2)+pt3*cos(phi3))^2 + (pt1*sin(phi1)+pt2*sin(phi2)+pt3*sin(phi3))^2)/(pt1+pt2+pt3))>>TotBal%i%i",iFile,iCentr),CentralityBinsCuts[iCentr] && Cut[0]);

            }
            if (iFile == 2 || iFile == 3) {
                tree[iFile]->Draw(Form("(sqrt((pt1*cos(phi1)+pt2*cos(phi2)+pt3*cos(phi3))^2 + (pt1*sin(phi1)+pt2*sin(phi2)+pt3*sin(phi3))^2)/(pt1+pt2+pt3))>>TotBal%i%i",iFile,iCentr),Cut[0]);
            }
        
            Y[iFile][iCentr] = HistTotBal->GetMean();
            Yerr[iFile][iCentr] = HistTotBal->GetMeanError();
            
        }
        
        gr[iFile] = new TGraphErrors(nBinsCentr,X,Y[iFile],Xerr,Yerr[iFile]);
        gr[iFile]->SetLineColor(Color[iFile]);
        gr[iFile]->GetXaxis()->SetLimits(0,100);
        gr[iFile]->GetXaxis()->SetTitle("% Centrality ");
        gr[iFile]->GetYaxis()->SetTitle("#LT P_{T} Balance #GT");
        gr[iFile]->SetLineStyle(9);
        
        t3->AddEntry(gr[iFile],LabelGraph[iFile],"l");
        gr[iFile]->Draw("SAME");
        
    }
    t3->Draw("SAME");
    /***
    c2->SaveAs("centrality.png");
    c2->SaveAs("centrality.pdf");
    c2->SaveAs("centrality.gif");
     ***/
}

    
 /***
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
    gr[1]->SetMinimum(-0.05);
    gr[1]->SetMaximum(1);
    gr[1]->GetXaxis()->SetLimits(0,80);
    gr[1]->GetXaxis()->SetTitle("% Centrality ");
    gr[1]->GetYaxis()->SetTitle("#LT P_{T} Balance #GT");

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
  
}

***/

