#include "utilities.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TStyle.h"
#include "TColor.h"
#include "TMath.h"
#define sign(a) ( ( (a) < 0 )  ?  -1   : ( (a) > 0 ) )


using namespace std;

void Nplots{
    
    TH1D::SetDefaultSumw2();
    
    TString label;
    cout << "Save fig label: ";
    cin >> label;

    //NJET with dif N
    int nAlgo = 2;
    
    int nN = 3;
    int N[]={2,3,4};
    
    int nR = 3;
    Int_t R[] = {3,4,5};
    
    int nVar = 15;
    
    TString xaxis[] = {"pt2*pow(pt1,-1.)","acos(cos(phi1-phi2))","acos(cos(phi2-phi3))","acos(cos(phi1-phi3))","sqrt(pow(acos(cos(phi2-phi3)),2.)+pow(eta2-eta3,2.))","sign(eta2)*(eta3-eta2)","nref","pt2*pow(pt1,-1.)","pt1*cos(phi1)+pt2*cos(phi2)+pt3*cos(phi3)","pt1*sin(phi1)+pt2*sin(phi2)+pt3*sin(phi3)","atan(abs(acos(cos(phi3-phi2)))/(sign(eta2)*(eta3-eta2)))","eta1","eta2","sqrt((pt1*cos(phi1)+pt2*cos(phi2)+pt3*cos(phi3))^2 + (pt1*sin(phi1)+pt2*sin(phi2)+pt3*sin(phi3))^2)/(pt1+pt2+pt3)","sign(eta2)*(eta3-eta2)"};
    
    TString stringName[] = {"#frac{P_{T_{2}}}{P_{T_{1}}}","#Delta#phi_{12}","#Delta#phi_{23}","#Delta#phi_{13}","#Delta R_{23}","#Delta#eta_{23}","N_{jet}","P_{T_{2}}#timesP_{T_{1}}^{-1}","P_{x}","P_{y}","#beta","#eta_{1}","#eta_{2}","total balance","#Delta#eta_{23}"};
    
    TString stringCuts[] = {"pt1>120 && pt2>30 && (acos(cos(phi1-phi2)))>2*TMath::Pi()/3 && pt3>10","pt1>120 && pt2>30 && pt3>10","pt1>120 && pt2>30 && pt3>10","pt1>120 && pt2>30 && pt3>10","pt1>120 && pt2>30 && pt3>10 && pt3>10","pt1>120 && pt2>30 && pt3>10","pt1>120","pt1>120 && pt2>30 && (acos(cos(phi1-phi2)))>2*TMath::Pi()/3 && pt3>10","pt1>120 && pt2>30 && pt3>10","pt1>120 && pt2>30 && pt3>10","pt1>120 && pt2>30 && pt3>10","pt1>120 && pt2>30 && pt3>10","pt1>120 && pt2>30 && pt3>10","pt1>120 && pt2>30 && pt3>10","pt1>120 && pt2>30 && pt3>10 && abs(eta2)<0.5" };
    
    Double_t histoxmin[] = {0,0,0,0,0,-3,0.0,0,-200,-200,-2,-2,-2,0,-2};
    
    Double_t histoxmax[] = {1,TMath::Pi(),TMath::Pi(),TMath::Pi(),TMath::Pi(),2,20.,1.0,200,200,2,2,2,1,2};
    
    
    //TO ADAPT A BIT MORE
    
    TFile*  file = new TFile("/afs/cern.ch/work/e/eruizvel/private/MultiJetEdna/MultiJet/prueba1HiForest_0.root");
    
    TH1D * hist1[nAlgo][nR][nN][nVar];
    
    for (int iR = 0  ; iR < nR ; iR++){
        
        for (int iN = 0 ; iN < nN ; iN++){
            
            TTree* tree[2];
            tree[0] = (TTree*)file->Get(Form("xc_R%i_N%i_PF",R[iR],N[iN]));
            tree[1] = (TTree*)file->Get(Form("ak%iPF",R[iR]));

            int col[] = {kBlue-3, kRed+1};
            
            for(int iVar = 0; iVar < nVar; iVar++){
                
                hist1[0][iR][iN][iVar] = new TH1D(Form("hist%s%d%d%d",stringName[iVar].Data(),0,iR,iN),Form(";%s;Event fraction",stringName[iVar].Data()),50,histoxmin[iVar],histoxmax[iVar]);
                tree[0]->Draw(Form("%s>>hist%s%d%d",xaxis[ivar].Data(),stringName[iVar].Data(),0,iR,iN),stringCuts[iVar].Data());
                hist1[0][iR][iN][iVar]->Scale(1./hist1[0][iR][iN][iVar]->Integral());
                hist1[0][iR][iN][iVar]->SetMarkerColor(col[0]);
                hist1[0][iR][iN][iVar]->SetLineColor(col[0]);
                
                hist1[1][iR][0][iVar] = new TH1D(Form("hist%s%d%d%d",stringName[iVar].Data(),0,iR,0),Form(";%s;Event fraction",stringName[iVar].Data()),50,histoxmin[iVar],histoxmax[iVar]);
                tree[1]->Draw(Form("%s>>hist%s%d%d",xaxis[ivar].Data(),stringName[iVar].Data(),0,iR,0),stringCuts[iVar].Data());
                hist1[1][iR][0][iVar]->Scale(1./hist1[1][iR][0][iVar]->Integral());
                hist1[1][iR][0][iVar]->SetMarkerColor(col[0]);
                hist1[1][iR][0][iVar]->SetLineColor(col[0]);
                
            }
        }
    }

    
    
    
    //PLOT SECTION
    
    TCanvas* c2[nVar][nN];
    
    for(int iVar = 0; iVar < nVar; iVar++){
        for (int iN = 0 ; iN < nN ; iN++){
            c2[iVar][iN]= new TCanvas(Form("c2%d_%d",iVar,N[iN]),"",3*450,500);
            makeMultiPanelCanvas(c2[iVar][iN],3,1,0.0,0.0,0.22,0.22,0.02);
            for (int iR = 0  ; iR < nR ; iR++){
                c2[iVar][iN]->cd(iR+1);
                
                makePretty(histVar[ialgo][ivar][ir]);
                
                Double_t max = hist1[0][iR][iN][iVar]->GetMaximum();
                hist1[0][iR][iN][iVar]->SetMaximum(max+0.02);
                hist1[0][iR][iN][iVar]->Draw("HIST SAME");
                hist1[1][iR][0][iVar]->Draw("HIST SAME");
                
                TLegend *t3=new TLegend(0.10,0.75,0.50,0.95);
                t3->SetFillColor(0);
                t3->SetBorderSize(0);
                t3->SetFillStyle(0);
                t3->SetTextFont(43);
                t3->SetTextSize(20);
                t3->AddEntry(hist1[0][iR][iN][iVar],"X-cone","p");
                t3->AddEntry(hist1[1][iR][0][iVar],"anti k_{T}","p");
                //drawText(Form("R = %d",ir+3),0.23,0.90,33);
                t3->AddEntry((TObject*)0, Form("R = %d",iR+3), "");
                t3->AddEntry((TObject*)0, Form("N = %d",iN+2), "");
                t3->Draw("SAME");
                    
            }
        
        c2[iVar][iN]->SaveAs(Form("%s%s_%d.png",label.Data(),stringName[ivar].Data(),N[iN]));
        c2[iVar][iN]->SaveAs(Form("%s%s_%d.gif",label.Data(),stringName[ivar].Data(),N[iN]));
        c2[iVar][iN]->SaveAs(Form("%s%s_%d.pdf",label.Data(),stringName[ivar].Data(),N[iN]));
        c2[iVar][iN]->SaveAs(Form("%s%s_%d.eps",label.Data(),stringName[ivar].Data(),N[iN]));
        }
    }
    
    
}