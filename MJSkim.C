#include <iostream>
#include <vector>
#include <algorithm>

#include "TCanvas.h"
#include "TString.h"
#include "TH1F.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TCanvas.h"
#include "TNtuple.h"
#include "TF1.h"


#include "treeSetup/skimChain.C"
#include "treeSetup/hiChain.C"
#include "treeSetup/hltChain.C"
#include "treeSetup/pfChainVec.C"
// #include "treeSetup/genChain.C"

#include "fastjet/ClusterSequence.hh"
#include "fastjet/contrib/XConePlugin.hh"

#include "event.h"

using namespace fastjet; 
// using namespace fastjet::contrib; 
using namespace std; 


void MJSkim(TString dataset = "/mnt/hadoop/cms/store/user/abaty/transferTargetDirectories/2015pp_MinBias_2/", TString outfname = "test.root"){ 
    TH2D::SetDefaultSumw2(true);
    TH1D::SetDefaultSumw2();
    TString mode = "PbPbData";
    
    int nR = 3;
    float R[] = {0.3, 0.4, 0.5};
    int radius[nR];
    
    for(int iR = 0; iR < nR; iR++){
        radius[iR] = (int)(10*R[iR]);
    }
    JetDefinition *jet_def_antikt[nR];
 
    for(int iR = 0; iR < nR; iR++){
  // jet_def_antikt[iR](antikt_algorithm, R[iR]);
        jet_def_antikt[iR] = new JetDefinition(antikt_algorithm, R[iR]);
    }
 
    int nJet = 3; //Three values for n
    int NJet[] = {3, 4, 5};
 
    fastjet::contrib::XConePlugin *plugin[nR][nJet]; //?
    JetDefinition *jet_def_xcone[nR][nJet];
 
    for(int iR = 0; iR < nR; iR++){
        for ( int iN = 0; iN < nJet; iN++){
            plugin[iR][iN] = new fastjet::contrib::XConePlugin(NJet[iN],R[iR],2);
            jet_def_xcone[iR][nJet] = new JetDefinition(plugin[iR][iN]);
        }
    }
   
    float etacut = 2;
    // TString algo=Form("ak%dPF",radius[iR]);
 
    TString infname = Form("%s",dataset.Data());

    hiChain   *fhi = new hiChain(infname.Data());
    hltChain   *fhlt = new hltChain(infname.Data());
    skimChain   *fskim = new skimChain(infname.Data());
    // akPu3PF *t = new akPu3PF(infname.Data(),algo);
    pfChainVec * fpf = new pfChainVec(infname.Data());
    // genChain * fgen = new genChain(infname.Data());

    int nentries = fpf->GetEntries();
    std::cout<<"nentries = "<<nentries<<std::endl;


    TFile * fnt = new TFile(outfname.Data(),"recreate");
    newEvent evnt;
 
    int nalgo = 2;
    
    TTree * treeMJ[2][nR][nJet];
    
    // algo = 0 is anti-Kt , algo = 1 is XCone.
    for(int iR = 0; iR < nR; iR++){
        
        treeMJ[0][iR][0] = new TTree(Form("ak%dPF",radius[iR]),"");
        
        for (int iN = 0; iN < nJet ; iN++){
            
            treeMJ[1][iR][iN] = new TTree(Form("xc_R%d_N%d_PF",radius[iR],NJet[iN]),"");
            
            // here there was a for loop over ialgo = 0 , 1 but iN only goes for ialgo = 1
            treeMJ[1][iR][iN]->Branch("run", &evnt.run, "run/I");
            treeMJ[1][iR][iN]->Branch("lumi", &evnt.lumi, "lumi/I");
            treeMJ[1][iR][iN]->Branch("evt", &evnt.evt, "evt/I");
            treeMJ[1][iR][iN]->Branch("hiBin", &evnt.hiBin, "hiBin/I");
            treeMJ[1][iR][iN]->Branch("pthat", &evnt.pthat, "pthat/F");
            treeMJ[1][iR][iN]->Branch("pt1", &evnt.pt1, "pt1/F");
            treeMJ[1][iR][iN]->Branch("pt2", &evnt.pt2, "pt2/F");
            treeMJ[1][iR][iN]->Branch("pt3", &evnt.pt3, "pt3/F");
            treeMJ[1][iR][iN]->Branch("eta1", &evnt.eta1, "eta1/F");
            treeMJ[1][iR][iN]->Branch("eta2", &evnt.eta2, "eta2/F");
            treeMJ[1][iR][iN]->Branch("eta3", &evnt.eta3, "eta3/F");
            treeMJ[1][iR][iN]->Branch("phi1", &evnt.phi1, "phi1/F");
            treeMJ[1][iR][iN]->Branch("phi2", &evnt.phi2, "phi2/F");
            treeMJ[1][iR][iN]->Branch("phi3", &evnt.phi3, "phi3/F");
            treeMJ[1][iR][iN]->Branch("nref", &evnt.nref, "nref/I");
            treeMJ[1][iR][iN]->Branch("rawpt", evnt.rawpt, "rawpt[nref]/F");
            treeMJ[1][iR][iN]->Branch("rawphi", evnt.rawphi, "rawphi[nref]/F");
            treeMJ[1][iR][iN]->Branch("raweta", evnt.raweta, "raweta[nref]/F");
        }

    }
        
    
    for (Long64_t jentry=0; jentry<nentries;jentry++) {

        if(nentries%1000==jentry)cout << jentry << endl;
        cout << jentry << endl;
  
        // t->GetEntry(jentry);
        fhi->GetEntry(jentry);
        fhlt->GetEntry(jentry);
        fskim->GetEntry(jentry);
        fpf->GetEntry(jentry);
        // fgen->GetEntry(jentry);

        // if(!(fskim->pHBHENoiseFilter && fskim->pPAcollisionEventSelectionPA && fabs(fhi->vz)<15 && fskim->pVertexFilterCutGplus && fskim->pprimaryvertexFilter)) continue;

        if(!(fskim->HBHENoiseFilterResultRun2Loose && fskim->pPAprimaryVertexFilter && fabs(fhi->vz)<15 && fskim->pBeamScrapingFilter)) continue;
        
        if(mode == "PbPbData" && !fhlt->HLT_HIPuAk4CaloJet80_Eta5p1_v1) continue;
        
        vector<PseudoJet> fjpfjets[2][nR][nJet];
  
        int nparticlefj = 0;
  
        vector<PseudoJet> particlespf;
  
        for(int ipart = 0; ipart < fpf->nPFpart; ipart++){
  
            // cout << ipart << endl;
            float pt = fpf->pfPt->at(ipart);
            if(pt<=0) continue;
            float eta = fpf->pfEta->at(ipart);
            if(fabs(eta) > 3) continue;
            float phi = fpf->pfPhi->at(ipart);
            float px = pt*cos(phi);
            float py = pt*sin(phi);
            float pz = pt*sinh(eta);
            float E = pt*cosh(eta);
            fastjet::PseudoJet Particle(px,py,pz,E);
            particlespf.push_back(Particle);
            nparticlefj++;
        }
  
        if(nparticlefj>0){
            for(int iR = 0; iR < nR; iR++){
                for(int ialgo = 0; ialgo < nalgo; ialgo++){
                    ClusterSequence cspf_ak(particlespf, *jet_def_antikt[iR]);
                    fjpfjets[0][iR][0] = sorted_by_pt(cspf_ak.inclusive_jets());
                    
                    for (int iN = 0; iN < nJet ; iN++){
                        ClusterSequence cspf_xcone(particlespf, *jet_def_xcone[iR][iN]);
                        fjpfjets[1][iR][iN] = sorted_by_pt(cspf_xcone.inclusive_jets());
                    }
                }
            }
        }
        particlespf.clear();
  
        int njet[nalgo][nR][nJet];
        vector<Jet> jets[nalgo][nR][nJet];
  
        for(int iR = 0; iR < nR; iR++){
            njet[0][iR][0] = 0;
            for(unsigned int ijet = 0;  ijet < fjpfjets[0][iR][0].size(); ijet++){
                float jtpt = fjpfjets[0][iR][0][ijet].perp();
                if(jtpt<5) continue;
                float jtphi = fjpfjets[0][iR][0][ijet].phi();
                float jteta = fjpfjets[0][iR][0][ijet].eta();
                if(fabs(jteta)>etacut) continue;
                Jet jet(jtpt, jteta, jtphi);
                jets[0][iR][0].push_back(jet);
                njet[0][iR][0]++;
            }
        }
        
        for(int iR = 0; iR < nR; iR++){
            for(int iN = 0; iN < nJet ; iN++){
                njet[1][iR][iN] = 0;
                for(unsigned int ijet = 0;  ijet < fjpfjets[1][iR][iN].size(); ijet++){
                    float jtpt = fjpfjets[1][iR][iN][ijet].perp();
                    if(jtpt<5) continue;
                    float jtphi = fjpfjets[1][iR][iN][ijet].phi();
                    float jteta = fjpfjets[1][iR][iN][ijet].eta();
                    if(fabs(jteta)>etacut) continue;
                    Jet jet(jtpt, jteta, jtphi);
                    jets[1][iR][iN].push_back(jet);
                    njet[1][iR][iN]++;
                }
            }
        }
  
        for(int iR = 0; iR < nR; iR++){
            if(njet[0][iR][0] > 0) evnt.setEvent((int)fhi->run, (int)fhi->lumi, (int)fhi->evt, (int)fhi->hiBin, &jets[0][iR][0]);
                treeMJ[0][iR][0]->Fill();
                evnt.reset();
            for (int iN = 0; iN < nJet ; iN ++){
                if(njet[1][iR][iN] > 0) evnt.setEvent((int)fhi->run, (int)fhi->lumi, (int)fhi->evt, (int)fhi->hiBin, &jets[1][iR][iN]);
                treeMJ[0][iR][iN]->Fill();
                evnt.reset();
            }
        }
 
    }

    fnt->cd();
    
    for(int iR = 0; iR < nR; iR++){
        treeMJ[0][iR][0]->Write();
        for (int iN = 0; iN < nJet ; iN ++){
            treeMJ[1][iR][iN]->Write();
        }
    }
    fnt->Close();
}


int main(int argc, char *argv[])
{ 
  MJSkim(argv[1],argv[3]);
  return 0;
}
