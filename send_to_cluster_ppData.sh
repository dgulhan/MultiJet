WD=/afs/cern.ch/work/e/eruizvel/private/MultiJetEdna/MultiJet


#######
#Changed by user
indir=/store/group/cmst3/group/hintt/mverweij/PP5TeV/data/HighPtJet80/crab_HighPtJet80_v2/160525_095945/mergePartialV2

label=ppDatahat80
#######

FILES=$(eos ls $indir/*.root)

for f in ${FILES[@]}
do
echo "bsub -q 1nd $WD/run.sh -d $indir -i $f -l $label"
bsub -q 8nh $WD/run_PbPbMC.sh -d $indir -i $f -l $labeldone


bjobs

