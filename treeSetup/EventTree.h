//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Mar 29 09:20:50 2016 by ROOT version 5.32/00
// from TTree EventTree/Event data
// found on file: /mnt/hadoop/cms/store/user/abaty/transferTargetDirectories/2015pp_MinBias6/HiForestAOD_257.root
//////////////////////////////////////////////////////////

#ifndef EventTree_h
#define EventTree_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include <vector>
#include <vector>

// Fixed size dimensions of array or collections stored in the TTree if any.

using namespace std;

class EventTree {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   UInt_t          run;
   ULong64_t       event;
   UInt_t          lumis;
   Bool_t          isData;
   Int_t           nEle;
   vector<int>     *eleCharge;
   vector<int>     *eleChargeConsistent;
   vector<float>   *eleEn;
   vector<float>   *eleD0;
   vector<float>   *eleDz;
   vector<float>   *eleD0Err;
   vector<float>   *eleDzErr;
   vector<float>   *eleTrkPt;
   vector<float>   *eleTrkEta;
   vector<float>   *eleTrkPhi;
   vector<int>     *eleTrkCharge;
   vector<float>   *eleTrkChi2;
   vector<float>   *eleTrkNdof;
   vector<float>   *eleTrkNormalizedChi2;
   vector<int>     *eleTrkValidHits;
   vector<int>     *eleTrkLayers;
   vector<float>   *elePt;
   vector<float>   *eleEta;
   vector<float>   *elePhi;
   vector<float>   *eleSCEn;
   vector<float>   *eleESEn;
   vector<float>   *eleSCEta;
   vector<float>   *eleSCPhi;
   vector<float>   *eleSCRawEn;
   vector<float>   *eleSCEtaWidth;
   vector<float>   *eleSCPhiWidth;
   vector<float>   *eleHoverE;
   vector<float>   *eleHoverEBc;
   vector<float>   *eleEoverP;
   vector<float>   *eleEoverPInv;
   vector<float>   *eleBrem;
   vector<float>   *eledEtaAtVtx;
   vector<float>   *eledPhiAtVtx;
   vector<float>   *eleSigmaIEtaIEta;
   vector<float>   *eleSigmaIEtaIEta_2012;
   vector<float>   *eleSigmaIPhiIPhi;
   vector<int>     *eleMissHits;
   vector<float>   *eleESEffSigmaRR;
   vector<float>   *elePFChIso;
   vector<float>   *elePFPhoIso;
   vector<float>   *elePFNeuIso;
   vector<float>   *elePFPUIso;
   vector<float>   *elePFChIso03;
   vector<float>   *elePFPhoIso03;
   vector<float>   *elePFNeuIso03;
   vector<float>   *elePFChIso04;
   vector<float>   *elePFPhoIso04;
   vector<float>   *elePFNeuIso04;
   vector<float>   *eleBC1E;
   vector<float>   *eleBC1Eta;
   vector<float>   *eleBC2E;
   vector<float>   *eleBC2Eta;
   Int_t           nPho;
   vector<float>   *phoE;
   vector<float>   *phoEt;
   vector<float>   *phoEta;
   vector<float>   *phoPhi;
   vector<float>   *phoSCE;
   vector<float>   *phoSCRawE;
   vector<float>   *phoESEn;
   vector<float>   *phoSCEta;
   vector<float>   *phoSCPhi;
   vector<float>   *phoSCEtaWidth;
   vector<float>   *phoSCPhiWidth;
   vector<float>   *phoSCBrem;
   vector<int>     *phohasPixelSeed;
   vector<float>   *phoR9;
   vector<float>   *phoHadTowerOverEm;
   vector<float>   *phoHoverE;
   vector<float>   *phoSigmaIEtaIEta;
   vector<float>   *phoE1x3;
   vector<float>   *phoE2x2;
   vector<float>   *phoE3x3;
   vector<float>   *phoE2x5Max;
   vector<float>   *phoE1x5;
   vector<float>   *phoE2x5;
   vector<float>   *phoE5x5;
   vector<float>   *phoMaxEnergyXtal;
   vector<float>   *phoSigmaEtaEta;
   vector<float>   *phoR1x5;
   vector<float>   *phoR2x5;
   vector<float>   *phoESEffSigmaRR;
   vector<float>   *phoSigmaIEtaIEta_2012;
   vector<float>   *phoSigmaIEtaIPhi_2012;
   vector<float>   *phoSigmaIPhiIPhi_2012;
   vector<float>   *phoE1x3_2012;
   vector<float>   *phoE2x2_2012;
   vector<float>   *phoE3x3_2012;
   vector<float>   *phoE2x5Max_2012;
   vector<float>   *phoE5x5_2012;
   vector<float>   *phoBC1E;
   vector<float>   *phoBC1Eta;
   vector<float>   *phoBC2E;
   vector<float>   *phoBC2Eta;
   vector<float>   *pho_ecalClusterIsoR2;
   vector<float>   *pho_ecalClusterIsoR3;
   vector<float>   *pho_ecalClusterIsoR4;
   vector<float>   *pho_ecalClusterIsoR5;
   vector<float>   *pho_hcalRechitIsoR1;
   vector<float>   *pho_hcalRechitIsoR2;
   vector<float>   *pho_hcalRechitIsoR3;
   vector<float>   *pho_hcalRechitIsoR4;
   vector<float>   *pho_hcalRechitIsoR5;
   vector<float>   *pho_trackIsoR1PtCut20;
   vector<float>   *pho_trackIsoR2PtCut20;
   vector<float>   *pho_trackIsoR3PtCut20;
   vector<float>   *pho_trackIsoR4PtCut20;
   vector<float>   *pho_trackIsoR5PtCut20;
   vector<float>   *pho_swissCrx;
   vector<float>   *pho_seedTime;
   vector<float>   *pfcIso1;
   vector<float>   *pfcIso2;
   vector<float>   *pfcIso3;
   vector<float>   *pfcIso4;
   vector<float>   *pfcIso5;
   vector<float>   *pfpIso1;
   vector<float>   *pfpIso2;
   vector<float>   *pfpIso3;
   vector<float>   *pfpIso4;
   vector<float>   *pfpIso5;
   vector<float>   *pfnIso1;
   vector<float>   *pfnIso2;
   vector<float>   *pfnIso3;
   vector<float>   *pfnIso4;
   vector<float>   *pfnIso5;
   Int_t           nMu;
   vector<float>   *muPt;
   vector<float>   *muEta;
   vector<float>   *muPhi;
   vector<int>     *muCharge;
   vector<int>     *muType;
   vector<int>     *muIsGood;
   vector<float>   *muD0;
   vector<float>   *muDz;
   vector<float>   *muChi2NDF;
   vector<float>   *muInnerD0;
   vector<float>   *muInnerDz;
   vector<int>     *muTrkLayers;
   vector<int>     *muPixelLayers;
   vector<int>     *muPixelHits;
   vector<int>     *muMuonHits;
   vector<int>     *muTrkQuality;
   vector<int>     *muStations;
   vector<float>   *muIsoTrk;
   vector<float>   *muPFChIso;
   vector<float>   *muPFPhoIso;
   vector<float>   *muPFNeuIso;
   vector<float>   *muPFPUIso;

   // List of branches
   TBranch        *b_run;   //!
   TBranch        *b_event;   //!
   TBranch        *b_lumis;   //!
   TBranch        *b_isData;   //!
   TBranch        *b_nEle;   //!
   TBranch        *b_eleCharge;   //!
   TBranch        *b_eleChargeConsistent;   //!
   TBranch        *b_eleEn;   //!
   TBranch        *b_eleD0;   //!
   TBranch        *b_eleDz;   //!
   TBranch        *b_eleD0Err;   //!
   TBranch        *b_eleDzErr;   //!
   TBranch        *b_eleTrkPt;   //!
   TBranch        *b_eleTrkEta;   //!
   TBranch        *b_eleTrkPhi;   //!
   TBranch        *b_eleTrkCharge;   //!
   TBranch        *b_eleTrkChi2;   //!
   TBranch        *b_eleTrkNdof;   //!
   TBranch        *b_eleTrkNormalizedChi2;   //!
   TBranch        *b_eleTrkValidHits;   //!
   TBranch        *b_eleTrkLayers;   //!
   TBranch        *b_elePt;   //!
   TBranch        *b_eleEta;   //!
   TBranch        *b_elePhi;   //!
   TBranch        *b_eleSCEn;   //!
   TBranch        *b_eleESEn;   //!
   TBranch        *b_eleSCEta;   //!
   TBranch        *b_eleSCPhi;   //!
   TBranch        *b_eleSCRawEn;   //!
   TBranch        *b_eleSCEtaWidth;   //!
   TBranch        *b_eleSCPhiWidth;   //!
   TBranch        *b_eleHoverE;   //!
   TBranch        *b_eleHoverEBc;   //!
   TBranch        *b_eleEoverP;   //!
   TBranch        *b_eleEoverPInv;   //!
   TBranch        *b_eleBrem;   //!
   TBranch        *b_eledEtaAtVtx;   //!
   TBranch        *b_eledPhiAtVtx;   //!
   TBranch        *b_eleSigmaIEtaIEta;   //!
   TBranch        *b_eleSigmaIEtaIEta_2012;   //!
   TBranch        *b_eleSigmaIPhiIPhi;   //!
   TBranch        *b_eleMissHits;   //!
   TBranch        *b_eleESEffSigmaRR;   //!
   TBranch        *b_elePFChIso;   //!
   TBranch        *b_elePFPhoIso;   //!
   TBranch        *b_elePFNeuIso;   //!
   TBranch        *b_elePFPUIso;   //!
   TBranch        *b_elePFChIso03;   //!
   TBranch        *b_elePFPhoIso03;   //!
   TBranch        *b_elePFNeuIso03;   //!
   TBranch        *b_elePFChIso04;   //!
   TBranch        *b_elePFPhoIso04;   //!
   TBranch        *b_elePFNeuIso04;   //!
   TBranch        *b_eleBC1E;   //!
   TBranch        *b_eleBC1Eta;   //!
   TBranch        *b_eleBC2E;   //!
   TBranch        *b_eleBC2Eta;   //!
   TBranch        *b_nPho;   //!
   TBranch        *b_phoE;   //!
   TBranch        *b_phoEt;   //!
   TBranch        *b_phoEta;   //!
   TBranch        *b_phoPhi;   //!
   TBranch        *b_phoSCE;   //!
   TBranch        *b_phoSCRawE;   //!
   TBranch        *b_phoESEn;   //!
   TBranch        *b_phoSCEta;   //!
   TBranch        *b_phoSCPhi;   //!
   TBranch        *b_phoSCEtaWidth;   //!
   TBranch        *b_phoSCPhiWidth;   //!
   TBranch        *b_phoSCBrem;   //!
   TBranch        *b_phohasPixelSeed;   //!
   TBranch        *b_phoR9;   //!
   TBranch        *b_phoHadTowerOverEm;   //!
   TBranch        *b_phoHoverE;   //!
   TBranch        *b_phoSigmaIEtaIEta;   //!
   TBranch        *b_phoE1x3;   //!
   TBranch        *b_phoE2x2;   //!
   TBranch        *b_phoE3x3;   //!
   TBranch        *b_phoE2x5Max;   //!
   TBranch        *b_phoE1x5;   //!
   TBranch        *b_phoE2x5;   //!
   TBranch        *b_phoE5x5;   //!
   TBranch        *b_phoMaxEnergyXtal;   //!
   TBranch        *b_phoSigmaEtaEta;   //!
   TBranch        *b_phoR1x5;   //!
   TBranch        *b_phoR2x5;   //!
   TBranch        *b_phoESEffSigmaRR;   //!
   TBranch        *b_phoSigmaIEtaIEta_2012;   //!
   TBranch        *b_phoSigmaIEtaIPhi_2012;   //!
   TBranch        *b_phoSigmaIPhiIPhi_2012;   //!
   TBranch        *b_phoE1x3_2012;   //!
   TBranch        *b_phoE2x2_2012;   //!
   TBranch        *b_phoE3x3_2012;   //!
   TBranch        *b_phoE2x5Max_2012;   //!
   TBranch        *b_phoE5x5_2012;   //!
   TBranch        *b_phoBC1E;   //!
   TBranch        *b_phoBC1Eta;   //!
   TBranch        *b_phoBC2E;   //!
   TBranch        *b_phoBC2Eta;   //!
   TBranch        *b_pho_ecalClusterIsoR2;   //!
   TBranch        *b_pho_ecalClusterIsoR3;   //!
   TBranch        *b_pho_ecalClusterIsoR4;   //!
   TBranch        *b_pho_ecalClusterIsoR5;   //!
   TBranch        *b_pho_hcalRechitIsoR1;   //!
   TBranch        *b_pho_hcalRechitIsoR2;   //!
   TBranch        *b_pho_hcalRechitIsoR3;   //!
   TBranch        *b_pho_hcalRechitIsoR4;   //!
   TBranch        *b_pho_hcalRechitIsoR5;   //!
   TBranch        *b_pho_trackIsoR1PtCut20;   //!
   TBranch        *b_pho_trackIsoR2PtCut20;   //!
   TBranch        *b_pho_trackIsoR3PtCut20;   //!
   TBranch        *b_pho_trackIsoR4PtCut20;   //!
   TBranch        *b_pho_trackIsoR5PtCut20;   //!
   TBranch        *b_pho_swissCrx;   //!
   TBranch        *b_pho_seedTime;   //!
   TBranch        *b_pfcIso1;   //!
   TBranch        *b_pfcIso2;   //!
   TBranch        *b_pfcIso3;   //!
   TBranch        *b_pfcIso4;   //!
   TBranch        *b_pfcIso5;   //!
   TBranch        *b_pfpIso1;   //!
   TBranch        *b_pfpIso2;   //!
   TBranch        *b_pfpIso3;   //!
   TBranch        *b_pfpIso4;   //!
   TBranch        *b_pfpIso5;   //!
   TBranch        *b_pfnIso1;   //!
   TBranch        *b_pfnIso2;   //!
   TBranch        *b_pfnIso3;   //!
   TBranch        *b_pfnIso4;   //!
   TBranch        *b_pfnIso5;   //!
   TBranch        *b_nMu;   //!
   TBranch        *b_muPt;   //!
   TBranch        *b_muEta;   //!
   TBranch        *b_muPhi;   //!
   TBranch        *b_muCharge;   //!
   TBranch        *b_muType;   //!
   TBranch        *b_muIsGood;   //!
   TBranch        *b_muD0;   //!
   TBranch        *b_muDz;   //!
   TBranch        *b_muChi2NDF;   //!
   TBranch        *b_muInnerD0;   //!
   TBranch        *b_muInnerDz;   //!
   TBranch        *b_muTrkLayers;   //!
   TBranch        *b_muPixelLayers;   //!
   TBranch        *b_muPixelHits;   //!
   TBranch        *b_muMuonHits;   //!
   TBranch        *b_muTrkQuality;   //!
   TBranch        *b_muStations;   //!
   TBranch        *b_muIsoTrk;   //!
   TBranch        *b_muPFChIso;   //!
   TBranch        *b_muPFPhoIso;   //!
   TBranch        *b_muPFNeuIso;   //!
   TBranch        *b_muPFPUIso;   //!

   // EventTree(TTree *tree=0);
   EventTree(TString infile,TTree *tree=0);
   virtual ~EventTree();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef EventTree_cxx
EventTree::EventTree(TString infile,TTree *tree)
{
   TFile *f = TFile::Open(infile.Data());
   tree = (TTree*) f->Get("ggHiNtuplizerGED/EventTree");
   Init(tree);
}

EventTree::~EventTree()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t EventTree::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t EventTree::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void EventTree::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   eleCharge = 0;
   eleChargeConsistent = 0;
   eleEn = 0;
   eleD0 = 0;
   eleDz = 0;
   eleD0Err = 0;
   eleDzErr = 0;
   eleTrkPt = 0;
   eleTrkEta = 0;
   eleTrkPhi = 0;
   eleTrkCharge = 0;
   eleTrkChi2 = 0;
   eleTrkNdof = 0;
   eleTrkNormalizedChi2 = 0;
   eleTrkValidHits = 0;
   eleTrkLayers = 0;
   elePt = 0;
   eleEta = 0;
   elePhi = 0;
   eleSCEn = 0;
   eleESEn = 0;
   eleSCEta = 0;
   eleSCPhi = 0;
   eleSCRawEn = 0;
   eleSCEtaWidth = 0;
   eleSCPhiWidth = 0;
   eleHoverE = 0;
   eleHoverEBc = 0;
   eleEoverP = 0;
   eleEoverPInv = 0;
   eleBrem = 0;
   eledEtaAtVtx = 0;
   eledPhiAtVtx = 0;
   eleSigmaIEtaIEta = 0;
   eleSigmaIEtaIEta_2012 = 0;
   eleSigmaIPhiIPhi = 0;
   eleMissHits = 0;
   eleESEffSigmaRR = 0;
   elePFChIso = 0;
   elePFPhoIso = 0;
   elePFNeuIso = 0;
   elePFPUIso = 0;
   elePFChIso03 = 0;
   elePFPhoIso03 = 0;
   elePFNeuIso03 = 0;
   elePFChIso04 = 0;
   elePFPhoIso04 = 0;
   elePFNeuIso04 = 0;
   eleBC1E = 0;
   eleBC1Eta = 0;
   eleBC2E = 0;
   eleBC2Eta = 0;
   phoE = 0;
   phoEt = 0;
   phoEta = 0;
   phoPhi = 0;
   phoSCE = 0;
   phoSCRawE = 0;
   phoESEn = 0;
   phoSCEta = 0;
   phoSCPhi = 0;
   phoSCEtaWidth = 0;
   phoSCPhiWidth = 0;
   phoSCBrem = 0;
   phohasPixelSeed = 0;
   phoR9 = 0;
   phoHadTowerOverEm = 0;
   phoHoverE = 0;
   phoSigmaIEtaIEta = 0;
   phoE1x3 = 0;
   phoE2x2 = 0;
   phoE3x3 = 0;
   phoE2x5Max = 0;
   phoE1x5 = 0;
   phoE2x5 = 0;
   phoE5x5 = 0;
   phoMaxEnergyXtal = 0;
   phoSigmaEtaEta = 0;
   phoR1x5 = 0;
   phoR2x5 = 0;
   phoESEffSigmaRR = 0;
   phoSigmaIEtaIEta_2012 = 0;
   phoSigmaIEtaIPhi_2012 = 0;
   phoSigmaIPhiIPhi_2012 = 0;
   phoE1x3_2012 = 0;
   phoE2x2_2012 = 0;
   phoE3x3_2012 = 0;
   phoE2x5Max_2012 = 0;
   phoE5x5_2012 = 0;
   phoBC1E = 0;
   phoBC1Eta = 0;
   phoBC2E = 0;
   phoBC2Eta = 0;
   pho_ecalClusterIsoR2 = 0;
   pho_ecalClusterIsoR3 = 0;
   pho_ecalClusterIsoR4 = 0;
   pho_ecalClusterIsoR5 = 0;
   pho_hcalRechitIsoR1 = 0;
   pho_hcalRechitIsoR2 = 0;
   pho_hcalRechitIsoR3 = 0;
   pho_hcalRechitIsoR4 = 0;
   pho_hcalRechitIsoR5 = 0;
   pho_trackIsoR1PtCut20 = 0;
   pho_trackIsoR2PtCut20 = 0;
   pho_trackIsoR3PtCut20 = 0;
   pho_trackIsoR4PtCut20 = 0;
   pho_trackIsoR5PtCut20 = 0;
   pho_swissCrx = 0;
   pho_seedTime = 0;
   pfcIso1 = 0;
   pfcIso2 = 0;
   pfcIso3 = 0;
   pfcIso4 = 0;
   pfcIso5 = 0;
   pfpIso1 = 0;
   pfpIso2 = 0;
   pfpIso3 = 0;
   pfpIso4 = 0;
   pfpIso5 = 0;
   pfnIso1 = 0;
   pfnIso2 = 0;
   pfnIso3 = 0;
   pfnIso4 = 0;
   pfnIso5 = 0;
   muPt = 0;
   muEta = 0;
   muPhi = 0;
   muCharge = 0;
   muType = 0;
   muIsGood = 0;
   muD0 = 0;
   muDz = 0;
   muChi2NDF = 0;
   muInnerD0 = 0;
   muInnerDz = 0;
   muTrkLayers = 0;
   muPixelLayers = 0;
   muPixelHits = 0;
   muMuonHits = 0;
   muTrkQuality = 0;
   muStations = 0;
   muIsoTrk = 0;
   muPFChIso = 0;
   muPFPhoIso = 0;
   muPFNeuIso = 0;
   muPFPUIso = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("run", &run, &b_run);
   fChain->SetBranchAddress("event", &event, &b_event);
   fChain->SetBranchAddress("lumis", &lumis, &b_lumis);
   fChain->SetBranchAddress("isData", &isData, &b_isData);
   fChain->SetBranchAddress("nEle", &nEle, &b_nEle);
   fChain->SetBranchAddress("eleCharge", &eleCharge, &b_eleCharge);
   fChain->SetBranchAddress("eleChargeConsistent", &eleChargeConsistent, &b_eleChargeConsistent);
   fChain->SetBranchAddress("eleEn", &eleEn, &b_eleEn);
   fChain->SetBranchAddress("eleD0", &eleD0, &b_eleD0);
   fChain->SetBranchAddress("eleDz", &eleDz, &b_eleDz);
   fChain->SetBranchAddress("eleD0Err", &eleD0Err, &b_eleD0Err);
   fChain->SetBranchAddress("eleDzErr", &eleDzErr, &b_eleDzErr);
   fChain->SetBranchAddress("eleTrkPt", &eleTrkPt, &b_eleTrkPt);
   fChain->SetBranchAddress("eleTrkEta", &eleTrkEta, &b_eleTrkEta);
   fChain->SetBranchAddress("eleTrkPhi", &eleTrkPhi, &b_eleTrkPhi);
   fChain->SetBranchAddress("eleTrkCharge", &eleTrkCharge, &b_eleTrkCharge);
   fChain->SetBranchAddress("eleTrkChi2", &eleTrkChi2, &b_eleTrkChi2);
   fChain->SetBranchAddress("eleTrkNdof", &eleTrkNdof, &b_eleTrkNdof);
   fChain->SetBranchAddress("eleTrkNormalizedChi2", &eleTrkNormalizedChi2, &b_eleTrkNormalizedChi2);
   fChain->SetBranchAddress("eleTrkValidHits", &eleTrkValidHits, &b_eleTrkValidHits);
   fChain->SetBranchAddress("eleTrkLayers", &eleTrkLayers, &b_eleTrkLayers);
   fChain->SetBranchAddress("elePt", &elePt, &b_elePt);
   fChain->SetBranchAddress("eleEta", &eleEta, &b_eleEta);
   fChain->SetBranchAddress("elePhi", &elePhi, &b_elePhi);
   fChain->SetBranchAddress("eleSCEn", &eleSCEn, &b_eleSCEn);
   fChain->SetBranchAddress("eleESEn", &eleESEn, &b_eleESEn);
   fChain->SetBranchAddress("eleSCEta", &eleSCEta, &b_eleSCEta);
   fChain->SetBranchAddress("eleSCPhi", &eleSCPhi, &b_eleSCPhi);
   fChain->SetBranchAddress("eleSCRawEn", &eleSCRawEn, &b_eleSCRawEn);
   fChain->SetBranchAddress("eleSCEtaWidth", &eleSCEtaWidth, &b_eleSCEtaWidth);
   fChain->SetBranchAddress("eleSCPhiWidth", &eleSCPhiWidth, &b_eleSCPhiWidth);
   fChain->SetBranchAddress("eleHoverE", &eleHoverE, &b_eleHoverE);
   fChain->SetBranchAddress("eleHoverEBc", &eleHoverEBc, &b_eleHoverEBc);
   fChain->SetBranchAddress("eleEoverP", &eleEoverP, &b_eleEoverP);
   fChain->SetBranchAddress("eleEoverPInv", &eleEoverPInv, &b_eleEoverPInv);
   fChain->SetBranchAddress("eleBrem", &eleBrem, &b_eleBrem);
   fChain->SetBranchAddress("eledEtaAtVtx", &eledEtaAtVtx, &b_eledEtaAtVtx);
   fChain->SetBranchAddress("eledPhiAtVtx", &eledPhiAtVtx, &b_eledPhiAtVtx);
   fChain->SetBranchAddress("eleSigmaIEtaIEta", &eleSigmaIEtaIEta, &b_eleSigmaIEtaIEta);
   fChain->SetBranchAddress("eleSigmaIEtaIEta_2012", &eleSigmaIEtaIEta_2012, &b_eleSigmaIEtaIEta_2012);
   fChain->SetBranchAddress("eleSigmaIPhiIPhi", &eleSigmaIPhiIPhi, &b_eleSigmaIPhiIPhi);
   fChain->SetBranchAddress("eleMissHits", &eleMissHits, &b_eleMissHits);
   fChain->SetBranchAddress("eleESEffSigmaRR", &eleESEffSigmaRR, &b_eleESEffSigmaRR);
   fChain->SetBranchAddress("elePFChIso", &elePFChIso, &b_elePFChIso);
   fChain->SetBranchAddress("elePFPhoIso", &elePFPhoIso, &b_elePFPhoIso);
   fChain->SetBranchAddress("elePFNeuIso", &elePFNeuIso, &b_elePFNeuIso);
   fChain->SetBranchAddress("elePFPUIso", &elePFPUIso, &b_elePFPUIso);
   fChain->SetBranchAddress("elePFChIso03", &elePFChIso03, &b_elePFChIso03);
   fChain->SetBranchAddress("elePFPhoIso03", &elePFPhoIso03, &b_elePFPhoIso03);
   fChain->SetBranchAddress("elePFNeuIso03", &elePFNeuIso03, &b_elePFNeuIso03);
   fChain->SetBranchAddress("elePFChIso04", &elePFChIso04, &b_elePFChIso04);
   fChain->SetBranchAddress("elePFPhoIso04", &elePFPhoIso04, &b_elePFPhoIso04);
   fChain->SetBranchAddress("elePFNeuIso04", &elePFNeuIso04, &b_elePFNeuIso04);
   fChain->SetBranchAddress("eleBC1E", &eleBC1E, &b_eleBC1E);
   fChain->SetBranchAddress("eleBC1Eta", &eleBC1Eta, &b_eleBC1Eta);
   fChain->SetBranchAddress("eleBC2E", &eleBC2E, &b_eleBC2E);
   fChain->SetBranchAddress("eleBC2Eta", &eleBC2Eta, &b_eleBC2Eta);
   fChain->SetBranchAddress("nPho", &nPho, &b_nPho);
   fChain->SetBranchAddress("phoE", &phoE, &b_phoE);
   fChain->SetBranchAddress("phoEt", &phoEt, &b_phoEt);
   fChain->SetBranchAddress("phoEta", &phoEta, &b_phoEta);
   fChain->SetBranchAddress("phoPhi", &phoPhi, &b_phoPhi);
   fChain->SetBranchAddress("phoSCE", &phoSCE, &b_phoSCE);
   fChain->SetBranchAddress("phoSCRawE", &phoSCRawE, &b_phoSCRawE);
   fChain->SetBranchAddress("phoESEn", &phoESEn, &b_phoESEn);
   fChain->SetBranchAddress("phoSCEta", &phoSCEta, &b_phoSCEta);
   fChain->SetBranchAddress("phoSCPhi", &phoSCPhi, &b_phoSCPhi);
   fChain->SetBranchAddress("phoSCEtaWidth", &phoSCEtaWidth, &b_phoSCEtaWidth);
   fChain->SetBranchAddress("phoSCPhiWidth", &phoSCPhiWidth, &b_phoSCPhiWidth);
   fChain->SetBranchAddress("phoSCBrem", &phoSCBrem, &b_phoSCBrem);
   fChain->SetBranchAddress("phohasPixelSeed", &phohasPixelSeed, &b_phohasPixelSeed);
   fChain->SetBranchAddress("phoR9", &phoR9, &b_phoR9);
   fChain->SetBranchAddress("phoHadTowerOverEm", &phoHadTowerOverEm, &b_phoHadTowerOverEm);
   fChain->SetBranchAddress("phoHoverE", &phoHoverE, &b_phoHoverE);
   fChain->SetBranchAddress("phoSigmaIEtaIEta", &phoSigmaIEtaIEta, &b_phoSigmaIEtaIEta);
   fChain->SetBranchAddress("phoE1x3", &phoE1x3, &b_phoE1x3);
   fChain->SetBranchAddress("phoE2x2", &phoE2x2, &b_phoE2x2);
   fChain->SetBranchAddress("phoE3x3", &phoE3x3, &b_phoE3x3);
   fChain->SetBranchAddress("phoE2x5Max", &phoE2x5Max, &b_phoE2x5Max);
   fChain->SetBranchAddress("phoE1x5", &phoE1x5, &b_phoE1x5);
   fChain->SetBranchAddress("phoE2x5", &phoE2x5, &b_phoE2x5);
   fChain->SetBranchAddress("phoE5x5", &phoE5x5, &b_phoE5x5);
   fChain->SetBranchAddress("phoMaxEnergyXtal", &phoMaxEnergyXtal, &b_phoMaxEnergyXtal);
   fChain->SetBranchAddress("phoSigmaEtaEta", &phoSigmaEtaEta, &b_phoSigmaEtaEta);
   fChain->SetBranchAddress("phoR1x5", &phoR1x5, &b_phoR1x5);
   fChain->SetBranchAddress("phoR2x5", &phoR2x5, &b_phoR2x5);
   fChain->SetBranchAddress("phoESEffSigmaRR", &phoESEffSigmaRR, &b_phoESEffSigmaRR);
   fChain->SetBranchAddress("phoSigmaIEtaIEta_2012", &phoSigmaIEtaIEta_2012, &b_phoSigmaIEtaIEta_2012);
   fChain->SetBranchAddress("phoSigmaIEtaIPhi_2012", &phoSigmaIEtaIPhi_2012, &b_phoSigmaIEtaIPhi_2012);
   fChain->SetBranchAddress("phoSigmaIPhiIPhi_2012", &phoSigmaIPhiIPhi_2012, &b_phoSigmaIPhiIPhi_2012);
   fChain->SetBranchAddress("phoE1x3_2012", &phoE1x3_2012, &b_phoE1x3_2012);
   fChain->SetBranchAddress("phoE2x2_2012", &phoE2x2_2012, &b_phoE2x2_2012);
   fChain->SetBranchAddress("phoE3x3_2012", &phoE3x3_2012, &b_phoE3x3_2012);
   fChain->SetBranchAddress("phoE2x5Max_2012", &phoE2x5Max_2012, &b_phoE2x5Max_2012);
   fChain->SetBranchAddress("phoE5x5_2012", &phoE5x5_2012, &b_phoE5x5_2012);
   fChain->SetBranchAddress("phoBC1E", &phoBC1E, &b_phoBC1E);
   fChain->SetBranchAddress("phoBC1Eta", &phoBC1Eta, &b_phoBC1Eta);
   fChain->SetBranchAddress("phoBC2E", &phoBC2E, &b_phoBC2E);
   fChain->SetBranchAddress("phoBC2Eta", &phoBC2Eta, &b_phoBC2Eta);
   fChain->SetBranchAddress("pho_ecalClusterIsoR2", &pho_ecalClusterIsoR2, &b_pho_ecalClusterIsoR2);
   fChain->SetBranchAddress("pho_ecalClusterIsoR3", &pho_ecalClusterIsoR3, &b_pho_ecalClusterIsoR3);
   fChain->SetBranchAddress("pho_ecalClusterIsoR4", &pho_ecalClusterIsoR4, &b_pho_ecalClusterIsoR4);
   fChain->SetBranchAddress("pho_ecalClusterIsoR5", &pho_ecalClusterIsoR5, &b_pho_ecalClusterIsoR5);
   fChain->SetBranchAddress("pho_hcalRechitIsoR1", &pho_hcalRechitIsoR1, &b_pho_hcalRechitIsoR1);
   fChain->SetBranchAddress("pho_hcalRechitIsoR2", &pho_hcalRechitIsoR2, &b_pho_hcalRechitIsoR2);
   fChain->SetBranchAddress("pho_hcalRechitIsoR3", &pho_hcalRechitIsoR3, &b_pho_hcalRechitIsoR3);
   fChain->SetBranchAddress("pho_hcalRechitIsoR4", &pho_hcalRechitIsoR4, &b_pho_hcalRechitIsoR4);
   fChain->SetBranchAddress("pho_hcalRechitIsoR5", &pho_hcalRechitIsoR5, &b_pho_hcalRechitIsoR5);
   fChain->SetBranchAddress("pho_trackIsoR1PtCut20", &pho_trackIsoR1PtCut20, &b_pho_trackIsoR1PtCut20);
   fChain->SetBranchAddress("pho_trackIsoR2PtCut20", &pho_trackIsoR2PtCut20, &b_pho_trackIsoR2PtCut20);
   fChain->SetBranchAddress("pho_trackIsoR3PtCut20", &pho_trackIsoR3PtCut20, &b_pho_trackIsoR3PtCut20);
   fChain->SetBranchAddress("pho_trackIsoR4PtCut20", &pho_trackIsoR4PtCut20, &b_pho_trackIsoR4PtCut20);
   fChain->SetBranchAddress("pho_trackIsoR5PtCut20", &pho_trackIsoR5PtCut20, &b_pho_trackIsoR5PtCut20);
   fChain->SetBranchAddress("pho_swissCrx", &pho_swissCrx, &b_pho_swissCrx);
   fChain->SetBranchAddress("pho_seedTime", &pho_seedTime, &b_pho_seedTime);
   fChain->SetBranchAddress("pfcIso1", &pfcIso1, &b_pfcIso1);
   fChain->SetBranchAddress("pfcIso2", &pfcIso2, &b_pfcIso2);
   fChain->SetBranchAddress("pfcIso3", &pfcIso3, &b_pfcIso3);
   fChain->SetBranchAddress("pfcIso4", &pfcIso4, &b_pfcIso4);
   fChain->SetBranchAddress("pfcIso5", &pfcIso5, &b_pfcIso5);
   fChain->SetBranchAddress("pfpIso1", &pfpIso1, &b_pfpIso1);
   fChain->SetBranchAddress("pfpIso2", &pfpIso2, &b_pfpIso2);
   fChain->SetBranchAddress("pfpIso3", &pfpIso3, &b_pfpIso3);
   fChain->SetBranchAddress("pfpIso4", &pfpIso4, &b_pfpIso4);
   fChain->SetBranchAddress("pfpIso5", &pfpIso5, &b_pfpIso5);
   fChain->SetBranchAddress("pfnIso1", &pfnIso1, &b_pfnIso1);
   fChain->SetBranchAddress("pfnIso2", &pfnIso2, &b_pfnIso2);
   fChain->SetBranchAddress("pfnIso3", &pfnIso3, &b_pfnIso3);
   fChain->SetBranchAddress("pfnIso4", &pfnIso4, &b_pfnIso4);
   fChain->SetBranchAddress("pfnIso5", &pfnIso5, &b_pfnIso5);
   fChain->SetBranchAddress("nMu", &nMu, &b_nMu);
   fChain->SetBranchAddress("muPt", &muPt, &b_muPt);
   fChain->SetBranchAddress("muEta", &muEta, &b_muEta);
   fChain->SetBranchAddress("muPhi", &muPhi, &b_muPhi);
   fChain->SetBranchAddress("muCharge", &muCharge, &b_muCharge);
   fChain->SetBranchAddress("muType", &muType, &b_muType);
   fChain->SetBranchAddress("muIsGood", &muIsGood, &b_muIsGood);
   fChain->SetBranchAddress("muD0", &muD0, &b_muD0);
   fChain->SetBranchAddress("muDz", &muDz, &b_muDz);
   fChain->SetBranchAddress("muChi2NDF", &muChi2NDF, &b_muChi2NDF);
   fChain->SetBranchAddress("muInnerD0", &muInnerD0, &b_muInnerD0);
   fChain->SetBranchAddress("muInnerDz", &muInnerDz, &b_muInnerDz);
   fChain->SetBranchAddress("muTrkLayers", &muTrkLayers, &b_muTrkLayers);
   fChain->SetBranchAddress("muPixelLayers", &muPixelLayers, &b_muPixelLayers);
   fChain->SetBranchAddress("muPixelHits", &muPixelHits, &b_muPixelHits);
   fChain->SetBranchAddress("muMuonHits", &muMuonHits, &b_muMuonHits);
   fChain->SetBranchAddress("muTrkQuality", &muTrkQuality, &b_muTrkQuality);
   fChain->SetBranchAddress("muStations", &muStations, &b_muStations);
   fChain->SetBranchAddress("muIsoTrk", &muIsoTrk, &b_muIsoTrk);
   fChain->SetBranchAddress("muPFChIso", &muPFChIso, &b_muPFChIso);
   fChain->SetBranchAddress("muPFPhoIso", &muPFPhoIso, &b_muPFPhoIso);
   fChain->SetBranchAddress("muPFNeuIso", &muPFNeuIso, &b_muPFNeuIso);
   fChain->SetBranchAddress("muPFPUIso", &muPFPUIso, &b_muPFPUIso);
   Notify();
}

Bool_t EventTree::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void EventTree::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t EventTree::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef EventTree_cxx
