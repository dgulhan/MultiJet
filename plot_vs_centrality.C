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
    TCut Cut[] = {"pt1>140 && pt3>50 && acos(cos(phi1-phi2))>2*TMath::Pi()/3 && abs(eta1-eta2)>0.2",
                  "pt1>140 && pt3>50 && acos(cos(phi1-phi2))>2*TMath::Pi()/3 && abs(eta1-eta2)>0.2",
                  "pt1>140 && pt3>50 && acos(cos(phi1-phi2))>2*TMath::Pi()/3 && abs(eta1-eta2)>0.2" ,
                  "pt1>140 && pt3>50 && acos(cos(phi1-phi2))>2*TMath::Pi()/3 && abs(eta1-eta2)>0.2"};

    
    int nFiles = 4;
    TFile *file[nFiles];
    TString Files[] = {
        "root://eoscms//eos/cms/store/group/cmst3/user/dgulhan/MultiJetSkims/20160720/PbPbMCpthat80+pullHiForestAOD_ALL.root",
        "/afs/cern.ch/work/e/eruizvel/public/PbPbDataHIHardProbes+pullHiForest_ALL.root",
        "root://eoscms//eos/cms/store/group/cmst3/user/dgulhan/MultiJetSkims/20160720/ppMCpthat80+pullHiForestAOD_ALL.root",
        "root://eoscms//eos/cms/store/group/cmst3/user/dgulhan/MultiJetSkims/20160726/ppDataHighPt80+pullHiForest_ALL.root"
    };
    
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
        tree[iFile] = (TTree*)file[iFile]->Get(Form("ak4PF",R[0],N[0]));
        
        for (int iCentr = 0 ; iCentr < nBinsCentr ; iCentr++) {
            cout<<"def hist"<<endl;
            HistTotBal[iFile][iCentr] = new TH1D(Form("TotBal%i%i",iFile,iCentr),"",100,0,200);
            cout<<"hist defined"<<endl;
            if (iFile == 0 || iFile ==1 ) {
                tree[iFile]->Draw(Form("(sqrt((pt1*cos(phi1)+pt2*cos(phi2)+pt3*cos(phi3))^2 + (pt1*sin(phi1)+pt2*sin(phi2)+pt3*sin(phi3))^2)/(pt1+pt2+pt3))>>TotBal%i%i",iFile,iCentr),CentralityBinsCuts[iCentr] && Cut[iFile]);

            }
            if (iFile == 2 || iFile == 3) {
                cout<<"accessing file: "<<iFile<<endl;
                tree[iFile]->Draw(Form("(sqrt((pt1*cos(phi1)+pt2*cos(phi2)+pt3*cos(phi3))^2 + (pt1*sin(phi1)+pt2*sin(phi2)+pt3*sin(phi3))^2)/(pt1+pt2+pt3))>>TotBal%i%i",iFile,iCentr),Cut[iFile]);
                cout<<"histo drawn"<<endl;
            }
            
            Y[iFile][iCentr] = HistTotBal[iFile][iCentr]->GetMean();
            cout<<"mean stored "<< Y[iFile][iCentr] << endl;
            Yerr[iFile][iCentr] = HistTotBal[iFile][iCentr]->GetMeanError();
            cout<<"meanerror"<<endl;
            
        }
        

    }
    
    
    TCanvas *c = new TCanvas ("c","",610,600);
    c->SetLeftMargin(0.23);
    
    
    TLegend *t3=new TLegend(0.55,0.63,0.88,0.78);
    t3->SetFillColor(0);
    t3->SetBorderSize(0);
    t3->SetFillStyle(0);
    t3->SetTextFont(43);
    t3->SetTextSize(16);
    TString LabelGraph[] = {"PbPb PYTHIA+HYDJET", "PbPb Data" , "pp PYTHIA", "pp Data"};
    TString LabelGraphMarc[] = {"l", "p" , "l", "p"};
    
    
    for (int iFile = 0; iFile<nFiles; iFile++) {
        gr[iFile] = new TGraphErrors(nBinsCentr,X,Y[iFile],Xerr,Yerr[iFile]);
        gr[iFile]->GetXaxis()->SetLimits(0,100);
        gr[iFile]->GetXaxis()->SetTitle("% Centrality ");
        gr[iFile]->GetYaxis()->SetTitle("#LT P_{T} Balance #GT");
        
        if (iFile == 0) {
            gr[iFile]->SetMinimum(0.10);
            gr[iFile]->SetMaximum(0.31);
            gr[iFile]->SetLineColor(kRed-7);
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
            //gr[iFile]->SetLineStyle(9);
            gr[iFile]->Draw("SAME");
        }
        if (iFile==3) {
            gr[iFile]->SetMarkerStyle(21);
            gr[iFile]->SetMarkerColor(kBlue);
            gr[iFile]->SetMarkerSize(1);
            gr[iFile]->Draw("P SAME");
            
        }

        
        t3->AddEntry(gr[iFile],LabelGraph[iFile],LabelGraphMarc[iFile]);

    }
    
    t3->AddEntry(c2,"anti-k_{T} R=0.4","");

    t3->Draw("SAME");
    drawText("CMS Preliminary",0.25,0.85,23);
    drawText("p_{T,1}>140 GeV  p_{T,2}>50 GeV p_{T,3}>50 GeV",0.25,0.82,16);
    drawText("|#Delta#phi_{2,3}|>2#pi/3 |#Delta#eta_{2,3}|>0.2",0.25,0.78,16);

    
    
    c->SaveAs("totbalvscentrality.png");
    c->SaveAs("totbalvscentrality.pdf");
    c->SaveAs("totbalvscentrality.gif");
    
}



