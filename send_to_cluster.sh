
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

indir=/store/group/cmst3/group/hintt/mverweij/PP5TeV/data/HighPtJet80/crab_HighPtJet80_v2/160525_095945/mergePartialV2

FILES=$(eos ls $indir/*.root)

for f in ${FILES[@]}
do
    echo "bsub -q 1nd $WD/run.sh -d $indir -i $f"
    bsub -q 1nd $WD/run.sh -d $indir -i $f
done


echo "jobs submited..."

echo "status"
bjobs



