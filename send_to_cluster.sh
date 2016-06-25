
## mounting eos necessary. see https://twiki.cern.ch/twiki/bin/view/TOTEM/CompEOS

HOME=/afs/cern.ch/user/e/eruizvel/private
WD=/afs/cern.ch/work/e/eruizvel/private/MuliJetEdna/MultiJet

echo "Mounting eos at $HOME"
eosmount $HOME/eos


indir=

until [ -z "$1" ]; do
case "$1" in
-i|--input) shift; indir="$1"; shift ;;
-h|--help) shift; echo "sh send_to_cluster.sh -i(--input) /your/dir/wo/eos "; shift;;
-*) shift ;;
*) break ;;
esac
done

FILES=$(eos ls $indir/*.root)

for f in ${FILES[@]}
do
    echo "f"
done


eosforceumount $HOME/eos
echo "eos unmounted and jobs submited..."



