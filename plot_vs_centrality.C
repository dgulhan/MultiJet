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
    TCut Cut[] = {"pt1>100 && pt3>30 && acos(cos(phi1-phi2))>2*TMath::Pi()/3 && abs(eta1-eta2)>0.2"};
    
    int Color [] = { kRed , kBlue, kGreen, kMagenta };
    
    int nFiles = 4;
    TFile *file[nFiles];
    TString Files[] = {
        "root://eoscms//eos/cms/store/group/cmst3/user/dgulhan/MultiJetSkims/20160712/PbPbPy8hat80HiForestAOD_ALL.root",
        "root://eoscms//eos/cms/store/group/cmst3/user/dgulhan/MultiJetSkims/20160712/MJSkim_PbPb_data.root",
        "root://eoscms//eos/cms/store/group/cmst3/user/dgulhan/MultiJetSkims/20160716/ppPy8hat80HiForestAOD_ALL.root" ,
        "root://eoscms//eos/cms/store/group/cmst3/user/dgulhan/MultiJetSkims/20160716/ppDatahat80HiForest_ALL.root"};

    
    TGraphErrors * gr [nFiles];
    
    Double_t X[] = {5.0 , 20. , 30.0 , 75.0 };
    Double_t Xerr[] = { 0.1 , 0.1 , 0.1 , 0.1 };
    
    Double_t Y[nFiles][nBinsCentr];
    Double_t Yerr[nFiles][nBinsCentr];

    TH1D * HistTotBal[nFiles][nBinsCentr];
    TTree * tree[nFiles];
    
    
    
    for ( int iFile = 0 ; iFile < nFiles ; iFile ++){
        
        
        cout<<"loading file:"<<Files[iFile].Data()<<endl;
        file[iFile] = TFile::Open( Files[iFile].Data() );
        tree[iFile] = (TTree*)file[iFile]->Get(Form("xc_R%i_N%i_PF",R[0],N[0]));
        
        for (int iCentr = 0 ; iCentr < nBinsCentr ; iCentr++) {
            cout<<"def hist"<<endl;
            HistTotBal[iFile][iCentr] = new TH1D(Form("TotBal%i%i",iFile,iCentr),"",100,0,200);
            cout<<"hist defined"<<endl;
            if (iFile == 0 || iFile ==1 ) {
                tree[iFile]->Draw(Form("(sqrt((pt1*cos(phi1)+pt2*cos(phi2)+pt3*cos(phi3))^2 + (pt1*sin(phi1)+pt2*sin(phi2)+pt3*sin(phi3))^2)/(pt1+pt2+pt3))>>TotBal%i%i",iFile,iCentr),CentralityBinsCuts[iCentr] && Cut[0]);

            }
            if (iFile == 2 || iFile == 3) {
                cout<<"accessing file: "<<iFile<<endl;
                tree[iFile]->Draw(Form("(sqrt((pt1*cos(phi1)+pt2*cos(phi2)+pt3*cos(phi3))^2 + (pt1*sin(phi1)+pt2*sin(phi2)+pt3*sin(phi3))^2)/(pt1+pt2+pt3))>>TotBal%i%i",iFile,iCentr),Cut[0]);
                cout<<"histo drawn"<<endl;
            }
            
            Y[iFile][iCentr] = HistTotBal[iFile][iCentr]->GetMean();
            cout<<"mean stored "<< Y[iFile][iCentr] << endl;
            Yerr[iFile][iCentr] = HistTotBal[iFile][iCentr]->GetMeanError();
            cout<<"meanerror"<<endl;
            
        }
        
            }
    
    
    TCanvas *c = new TCanvas ("c","",600,600);
    
    TLegend *t3=new TLegend(0.48,0.73,0.83,0.89);
    t3->SetFillColor(0);
    t3->SetBorderSize(0);
    t3->SetFillStyle(0);
    t3->SetTextFont(43);
    t3->SetTextSize(18);
    TString LabelGraph[] = {"PbPb PYTHIA+HYDJET", "PbPb Data" , "pp PYTHIA", "pp Data"};
    
    for (int iFile = 0; iFile<nFiles; iFile++) {
        gr[iFile] = new TGraphErrors(nBinsCentr,X,Y[iFile],Xerr,Yerr[iFile]);
        gr[iFile]->SetLineColor(Color[iFile]);
        gr[iFile]->GetXaxis()->SetLimits(0,100);
        gr[iFile]->GetXaxis()->SetTitle("% Centrality ");
        gr[iFile]->GetYaxis()->SetTitle("#LT P_{T} Balance #GT");
        gr[iFile]->SetLineStyle(9);
        
        if (iFile == 0) {
            gr[iFile]->SetMinimum(0.11);
            gr[iFile]->SetMaximum(0.30);
            gr[iFile]->GetYaxis()->SetTitleOffset(1.4);
            gr[iFile]->Draw();
        } else {
            gr[iFile]->GetYaxis()->SetTitleOffset(1.4);
            gr[iFile]->Draw("SAME");
        }
        
        t3->AddEntry(gr[iFile],LabelGraph[iFile],"l");

    }
    

    t3->Draw("SAME");
    drawText("CMS Preliminary",0.12,0.85,23);
    drawText("p_{T,1}>100 GeV  p_{T,2}>30 GeV p_{T,3}>30 GeV",0.13,0.82,16);
    drawText("|#Delta#phi_{2,3}|>2#pi/3 |#Delta#eta_{2,3}|>0.2",0.13,0.79,16);


    
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

