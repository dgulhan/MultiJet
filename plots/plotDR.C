#include "utilities.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TStyle.h"
#include "TColor.h"
#define sign(a) ( ( (a) < 0 )  ?  -1   : ( (a) > 0 ) )


void plotDR(){
    
    TH1D::SetDefaultSumw2();
    
    TString fin;
    TString label;
    
    
    cout << "Save fig label: ";
    cin >> label;
    
    
    TFile*  file = new TFile("/Users/eruiz/CMS/filesw1/forEdna/MJSkim_pp_data_jet80.root");
    
    Int_t R[] = {3,4,5};
    int nvar = 15;
    TH1D * histVar[2][nvar][3];

    TString xaxis[] = {"pt2*pow(pt1,-1.)","acos(cos(phi1-phi2))","acos(cos(phi2-phi3))","acos(cos(phi1-phi3))","sqrt(pow(acos(cos(phi2-phi3)),2.)+pow(eta2-eta3,2.))","sign(eta2)*(eta3-eta2)","nref","pt2*pow(pt1,-1.)","pt1*cos(phi1)+pt2*cos(phi2)+pt3*cos(phi3)","pt1*sin(phi1)+pt2*sin(phi2)+pt3*sin(phi3)","atan(abs(acos(cos(phi3-phi2)))/(sign(eta2)*(eta3-eta2)))","eta1","eta2","sqrt((pt1*cos(phi1)+pt2*cos(phi2)+pt3*cos(phi3))^2 + (pt1*sin(phi1)+pt2*sin(phi2)+pt3*sin(phi3))^2)/(pt1+pt2+pt3)","sign(eta2)*(eta3-eta2)"};
    
    TString stringName[] = {"#frac{P_{T_{2}}}{P_{T_{1}}}","#Delta#phi_{12}","#Delta#phi_{23}","#Delta#phi_{13}","#Delta R_{23}","#Delta#eta_{23}","N_{jet}","P_{T_{2}}#timesP_{T_{1}}^{-1}","P_{x}","P_{y}","#beta","#eta_{1}","#eta_{2}","total balance","#Delta#eta_{23}"};
    
    TString stringCuts[] = {"pt1>120 && pt2>30 && (acos(cos(phi1-phi2)))>2*TMath::Pi()/3 && pt3>10","pt1>120 && pt2>30 && pt3>10","pt1>120 && pt2>30 && pt3>10","pt1>120 && pt2>30 && pt3>10","pt1>120 && pt2>30 && pt3>10 && pt3>10","pt1>120 && pt2>30 && pt3>10","pt1>120","pt1>120 && pt2>30 && (acos(cos(phi1-phi2)))>2*TMath::Pi()/3 && pt3>10","pt1>120 && pt2>30 && pt3>10","pt1>120 && pt2>30 && pt3>10","pt1>120 && pt2>30 && pt3>10","pt1>120 && pt2>30 && pt3>10","pt1>120 && pt2>30 && pt3>10","pt1>120 && pt2>30 && pt3>10","pt1>120 && pt2>30 && pt3>10 && abs(eta2)<0.5" };
    
    Float_t histoxmin[] = {0,0,0,0,0,-3,0.0,0,-200,-200,-2,-2,-2,0,-2};
    
    Float_t histoxmax[] = {1,TMath::Pi(),TMath::Pi(),TMath::Pi(),TMath::Pi(),2,20.,1.0,200,200,2,2,2,1,2};
    
    
    
    for (int rval = 0 ; rval < 3 ; rval++ ){
        
        TTree* tree[2];
        tree[0] = (TTree*)file->Get(Form("xc%iPF",R[rval]));
        tree[1] = (TTree*)file->Get(Form("ak%iPF",R[rval]));
        
        
        
        int col[] = {kBlue-3, kRed+1};
        
        for(int ivar = 0; ivar < nvar; ivar++){
            
            for(int ialgo = 0; ialgo < 2; ialgo++){
                
                histVar[ialgo][ivar][rval] = new TH1D(Form("hist%s%d%d",stringName[ivar].Data(),ialgo,rval),Form(";%s;Event fraction",stringName[ivar].Data()),50,histoxmin[ivar],histoxmax[ivar]);
                tree[ialgo]->Draw(Form("%s>>hist%s%d%d",xaxis[ivar].Data(),stringName[ivar].Data(),ialgo,rval),stringCuts[ivar].Data());
                histVar[ialgo][ivar][rval]->Scale(1./histVar[ialgo][ivar][rval]->Integral());
                
                histVar[ialgo][ivar][rval]->SetMarkerColor(col[ialgo]);
                histVar[ialgo][ivar][rval]->SetLineColor(col[ialgo]);
                
            }
        }
        
        TLegend *t3=new TLegend(0.64,0.8,0.99,0.95);
        t3->SetFillColor(0);
        t3->SetBorderSize(0);
        t3->SetFillStyle(0);
        t3->SetTextFont(43);
        t3->SetTextSize(30);
        t3->AddEntry(histVar[0][0][rval],"X-cone","p");
        t3->AddEntry(histVar[1][0][rval],"anti k_{T}","p");
        
        
    }

    
//PYTHIA 6
    
    TH1D *histVarPyt6[2][nvar][3];
    
    
    TFile*  filePya6 = new TFile("/Users/eruiz/CMS/filesw1/forEdna/MJSkim_pp_pythia6_pthat100.root");
    
    for (int rval = 0 ; rval < 3 ; rval++ ){
        
        TTree* tree[2];
        tree[0] = (TTree*)filePya6->Get(Form("xc%iPF",R[rval]));
        tree[1] = (TTree*)filePya6->Get(Form("ak%iPF",R[rval]));
        
        int col[] = {kYellow-4, kMagenta};
        
        for(int ivar = 0; ivar < nvar; ivar++){
            
            for(int ialgo = 0; ialgo < 2; ialgo++){
                
                histVarPyt6[ialgo][ivar][rval] = new TH1D(Form("hist%s%d%d",stringName[ivar].Data(),ialgo,rval),Form(";%s;Event fraction",stringName[ivar].Data()),50,histoxmin[ivar],histoxmax[ivar]);
                tree[ialgo]->Draw(Form("%s>>hist%s%d%d",xaxis[ivar].Data(),stringName[ivar].Data(),ialgo,rval),stringCuts[ivar].Data());
                histVarPyt6[ialgo][ivar][rval]->Scale(1./histVarPyt6[ialgo][ivar][rval]->Integral());
                histVarPyt6[ialgo][ivar][rval]->SetLineColor(col[ialgo]);
                histVarPyt6[ialgo][ivar][rval]->SetLineWidth(2);
            }
        }
        
        
    }
    
    
//PYTHIA 8
    
    TH1D *histVarPyt8[2][nvar][3];
    
    
    TFile*  filePya8 = new TFile("/Users/eruiz/CMS/filesw1/forEdna/MJSkim_pp_pythia8_pthat100.root");
    
    for (int rval = 0 ; rval < 3 ; rval++ ){
        
        TTree* tree[2];
        tree[0] = (TTree*)filePya8->Get(Form("xc%iPF",R[rval]));
        tree[1] = (TTree*)filePya8->Get(Form("ak%iPF",R[rval]));
        
        int col[] = {kCyan, kSpring-2};
        
        for(int ivar = 0; ivar < nvar; ivar++){
            
            for(int ialgo = 0; ialgo < 2; ialgo++){
                
                histVarPyt8[ialgo][ivar][rval] = new TH1D(Form("hist%s%d%d",stringName[ivar].Data(),ialgo,rval),Form(";%s;Event fraction",stringName[ivar].Data()),50,histoxmin[ivar],histoxmax[ivar]);
                tree[ialgo]->Draw(Form("%s>>hist%s%d%d",xaxis[ivar].Data(),stringName[ivar].Data(),ialgo,rval),stringCuts[ivar].Data());
                histVarPyt8[ialgo][ivar][rval]->Scale(1./histVarPyt8[ialgo][ivar][rval]->Integral());
                histVarPyt8[ialgo][ivar][rval]->SetLineColor(col[ialgo]);
                histVarPyt8[ialgo][ivar][rval]->SetLineWidth(2);
            }
        }
        
        
    }

    
    
//-----PLOTING LOOP----------
    
    
    TCanvas * c2[nvar];
    
    for(int ivar = 0; ivar < nvar; ivar++){
        c2[ivar]= new TCanvas(Form("c2%d",ivar),"",3*450,500);
        makeMultiPanelCanvas(c2[ivar],3,1,0.0,0.0,0.22,0.22,0.02);
        
        for (int ir = 0; ir < 3; ir++ )
        {
            c2[ivar]->cd(ir+1);
            for (int ialgo = 0; ialgo < 2; ialgo++){
                makePretty(histVar[ialgo][ivar][ir]);
                
                Double_t max = histVarPyt6[ialgo][ivar][ir]->GetMaximum();
                histVarPyt6[ialgo][ivar][ir]->SetMaximum(max+0.02);
                histVarPyt6[ialgo][ivar][ir]->Draw("HIST SAME");
                histVarPyt8[ialgo][ivar][ir]->Draw("HIST SAME");
                histVar[ialgo][ivar][ir]->Draw("SAME");

            }
            
            TLegend *t3=new TLegend(0.10,0.75,0.50,0.95);
            t3->SetFillColor(0);
            t3->SetBorderSize(0);
            t3->SetFillStyle(0);
            t3->SetTextFont(43);
            t3->SetTextSize(20);
            t3->AddEntry(histVar[0][ivar][ir],"X-cone","p");
            t3->AddEntry(histVar[1][ivar][ir],"anti k_{T}","p");
            t3->AddEntry(histVarPyt6[0][ivar][ir],"X-cone Pythia 6","l");
            t3->AddEntry(histVarPyt6[1][ivar][ir],"anti k_{T} Pythia 6","l");
            t3->AddEntry(histVarPyt8[0][ivar][ir],"X-cone Pythia 8","l");
            t3->AddEntry(histVarPyt8[1][ivar][ir],"anti k_{T} Pythia 8","l");
            //drawText(Form("R = %d",ir+3),0.23,0.90,33);
            t3->AddEntry((TObject*)0, Form("R = %d",ir+3), "");
            t3->Draw("SAME");
            
        }
        
        
        
        c2[ivar]->SaveAs(Form("%s%s.png",label.Data(),stringName[ivar].Data()));
        
    }
   
  
    
    
}



