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
#include "TMath.h"
#include "TNtuple.h"
#include "TF1.h"


#include "treeSetup/skimChain.C"
#include "treeSetup/hiChain.C"
#include "treeSetup/hltChain.C"
#include "treeSetup/pfChainVec.C"
#include "treeSetup/genChain.C"
#include "treeSetup/jetChain.C"

#include "fastjet/ClusterSequence.hh"
#include "fastjet/contrib/XConePlugin.hh"

#include "DogaL2L3.h"
#include "event_pull.h"
#define sign(a) ( ( (a) < 0 )  ?  -1   : ( (a) > 0 ) )




using namespace fastjet;
// using namespace fastjet::contrib;
using namespace std;




void Pull_Skim(TString dataset = "", TString outfname = "", TString mode = "", bool doMatchAK = false){
    TH2D::SetDefaultSumw2(true);
    TH1D::SetDefaultSumw2();
	
    //cout<<"string match: "<<doMatchAK<<endl;
    DogaL2L3 * L2L3 = new DogaL2L3(4, (int)3);

	//temporary
	float etacut = 2;
    float jetPtMin = 10; 
    float PFPtCut = 1.0;
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
    //cout<<"Input file:"<<dataset.Data()<<std::endl;
    
    TString PFcollection = "pfcandAnalyzer";
    if(mode == "PbPbData" || mode == "PbPbMC") PFcollection = "pfcandAnalyzerCS";
    
    bool doGen = true;
    if(mode == "PbPbData" || mode == "ppData") doGen = false;
    
    hiChain   *fhi = new hiChain(infname.Data());
    hltChain   *fhlt = new hltChain(infname.Data());
    skimChain   *fskim = new skimChain(infname.Data());
    // akPu3PF *t = new akPu3PF(infname.Data(),algo);
    pfChainVec * fpf = new pfChainVec(infname.Data(), PFcollection);
    jetChain * fjet = new jetChain(infname.Data(), "ak3PF");
	genChain *fgen;
    if(doGen)fgen = new genChain(infname.Data());
    

    int nentries = fpf->GetEntries();
    std::cout<<"nentries = "<<nentries<<std::endl;
    std::cout<<"Outfile: "<<outfname.Data()<<std::endl;
    std::cout<<"Mode: "<<mode.Data()<<std::endl;
    std::cout<<"Matching akt: "<<doMatchAK<<std::endl;
    
    TFile * fnt;
    
    
 	    fnt = new TFile(outfname.Data(),"recreate");
	
	
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
       
                treeMJ[ialgo][iR][iN]->Branch("nref", &evnt.nref, "nref/I");
                treeMJ[ialgo][iR][iN]->Branch("rawPt", evnt.rawPt, "rawPt[nref]/F");
				
                treeMJ[ialgo][iR][iN]->Branch("jtPt", evnt.jtPt, "jtPt[nref]/F");
                treeMJ[ialgo][iR][iN]->Branch("jtPhi", evnt.jtPhi, "jtPhi[nref]/F");
                treeMJ[ialgo][iR][iN]->Branch("jtEta", evnt.jtEta, "jtEta[nref]/F");
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
    cout << "before event loop" << endl;
    for (Long64_t jentry = 0; jentry < nentries; jentry++) {

    // for (Long64_t jentry = 0; jentry < 10; jentry++) {
        
        // if(nentries%1000 == jentry)cout << jentry << endl;
        cout << "jentry:" << jentry << endl;
     
        fhi->GetEntry(jentry);
        cout << "fhlt" << endl;
		fhlt->GetEntry(jentry);
        cout << "fskim" << endl;
        fskim->GetEntry(jentry);
        cout << "fpf" << endl;
        fpf->GetEntry(jentry);
        cout << "fjet" << endl;
        fjet->GetEntry(jentry);

        if(doGen) fgen->GetEntry(jentry);
        
        if((mode == "ppData" || mode == "ppMC") && !(fskim->HBHENoiseFilterResultRun2Loose && fskim->pPAprimaryVertexFilter && fabs(fhi->vz)<15 && fskim->pBeamScrapingFilter)) continue;
        
        if((mode == "PbPbData") && !(fhlt->HLT_HIPuAK4CaloJet80_Eta5p1_v1 && fskim->pprimaryVertexFilter && fskim->pclusterCompatibilityFilter && fskim->pcollisionEventSelection && fskim->HBHENoiseFilterResultRun2Loose)) continue;
        if((mode == "PbPbMC") && !(fskim->pprimaryVertexFilter && fskim->pclusterCompatibilityFilter && fskim->pcollisionEventSelection && fskim->HBHENoiseFilterResultRun2Loose)) continue;
        
        float evt = (int)fhi->evt;
		// if(evt > 93624) break;
        vector<PseudoJet> fjPFjets[nalgo][nR][nJet];
        vector<PseudoJet> fjGenJets[nalgo][nR][nJet];

        // Cluster Secuence
        ClusterSequence *csPFAK[nalgo][nR][nJet];
        ClusterSequence *csPFXCone[nalgo][nR][nJet];
        ClusterSequence *csGenAK[nalgo][nR][nJet];
        ClusterSequence *csGenXCone[nalgo][nR][nJet];
        cout << 1 << endl;
        //cluster PF candidates
        vector<PseudoJet> particlespf;
        for(int ipart = 0; ipart < fpf->nPFpart; ipart++){
            //cout << "Ipart loop: "<<ipart<<"of "<<fpf->nPFpart<<endl;
            // //cout << ipart << endl;
            float pt = fpf->pfPt->at(ipart);
            if((mode == "PbPbData" || mode == "PbPbMC") && pt <= PFPtCut) continue;
            // if((mode == "ppData" || mode == "ppMC") && pt <= 0.1) continue;
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
        cout << 2 << endl;
 
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
        cout << 3 << endl;

        vector<PseudoJet> particles;
        if(doGen){
            //!cluster gen particles from signal
            for(int ipart = 0; ipart < fgen->mult; ipart++){
                //cout << "Ipart loop: "<<ipart<<"of "<<fpf->nPFpart<<endl;
                // //cout << ipart << endl;
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
                
                // //cout << ipart << endl;
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
        cout << 4 << endl;
       
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
							    float constitPhi = jGenConstituents[jConst].phi();
							    float constitEta = jGenConstituents[jConst].eta();
							    float constitPt = jGenConstituents[jConst].pt();

                                genratio_i = w_ratio_i(genEta, genPhi, genPt, constitEta, constitPhi, constitPt);
                                genPullEta += genratio_i*(constitEta-genEta);
                                genPullPhi += genratio_i*(deltaPhi(constitPhi,genPhi));
                            }
                            Jet genjet(genPt, genEta, genPhi, genPullEta,genPullPhi);
                            genjets[ialgo][iR][iN].push_back(genjet);
                        }
                    }
			     }
		     }
         }			 
			
        cout << 5 << endl;
       
         for(int ialgo = 0; ialgo < 2; ialgo++){
            for(int iR = 0; iR < nR; iR++){
                for(int iN = 0; iN < nJet ; iN++){
				    cout << ialgo << " "<< iR << " " << iN << endl;
                    if(ialgo == 0 && iN > 0) continue; //!anti-kt has no jet number setting		
                    for(unsigned int ijet = 0;  ijet < fjPFjets[ialgo][iR][iN].size(); ijet++){ //!loop over reco jets
                        float rawPt = fjPFjets[ialgo][iR][iN][ijet].perp();
                       
                        float jtEta = fjPFjets[ialgo][iR][iN][ijet].eta();
  					    cout << 5.01 << endl;

						float jtPt = L2L3->get_corrected_pt(rawPt, jtEta);					
  					    cout << 5.02 << endl;
  					    if(jtPt < jetPtMin) continue;
                        float jtPhi = fjPFjets[ialgo][iR][iN][ijet].phi();
                        if(fabs(jtEta + R[iR]) > etacut) continue;

                        float jtPullEta = 0; //!initiaize first coordinate of the pull vector for the i-jet.
                        float jtPullPhi = 0; //!initiaize second coordinate of the pull vector for the i-jet.
                        float ratio_i = 0;
                        vector<PseudoJet> jPFConstituents = fjPFjets[ialgo][iR][iN][ijet].constituents();
                        for (unsigned jConst = 0; jConst< jPFConstituents.size(); jConst++){ //!load pf constituents of the jet. Here we sum over the pull value for each particle constituent
							float constitPhi = jPFConstituents[jConst].phi();
							float constitEta = jPFConstituents[jConst].eta();
							float constitPt = jPFConstituents[jConst].pt();

                            ratio_i = w_ratio_i(jtEta, jtPhi, jtPt, constitEta, constitPhi, constitPt);
                            jtPullEta += ratio_i*(constitEta - jtEta);
                            jtPullPhi += ratio_i*(deltaPhi(constitPhi, jtPhi));
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
						cout << 5.1 << endl;
                        Jet jet(jtPt, jtEta, jtPhi, jtPullEta, jtPullPhi, rawPt, hasRef, refPt, refEta, refPhi, refPullEta, refPullPhi, refIndex);
						
						cout << 5.2 << endl;
                        jets[ialgo][iR][iN].push_back(jet);
                        njet[ialgo][iR][iN]++;
                    }
					
					if(doMatchAK && doGen){//!after one algo is done the matched bool needs to be set to false for AK
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
        cout << 6 << endl;

        for(int iR = 0; iR < nR; iR++){
            if(njet[0][iR][0] > 0) evnt.setEvent((int)fhi->run, (int)fhi->lumi, (int)fhi->evt, (int)fhi->hiBin, fjet->pthat, &jets[0][iR][0], &genjets[0][iR][0]);
            treeMJ[0][iR][0]->Fill();
            // std::cout<<"Filling akt trees"<<std::endl;
            evnt.reset();
            for (int iN = 0; iN < nJet ; iN ++){
                if(njet[1][iR][iN] > 0) evnt.setEvent((int)fhi->run, (int)fhi->lumi, (int)fhi->evt, (int)fhi->hiBin, fjet->pthat, &jets[1][iR][iN], &genjets[1][iR][iN]);
                treeMJ[1][iR][iN]->Fill();
                // std::cout<<"Filling xcone trees"<<std::endl;
                evnt.reset();
            }
        }
		if(particlespf.size()>0){
			for(int iR = 0; iR < nR; iR++){
				delete csPFAK[0][iR][0];
				for (int iN = 0; iN < nJet ; iN++){
					delete csPFXCone[1][iR][iN];
					
				}
			}
		}
		if(doGen){
			if(particles.size()>0){
				for(int iR = 0; iR < nR; iR++){
					delete csGenAK[0][iR][0];
					for (int iN = 0; iN < nJet ; iN++){
						delete csGenXCone[1][iR][iN];
					
					}
				}
			}
		}
    } 
    cout << 7 << endl;

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
    Pull_Skim(argv[1], argv[2], argv[3], ((bool)atoi(argv[4])));
    return 0;
}









