WD=/afs/cern.ch/work/e/eruizvel/private/MultiJetEdna/MultiJet


#######
#Changed by user
indir=/store/group/cmst3/group/hintt/mverweij/CS/MC/PbPb/Pythia8_Dijet80_pp_TuneCUETP8M1_Hydjet_Min_Bias_5020GeV/crab_HiForestDijet80V3/160701_225507/0000
label=PbPbPy8hat80
#######

FILES=$(eos ls $indir/*.root)

for f in ${FILES[@]}
do
echo "bsub -q 1nd $WD/run.sh -d $indir -i $f -l $label"
bsub -q 8nh $WD/run_PbPbMC.sh -d $indir -i $f -l $labeldone


bjobs


