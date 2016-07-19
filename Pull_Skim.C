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
#include "treeSetup/genChain.C"

#include "fastjet/ClusterSequence.hh"
#include "fastjet/contrib/XConePlugin.hh"

#include "event_pull.h"
#define sign(a) ( ( (a) < 0 )  ?  -1   : ( (a) > 0 ) )




using namespace fastjet;
// using namespace fastjet::contrib;
using namespace std;




void Pull_Skim(TString dataset = "", TString outfname = "", TString mode = "", bool doMatchAK = ){
    TH2D::SetDefaultSumw2(true);
    TH1D::SetDefaultSumw2();
	
    //bool doMatchAK = true;
	float etacut = 2;
    float jetPtMin = 10;
    
    int nR = 3;
    float R[] = {0.3, 0.4, 0.5};
    int radius[nR];
    
    for(int iR = 0; iR < nR; iR++){
        radius[iR] = (int)(10*R[iR]);
    }
    JetDefinition *JetDefAntiKt[nR];
    
    for(int iR = 0; iR < nR; iR++){
        // JetDefAntiKt[iR](antikt_algorithm, R[iR]);
        JetDefAntiKt[iR] = new JetDefinition(antikt_algorithm, R[iR]);
    }
    
    
    
    int nJet = 3; //number of values for n (xcone relevant)
    int NJet[] = {2,3,4};
    
    fastjet::contrib::XConePlugin *plugin[nR][nJet]; //
    JetDefinition *JetDefXCone[nR][nJet];
    
    for(int iR = 0; iR < nR; iR++){
        for ( int iN = 0; iN < nJet; iN++){
            plugin[iR][iN] = new fastjet::contrib::XConePlugin(NJet[iN],R[iR],2);
            JetDefXCone[iR][iN] = new JetDefinition(plugin[iR][iN]);
        }
    }
    
    
    

    TString infname = Form("%s",dataset.Data());
    cout<<"Input file:"<<dataset.Data()<<std::endl;
    
    TString PFcollection = "pfcandAnalyzer";
    if(mode == "PbPbData" || mode == "PbPbMC") PFcollection = "pfcandAnalyzerCS";
    
    bool doGen = true;
    if(mode == "PbPbData" || mode == "ppData") doGen = false;
    
    hiChain   *fhi = new hiChain(infname.Data());
    hltChain   *fhlt = new hltChain(infname.Data());
    skimChain   *fskim = new skimChain(infname.Data());
    // akPu3PF *t = new akPu3PF(infname.Data(),algo);
    pfChainVec * fpf = new pfChainVec(infname.Data(), PFcollection);
	genChain *fgen;
    if(doGen)fgen = new genChain(infname.Data());
    

    int nentries = fpf->GetEntries();
    std::cout<<"nentries = "<<nentries<<std::endl;
    std::cout<<"Outfile: "<<outfname.Data()<<std::endl;
    std::cout<<"Mode: "<<mode.Data()<<std::endl;
    std::cout<<"Matching akt: "<<doMatchAK<<std::endl;
    
    TFile * fnt;
    
    if(doMatchAK){
	    fnt = new TFile(Form("AKmatched+%s",outfname.Data()),"recreate");
    }else{
 	    fnt = new TFile(outfname.Data(),"recreate");
	}
	
	newEvent evnt(doGen);
    
    int nalgo = 2;
    TTree * treeMJ[2][nR][nJet];

    // algo = 0 is anti-Kt , algo = 1 is XCone.
    for(int ialgo = 0; ialgo < 2; ialgo++){
        for(int iR = 0; iR < nR; iR++){
            for (int iN = 0; iN < nJet ; iN++){
                if(ialgo == 0 && iN > 0) continue;
                
                if(ialgo == 0) treeMJ[ialgo][iR][iN] = new TTree(Form("ak%dPF",radius[iR]),"");
                if(ialgo == 1) treeMJ[ialgo][iR][iN] = new TTree(Form("xc_R%d_N%d_PF",radius[iR],NJet[iN]),"");
                treeMJ[ialgo][iR][iN]->Branch("run", &evnt.run, "run/I");
                treeMJ[ialgo][iR][iN]->Branch("lumi", &evnt.lumi, "lumi/I");
                treeMJ[ialgo][iR][iN]->Branch("evt", &evnt.evt, "evt/I");
                treeMJ[ialgo][iR][iN]->Branch("hiBin", &evnt.hiBin, "hiBin/I");
                treeMJ[ialgo][iR][iN]->Branch("pthat", &evnt.pthat, "pthat/F");
                treeMJ[ialgo][iR][iN]->Branch("pt1", &evnt.pt1, "pt1/F");
                treeMJ[ialgo][iR][iN]->Branch("pt2", &evnt.pt2, "pt2/F");
                treeMJ[ialgo][iR][iN]->Branch("pt3", &evnt.pt3, "pt3/F");
                treeMJ[ialgo][iR][iN]->Branch("eta1", &evnt.eta1, "eta1/F");
                treeMJ[ialgo][iR][iN]->Branch("eta2", &evnt.eta2, "eta2/F");
                treeMJ[ialgo][iR][iN]->Branch("eta3", &evnt.eta3, "eta3/F");
                treeMJ[ialgo][iR][iN]->Branch("phi1", &evnt.phi1, "phi1/F");
                treeMJ[ialgo][iR][iN]->Branch("phi2", &evnt.phi2, "phi2/F");
                treeMJ[ialgo][iR][iN]->Branch("phi3", &evnt.phi3, "phi3/F");
                //pull for leading, subleading and third jet.
                treeMJ[ialgo][iR][iN]->Branch("pullEta1", &evnt.pullEta1, "pullEta1/F");
                treeMJ[ialgo][iR][iN]->Branch("pullPhi1", &evnt.pullPhi1, "pullPhi1/F");
                treeMJ[ialgo][iR][iN]->Branch("pullEta2", &evnt.pullEta2, "pullEta2/F");
                treeMJ[ialgo][iR][iN]->Branch("pullPhi2", &evnt.pullPhi2, "pullPhi2/F");
                treeMJ[ialgo][iR][iN]->Branch("pullEta3", &evnt.pullEta3, "pullEta3/F");
                treeMJ[ialgo][iR][iN]->Branch("pullPhi3", &evnt.pullPhi3, "pullPhi3/F");
                
                treeMJ[ialgo][iR][iN]->Branch("phi1", &evnt.phi1, "phi1/F");
                treeMJ[ialgo][iR][iN]->Branch("phi2", &evnt.phi2, "phi2/F");
                treeMJ[ialgo][iR][iN]->Branch("phi3", &evnt.phi3, "phi3/F");
                
                

                if(mode == "ppMC" || mode == "PbPbMC"){
                    treeMJ[ialgo][iR][iN]->Branch("refPt1", &evnt.refPt1, "refPt1/F");
                    treeMJ[ialgo][iR][iN]->Branch("refPt2", &evnt.refPt2, "refPt2/F");
                    treeMJ[ialgo][iR][iN]->Branch("refPt3", &evnt.refPt3, "refPt3/F");
                    treeMJ[ialgo][iR][iN]->Branch("refEta1", &evnt.refEta1, "refEta1/F");
                    treeMJ[ialgo][iR][iN]->Branch("refEta2", &evnt.refEta2, "refEta2/F");
                    treeMJ[ialgo][iR][iN]->Branch("refEta3", &evnt.refEta3, "refEta3/F");
                    treeMJ[ialgo][iR][iN]->Branch("refPhi1", &evnt.refPhi1, "refPhi1/F");
                    treeMJ[ialgo][iR][iN]->Branch("refPhi2", &evnt.refPhi2, "refPhi2/F");
                    treeMJ[ialgo][iR][iN]->Branch("refPhi3", &evnt.refPhi3, "refPhi3/F");
					//pull
                    treeMJ[ialgo][iR][iN]->Branch("refPullEta1", &evnt.refPullEta1, "refPullEta1/F");
                    treeMJ[ialgo][iR][iN]->Branch("refPullPhi1", &evnt.refPullPhi1, "refPullPhi1/F");
                    treeMJ[ialgo][iR][iN]->Branch("refPullEta2", &evnt.refPullEta2, "refPullEta2/F");
                    treeMJ[ialgo][iR][iN]->Branch("refPullPhi2", &evnt.refPullPhi2, "refPullPhi2/F");
                    treeMJ[ialgo][iR][iN]->Branch("refPullEta3", &evnt.refPullEta3, "refPullEta3/F");
                    treeMJ[ialgo][iR][iN]->Branch("refPullPhi3", &evnt.refPullPhi3, "refPullPhi3/F");
					
                    if(doGen){
                        treeMJ[ialgo][iR][iN]->Branch("genPt1", &evnt.genPt1, "genPt1/F");
                        treeMJ[ialgo][iR][iN]->Branch("genPt2", &evnt.genPt2, "genPt2/F");
                        treeMJ[ialgo][iR][iN]->Branch("genPt3", &evnt.genPt3, "genPt3/F");
                        treeMJ[ialgo][iR][iN]->Branch("genEta1", &evnt.genEta1, "genEta1/F");
                        treeMJ[ialgo][iR][iN]->Branch("genEta2", &evnt.genEta2, "genEta2/F");
                        treeMJ[ialgo][iR][iN]->Branch("genEta3", &evnt.genEta3, "genEta3/F");
                        treeMJ[ialgo][iR][iN]->Branch("genPhi1", &evnt.genPhi1, "genPhi1/F");
                        treeMJ[ialgo][iR][iN]->Branch("genPhi2", &evnt.genPhi2, "genPhi2/F");
                        treeMJ[ialgo][iR][iN]->Branch("genPhi3", &evnt.genPhi3, "genPhi3/F");
                        //pull
                        treeMJ[ialgo][iR][iN]->Branch("genPullEta1", &evnt.genPullEta1, "genPullEta1/F");
                        treeMJ[ialgo][iR][iN]->Branch("genPullPhi1", &evnt.genPullPhi1, "genPullPhi1/F");
                        treeMJ[ialgo][iR][iN]->Branch("genPullEta2", &evnt.genPullEta2, "genPullEta2/F");
                        treeMJ[ialgo][iR][iN]->Branch("genPullPhi2", &evnt.genPullPhi2, "genPullPhi2/F");
                        treeMJ[ialgo][iR][iN]->Branch("genPullEta3", &evnt.genPullEta3, "genPullEta3/F");
                        treeMJ[ialgo][iR][iN]->Branch("genPullPhi3", &evnt.genPullPhi3, "genPullPhi3/F");

                        
                    }
                }
                treeMJ[ialgo][iR][iN]->Branch("nref", &evnt.nref, "nref/I");
                treeMJ[ialgo][iR][iN]->Branch("rawPt", evnt.rawPt, "rawPt[nref]/F");
                treeMJ[ialgo][iR][iN]->Branch("rawPhi", evnt.rawPhi, "rawPhi[nref]/F");
                treeMJ[ialgo][iR][iN]->Branch("rawEta", evnt.rawEta, "rawEta[nref]/F");
                //Pull
                treeMJ[ialgo][iR][iN]->Branch("pullEta", evnt.pullEta, "pullEta[nref]/F");
                treeMJ[ialgo][iR][iN]->Branch("pullPhi", evnt.pullPhi, "pullPhi[nref]/F");
                
                if(mode == "ppMC" || mode == "PbPbMC"){
                    treeMJ[ialgo][iR][iN]->Branch("refPt", evnt.refPt, "refPt[nref]/F");
                    treeMJ[ialgo][iR][iN]->Branch("refPhi", evnt.refPhi, "refPhi[nref]/F");
                    treeMJ[ialgo][iR][iN]->Branch("refEta", evnt.refEta, "refEta[nref]/F");
                    //pull
                    treeMJ[ialgo][iR][iN]->Branch("refPullEta", evnt.refPullEta, "pullEta[nref]/F");
                    treeMJ[ialgo][iR][iN]->Branch("refPullPhi", evnt.refPullPhi, "pullPhi[nref]/F");
                    
                    if(doGen){
                        treeMJ[ialgo][iR][iN]->Branch("ngen", &evnt.ngen, "ngen/I");
                        treeMJ[ialgo][iR][iN]->Branch("genPt", evnt.genPt, "genPt[ngen]/F");
                        treeMJ[ialgo][iR][iN]->Branch("genPhi", evnt.genPhi, "genPhi[ngen]/F");
                        treeMJ[ialgo][iR][iN]->Branch("genEta", evnt.genEta, "genEta[ngen]/F");
                        //pull
                        treeMJ[ialgo][iR][iN]->Branch("genPullEta", evnt.genPullEta, "genPullEta[ngen]/F");
                        treeMJ[ialgo][iR][iN]->Branch("genPullPhi", evnt.genPullPhi, "genPullPhi[ngen]/F");
                        
                    }
                }
            }
        }
    }
    
    for (Long64_t jentry = 0; jentry < nentries; jentry++) {

    // for (Long64_t jentry = 0; jentry < 10; jentry++) {
        
        if(nentries%1000 == jentry)cout << jentry << endl;
     
        fhi->GetEntry(jentry);
        fhlt->GetEntry(jentry);
        fskim->GetEntry(jentry);
        fpf->GetEntry(jentry);

        if(doGen) fgen->GetEntry(jentry);
        
        if((mode == "ppData" || mode == "ppMC") && !(fskim->HBHENoiseFilterResultRun2Loose && fskim->pPAprimaryVertexFilter && fabs(fhi->vz)<15 && fskim->pBeamScrapingFilter)) continue;
        
        if((mode == "PbPbData") && !(fhlt->HLT_HIPuAK4CaloJet80_Eta5p1_v1 && fskim->pprimaryVertexFilter && fskim->pclusterCompatibilityFilter && fskim->pcollisionEventSelection && fskim->HBHENoiseFilterResultRun2Loose)) continue;
        if((mode == "PbPbMC") && !(fskim->pprimaryVertexFilter && fskim->pclusterCompatibilityFilter && fskim->pcollisionEventSelection && fskim->HBHENoiseFilterResultRun2Loose)) continue;
        
        
        vector<PseudoJet> fjPFjets[nalgo][nR][nJet];
        vector<PseudoJet> fjGenJets[nalgo][nR][nJet];

        // Cluster Secuence
        ClusterSequence *csPFAK[nalgo][nR][nJet];
        ClusterSequence *csPFXCone[nalgo][nR][nJet];
        ClusterSequence *csGenAK[nalgo][nR][nJet];
        ClusterSequence *csGenXCone[nalgo][nR][nJet];
        
        //cluster PF candidates
        vector<PseudoJet> particlespf;
        for(int ipart = 0; ipart < fpf->nPFpart; ipart++){
            //cout << "Ipart loop: "<<ipart<<"of "<<fpf->nPFpart<<endl;
            // cout << ipart << endl;
            float pt = fpf->pfPt->at(ipart);
            if(pt<=0.5) continue;
            float eta = fpf->pfEta->at(ipart);
            if(fabs(eta) > etacut) continue;
            float phi = fpf->pfPhi->at(ipart);
            float px = pt*cos(phi);
            float py = pt*sin(phi);
            float pz = pt*sinh(eta);
            float E = pt*cosh(eta);
            fastjet::PseudoJet Particle(px,py,pz,E);
            particlespf.push_back(Particle);
        }
        
        if(particlespf.size()>0){
            for(int iR = 0; iR < nR; iR++){
                csPFAK[0][iR][0] = new ClusterSequence (particlespf, *JetDefAntiKt[iR]);
                fjPFjets[0][iR][0] = sorted_by_pt(csPFAK[0][iR][0]->inclusive_jets());
                //cout<<"Sorting for ak"<<endl;
                for (int iN = 0; iN < nJet ; iN++){
                    //cout<<"Sorting for xcone"<<endl;
                    csPFXCone[1][iR][iN] = new ClusterSequence(particlespf, *JetDefXCone[iR][iN]);
                    fjPFjets[1][iR][iN] = sorted_by_pt(csPFXCone[1][iR][iN]->inclusive_jets());
                    
                }
            }
        }
        particlespf.clear();
                
        if(doGen){
            //!cluster gen particles from signal
            vector<PseudoJet> particles;
            for(int ipart = 0; ipart < fgen->mult; ipart++){
                //cout << "Ipart loop: "<<ipart<<"of "<<fpf->nPFpart<<endl;
                // cout << ipart << endl;
                if(fgen->sube->at(ipart) != 0) continue;
                float pt = fgen->pt->at(ipart);
                if(pt<=0) continue;
                float eta = fgen->eta->at(ipart);
                if(fabs(eta) > etacut) continue;
                float phi = fgen->phi->at(ipart);
                float px = pt*cos(phi);
                float py = pt*sin(phi);
                float pz = pt*sinh(eta);
                float E = pt*cosh(eta);
                
                // cout << ipart << endl;
                fastjet::PseudoJet Particle(px,py,pz,E);
                particles.push_back(Particle);
            }
            if(particles.size()>0){
                for(int iR = 0; iR < nR; iR++){
                    //! Clustering for gen particles.
                    csGenAK[0][iR][0] = new ClusterSequence(particles, *JetDefAntiKt[iR]);
                    fjGenJets[0][iR][0] = sorted_by_pt(csGenAK[0][iR][0]->inclusive_jets());
                    //cout<<"Sorting for ak"<<endl;
                    for (int iN = 0; iN < nJet ; iN++){
                        //cout<<"Sorting for xcone"<<endl;
                        csGenXCone[1][iR][iN] = new ClusterSequence(particles, *JetDefXCone[iR][iN]);
                        fjGenJets[1][iR][iN] = sorted_by_pt(csGenXCone[1][iR][iN]->inclusive_jets());
                        
                    }
                }
            }
            particles.clear();
            
        }
        
        int njet[nalgo][nR][nJet];
        vector<Jet> jets[nalgo][nR][nJet];
        vector<Jet> genjets[nalgo][nR][nJet];
        
        for(int ialgo = 0; ialgo < 2; ialgo++){
            for(int iR = 0; iR < nR; iR++){
                for(int iN = 0; iN < nJet ; iN++){
                    if(ialgo == 0 && iN > 0) continue; //!anti-kt has no jet number setting
                    njet[ialgo][iR][iN] = 0;
					
					//! For MC calculate gen-level values, done first so the matching with reco can be done
                    if(doGen){
                        for(unsigned int ijet = 0;  ijet < fjGenJets[ialgo][iR][iN].size(); ijet++){ //!loop over gen jets
                            
                            float genEta = fjGenJets[ialgo][iR][iN][ijet].eta();
                            float genPhi = fjGenJets[ialgo][iR][iN][ijet].phi();
                            float genPt = fjGenJets[ialgo][iR][iN][ijet].perp();
                            if(fabs(genEta + R[iR]) > etacut) continue;

                            //////////
                            
                            float genPullEta = 0 ;
                            float genPullPhi = 0 ;
                            float genratio_i = 0 ;
                            
                            vector<PseudoJet> jGenConstituents = fjGenJets[ialgo][iR][iN][ijet].constituents();
                            
                            for (unsigned jConst = 0; jConst< jGenConstituents.size(); jConst++){ //!load pf constituents of the jet. Here we sum over the pull value for each particle constituent
                                genratio_i = w_ratio_i(genEta,genPhi,genPt,jGenConstituents[jConst].eta(),jGenConstituents[jConst].phi(),jGenConstituents[jConst].pt());
                                genPullEta += genratio_i*(jGenConstituents[jConst].eta()-genEta);
                                genPullPhi += genratio_i*(deltaPhi(jGenConstituents[jConst].phi(),genPhi));
                            }
                            Jet genjet(genPt, genEta, genPhi, genPullEta,genPullPhi);
                            genjets[ialgo][iR][iN].push_back(genjet);
                        }
                    }
			     }
		     }
         }			 
			
         for(int ialgo = 0; ialgo < 2; ialgo++){
            for(int iR = 0; iR < nR; iR++){
                for(int iN = 0; iN < nJet ; iN++){
                    if(ialgo == 0 && iN > 0) continue; //!anti-kt has no jet number setting		
                    for(unsigned int ijet = 0;  ijet < fjPFjets[ialgo][iR][iN].size(); ijet++){ //!loop over reco jets
                        float jtPt = fjPFjets[ialgo][iR][iN][ijet].perp();
                       
  					    if(jtPt < jetPtMin) continue;
                        float jtPhi = fjPFjets[ialgo][iR][iN][ijet].phi();
                        float jtEta = fjPFjets[ialgo][iR][iN][ijet].eta();
                        if(fabs(jtEta + R[iR]) > etacut) continue;

                        float jtPullEta = 0; //!initiaize first coordinate of the pull vector for the i-jet.
                        float jtPullPhi = 0; //!initiaize second coordinate of the pull vector for the i-jet.
                        float ratio_i = 0;
                        vector<PseudoJet> jPFConstituents = fjPFjets[ialgo][iR][iN][ijet].constituents();
                        for (unsigned jConst = 0; jConst< jPFConstituents.size(); jConst++){ //!load pf constituents of the jet. Here we sum over the pull value for each particle constituent
                            ratio_i = w_ratio_i(jtEta,jtPhi,jtPt,jPFConstituents[jConst].eta(),jPFConstituents[jConst].phi(),jPFConstituents[jConst].pt());
                            jtPullEta += ratio_i*(jPFConstituents[jConst].eta()-jtEta);
                            jtPullPhi += ratio_i*(deltaPhi(jPFConstituents[jConst].phi(),jtPhi));
                        }
                        
                        float refPt, refEta, refPhi, refPullPhi, refPullEta;
                        refPt = refEta = refPhi = -99;
                        refPullPhi = refPullEta = -99;
						bool hasRef = false;
						int refIndex = -99;
                        if(doGen){ //! reco to gen matchin
						    if(doMatchAK && ialgo > 0){
  							    for(unsigned int igen = 0; igen < genjets[0][iR][0].size(); igen++){
							        float matchEta = genjets[0][iR][0][igen].eta;
						            float matchPhi = genjets[0][iR][0][igen].phi;
									bool matched = genjets[0][iR][0][igen].matched;
									if(deltaR(jtEta, jtPhi, matchEta, matchPhi) < R[iR] && !matched){
									   refIndex = igen;
									   refEta = matchEta; 
									   refPhi = matchPhi; 
									   refPt = genjets[0][iR][0][igen].pt;
									   refPullEta = genjets[0][iR][0][igen].pullEta;
									   refPullPhi = genjets[0][iR][0][igen].pullPhi;
									   genjets[0][iR][0][igen].matched = true;
									   hasRef = true;
									   break;
								   }
								}						
							}
							else{
								for(unsigned int igen = 0; igen < genjets[ialgo][iR][iN].size(); igen++){
								   float matchEta = genjets[ialgo][iR][iN][igen].eta;
								   float matchPhi = genjets[ialgo][iR][iN][igen].phi;
								   bool matched = genjets[ialgo][iR][iN][igen].matched;
								   if(deltaR(jtEta, jtPhi, matchEta, matchPhi) < R[iR] && !matched){
									   refIndex = igen;
									   refEta = matchEta; 
									   refPhi = matchPhi; 
									   refPt = genjets[ialgo][iR][iN][igen].pt;
									   refPullEta = genjets[ialgo][iR][iN][igen].pullEta;
									   refPullPhi = genjets[ialgo][iR][iN][igen].pullPhi;
									   genjets[ialgo][iR][iN][igen].matched = true;
									   hasRef = true;
									   break;
								   }
								}
							}
							
                        }
                        Jet jet(jtPt, jtEta, jtPhi, jtPullEta, jtPullPhi, hasRef, refPt, refEta, refPhi, refPullEta, refPullPhi, refIndex);
                        jets[ialgo][iR][iN].push_back(jet);
                        njet[ialgo][iR][iN]++;
                    }
					
					if(doMatchAK){//!after one algo is done the matched bool needs to be set to false for AK
					//!jets as they are going to be reused
					    for(unsigned int igen = 0; igen < genjets[ialgo][iR][iN].size(); igen++){
						    genjets[0][iR][0][igen].matched = false;
					    }
					}
					
                    if(doGen){ //!gen to reco matching
                    // if(0){ //!gen to reco matching
					    for(unsigned int igen = 0; igen < genjets[ialgo][iR][iN].size(); igen++){
						    float genEta = genjets[ialgo][iR][iN][igen].eta;
						    float genPhi = genjets[ialgo][iR][iN][igen].phi;
						    float genPt = genjets[ialgo][iR][iN][igen].pt;
						    bool recoGenMatched = genjets[ialgo][iR][iN][igen].matched;
							if(recoGenMatched){
							     for(unsigned int ijet = 0;  ijet < jets[ialgo][iR][iN].size(); ijet++){ //!loop over reco jets
						            float jtEta = jets[ialgo][iR][iN][ijet].eta;
						            float jtPhi = jets[ialgo][iR][iN][ijet].phi;
						            float jtPt = jets[ialgo][iR][iN][ijet].phi;
						            float refEta = jets[ialgo][iR][iN][ijet].refEta;
						            float refPhi = jets[ialgo][iR][iN][ijet].refPhi;
						            float refPt = jets[ialgo][iR][iN][ijet].refPt;
								    if(deltaR(jtEta, jtPhi, genEta, genPhi) < R[iR]){
									   if(((int)igen)!=jets[ialgo][iR][iN][ijet].refIndex){
									       if(deltaR(jtEta, jtPhi, genEta, genPhi) < deltaR(jtEta, jtPhi, refEta, refPhi) && fabs(jtPt-genPt) < fabs(jtPt-refPt)){
									           jets[ialgo][iR][iN][ijet].refEta = genEta;
									           jets[ialgo][iR][iN][ijet].refPhi = genPhi; 
									           jets[ialgo][iR][iN][ijet].refPt = genPt;
									           jets[ialgo][iR][iN][ijet].refPullPhi = genjets[ialgo][iR][iN][igen].pullPhi;
									           jets[ialgo][iR][iN][ijet].refPullEta = genjets[ialgo][iR][iN][igen].pullEta;
										   }
									   }
								       break;
							        }
							    }
							}
					    }			
					
					}
                }
            }
        }

        for(int iR = 0; iR < nR; iR++){
            if(njet[0][iR][0] > 0) evnt.setEvent((int)fhi->run, (int)fhi->lumi, (int)fhi->evt, (int)fhi->hiBin, &jets[0][iR][0], &genjets[0][iR][0]);
            treeMJ[0][iR][0]->Fill();
            // std::cout<<"Filling akt trees"<<std::endl;
            evnt.reset();
            for (int iN = 0; iN < nJet ; iN ++){
                if(njet[1][iR][iN] > 0) evnt.setEvent((int)fhi->run, (int)fhi->lumi, (int)fhi->evt, (int)fhi->hiBin, &jets[1][iR][iN], &genjets[1][iR][iN]);
                treeMJ[1][iR][iN]->Fill();
                // std::cout<<"Filling xcone trees"<<std::endl;
                evnt.reset();
            }
        }
        for(int iR = 0; iR < nR; iR++){
            delete csPFAK[0][iR][0];
            for (int iN = 0; iN < nJet ; iN++){
                delete csPFXCone[1][iR][iN];
                
            }
        }
    } 
    
    fnt->cd();
    
    for(int iR = 0; iR < nR; iR++){
        treeMJ[0][iR][0]->Write();
        std::cout<<"Writing akt trees"<<std::endl;
        for (int iN = 0; iN < nJet ; iN ++){
            treeMJ[1][iR][iN]->Write();
            std::cout<<"Writing xcone trees"<<std::endl;
        }
    }
    fnt->Close();
    std::cout<<"Closing file"<<std::endl;
}

 



int main(int argc, char *argv[])
{
    Pull_Skim(argv[1],argv[2],argv[3]);
    return 0;
}









