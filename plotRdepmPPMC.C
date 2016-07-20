#include "utilities.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TStyle.h"
#include "TColor.h"
#define sign(a) ( ( (a) < 0 )  ?  -1   : ( (a) > 0 ) )


void plotRdepmPPMC(){
    
    TH1D::SetDefaultSumw2();
    
    TString fin;
    TString label;
    
    
    cout << "Save fig label: ";
    cin >> label;
    
    
    //TFile*  file = new TFile("/Users/eruiz/CMS/filesw1/forEdna/MJSkim_pp_data_jet80.root");
    
    Int_t R[] = {3,4,5};
    Int_t N[] = {3};
    int nR=3;
    int nN=1; //XCone
    int nAlgo=2;//XCone and antiKt
    int nVar = 9;

    TString xaxis[] = {"acos(cos(phi1-phi3))","acos(cos(phi1-phi2))","acos(cos(phi2-phi3))","sign(eta1)*(eta3-eta1)","sign(eta1)*(eta2-eta1)","sign(eta2)*(eta3-eta2)","sqrt(pow(acos(cos(phi1-phi3)),2.)+pow(eta1-eta3,2.))","sqrt(pow(acos(cos(phi1-phi2)),2.)+pow(eta1-eta2,2.))","sqrt(pow(acos(cos(phi2-phi3)),2.)+pow(eta2-eta3,2.))" };
    
    //{"pt2*pow(pt1,-1.)","acos(cos(phi1-phi2))","acos(cos(phi2-phi3))","acos(cos(phi1-phi3))","sqrt(pow(acos(cos(phi2-phi3)),2.)+pow(eta2-eta3,2.))","sign(eta2)*(eta3-eta2)","nref","pt2*pow(pt1,-1.)","pt1*cos(phi1)+pt2*cos(phi2)+pt3*cos(phi3)","pt1*sin(phi1)+pt2*sin(phi2)+pt3*sin(phi3)","atan(abs(acos(cos(phi3-phi2)))/(sign(eta2)*(eta3-eta2)))","eta1","eta2","sqrt((pt1*cos(phi1)+pt2*cos(phi2)+pt3*cos(phi3))^2 + (pt1*sin(phi1)+pt2*sin(phi2)+pt3*sin(phi3))^2)/(pt1+pt2+pt3)","sign(eta2)*(eta3-eta2)"};
    
    TString stringName[] = {"#Delta#phi_{1,3}" , "#Delta#phi_{1,2}" , "#Delta#phi_{2,3}" , "#Delta#eta_{1,3}" , "#Delta#eta_{1,2}" , "#Delta#eta_{2,3}" , "#Delta R_{1,3}" , "#Delta R_{1,2}" , "#Delta R_{2,3}" };

    
    //{"#frac{P_{T_{2}}}{P_{T_{1}}}","#Delta#phi_{12}","#Delta#phi_{23}","#Delta#phi_{13}","#Delta R_{23}","#Delta#eta_{23}","N_{jet}","P_{T_{2}}#timesP_{T_{1}}^{-1}","P_{x}","P_{y}","#beta","#eta_{1}","#eta_{2}","total balance","#Delta#eta_{23}"};
    
    TString stringCuts[] = {
        " pt1>180 && pt3>70 && acos(cos(phi1-phi2))>2*TMath::Pi()/3 && abs(eta1-eta2)>0.2" ,
        " pt1>180 && pt3>70 && abs(eta1-eta2)>0.2" ,
        " pt1>180 && pt3>70 && acos(cos(phi1-phi2))>2*TMath::Pi()/3 && abs(eta1-eta2)>0.2" ,
        " pt1>180 && pt3>70 && acos(cos(phi1-phi2))>2*TMath::Pi()/3 && abs(eta1-eta2)>0.2" ,
        " pt1>180 && pt3>70 && acos(cos(phi1-phi2))>2*TMath::Pi()/3 && abs(eta1-eta2)>0.2" ,
        " pt1>180 && pt3>70 && acos(cos(phi1-phi2))>2*TMath::Pi()/3 && abs(eta1-eta2)>0.2" ,
        " pt1>180 && pt3>70 && acos(cos(phi1-phi2))>2*TMath::Pi()/3 && abs(eta1-eta2)>0.2" ,
        " pt1>180 && pt3>70 && acos(cos(phi1-phi2))>2*TMath::Pi()/3 && abs(eta1-eta2)>0.2" ,
        " pt1>180 && pt3>70 && acos(cos(phi1-phi2))>2*TMath::Pi()/3 && abs(eta1-eta2)>0.2",
    };
    //{"pt1>120 && pt2>30 && (acos(cos(phi1-phi2)))>2*TMath::Pi()/3 && pt3>10","pt1>120 && pt2>30 && pt3>10","pt1>120 && pt2>30 && pt3>10","pt1>120 && pt2>30 && pt3>10","pt1>120 && pt2>30 && pt3>10 && pt3>10","pt1>120 && pt2>30 && pt3>10","pt1>120","pt1>120 && pt2>30 && (acos(cos(phi1-phi2)))>2*TMath::Pi()/3 && pt3>10","pt1>120 && pt2>30 && pt3>10","pt1>120 && pt2>30 && pt3>10","pt1>120 && pt2>30 && pt3>10","pt1>120 && pt2>30 && pt3>10","pt1>120 && pt2>30 && pt3>10","pt1>120 && pt2>30 && pt3>10","pt1>120 && pt2>30 && pt3>10 && abs(eta2)<0.5" };
    
    Double_t histoxmin[] = {0,0,0,-2.,-2.,-2.,0.,0.,0.};
    
    //{0,0,0,0,0,-3,0.0,0,-200,-200,-2,-2,-2,0,-2};
    
    Double_t histoxmax[] = {TMath::Pi(),TMath::Pi(),TMath::Pi(),2.,2.,2.,4.,4.,4.};
    

    //{1,TMath::Pi(),TMath::Pi(),TMath::Pi(),TMath::Pi(),2,20.,1.0,200,200,2,2,2,1,2};
    
    //Loops for anti KT. algo = 0
    

// PP  MC  DATA
    
    TH1D *histpp[nAlgo][nVar][nR][nN];
    
    
    TFile*  filepp = TFile::Open("root://eoscms//eos/cms/store/group/cmst3/user/dgulhan/MultiJetSkims/20160716/ppPy8hat80HiForestAOD_ALL.root");
    
    int colpp[] = {kBlue-3, kRed+1};
    
    
    for (int iR = 0 ; iR < nR ; iR++ ){
        
        TTree* tree[4];
        tree[0] = (TTree*)filepp->Get(Form("ak%iPF",R[iR]));
        for (int iN = 0; iN < nN ; iN++) {
            tree[iN+1] = (TTree*)filepp->Get(Form("xc_R%i_N%i_PF",R[iR],N[iN]));
            cout<<Form("xc_R%i_N%i_PF",R[iR],N[iN])<<endl;
        }
        
        
        
        for(int iVar = 0; iVar < nVar; iVar++){
            
            
            histpp[0][iVar][iR][0] = new TH1D(Form("hist_A%d_N%s_R%d_N%d",0,stringName[iVar].Data(),R[iR],0),Form(";%s;Event fraction",stringName[iVar].Data()),50,histoxmin[iVar],histoxmax[iVar]);
            tree[0]->Draw(Form("%s>>hist_A%d_N%s_R%d_N%d",xaxis[iVar].Data(),0,stringName[iVar].Data(),R[iR],0),stringCuts[iVar].Data());
            histpp[0][iVar][iR][0]->Scale(1./histpp[0][iVar][iR][0]->Integral());
            histpp[0][iVar][iR][0]->SetLineColor(colpp[0]);
            histpp[0][iVar][iR][0]->SetLineWidth(2);
            
            for (int iN = 0; iN < nN ; iN++) {
                
                histpp[1][iVar][iR][iN] = new TH1D(Form("hist_A%d_N%s_R%d_N%d",1,stringName[iVar].Data(),R[iR],N[iN]),Form(";%s;Event fraction",stringName[iVar].Data()),50,histoxmin[iVar],histoxmax[iVar]);
                tree[iN+1]->Draw(Form("%s>>hist_A%d_N%s_R%d_N%d",xaxis[iVar].Data(),1,stringName[iVar].Data(),R[iR],N[iN]),stringCuts[iVar].Data());
                histpp[1][iVar][iR][iN]->Scale(1./histpp[1][iVar][iR][iN]->Integral());
                histpp[1][iVar][iR][iN]->SetLineColor(colpp[1]);
                histpp[1][iVar][iR][iN]->SetLineWidth(2);
                
                
            }
            
        }
        
    }
    

//END FOR PP

    

    //    PbPb    DATA
    
    

    /*
    TH1D *histPbPb[nAlgo][nVar][nR][nN];
    
    
    TFile*  filePbPb = new TFile("/Users/eruiz/CMS/pp_vs_PbPb_MC/MJSkim_PbPb_PYTHIA8_HYDJET_pthat120.root");
    int col[] = {kOrange-4, kGreen};
    
    for (int iR = 0 ; iR < nR ; iR++ ){
        
        TTree* tree[4];
        tree[0] = (TTree*)filePbPb->Get(Form("ak%iPF",R[iR]));
        for (int iN = 0; iN < nN ; iN++) {
            tree[iN+1] = (TTree*)filePbPb->Get(Form("xc_R%i_N%i_PF",R[iR],N[iN]));
            cout<<Form("xc_R%i_N%i_PF",R[iR],N[iN])<<endl;
        }
        
        
        
        for(int iVar = 0; iVar < nVar; iVar++){
            
            
            histPbPb[0][iVar][iR][0] = new TH1D(Form("hist_A%d_N%s_R%d_N%d",0,stringName[iVar].Data(),R[iR],0),Form(";%s;Event fraction",stringName[iVar].Data()),50,histoxmin[iVar],histoxmax[iVar]);
            tree[0]->Draw(Form("%s>>hist_A%d_N%s_R%d_N%d",xaxis[iVar].Data(),0,stringName[iVar].Data(),R[iR],0),stringCuts[iVar].Data());
            histPbPb[0][iVar][iR][0]->Scale(1./histPbPb[0][iVar][iR][0]->Integral());
            histPbPb[0][iVar][iR][0]->SetLineColor(col[0]);
            histPbPb[0][iVar][iR][0]->SetLineWidth(2);
            
            for (int iN = 0; iN < nN ; iN++) {
                
                histPbPb[1][iVar][iR][iN] = new TH1D(Form("hist_A%d_N%s_R%d_N%d",1,stringName[iVar].Data(),R[iR],N[iN]),Form(";%s;Event fraction",stringName[iVar].Data()),50,histoxmin[iVar],histoxmax[iVar]);
                tree[iN+1]->Draw(Form("%s>>hist_A%d_N%s_R%d_N%d",xaxis[iVar].Data(),1,stringName[iVar].Data(),R[iR],N[iN]),stringCuts[iVar].Data());
                histPbPb[1][iVar][iR][iN]->Scale(1./histPbPb[1][iVar][iR][iN]->Integral());
                histPbPb[1][iVar][iR][iN]->SetLineColor(col[1]);
                histPbPb[1][iVar][iR][iN]->SetLineWidth(2);

                
            }
            
        }
        
    }
    
    
  
    TCanvas *c1[nAlgo][nVar][nR][nN];
    
    for(int iVar = 0; iVar < nVar; iVar++)
    {
        for (int iR = 0; iR < nR; iR++ ){
            
            for (int iN = 0; iN < nN ; iN++) {
                
                c1[1][iVar][iR][iN] = new TCanvas(Form("c2%d%d%d%d",iVar,iR,1,iN),"",500,500);
                histPbPb[1][iVar][iR][iN]->Draw("SAME");
                histPbPb[0][iVar][iR][0]->Draw("SAME");
                
            }
            
        }
    }
    ***/
    

    
    
//-----PLOTING LOOP----------
    TCanvas * c2[nVar][nN];
    
    for(int iVar = 0; iVar < nVar; iVar++){
        for (int iN = 0; iN < nN; iN++) {
            c2[iVar][iN]= new TCanvas(Form("c2%d%d",iVar,iN),"",3*450,500);
            makeMultiPanelCanvas(c2[iVar][iN],3,1,0.0,0.0,0.22,0.22,0.02);
           
            for (int iR = 0; iR < nR; iR++ )
            {
                c2[iVar][iN]->cd(iR+1);
                
                makePretty(histpp[0][iVar][iR][0]);
                makePretty(histpp[1][iVar][iR][iN]);
                //makePretty(histPbPb[0][iVar][iR][0]);
                //makePretty(histPbPb[1][iVar][iR][iN]);
                
                Double_t max = histpp[1][iVar][0][1]->GetMaximum();
                histpp[1][iVar][iR][iN]->SetMaximum(max+0.03);
                histpp[1][iVar][iR][iN]->GetXaxis()->SetNdivisions(505);
                histpp[1][iVar][iR][iN]->Draw("HIST SAME");
                histpp[0][iVar][iR][0]->Draw("HIST SAME");
                //histPbPb[1][iVar][iR][iN]->Draw("HIST SAME");
                //histPbPb[0][iVar][iR][0]->Draw("HIST SAME");
                
                //histPbPb[0][iVar][iR][0]->SetStats(0);
                //histPbPb[1][iVar][iR][iN]->SetStats(0);
                histpp[0][iVar][iR][0]->SetStats(0);
                histpp[1][iVar][iR][iN]->SetStats(0);
                
            TLegend *t3=new TLegend(0.10,0.75,0.50,0.95);
            t3->SetFillColor(0);
            t3->SetBorderSize(0);
            t3->SetFillStyle(0);
            t3->SetTextFont(43);
            t3->SetTextSize(20);
            //t3->AddEntry(histPbPb[0][iVar][iR][0],"anti k_{T} PbPb MC","l");
            //t3->AddEntry(histPbPb[1][iVar][iR][iN],Form("XCone PbPb MC N=%d",N[iN]),"l");
            t3->AddEntry(histpp[0][iVar][iR][0],"anti k_{T} pp MC","l");
            t3->AddEntry(histpp[1][iVar][iR][iN],Form("XCone pp MC N=%d",N[iN]),"l");
            t3->AddEntry((TObject*)0, Form("R = %d",R[iR]), "");
            t3->Draw("SAME");
        
            
            }
        
        
        
            c2[iVar][iN]->SaveAs(Form("%s%s_N%d.png",label.Data(),stringName[iVar].Data(),iN+2));
            c2[iVar][iN]->SaveAs(Form("%s%s_N%d.pdf",label.Data(),stringName[iVar].Data(),iN+2));
            c2[iVar][iN]->SaveAs(Form("%s%s_N%d.gif",label.Data(),stringName[iVar].Data(),iN+2));
            
        }
        
    }
    
  
    
}





