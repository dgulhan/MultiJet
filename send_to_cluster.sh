WD=/afs/cern.ch/work/e/eruizvel/private/MultiJetEdna/MultiJet



#######
#Changed by user

indir=/store/group/cmst3/group/hintt/mverweij/jetsPbPb/Run2/MC/PP/Pythia8_Dijet80_pp502_TuneCUETP8M1/crab_HiForestDijet80PP_v5/160701_225932/0000
label=ppPy8hat80

#######

FILES=$(eos ls $indir/*.root)

for f in ${FILES[@]}
do
echo "bsub -q 8nh $WD/run.sh -d $indir -i $f -l $label"
bsub -q 8nh $WD/run.sh -d $indir -i $f -l $label
done


bjobs


