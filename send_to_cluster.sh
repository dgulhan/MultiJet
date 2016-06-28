
## mounting eos necessary. see https://twiki.cern.ch/twiki/bin/view/TOTEM/CompEOS

#HOME=/afs/cern.ch/user/e/eruizvel/private
WD=/afs/cern.ch/work/e/eruizvel/private/MuliJetEdna/MultiJet

#echo "Mounting eos at $HOME"
#eosmount $HOME/eos


indir=

until [ -z "$1" ]; do
case "$1" in
-i|--input) shift; indir="$1"; shift ;;
-h|--help) shift; echo "sh send_to_cluster.sh -i(--input) /your/dir/wo/eos "; shift;;
-*) shift ;;
*) break ;;
esac
done

#######
#Changed by user
indir=/store/group/cmst3/group/hintt/mverweij/jetsPbPb/Run2/MC/PP/Pythia6_Dijet100_pp502/local/zcutcombi/v1
label=Pyth6Dij100PP
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

