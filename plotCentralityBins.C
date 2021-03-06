#include "utilities.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TStyle.h"
#include "TMath.h"
#include "TColor.h"
#include <stdio.h>
#define sign(a) ( ( (a) < 0 )  ?  -1   : ( (a) > 0 ) )



void plotCentralityBins(){
    TH1D::SetDefaultSumw2();


    int R = 4;
    int N = 3;

    int iVar;
    cout<<"Var number: ";
    cin >> iVar;

    //acos(cos(phi1-phi2))> 2*TMath::Pi()/2
    TString CentrText[] = {"Centr. 100-50%","Centr. 50-30%","Centr. 30-10%","Centr. 10-0%"};
    int nCentrBins = 4;

    TString XAxis[] = {
        "(pt1-pt2)/(pt1+pt2)",
        "sqrt((pt1*cos(phi1)+pt2*cos(phi2)+pt3*cos(phi3))^2 + (pt1*sin(phi1)+pt2*sin(phi2)+pt3*sin(phi3))^2)/(pt1+pt2+pt3)",
        "acos(cos(phi1-phi3))",
        "acos(cos(phi1-phi2))",
        "acos(cos(phi2-phi3))",
        "sign(eta1)*(eta3-eta1)",
        "sign(eta1)*(eta2-eta1)",
        "sign(eta2)*(eta3-eta2)",
        "sqrt(pow(acos(cos(phi1-phi3)),2.)+pow(eta1-eta3,2.))",
        "sqrt(pow(acos(cos(phi1-phi2)),2.)+pow(eta1-eta2,2.))",
        "sqrt(pow(acos(cos(phi2-phi3)),2.)+pow(eta2-eta3,2.))"
    };

    TString XLabel[] = {
        "A_{j}",
        "P_{T_{Bal}}",
        "#Delta#phi_{1,3}" ,
        "#Delta#phi_{1,2}" ,
        "#Delta#phi_{2,3}" ,
        "#Delta#eta_{1,3}" ,
        "#Delta#eta_{1,2}" ,
        "#Delta#eta_{2,3}" ,
        "#Delta R_{1,3}" ,
        "#Delta R_{1,2}" ,
        "#Delta R_{2,3}"
    };



    TString Files[] = {
        //"root://eoscms//eos/cms/store/group/cmst3/user/dgulhan/MultiJetSkims/20160720/PbPbMCpthat80+pullHiForestAOD_ALL.root",
        "/afs/cern.ch/work/e/eruizvel/public/CutconstPbPbMCpthat80+pullHiForestAOD_ALL.root",
        "/afs/cern.ch/work/e/eruizvel/public/PbPbDataHIHardProbes+pullHiForest_ALLrepro.root",
        "root://eoscms//eos/cms/store/group/cmst3/user/dgulhan/MultiJetSkims/20160720/ppMCpthat80+pullHiForestAOD_ALL.root",
        "root://eoscms//eos/cms/store/group/cmst3/user/dgulhan/MultiJetSkims/20160726/ppDataHighPt80+pullHiForest_ALL.root"
    };

    int nFiles = 4;

    TCut CentralityBinsCuts[] = {
        " 50 < hiBin/2 && hiBin/2 < 100 ",
        " 30 < hiBin/2 && hiBin/2 < 50 " ,
        " 10 < hiBin/2 && hiBin/2 < 30 " ,
        " 0 < hiBin/2 && hiBin/2 < 10"
    };

    TCut ppCuts[] = {
        " pt1>100 && pt2>30 && pt3>0 && acos(cos(phi1-phi2))>2*TMath::Pi()/3 && abs(eta1-eta2)>0.2",
        " pt1>100 && pt2>30 && pt3>0 && acos(cos(phi1-phi2))>2*TMath::Pi()/3 && abs(eta1-eta2)>0.2",
        " pt1>100 && pt3>30 && acos(cos(phi1-phi2))>2*TMath::Pi()/3 && abs(eta1-eta2)>0.2" ,
        " pt1>100 && pt3>30 && abs(eta1-eta2)>0.2" ,
        " pt1>100 && pt3>30 && acos(cos(phi1-phi2))>2*TMath::Pi()/3 && abs(eta1-eta2)>0.2" ,
        " pt1>100 && pt3>30 && acos(cos(phi1-phi2))>2*TMath::Pi()/3 && abs(eta1-eta2)>0.2" ,
        " pt1>100 && pt3>30 && acos(cos(phi1-phi2))>2*TMath::Pi()/3 && abs(eta1-eta2)>0.2" ,
        " pt1>100 && pt3>30 && acos(cos(phi1-phi2))>2*TMath::Pi()/3 && abs(eta1-eta2)>0.2" ,
        " pt1>100 && pt3>30 && acos(cos(phi1-phi2))>2*TMath::Pi()/3 && abs(eta1-eta2)>0.2" ,
        " pt1>100 && pt3>30 && acos(cos(phi1-phi2))>2*TMath::Pi()/3 && abs(eta1-eta2)>0.2" ,
        " pt1>100 && pt3>30 && acos(cos(phi1-phi2))>2*TMath::Pi()/3 && abs(eta1-eta2)>0.2",
    };




    TCut PbPbCuts[] = {
      " pt1>100 && pt2>30 && pt3>0 && acos(cos(phi1-phi2))>2*TMath::Pi()/3 && abs(eta1-eta2)>0.2",
      " pt1>100 && pt2>30 && pt3>0 && acos(cos(phi1-phi2))>2*TMath::Pi()/3 && abs(eta1-eta2)>0.2",
      " pt1>100 && pt3>30 && acos(cos(phi1-phi2))>2*TMath::Pi()/3 && abs(eta1-eta2)>0.2" ,
      " pt1>100 && pt3>30 && abs(eta1-eta2)>0.2" ,
      " pt1>100 && pt3>30 && acos(cos(phi1-phi2))>2*TMath::Pi()/3 && abs(eta1-eta2)>0.2" ,
      " pt1>100 && pt3>30 && acos(cos(phi1-phi2))>2*TMath::Pi()/3 && abs(eta1-eta2)>0.2" ,
      " pt1>100 && pt3>30 && acos(cos(phi1-phi2))>2*TMath::Pi()/3 && abs(eta1-eta2)>0.2" ,
      " pt1>100 && pt3>30 && acos(cos(phi1-phi2))>2*TMath::Pi()/3 && abs(eta1-eta2)>0.2" ,
      " pt1>100 && pt3>30 && acos(cos(phi1-phi2))>2*TMath::Pi()/3 && abs(eta1-eta2)>0.2" ,
      " pt1>100 && pt3>30 && acos(cos(phi1-phi2))>2*TMath::Pi()/3 && abs(eta1-eta2)>0.2" ,
      " pt1>100 && pt3>30 && acos(cos(phi1-phi2))>2*TMath::Pi()/3 && abs(eta1-eta2)>0.2",
  };




    TString TextCut[] = {
        "#Delta#phi_{1,2}> 2#pi/3 |#Delta#eta_{1,2}|>0.2" ,
        "#Delta#phi_{1,2}> 2#pi/3 |#Delta#eta_{1,2}|>0.2" ,
        "#Delta#phi_{1,2}> 2#pi/3 |#Delta#eta_{1,2}|>0.2" ,
        "|#Delta#eta_{1,2}|>0.2" ,
        "#Delta#phi_{1,2}> 2#pi/3 |#Delta#eta_{1,2}|>0.2" ,
        "#Delta#phi_{1,2}> 2#pi/3 |#Delta#eta_{1,2}|>0.2" ,
        "#Delta#phi_{1,2}> 2#pi/3 |#Delta#eta_{1,2}|>0.2" ,
        "#Delta#phi_{1,2}> 2#pi/3 |#Delta#eta_{1,2}|>0.2",
        "#Delta#phi_{1,2}> 2#pi/3 |#Delta#eta_{1,2}|>0.2" ,
        "#Delta#phi_{1,2}> 2#pi/3 |#Delta#eta_{1,2}|>0.2" ,
        "#Delta#phi_{1,2}> 2#pi/3 |#Delta#eta_{1,2}|>0.2"
    };


    Double_t YMaxHist[] = {0.2,0.16,0.12,0.25,0.12,0.095,0.09,0.13,0.15,0.17,0.12};
    Double_t XMin[] = {0,0,0,0,0,-2.,-2.,-2.,0.,0.,0.};
    Double_t XMax[] = {1.0,1.0,TMath::Pi(),TMath::Pi(),TMath::Pi(),2.,2.,2.,4.,4.,4.};


    TFile *file[nFiles];
    TH1D *hist[nFiles][nCentrBins];
    TTree *tree[nFiles];

    int Color[] = {kRed,kBlue};

    for ( int iFile = 0 ; iFile < nFiles ; iFile++ ){
        file[iFile] = TFile::Open(Files[iFile].Data());

        //if (iFile == 3 ){tree[iFile] = (TTree*)file[iFile]->Get("xc4PF");}
        //if (iFile  < 3 ){tree[iFile] = (TTree*)file[iFile]->Get(Form("xc_R%i_N%i_PF",R,N));}

        //tree[iFile] = (TTree*)file[iFile]->Get(Form("xc_R%i_N%i_PF",R,N));
        tree[iFile] = (TTree*)file[iFile]->Get(Form("xc_R4_N3_PF",R,N));

        for ( int iCentr = 0 ; iCentr < nCentrBins ; iCentr++ ) {

            if (iFile==0){
                hist[iFile][iCentr] = new TH1D(Form("hist_F%iV%iC%i",iFile,iVar,iCentr),Form(";%s;Event fraction",XLabel[iVar].Data()),50,XMin[iVar],XMax[iVar]);
                tree[iFile]->Draw(Form("%s>>hist_F%iV%iC%i",XAxis[iVar].Data(),iFile,iVar,iCentr),CentralityBinsCuts[iCentr] && PbPbCuts[iVar]);
                hist[iFile][iCentr]->Scale(1./hist[iFile][iCentr]->Integral());
                hist[iFile][iCentr]->SetStats(0);

            }

            if (iFile==1){

                hist[iFile][iCentr] = new TH1D(Form("hist_F%iV%iC%i",iFile,iVar,iCentr),Form(";%s;Event fraction",XLabel[iVar].Data()),50,XMin[iVar],XMax[iVar]);
                tree[iFile]->Draw(Form("%s>>hist_F%iV%iC%i",XAxis[iVar].Data(),iFile,iVar,iCentr),CentralityBinsCuts[iCentr] && PbPbCuts[iVar]);
                hist[iFile][iCentr]->Scale(1./hist[iFile][iCentr]->Integral());
                hist[iFile][iCentr]->SetStats(0);
            }



            if (iFile == 2 || iFile==3) {
                //For pp centrality is not computed.
                cout<<"Reading pp"<<endl;
                hist[iFile][0] = new TH1D(Form("hist_F%iV%iC%i",iFile,iVar,iCentr),Form(";%s;Event fraction",XLabel[iVar].Data()),50,XMin[iVar],XMax[iVar]);
                tree[iFile]->Draw(Form("%s>>hist_F%iV%iC%i",XAxis[iVar].Data(),iFile,iVar,iCentr),ppCuts[iVar]);
                hist[iFile][0]->Scale(1./hist[iFile][0]->Integral());
                hist[iFile][0]->SetStats(0);


            }
        }
    }

    TCanvas * c2 = new TCanvas("c2","c2",4*451,450);
    makeMultiPanelCanvas(c2,4,1,0.0,0.0,0.17,0.17,0.02);

    TLegend *t3=new TLegend(0.33,0.84,0.49,0.96);
    t3->SetFillColor(0);
    t3->SetBorderSize(0);
    t3->SetFillStyle(0);
    t3->SetTextFont(43);
    t3->SetTextSize(15);
    t3->SetTextAlign(13);

    for (int iCentr = 0 ; iCentr < nCentrBins ; iCentr++) {

        for ( int iFile = 0 ; iFile < nFiles ; iFile++ ){

            c2->cd(iCentr+1);

            if (iFile==0){

                makePretty(hist[iFile][iCentr]);
                hist[iFile][iCentr]->SetMaximum(YMaxHist[iVar]);
                hist[iFile][iCentr]->GetXaxis()->SetLimits(XMin[iVar]+0.0001,XMax[iVar]-0.0001);

                hist[iFile][iCentr]->Draw("SAME HIST");
                hist[iFile][iCentr]->SetFillStyle(3005);
                hist[iFile][iCentr]->SetFillColorAlpha(Color[0],0.35);
                hist[iFile][iCentr]->SetLineColor(Color[0]);
            }

            if (iFile==1){

                makePretty(hist[iFile][iCentr]);
                //hist[iFile][iCentr]->Draw("SAME");
                hist[iFile][iCentr]->SetMarkerStyle(20);
                hist[iFile][iCentr]->SetMarkerSize(0.5);
                hist[iFile][iCentr]->SetMarkerColor(Color[0]);
                hist[iFile][iCentr]->SetLineColor(Color[0]);
                hist[iFile][iCentr]->GetXaxis()->SetLimits(XMin[iVar]+0.0001,XMax[iVar]-0.0001);

            }

            if (iFile==2){

                makePretty(hist[iFile][0]);
                hist[iFile][0]->Draw("SAME HIST");
                hist[iFile][0]->SetFillColorAlpha(Color[1],0.35);
                hist[iFile][0]->SetFillStyle(3004);
                hist[iFile][0]->SetLineColor(Color[1]);
                hist[iFile][0]->GetXaxis()->SetLimits(XMin[iVar]+0.0001,XMax[iVar]-0.0001);

            }

            if (iFile==3){


                makePretty(hist[iFile][0]);
                //hist[iFile][0]->Draw("SAME");
                hist[iFile][0]->SetMarkerStyle(20);
                hist[iFile][0]->SetMarkerSize(0.5);
                hist[iFile][0]->SetMarkerColor(Color[1]);
                hist[iFile][0]->SetLineColor(Color[1]);
                hist[iFile][0]->GetXaxis()->SetLimits(XMin[iVar]+0.0001,XMax[iVar]-0.0001);

            }
        }

        TLegend *t2;

        if (iCentr == 0){ t2=new TLegend(0.19,0.83,0.26,0.95);}
        if (iCentr > 0){ t2=new TLegend(0.015,0.83,0.03,0.95);}

        t2->SetFillColor(0);
        t2->SetBorderSize(0);
        t2->SetFillStyle(0);
        t2->SetTextFont(43);
        t2->SetTextSize(19);
        t2->AddEntry(c2 ,CentrText[iCentr].Data(),"");
        t2->Draw("SAME");

        if (iCentr == 0){
            drawText("CMS Preliminary",0.20,0.93,23);

        }
        if (iCentr == 1) {
            drawText("p_{T,1}>100 GeV  p_{T,2}>30 GeV p_{T,3}>30 GeV",0.03,0.93,18);
            //drawText("p_{T,1}>0 GeV  p_{T,2}>0 GeV p_{T,3}>0 GeV",0.03,0.93,18);
            drawText("",0.03,0.80,18);
        }
        if (iCentr == 2){
            drawText(Form("%s",TextCut[iVar].Data()),0.03,0.93,18);
        }

        for ( int iFile = 0 ; iFile < nFiles ; iFile++ ){
            if (iCentr == nCentrBins-1 ){
                if (iFile == 0 ) {
                    t3->AddEntry(hist[iFile][iCentr],"XCone PbPb PYTHIA+HYDJET ","f");
                }
                if (iFile == 1) {
                    //t3->AddEntry(hist[iFile][iCentr],"anti-kt PbPb Data","p");
                }
                if (iFile == 2 ){
                    t3->AddEntry(hist[iFile][0],"XCone pp PYTHIA","f");
                }
                if (iFile == 3) {
                    //t3->AddEntry(hist[iFile][0],"anti-kt pp Data","p");

                }
            t3->Draw("SAME");
            }



        }


    }


    c2->SaveAs(Form("FiguresWOData/xcCentrPt100%s.png",XLabel[iVar].Data()));
    c2->SaveAs(Form("FiguresWOData/xcCentrPt100%s.eps",XLabel[iVar].Data()));
    c2->SaveAs(Form("FiguresWOData/xcCentrPt100%s.gif",XLabel[iVar].Data()));









}
