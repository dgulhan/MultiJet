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




using namespace fastjet;
// using namespace fastjet::contrib;
using namespace std;

float deltaPhi( float phi1, float phi2) {
    float dphi = phi1 - phi2;
    
    if ( dphi > 3.141592653589 )
        dphi = dphi - 2. * 3.141592653589;
    if ( dphi <= -3.141592653589 )
        dphi = dphi + 2. * 3.141592653589;
    
    if ( TMath::Abs(dphi) > 3.141592653589 ) {
        cout << " commonUtility::getDPHI error!!! dphi is bigger than 3.141592653589 " << endl;
    }
    
    return dphi;
}


float deltaR( float eta1, float phi1, float eta2, float phi2){
    float theDphi = deltaPhi( phi1, phi2);
    float theDeta = eta1 - eta2;
    return sqrt( theDphi*theDphi + theDeta*theDeta);
}


void Pull_Skim(TString dataset = "", TString outfname = "", TString mode = "" ){
    TH2D::SetDefaultSumw2(true);
    TH1D::SetDefaultSumw2();
    
    
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
    
    
    
    int nJet = 3; //number of values for n (xcone relevant)
    int NJet[] = {2,3,4};
    
    fastjet::contrib::XConePlugin *plugin[nR][nJet]; //
    JetDefinition *jet_def_xcone[nR][nJet];
    
    for(int iR = 0; iR < nR; iR++){
        for ( int iN = 0; iN < nJet; iN++){
            plugin[iR][iN] = new fastjet::contrib::XConePlugin(NJet[iN],R[iR],2);
            jet_def_xcone[iR][iN] = new JetDefinition(plugin[iR][iN]);
        }
    }
    
    
    
    float etacut = 2;

    TString infname = Form("%s",dataset.Data());
    cout<<"Input file:"<<dataset.Data()<<std::endl;
    
    TString PFcollection = "pfcandAnalyzer";
    if(mode == "PbPbData" || mode == "PbPbMC") PFcollection = "pfcandAnalyzerCS";
    
    
    hiChain   *fhi = new hiChain(infname.Data());
    hltChain   *fhlt = new hltChain(infname.Data());
    skimChain   *fskim = new skimChain(infname.Data());
    // akPu3PF *t = new akPu3PF(infname.Data(),algo);
    pfChainVec * fpf = new pfChainVec(infname.Data(), PFcollection);
    genChain * fgen = new genChain(infname.Data());
    bool doGen = true;
    
    int nentries = fpf->GetEntries();
    std::cout<<"nentries = "<<nentries<<std::endl;
    std::cout<<"Outfile: "<<outfname.Data()<<std::endl;
    std::cout<<"Mode: "<<mode.Data()<<std::endl;
    
    TFile * fnt = new TFile(outfname.Data(),"recreate");
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
                treeMJ[ialgo][iR][iN]->Branch("pull_y1", &evnt.pull_y1, "pull_y1/F");
                treeMJ[ialgo][iR][iN]->Branch("pull_phi1", &evnt.pull_phi1, "pull_phi1/F");
                treeMJ[ialgo][iR][iN]->Branch("pull_y2", &evnt.pull_y2, "pull_y2/F");
                treeMJ[ialgo][iR][iN]->Branch("pull_phi2", &evnt.pull_phi2, "pull_phi2/F");
                treeMJ[ialgo][iR][iN]->Branch("pull_y3", &evnt.pull_y3, "pull_y3/F");
                treeMJ[ialgo][iR][iN]->Branch("pull_phi3", &evnt.pull_phi3, "pull_phi3/F");
                
                treeMJ[ialgo][iR][iN]->Branch("phi1", &evnt.phi1, "phi1/F");
                treeMJ[ialgo][iR][iN]->Branch("phi2", &evnt.phi2, "phi2/F");
                treeMJ[ialgo][iR][iN]->Branch("phi3", &evnt.phi3, "phi3/F");
                
                

                if(mode == "ppMC" || mode == "PbPbMC"){
                    treeMJ[ialgo][iR][iN]->Branch("refpt1", &evnt.refpt1, "refpt1/F");
                    treeMJ[ialgo][iR][iN]->Branch("refpt2", &evnt.refpt2, "refpt2/F");
                    treeMJ[ialgo][iR][iN]->Branch("refpt3", &evnt.refpt3, "refpt3/F");
                    treeMJ[ialgo][iR][iN]->Branch("refeta1", &evnt.refeta1, "refeta1/F");
                    treeMJ[ialgo][iR][iN]->Branch("refeta2", &evnt.refeta2, "refeta2/F");
                    treeMJ[ialgo][iR][iN]->Branch("refeta3", &evnt.refeta3, "refeta3/F");
                    treeMJ[ialgo][iR][iN]->Branch("refphi1", &evnt.refphi1, "refphi1/F");
                    treeMJ[ialgo][iR][iN]->Branch("refphi2", &evnt.refphi2, "refphi2/F");
                    treeMJ[ialgo][iR][iN]->Branch("refphi3", &evnt.refphi3, "refphi3/F");
                    //pull
                    treeMJ[ialgo][iR][iN]->Branch("refpull_y1", &evnt.refpull_y1, "refpull_y1/F");
                    treeMJ[ialgo][iR][iN]->Branch("refpull_phi1", &evnt.refpull_phi1, "refpull_phi1/F");
                    treeMJ[ialgo][iR][iN]->Branch("refpull_y2", &evnt.refpull_y2, "refpull_y2/F");
                    treeMJ[ialgo][iR][iN]->Branch("refpull_phi2", &evnt.refpull_phi2, "refpull_phi2/F");
                    treeMJ[ialgo][iR][iN]->Branch("refpull_y3", &evnt.refpull_y3, "refpull_y3/F");
                    treeMJ[ialgo][iR][iN]->Branch("refpull_phi3", &evnt.refpull_phi3, "refpull_phi3/F");
                    
                    if(doGen){
                        treeMJ[ialgo][iR][iN]->Branch("genpt1", &evnt.genpt1, "genpt1/F");
                        treeMJ[ialgo][iR][iN]->Branch("genpt2", &evnt.genpt2, "genpt2/F");
                        treeMJ[ialgo][iR][iN]->Branch("genpt3", &evnt.genpt3, "genpt3/F");
                        treeMJ[ialgo][iR][iN]->Branch("geneta1", &evnt.geneta1, "geneta1/F");
                        treeMJ[ialgo][iR][iN]->Branch("geneta2", &evnt.geneta2, "geneta2/F");
                        treeMJ[ialgo][iR][iN]->Branch("geneta3", &evnt.geneta3, "geneta3/F");
                        treeMJ[ialgo][iR][iN]->Branch("genphi1", &evnt.genphi1, "genphi1/F");
                        treeMJ[ialgo][iR][iN]->Branch("genphi2", &evnt.genphi2, "genphi2/F");
                        treeMJ[ialgo][iR][iN]->Branch("genphi3", &evnt.genphi3, "genphi3/F");
                        //pull
                        treeMJ[ialgo][iR][iN]->Branch("genpull_y1", &evnt.genpull_y1, "genpull_y1/F");
                        treeMJ[ialgo][iR][iN]->Branch("genpull_phi1", &evnt.genpull_phi1, "genpull_phi1/F");
                        treeMJ[ialgo][iR][iN]->Branch("genpull_y2", &evnt.genpull_y2, "genpull_y2/F");
                        treeMJ[ialgo][iR][iN]->Branch("genpull_phi2", &evnt.genpull_phi2, "genpull_phi2/F");
                        treeMJ[ialgo][iR][iN]->Branch("genpull_y3", &evnt.genpull_y3, "genpull_y3/F");
                        treeMJ[ialgo][iR][iN]->Branch("genpull_phi3", &evnt.genpull_phi3, "genpull_phi3/F");

                        
                    }
                }
                treeMJ[ialgo][iR][iN]->Branch("nref", &evnt.nref, "nref/I");
                treeMJ[ialgo][iR][iN]->Branch("rawpt", evnt.rawpt, "rawpt[nref]/F");
                treeMJ[ialgo][iR][iN]->Branch("rawphi", evnt.rawphi, "rawphi[nref]/F");
                treeMJ[ialgo][iR][iN]->Branch("raweta", evnt.raweta, "raweta[nref]/F");
                //Pull
                treeMJ[ialgo][iR][iN]->Branch("pull_y", evnt.pull_y, "pull_y[nref]/F");
                treeMJ[ialgo][iR][iN]->Branch("pull_phi", evnt.pull_phi, "pull_phi[nref]/F");
                
                if(mode == "ppMC" || mode == "PbPbMC"){
                    treeMJ[ialgo][iR][iN]->Branch("refpt", evnt.refpt, "refpt[nref]/F");
                    treeMJ[ialgo][iR][iN]->Branch("refphi", evnt.refphi, "refphi[nref]/F");
                    treeMJ[ialgo][iR][iN]->Branch("refeta", evnt.refeta, "refeta[nref]/F");
                    //pull
                    treeMJ[ialgo][iR][iN]->Branch("refpull_y", evnt.pull_y, "pull_y[nref]/F");
                    treeMJ[ialgo][iR][iN]->Branch("refpull_phi", evnt.pull_phi, "pull_phi[nref]/F");
                    
                    if(doGen){
                        treeMJ[ialgo][iR][iN]->Branch("ngen", &evnt.ngen, "ngen/I");
                        treeMJ[ialgo][iR][iN]->Branch("genpt", evnt.genpt, "genpt[ngen]/F");
                        treeMJ[ialgo][iR][iN]->Branch("genphi", evnt.genphi, "genphi[ngen]/F");
                        treeMJ[ialgo][iR][iN]->Branch("geneta", evnt.geneta, "geneta[ngen]/F");
                        //pull
                        treeMJ[ialgo][iR][iN]->Branch("genpull_y", evnt.genpull_y, "genpull_y[ngen]/F");
                        treeMJ[ialgo][iR][iN]->Branch("genpull_phi", evnt.genpull_phi, "genpull_phi[ngen]/F");
                        
                    }
                }
            }
        }
    }
    
    //for (Long64_t jentry = 0; jentry < nentries; jentry++) {

    for (Long64_t jentry = 0; jentry < 100; jentry++) {
        
        if(nentries%1000 == jentry)cout << jentry << endl;
     
        fhi->GetEntry(jentry);
        fhlt->GetEntry(jentry);
        fskim->GetEntry(jentry);
        fpf->GetEntry(jentry);

        if(mode == "ppMC" || mode == "PbPbMC") fgen->GetEntry(jentry);
        
        
        if((mode == "ppData" || mode == "ppMC") && !(fskim->HBHENoiseFilterResultRun2Loose && fskim->pPAprimaryVertexFilter && fabs(fhi->vz)<15 && fskim->pBeamScrapingFilter)) continue;
        
        if((mode == "PbPbData") && !(fhlt->HLT_HIPuAK4CaloJet80_Eta5p1_v1 && fskim->pprimaryVertexFilter && fskim->pclusterCompatibilityFilter && fskim->pcollisionEventSelection && fskim->HBHENoiseFilterResultRun2Loose)) continue;
        if((mode == "PbPbMC") && !(fskim->pprimaryVertexFilter && fskim->pclusterCompatibilityFilter && fskim->pcollisionEventSelection && fskim->HBHENoiseFilterResultRun2Loose)) continue;
        
        
        vector<PseudoJet> fjpfjets[nalgo][nR][nJet];
        vector<PseudoJet> fjgenjets[nalgo][nR][nJet];
        
        // Cluster Secuence
        ClusterSequence *cspf_ak[nalgo][nR][nJet];
        ClusterSequence *cspf_xcone[nalgo][nR][nJet];
        ClusterSequence *csgen_ak[nalgo][nR][nJet];
        ClusterSequence *csgen_xcone[nalgo][nR][nJet];
        
        //cluster PF candidates
        vector<PseudoJet> particlespf;
        for(int ipart = 0; ipart < fpf->nPFpart; ipart++){
            //cout << "Ipart loop: "<<ipart<<"of "<<fpf->nPFpart<<endl;
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
        }
        
        
        if(particlespf.size()>0){
            for(int iR = 0; iR < nR; iR++){
                cspf_ak[0][iR][0] = new ClusterSequence (particlespf, *jet_def_antikt[iR]);
                fjpfjets[0][iR][0] = sorted_by_pt(cspf_ak[0][iR][0]->inclusive_jets());
                //cout<<"Sorting for ak"<<endl;
                for (int iN = 0; iN < nJet ; iN++){
                    //cout<<"Sorting for xcone"<<endl;
                    cspf_xcone[1][iR][iN] = new ClusterSequence(particlespf, *jet_def_xcone[iR][iN]);
                    fjpfjets[1][iR][iN] = sorted_by_pt(cspf_xcone[1][iR][iN]->inclusive_jets());
                    
                }
            }
        }
        particlespf.clear();
        
        
        if(mode == "ppMC" || mode == "PbPbMC"){
            //cluster gen particles from signal
            vector<PseudoJet> particles;
            for(int ipart = 0; ipart < fgen->mult; ipart++){
                //cout << "Ipart loop: "<<ipart<<"of "<<fpf->nPFpart<<endl;
                // cout << ipart << endl;
                if(fgen->sube->at(ipart) != 0) continue;
                float pt = fgen->pt->at(ipart);
                if(pt<=0) continue;
                float eta = fgen->eta->at(ipart);
                if(fabs(eta) > 3) continue;
                float phi = fgen->phi->at(ipart);
                float px = pt*cos(phi);
                float py = pt*sin(phi);
                float pz = pt*sinh(eta);
                float E = pt*cosh(eta);
                
                cout << ipart << endl;
                fastjet::PseudoJet Particle(px,py,pz,E);
                particles.push_back(Particle);
            }
            if(particles.size()>0){
                for(int iR = 0; iR < nR; iR++){
                    // Clustering for gen particles.
                    csgen_ak[0][iR][0] = new ClusterSequence(particles, *jet_def_antikt[iR]);
                    fjgenjets[0][iR][0] = sorted_by_pt(csgen_ak[0][iR][0]->inclusive_jets());
                    //cout<<"Sorting for ak"<<endl;
                    for (int iN = 0; iN < nJet ; iN++){
                        //cout<<"Sorting for xcone"<<endl;
                        csgen_xcone[1][iR][iN] = new ClusterSequence(particles, *jet_def_xcone[iR][iN]);
                        fjgenjets[1][iR][iN] = sorted_by_pt(csgen_xcone[1][iR][iN]->inclusive_jets());
                        
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
                    if(ialgo == 0 && iN > 0) continue;
                    njet[ialgo][iR][iN] = 0;
                    
                    for(unsigned int ijet = 0;  ijet < fjpfjets[ialgo][iR][iN].size(); ijet++){
                        float jtpt = fjpfjets[ialgo][iR][iN][ijet].perp();
                        if(jtpt<5) continue;
                        float jtphi = fjpfjets[ialgo][iR][iN][ijet].phi();
                        float jteta = fjpfjets[ialgo][iR][iN][ijet].eta();
                        float jtrap = fjpfjets[ialgo][iR][iN][ijet].rap();
                        
                        float pull_y = 0; //initiaize first coordinate of the pull vector for the i-jet.
                        float pull_phi = 0; //initiaize second coordinate of the pull vector for the i-jet.
                        float ratio_i = 0;
                        vector<PseudoJet> jpfconstituents = fjpfjets[ialgo][iR][iN][ijet].constituents();
                        for (unsigned j_const = 0; j_const< jpfconstituents.size(); j_const++){ //load pf constituents of the jet. Here we sum over the pull value for each particle constituent
                            //pull_y = pull_y + Pull1_i(jtrap,jtphi,jtpt,jpfconstituents[j_const].rap(),jpfconstituents[j_const].phi(),jpfconstituents[j_const].pt());
                            //pull_phi = pull_phi + Pull2_i(jtrap,jtphi,jtpt,jpfconstituents[j_const].rap(),jpfconstituents[j_const].phi(),jpfconstituents[j_const].pt());
                            ratio_i= w_ratio_i(jtrap,jtphi,jtpt,jpfconstituents[j_const].rap(),jpfconstituents[j_const].phi(),jpfconstituents[j_const].pt());
                            cout<<"ratio raw: "<<ratio_i<<endl;
                            pull_y = pull_y + ratio_i*(jpfconstituents[j_const].rap()-jtrap);
                            pull_phi = pull_phi + ratio_i*(jpfconstituents[j_const].phi()-jtphi);
                            cout<<"Jtrap: "<<jtrap<<" jtphi: "<<jtphi<<" jtpt: "<<jtpt<<" prap: "<<jpfconstituents[j_const].rap()<<" pphi: "<<jpfconstituents[j_const].phi()<<" ppt: "<<jpfconstituents[j_const].pt()<<" pull_y:"<<pull_y<<" pull_phi: "<<pull_phi<<endl;
                        }
                        
                        if(fabs(jteta)>etacut) continue;
                        float refpt, refeta, refphi, refpull_phi, refpull_y;
                        refpt = refeta = refphi = -99;
                        refpull_phi = refpull_y = -99;
                        
                        if(mode == "ppMC" || mode == "PbPbMC"){ // matching to gen jets
                            float ptrat = 9999;
                            for(unsigned int ijet = 0;  ijet < fjgenjets[ialgo][iR][iN].size(); ijet++){
                                float geneta = fjgenjets[ialgo][iR][iN][ijet].eta();
                                float genphi = fjgenjets[ialgo][iR][iN][ijet].phi();
                                float genrap = fjgenjets[ialgo][iR][iN][ijet].rap();
                                
                                
                                if(deltaR(jteta, jtphi, geneta, genphi) < R[iR]){
                                    float genpt = fjgenjets[ialgo][iR][iN][ijet].perp();
                                    
                                    if(fabs(jtpt/genpt - 1) < fabs(ptrat - 1) ){
                                        
                                        
                                        float genpull_y = 0;
                                        float genpull_phi = 0;
                                        vector<PseudoJet> jgenconstituents = fjgenjets[ialgo][iR][iN][ijet].constituents();
                                        
                                        for (unsigned j_const = 0; j_const< jgenconstituents.size(); j_const++){ //load pf constituents of the jet. Here we sum over the pull value for each particle constituent
                                            genpull_y = genpull_y + Pull1_i(genrap,genphi,genpt,jgenconstituents[j_const].rap(),jgenconstituents[j_const].phi(),jgenconstituents[j_const].pt());
                                            genpull_phi = genpull_phi + Pull2_i(genrap,genphi,genpt,jgenconstituents[j_const].rap(),jgenconstituents[j_const].phi(),jgenconstituents[j_const].pt());
                                            
                                            
                                        }

                                        
                                        ptrat = jtpt/genpt;
                                        refpt = genpt;
                                        refeta = geneta;
                                        refphi = genphi;
                                        refpull_y = genpull_y;
                                        refpull_phi = genpull_phi;
                                        if(ptrat < 0.1) break;
                                    }
                                }
                            }
                        }
                        Jet jet(jtpt, jteta, jtphi, pull_y, pull_phi, refpt, refeta, refphi, refpull_y, refpull_phi);
                        jets[ialgo][iR][iN].push_back(jet);
                        njet[ialgo][iR][iN]++;
                    }
                    if(doGen){
                        cout << "ngen = " << fjgenjets[ialgo][iR][iN].size() << endl;
                        for(unsigned int ijet = 0;  ijet < fjgenjets[ialgo][iR][iN].size(); ijet++){
                            
                            float geneta = fjgenjets[ialgo][iR][iN][ijet].eta();
                            float genphi = fjgenjets[ialgo][iR][iN][ijet].phi();
                            float genpt = fjgenjets[ialgo][iR][iN][ijet].perp();
                            
                            //////////
                            
                            float genrap = fjgenjets[ialgo][iR][iN][ijet].rap();
                            float genpull_y = 0 ;
                            float genpull_phi = 0 ;
                            vector<PseudoJet> jgenconstituents = fjgenjets[ialgo][iR][iN][ijet].constituents();
                            
                            for (unsigned j_const = 0; j_const< jgenconstituents.size(); j_const++){ //load pf constituents of the jet. Here we sum over the pull value for each particle constituent
                                genpull_y = genpull_y + Pull1_i(genrap,genphi,genpt,jgenconstituents[j_const].rap(),jgenconstituents[j_const].phi(),jgenconstituents[j_const].pt());
                                genpull_phi = genpull_phi + Pull2_i(genrap,genphi,genpt,jgenconstituents[j_const].rap(),jgenconstituents[j_const].phi(),jgenconstituents[j_const].pt());
                                
                                
                            }
                            Jet genjet(genpt, geneta, genphi, genpull_y,genpull_phi);
                            genjets[ialgo][iR][iN].push_back(genjet);
                        }
                    }

                }
            }
        }

        for(int iR = 0; iR < nR; iR++){
            if(njet[0][iR][0] > 0) evnt.setEvent((int)fhi->run, (int)fhi->lumi, (int)fhi->evt, (int)fhi->hiBin, &jets[0][iR][0], &genjets[0][iR][0]);
            treeMJ[0][iR][0]->Fill();
            std::cout<<"Filling akt trees"<<std::endl;
            evnt.reset();
            for (int iN = 0; iN < nJet ; iN ++){
                if(njet[1][iR][iN] > 0) evnt.setEvent((int)fhi->run, (int)fhi->lumi, (int)fhi->evt, (int)fhi->hiBin, &jets[1][iR][iN], &genjets[1][iR][iN]);
                treeMJ[1][iR][iN]->Fill();
                std::cout<<"Filling xcone trees"<<std::endl;
                evnt.reset();
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









