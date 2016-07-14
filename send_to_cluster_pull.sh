
WD=/afs/cern.ch/work/e/eruizvel/private/MultiJetEdna/MultiJet
g++ /afs/cern.ch/work/e/eruizvel/private/MultiJetEdna/MultiJet/Pull_Skim.C  `fastjet-install/bin/fastjet-config --cxxflags --libs --plugins` $(root-config --cflags --libs) -lNsubjettiness -Wall -O2 -o /afs/cern.ch/work/e/eruizvel/private/MultiJetEdna/MultiJet/dijetPull

chmod 755 $WD/run_pull.sh

#######
#Changed by user
#indir=/store/group/cmst3/group/hintt/mverweij/jetsPbPb/Run2/MC/PP/Pythia8_Dijet80_pp502_TuneCUETP8M1/crab_HiForestDijet80PP_v5/160701_225932/0000
#label=ppMCpthat80+pull
/store/group/cmst3/group/hintt/mverweij/CS/MC/PbPb/Pythia8_Dijet80_pp_TuneCUETP8M1_Hydjet_Min_Bias_5020GeV/crab_HiForestDijet80V3/160701_225507/0000

label=PbPbMCpthat80+pull

mode=PbPbMC
#######

FILES=$(eos ls $indir/*.root)

for f in ${FILES[@]}
do
    echo "bsub -q 1nd $WD/run_pull.sh -d $indir -i $f -l $labeldone -m $mode"
    bsub -q 1nd $WD/run_pull.sh -d $indir -i $f -l $label -m $mode
done

bjobs

