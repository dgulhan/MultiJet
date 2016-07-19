#include "utilities.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TStyle.h"
#include "TMath.h"
#include "TColor.h"
#include <stdio.h>
#define sign(a) ( ( (a) < 0 )  ?  -1   : ( (a) > 0 ) )



void plotComparisonXCaKT(){
    TH1D::SetDefaultSumw2();
    
    
    int R = 4;
    int N = 3;
    int nFiles = 2;
    int nAlgo = 2;
    int nCentrBins = 1;


    //int iVar;
    //cout<<"Var number: ";
    //cin >> iVar;
    
    //acos(cos(phi1-phi2))> 2*TMath::Pi()/2
    
    TString XAxis[] = {"acos(cos(phi1-phi3))","acos(cos(phi1-phi2))","acos(cos(phi2-phi3))","sign(eta1)*(eta3-eta1)","sign(eta1)*(eta2-eta1)","sign(eta2)*(eta3-eta2)","sqrt(pow(acos(cos(phi1-phi3)),2.)+pow(eta1-eta3,2.))","sqrt(pow(acos(cos(phi1-phi2)),2.)+pow(eta1-eta2,2.))","sqrt(pow(acos(cos(phi2-phi3)),2.)+pow(eta2-eta3,2.))" };
    
    TString XLabel[] = {"#Delta#phi_{1,3}" , "#Delta#phi_{1,2}" , "#Delta#phi_{2,3}" , "#Delta#eta_{1,3}" , "#Delta#eta_{1,2}" , "#Delta#eta_{2,3}" , "#Delta R_{1,3}" , "#Delta R_{1,2}" , "#Delta R_{2,3}" };
    
    TString Files[] = { "root://eoscms//eos/cms/store/group/cmst3/user/dgulhan/MultiJetSkims/20160712/PbPbPy8hat80HiForestAOD_ALL.root", "root://eoscms//eos/cms/store/group/cmst3/user/dgulhan/MultiJetSkims/20160712/MJSkim_PbPb_data.root", "ALL/ppPy8hat80HiForestAOD_ALL.root","ALL/ppDatahat80HiForest_ALL.root"};
    
    
    
    TCut PPCuts[] = { " pt1>100 && pt3>50 && acos(cos(phi1-phi2))>2*TMath::Pi()/3" ,
                      " pt1>100 && pt3>50 " ,
                      " pt1>100 && pt3>50 && acos(cos(phi1-phi2))>2*TMath::Pi()/3 " ,
                      " pt1>100 && pt3>50 && acos(cos(phi1-phi2))>2*TMath::Pi()/3" ,
                      " pt1>100 && pt3>50 && acos(cos(phi1-phi2))>2*TMath::Pi()/3 " ,
                      " pt1>100 && pt3>50 && acos(cos(phi1-phi2))>2*TMath::Pi()/3 " ,
                      " pt1>100 && pt3>50 && acos(cos(phi1-phi2))>2*TMath::Pi()/3 " ,
                      " pt1>100 && pt3>50 && acos(cos(phi1-phi2))>2*TMath::Pi()/3" ,
                      " pt1>100 && pt3>50 && acos(cos(phi1-phi2))>2*TMath::Pi()/3",
                       };
    
    //TCut PbPbCuts[] = { " pt1>100 && pt3>30 && acos(cos(phi1-phi2))>2*TMath::Pi()/3" , " pt1>100 && pt3>30 " , " pt1>100 && pt3>30 && acos(cos(phi1-phi2))>2*TMath::Pi()/3 " , " pt1>100 && pt3>30 && acos(cos(phi1-phi2))>2*TMath::Pi()/3" , " pt1>100 && pt3>30 " , " pt1>100 && pt3>30 && acos(cos(phi1-phi2))>2*TMath::Pi()/3 " , " pt1>100 && pt3>30 " , " pt1>100 && pt3>30 && acos(cos(phi1-phi2))>2*TMath::Pi()/3" , " pt1>100 && pt3>30 && acos(cos(phi1-phi2))>2*TMath::Pi()/3", " pt1>100 && pt3>30" };
    
    TCut PbPbCuts[] = { " pt1>100 && pt3>50 && acos(cos(phi1-phi2))>2*TMath::Pi()/3 && abs(eta1-eta2)>0.2" ,
                        " pt1>100 && pt3>50 && abs(eta1-eta2)>0.2" ,
                        " pt1>100 && pt3>50 && acos(cos(phi1-phi2))>2*TMath::Pi()/3 && abs(eta1-eta2)>0.2" ,
                        " pt1>100 && pt3>50 && acos(cos(phi1-phi2))>2*TMath::Pi()/3 && abs(eta1-eta2)>0.2" ,
                        " pt1>100 && pt3>50 && acos(cos(phi1-phi2))>2*TMath::Pi()/3 && abs(eta1-eta2)>0.2" ,
                        " pt1>100 && pt3>50 && acos(cos(phi1-phi2))>2*TMath::Pi()/3 && abs(eta1-eta2)>0.2" ,
                        " pt1>100 && pt3>50 && acos(cos(phi1-phi2))>2*TMath::Pi()/3 && abs(eta1-eta2)>0.2" ,
                        " pt1>100 && pt3>50 && acos(cos(phi1-phi2))>2*TMath::Pi()/3 && abs(eta1-eta2)>0.2" ,
                        " pt1>100 && pt3>50 && acos(cos(phi1-phi2))>2*TMath::Pi()/3 && abs(eta1-eta2)>0.2",
                         };
    
    

    
    TString TextCut[] = {"#Delta#phi_{1,2}> 2#pi/3 |#Delta#eta_{1,2}|>0.2" ,
                         "|#Delta#eta_{1,2}|>0.2" ,
                         "#Delta#phi_{1,2}> 2#pi/3 |#Delta#eta_{1,2}|>0.2" ,
                         "#Delta#phi_{1,2}> 2#pi/3 |#Delta#eta_{1,2}|>0.2" ,
                         "#Delta#phi_{1,2}> 2#pi/3 |#Delta#eta_{1,2}|>0.2" ,
                         "#Delta#phi_{1,2}> 2#pi/3 |#Delta#eta_{1,2}|>0.2",
                         "#Delta#phi_{1,2}> 2#pi/3 |#Delta#eta_{1,2}|>0.2" ,
                         "#Delta#phi_{1,2}> 2#pi/3 |#Delta#eta_{1,2}|>0.2" ,
                         "#Delta#phi_{1,2}> 2#pi/3 |#Delta#eta_{1,2}|>0.2"
                        };
    
    Double_t YMaxHist[] = {0.08,0.22,0.11,0.081,0.08,0.11,0.11,0.12,0.10,0.15};
    Double_t XMin[] = {0,0,0,-2.,-2.,-2.,0.,0.,0.,-110};
    Double_t XMax[] = {TMath::Pi(),TMath::Pi(),TMath::Pi(),2.,2.,2.,4.,4.,4.,300};
    
    
    
    
    /***
    for ( int iFile = 0 ; iFile < nFiles ; iFile++ ){
        for (int iAlgo = 0 ;  iAlgo<nAlgo ; iAlgo++){
            
            file[iFile] = TFile::Open(Files[iFile].Data());
            
            if (iAlgo == 0){
                tree[iFile][iAlgo]=(TTree*)file[iFile]->Get("ak4PF");
            }
            if (iAlgo == 1){
                tree[iFile][iAlgo]=(TTree*)file[iFile]->Get(Form("xc_R%i_N%i_PF",R,N));
            }
            
            if (iFile == 0){
                hist[iFile][iAlgo]=new TH1D(Form("hist_F%iV%iA%i",iFile,iVar,iAlgo),Form(";%s;Event fraction",XLabel[iVar].Data()),50,XMin[iVar],XMax[iVar]);
                cout<<Form("%s>>hist_F%iV%iA%i",XAxis[iVar].Data(),iFile,iVar,iAlgo)<<endl;
                tree[iFile][iAlgo]->Draw(Form("%s>>hist_F%iV%iA%i",XAxis[iVar].Data(),iFile,iVar,iAlgo));
            }
            
            
        }

    }
    
    
    ***/
    for ( int iVar = 0; iVar<9 ; iVar++){
        TFile *file[nFiles];
        TH1D *hist[nFiles][nAlgo];
        TTree *tree[nFiles][nAlgo];
    
    for ( int iFile = 0 ; iFile < nFiles ; iFile++ ){
        cout<<iFile<<endl;
        
        file[iFile] = TFile::Open(Files[iFile].Data());
        
        //if (iFile == 3 ){tree[iFile] = (TTree*)file[iFile]->Get("xc4PF");}
        //if (iFile  < 3 ){tree[iFile] = (TTree*)file[iFile]->Get(Form("xc_R%i_N%i_PF",R,N));}
        
        tree[iFile][0] = (TTree*)file[iFile]->Get("ak4PF");
        tree[iFile][1] = (TTree*)file[iFile]->Get(Form("xc_R%i_N%i_PF",R,N));
        
    
            
        if (iFile==0){
            //akt
            hist[iFile][0]= new TH1D(Form("hist_F%iV%iA%i",iFile,iVar,0),Form(";%s;Event fraction",XLabel[iVar].Data()),50,XMin[iVar],XMax[iVar]);
            

            tree[iFile][0]->Draw(Form("%s>>hist_F%iV%iA%i",XAxis[iVar].Data(),iFile,iVar,0),PbPbCuts[iVar]);
            

            hist[iFile][0]->Scale(1./hist[iFile][0]->Integral());
            hist[iFile][0]->SetStats(0);
            //xcone
            hist[iFile][1]  = new TH1D(Form("hist_F%iV%iA%i",iFile,iVar,1),Form(";%s;Event fraction",XLabel[iVar].Data()),50,XMin[iVar],XMax[iVar]);
            tree[iFile][1]->Draw(Form("%s>>hist_F%iV%iA%i",XAxis[iVar].Data(),iFile,iVar,1),PbPbCuts[iVar]);
            hist[iFile][1]->Scale(1./hist[iFile][1]->Integral());
            hist[iFile][1]->SetStats(0);
            
        }
            
        if (iFile==1){
           
            //akt = 0
            hist[iFile][0]  = new TH1D(Form("hist_F%iV%iA%i",iFile,iVar,0),Form(";%s;Event fraction",XLabel[iVar].Data()),50,XMin[iVar],XMax[iVar]);
            tree[iFile][0]->Draw(Form("%s>>hist_F%iV%iA%i",XAxis[iVar].Data(),iFile,iVar,0),PbPbCuts[iVar]);
            hist[iFile][0]->Scale(1./hist[iFile][0]->Integral());
            hist[iFile][0]->SetStats(0);
                
            //XCone = 1
            hist[iFile][1]  = new TH1D(Form("hist_F%iV%iA%i",iFile,iVar,1),Form(";%s;Event fraction",XLabel[iVar].Data()),50,XMin[iVar],XMax[iVar]);
            tree[iFile][1]->Draw(Form("%s>>hist_F%iV%iA%i",XAxis[iVar].Data(),iFile,iVar,1),PbPbCuts[iVar]);
            hist[iFile][1]->Scale(1./hist[iFile][1]->Integral());
            hist[iFile][1]->SetStats(0);
                
                
        }
            
        
        if (iFile == 2 || iFile==3) {
            cout<<4<<endl;
            //For pp centrality is not computed !!
        
            //ak = 0
            hist[iFile][0] = new TH1D(Form("hist_F%iV%iA%i",iFile,iVar,0),Form(";%s;Event fraction",XLabel[iVar].Data()),50,XMin[iVar],XMax[iVar]);
            tree[iFile][0]->Draw(Form("%s>>hist_F%iV%iA%i",XAxis[iVar].Data(),iFile,iVar,0),PPCuts[iVar]);
            hist[iFile][0]->Scale(1./hist[iFile][0]->Integral());
            hist[iFile][0]->SetStats(0);
                
            //xcone = 1
            hist[iFile][1] = new TH1D(Form("hist_F%iV%iA%i",iFile,iVar,1),Form(";%s;Event fraction",XLabel[iVar].Data()),50,XMin[iVar],XMax[iVar]);
            tree[iFile][1]->Draw(Form("%s>>hist_F%iV%iA%i",XAxis[iVar].Data(),iFile,iVar,1),PPCuts[iVar]);
            hist[iFile][1]->Scale(1./hist[iFile][1]->Integral());
            hist[iFile][1]->SetStats(0);
                
            
                
        }
    }
    
    int ColorAK[] = {kGreen+1,kGreen};
    int ColorXC[] = {kMagenta,kBlue};

    TCanvas * c2 = new TCanvas("c2","c2",550,450);
    makeMultiPanelCanvas(c2,1,1,-0.12,0.0,0.15,0.16,0.02);

    c2->cd(1);
    TLegend *t3=new TLegend(0.17,0.77,0.27,0.92);
    t3->SetFillColor(0);
    t3->SetBorderSize(0);
    t3->SetFillStyle(0);
    t3->SetTextFont(43);
    t3->SetTextSize(15);
    t3->SetTextAlign(13);

    for ( int iFile = 0 ; iFile < nFiles ; iFile++ ){
        if (iFile==0){
            
            //akt
            makePretty(hist[iFile][0] );
            hist[iFile][0]->SetMaximum(YMaxHist[iVar]);
            hist[iFile][0]->GetXaxis()->SetLimits(XMin[iVar]+0.0001,XMax[iVar]-0.0001);
            
            hist[iFile][0]->Draw("SAME HIST");
            hist[iFile][0]->SetFillStyle(3005);
            hist[iFile][0]->SetFillColorAlpha(ColorAK[0],0.35);
            hist[iFile][0]->SetLineColor(ColorAK[0]);
            t3->AddEntry(hist[iFile][0] ,"anti-k_{T} PbPb PYTHIA+HYDJET","f");
            //xcone
            makePretty(hist[iFile][1]);
            hist[iFile][1]->SetMaximum(YMaxHist[iVar]);
            hist[iFile][1]->GetXaxis()->SetLimits(XMin[iVar]+0.0001,XMax[iVar]-0.0001);
            
            hist[iFile][1]->Draw("SAME HIST");
            hist[iFile][1]->SetFillStyle(3004);
            hist[iFile][1]->SetFillColorAlpha(ColorXC[0],0.35);
            hist[iFile][1]->SetLineColor(ColorXC[0]);
            t3->AddEntry(hist[iFile][1] ,"XCone PbPb PYTHIA+HYDJET","f");
        }
        if (iFile==1){
            //akt
            makePretty(hist[iFile][0] );
            hist[iFile][0]->Draw("SAME");
            hist[iFile][0]->SetMarkerStyle(20);
            hist[iFile][0]->SetMarkerSize(0.5);
            hist[iFile][0]->SetMarkerColor(ColorAK[0]);
            hist[iFile][0]->SetLineColor(ColorAK[0]);
            hist[iFile][0]->GetXaxis()->SetLimits(XMin[iVar]+0.0001,XMax[iVar]-0.0001);
            t3->AddEntry(hist[iFile][0] ,"anti-k_{T} PbPb Data","p");

            //xcone
            makePretty(hist[iFile][1] );
            hist[iFile][1]->Draw("SAME");
            hist[iFile][1]->SetMarkerStyle(20);
            hist[iFile][1]->SetMarkerSize(0.5);
            hist[iFile][1]->SetMarkerColor(ColorXC[0]);
            hist[iFile][1]->SetLineColor(ColorXC[0]);
            hist[iFile][1]->GetXaxis()->SetLimits(XMin[iVar]+0.0001,XMax[iVar]-0.0001);
            t3->AddEntry(hist[iFile][1] ,"XCone PbPb Data","p");

        }
    }
    t3->Draw("SAME");
    drawText("CMS Preliminary",0.17,0.93,23);
    drawText("p_{T,1}>100 GeV  p_{T,2}>50 GeV p_{T,3}>50 GeV",0.18,0.74,16);
    drawText(Form("%s",TextCut[iVar].Data()),0.18,0.69,16);
    
    c2->SaveAs(Form("PLOTALGO/pt50MCPbPbalgorithm%s.png",XLabel[iVar].Data()));
    c2->SaveAs(Form("PLOTALGO/pt50MCPbPbalgorithm%s.eps",XLabel[iVar].Data()));
    c2->SaveAs(Form("PLOTALGO/pt50MCPbPbalgorithm%s.gif",XLabel[iVar].Data()));
}
    /***
    TLegend *t3=new TLegend(0.33,0.80,0.49,0.96);
    t3->SetFillColor(0);
    t3->SetBorderSize(0);
    t3->SetFillStyle(0);
    t3->SetTextFont(43);
    t3->SetTextSize(15);
    t3->SetTextAlign(13);
    
    c2->cd(1);
    for ( int iFile = 0 ; iFile < nFiles ; iFile++ ){
        
        
        if (iFile==0){
                
                //akt
            makePretty(hist[iFile][0] );
            hist[iFile][0]->SetMaximum(YMaxHist[iVar]);
            hist[iFile][0]->GetXaxis()->SetLimits(XMin[iVar]+0.0001,XMax[iVar]-0.0001);
            
            hist[iFile][0]->Draw("SAME HIST");
            hist[iFile][0]->SetFillStyle(3005);
            hist[iFile][0]->SetFillColorAlpha(Color[0],0.35);
            hist[iFile][0]->SetLineColor(Color[0]);
                
                //xcone
            makePretty(hist[iFile][1] );
            hist[iFile][1] ->SetMaximum(YMaxHist[iVar]);
            hist[iFile][1] ->GetXaxis()->SetLimits(XMin[iVar]+0.0001,XMax[iVar]-0.0001);
                
            hist[iFile][1] ->Draw("SAME HIST");
            hist[iFile][1] ->SetFillStyle(3005);
            hist[iFile][1] ->SetFillColorAlpha(Color[0],0.35);
            hist[iFile][1] ->SetLineColor(Color[0]);
        }
            
        if (iFile==1){
            //akt
            makePretty(hist[iFile][0] );
            hist[iFile][0] ->Draw("SAME");
            hist[iFile][0] ->SetMarkerStyle(20);
            hist[iFile][0] ->SetMarkerSize(0.5);
            hist[iFile][0] ->SetMarkerColor(Color[0]);
            hist[iFile][0] ->SetLineColor(Color[0]);
            hist[iFile][0] ->GetXaxis()->SetLimits(XMin[iVar]+0.0001,XMax[iVar]-0.0001);
                
            //xcone
            makePretty(hist[iFile][1] );
            hist[iFile][1] ->Draw("SAME");
            hist[iFile][1] ->SetMarkerStyle(20);
            hist[iFile][1] ->SetMarkerSize(0.5);
            hist[iFile][1] ->SetMarkerColor(Color[0]);
            hist[iFile][1] ->SetLineColor(Color[0]);
            hist[iFile][1] ->GetXaxis()->SetLimits(XMin[iVar]+0.0001,XMax[iVar]-0.0001);

        }
            
        if (iFile==2){
            //akt
            makePretty(hist[iFile][0]);
            hist[iFile][0]->Draw("SAME HIST");
            hist[iFile][0]->SetFillColorAlpha(Color[1],0.35);
            hist[iFile][0]->SetFillStyle(3004);
            hist[iFile][0]->SetLineColor(Color[1]);
            hist[iFile][0]->GetXaxis()->SetLimits(XMin[iVar]+0.0001,XMax[iVar]-0.0001);
                
            //xcone
            makePretty(hist[iFile][1]);
            hist[iFile][1]->Draw("SAME HIST");
            hist[iFile][1]->SetFillColorAlpha(Color[1],0.35);
            hist[iFile][1]->SetFillStyle(3004);
            hist[iFile][1]->SetLineColor(Color[1]);
            hist[iFile][1]->GetXaxis()->SetLimits(XMin[iVar]+0.0001,XMax[iVar]-0.0001);
        }
            
        if (iFile==3){
            //akt
            makePretty(hist[iFile][0]);
            hist[iFile][0]->Draw("SAME");
            hist[iFile][0]->SetMarkerStyle(20);
            hist[iFile][0]->SetMarkerSize(0.5);
            hist[iFile][0]->SetMarkerColor(Color[1]);
            hist[iFile][0]->SetLineColor(Color[1]);
            hist[iFile][0]->GetXaxis()->SetLimits(XMin[iVar]+0.0001,XMax[iVar]-0.0001);
            
            //xcone
            makePretty(hist[iFile][1]);
            hist[iFile][1]->Draw("SAME");
            hist[iFile][1]->SetMarkerStyle(20);
            hist[iFile][1]->SetMarkerSize(0.5);
            hist[iFile][1]->SetMarkerColor(Color[1]);
            hist[iFile][1]->SetLineColor(Color[1]);
            hist[iFile][1]->GetXaxis()->SetLimits(XMin[iVar]+0.0001,XMax[iVar]-0.0001);

        }
    }
        
    
    
    drawText("CMS Preliminary",0.20,0.93,23);
    drawText("p_{T,1}>100 GeV  p_{T,2}>30 GeV p_{T,3}>30 GeV",0.03,0.93,18);
    drawText(Form("%s",TextCut[iVar].Data()),0.03,0.93,18);
    
        
    for ( int iFile = 0 ; iFile < nFiles ; iFile++ ){
        if (iFile == 0 && nCentrBins != 1 ) {
                t3->AddEntry(hist[iFile][1] ,"XCone PbPb PYTHIA+HYDJET","f");
            }
            if (iFile == 1 && nCentrBins != 1 ) {
                t3->AddEntry(hist[iFile][1] ,"XCone PbPb Data","p");
            }
            if (iFile == 2 && nCentrBins != 1 ){
                t3->AddEntry(hist[iFile][1],"XCone pp PYTHIA","f");
            }
            if (iFile == 3 && nCentrBins != 1 ) {
                t3->AddEntry(hist[iFile][1],"XCone pp Data","p");

            }
        else{
            t3->AddEntry(hist[iFile][0] ,"anti-k_{T} PbPb PYTHIA+HYDJET","f");
            t3->AddEntry(hist[iFile][1] ,"XCone PbPb PYTHIA+HYDJET","f");
        }
        t3->Draw("SAME");
        
            

            
    }
        
        
    
    
    
    c2->SaveAs(Form("PLOTALGO/algorithm%s.png",XLabel[iVar].Data()));
    c2->SaveAs(Form("PLOTALGO/algorithm%s.eps",XLabel[iVar].Data()));
    c2->SaveAs(Form("PLOTALGO/algorithm%s.gif",XLabel[iVar].Data()));
    
    ***/
    

    
    
    
    
}
