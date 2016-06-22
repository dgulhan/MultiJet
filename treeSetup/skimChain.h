//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Jan 22 19:01:16 2013 by ROOT version 5.32/00
// from TTree HltTree/
// found on file: root://eoscms//eos/cms/store/caf/user/velicanu/PA2013_merged/PA2013_HiForest_Express_r210534_stablebeams_72bunch.root
//////////////////////////////////////////////////////////

#ifndef skimChain_h
#define skimChain_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class skimChain {
public :
   TChain          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain
   // Declaration of leaf types
   Int_t           superFilterPath;
   Int_t           reco_extra;
   Int_t           reco_extra_jet;
   Int_t           pat_step;
   Int_t           ana_step;
   Int_t           pcollisionEventSelection;
   Int_t           pHBHENoiseFilter;
   Int_t           HBHENoiseFilterResultRun2Loose;
   Int_t           phiEcalRecHitSpikeFilter;
   Int_t           pPAcollisionEventSelectionPA;
   Int_t           phfPosFilter3;
   Int_t           phfNegFilter3;
   Int_t           phfPosFilter2;
   Int_t           phfNegFilter2;
   Int_t           phfPosFilter1;
   Int_t           phfNegFilter1;
   Int_t           phltPixelClusterShapeFilter;
   Int_t           pprimaryvertexFilter;
   Int_t           pPAprimaryVertexFilter;
   Int_t           pBeamScrapingFilter;
   Int_t           pVertexFilterCutG;
   Int_t           pVertexFilterCutGloose;
   Int_t           pVertexFilterCutGtight;
   Int_t           pVertexFilterCutGplus;
   Int_t           pVertexFilterCutE;
   Int_t           pVertexFilterCutEandG;
   Int_t           hltAna;

   // List of branches
   TBranch        *b_superFilterPath;   //!
   TBranch        *b_reco_extra;   //!
   TBranch        *b_reco_extra_jet;   //!
   TBranch        *b_pat_step;   //!
   TBranch        *b_ana_step;   //!
   TBranch        *b_pcollisionEventSelection;   //!
   TBranch        *b_pHBHENoiseFilter;   //!
   TBranch        *b_HBHENoiseFilterResultRun2Loose;   //!
   TBranch        *b_phiEcalRecHitSpikeFilter;   //!
   TBranch        *b_pPAcollisionEventSelectionPA;   //!
   TBranch        *b_phfPosFilter3;   //!
   TBranch        *b_phfNegFilter3;   //!
   TBranch        *b_phfPosFilter2;   //!
   TBranch        *b_phfNegFilter2;   //!
   TBranch        *b_phfPosFilter1;   //!
   TBranch        *b_phfNegFilter1;   //!
   TBranch        *b_phltPixelClusterShapeFilter;   //!
   TBranch        *b_pprimaryvertexFilter;   //!
   TBranch        *b_pPAprimaryVertexFilter;   //!
   TBranch        *b_pBeamScrapingFilter;   //!
   TBranch        *b_pVertexFilterCutG;   //!
   TBranch        *b_pVertexFilterCutGloose;   //!
   TBranch        *b_pVertexFilterCutGtight;   //!
   TBranch        *b_pVertexFilterCutGplus;   //!
   TBranch        *b_pVertexFilterCutE;   //!
   TBranch        *b_pVertexFilterCutEandG;   //!
   TBranch        *b_hltAna;   //!


   // skimChain(TString infile="root://eoscms//eos/cms/store/caf/user/velicanu/PA2013_merged/PA2013_HiForest_Express_r210614_autoforest.root", TTree *tree=0);
   skimChain(TString infile, TChain *tree=0);
   virtual ~skimChain();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TChain *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef skimChain_cxx
skimChain::skimChain(TString infile,TChain *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   
   tree = new TChain("skimanalysis/HltTree");
   tree->Add(infile.Data());
   Init(tree);
}

skimChain::~skimChain()
{
   if (!fChain) return;
}

Int_t skimChain::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t skimChain::LoadTree(Long64_t entry)
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

void skimChain::Init(TChain *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("superFilterPath", &superFilterPath, &b_superFilterPath);
   fChain->SetBranchAddress("reco_extra", &reco_extra, &b_reco_extra);
   fChain->SetBranchAddress("reco_extra_jet", &reco_extra_jet, &b_reco_extra_jet);
   fChain->SetBranchAddress("pat_step", &pat_step, &b_pat_step);
   fChain->SetBranchAddress("ana_step", &ana_step, &b_ana_step);
   fChain->SetBranchAddress("pcollisionEventSelection", &pcollisionEventSelection, &b_pcollisionEventSelection);
   fChain->SetBranchAddress("pHBHENoiseFilter", &pHBHENoiseFilter, &b_pHBHENoiseFilter);
   fChain->SetBranchAddress("HBHENoiseFilterResultRun2Loose", &HBHENoiseFilterResultRun2Loose, &b_HBHENoiseFilterResultRun2Loose);
   fChain->SetBranchAddress("phiEcalRecHitSpikeFilter", &phiEcalRecHitSpikeFilter, &b_phiEcalRecHitSpikeFilter);
   fChain->SetBranchAddress("pPAcollisionEventSelectionPA", &pPAcollisionEventSelectionPA, &b_pPAcollisionEventSelectionPA);
   fChain->SetBranchAddress("phfPosFilter3", &phfPosFilter3, &b_phfPosFilter3);
   fChain->SetBranchAddress("phfNegFilter3", &phfNegFilter3, &b_phfNegFilter3);
   fChain->SetBranchAddress("phfPosFilter2", &phfPosFilter2, &b_phfPosFilter2);
   fChain->SetBranchAddress("phfNegFilter2", &phfNegFilter2, &b_phfNegFilter2);
   fChain->SetBranchAddress("phfPosFilter1", &phfPosFilter1, &b_phfPosFilter1);
   fChain->SetBranchAddress("phfNegFilter1", &phfNegFilter1, &b_phfNegFilter1);
   fChain->SetBranchAddress("phltPixelClusterShapeFilter", &phltPixelClusterShapeFilter, &b_phltPixelClusterShapeFilter);
   fChain->SetBranchAddress("pprimaryvertexFilter", &pprimaryvertexFilter, &b_pprimaryvertexFilter);
   fChain->SetBranchAddress("pPAprimaryVertexFilter", &pPAprimaryVertexFilter, &b_pPAprimaryVertexFilter);
   fChain->SetBranchAddress("pBeamScrapingFilter", &pBeamScrapingFilter, &b_pBeamScrapingFilter);
   fChain->SetBranchAddress("pVertexFilterCutG", &pVertexFilterCutG, &b_pVertexFilterCutG);
   fChain->SetBranchAddress("pVertexFilterCutGloose", &pVertexFilterCutGloose, &b_pVertexFilterCutGloose);
   fChain->SetBranchAddress("pVertexFilterCutGtight", &pVertexFilterCutGtight, &b_pVertexFilterCutGtight);
   fChain->SetBranchAddress("pVertexFilterCutGplus", &pVertexFilterCutGplus, &b_pVertexFilterCutGplus);
   fChain->SetBranchAddress("pVertexFilterCutE", &pVertexFilterCutE, &b_pVertexFilterCutE);
   fChain->SetBranchAddress("pVertexFilterCutEandG", &pVertexFilterCutEandG, &b_pVertexFilterCutEandG);
   fChain->SetBranchAddress("hltAna", &hltAna, &b_hltAna);
   Notify();
}

Bool_t skimChain::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void skimChain::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t skimChain::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef skimChain_cxx
