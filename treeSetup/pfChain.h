//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed May 18 03:47:47 2016 by ROOT version 5.32/00
// from TTree pfChain/dijet tree
// found on file: /mnt/hadoop/cms/store/user/dgulhan/pPb/HP04/prod16/Hijing_Pythia_pt15/HiForest_v77_merged01/pt15_HP04_prod16_v77_merged_forest_0.root
//////////////////////////////////////////////////////////

#ifndef pfChain_h
#define pfChain_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

// Fixed size dimensions of array or collections stored in the TTree if any.

class pfChain {
public :
   TChain          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

   // Declaration of leaf types
   Int_t           nPFpart;
   Int_t           pfId[1106];   //[nPFpart]
   Float_t         pfPt[1106];   //[nPFpart]
   Float_t         pfEta[1106];   //[nPFpart]
   Float_t         pfPhi[1106];   //[nPFpart]

   // List of branches
   TBranch        *b_nPFpart;   //!
   TBranch        *b_pfId;   //!
   TBranch        *b_pfPt;   //!
   TBranch        *b_pfEta;   //!
   TBranch        *b_pfPhi;   //!
   
   TFile *f;
   pfChain(TString infile, TChain *tree=0);
   virtual ~pfChain();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TChain *tree);
   virtual void     Loop();
   void     Close();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef pfChain_cxx
pfChain::pfChain(TString infile, TChain *tree) 
{

   tree = new TChain("pfcandAnalyzer/pfChain");
   tree->Add(infile.Data());

   Init(tree);
}

pfChain::~pfChain()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t pfChain::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Int_t pfChain::GetEntriesFast()
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntre(entry);
}
Long64_t pfChain::LoadTree(Long64_t entry)
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

void pfChain::Init(TChain *tree)
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

   fChain->SetBranchAddress("nPFpart", &nPFpart, &b_nPFpart);
   fChain->SetBranchAddress("pfId", pfId, &b_pfId);
   fChain->SetBranchAddress("pfPt", pfPt, &b_pfPt);
   fChain->SetBranchAddress("pfEta", pfEta, &b_pfEta);
   fChain->SetBranchAddress("pfPhi", pfPhi, &b_pfPhi);
   Notify();
}

Bool_t pfChain::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void pfChain::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t pfChain::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
void pfChain::Close() 
{
   f->Close();
   delete fChain;
}
#endif // #ifdef pfChain_cxx
