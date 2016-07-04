## mounting eos necessary. see https://twiki.cern.ch/twiki/bin/view/TOTEM/CompEOS

#HOME=/afs/cern.ch/user/e/eruizvel/private
#echo "Mounting eos at $HOME"
#eosmount $HOME/eos


#######
#Changed by user
#indir=/store/group/cmst3/group/hintt/mverweij/jetsPbPb/Run2/MC/PP/Pythia6_Dijet100_pp502/local/zcutcombi/v1
indir=/store/group/cmst3/group/hintt/mverweij/CS/MC/PbPb/Pythia8_Dijet80_pp_TuneCUETP8M1_Hydjet_Min_Bias_5020GeV/crab_HiForestDijet80V3/160701_225507/0000
label=PbPbPy8hat80
WD=/afs/cern.ch/work/e/eruizvel/private/MultiJetEdna/MultiJet
#######

FILES=$(eos ls $indir/*.root)

for f in ${FILES[@]}
do
echo "bsub -q 1nd $WD/run.sh -d $indir -i $f -l $label"
bsub -q 1nd $WD/run.sh -d $indir -i $f -l $label
done


echo "jobs submited..."

echo "status"
bjobs


