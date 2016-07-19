
WD=/afs/cern.ch/work/e/eruizvel/private/MultiJetEdna/MultiJet
g++ /afs/cern.ch/work/e/eruizvel/private/MultiJetEdna/MultiJet/Pull_Skim.C  `fastjet-install/bin/fastjet-config --cxxflags --libs --plugins` $(root-config --cflags --libs) -lNsubjettiness -Wall -O2 -o /afs/cern.ch/work/e/eruizvel/private/MultiJetEdna/MultiJet/dijetPull

chmod 755 $WD/run_pull.sh

#######
#Changed by user
indir=/store/group/cmst3/group/hintt/mverweij/jetsPbPb/Run2/MC/PP/Pythia8_Dijet80_pp502_TuneCUETP8M1/crab_HiForestDijet80PP_v5/160701_225932/0000
label=ppMCpthat80+pull

#indir=/store/group/cmst3/group/hintt/mverweij/CS/MC/PbPb/Pythia8_Dijet80_pp_TuneCUETP8M1_Hydjet_Min_Bias_5020GeV/crab_HiForestDijet80V3/160701_225507/0000

#label=PbPbMCpthat80+pull

#indir=/store/group/cmst3/group/hintt/mverweij/PP5TeV/data/HighPtJet80/crab_HighPtJet80_v2/160525_095945/mergePartialV2
#label=ppDataHighPt80+pull

#indir=/store/group/cmst3/group/hintt/mverweij/CS/data/HIHardProbes/crab_HIHardProbes_v5/160313_203758/merge
#label=PbPbDataHIHardProbes+pull

mode=ppMC

#doMatchAK=1 #false / true

#######

FILES=$(eos ls $indir/*.root)

for f in ${FILES[@]}
do
    echo "bsub -q 1nd $WD/run_pull.sh -d $indir -i $f -l $label -m $mode"
    bsub -q 1nh $WD/run_pull.sh -d $indir -i $f -l $label -m $mode #-a $doMatchAK
done

bjobs

