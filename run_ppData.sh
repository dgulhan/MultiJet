

indir=
infile=
inlabel=

until [ -z "$1" ]; do
case "$1" in
-i|--input) shift; infile="$1"; shift ;;
-d|--dir) shift; indir="$1"; shift;;
-l|--label) shift; inlabel="$1"; shift;;
-h|--help) shift; echo "sh run_ppData.sh -d(--dir) your/directory -i(--input) HiForest_0.root -l(--label) label for output name"; shift;;
-*) shift ;;
*) break ;;
esac
done
echo "Flags leidas"


WD=/afs/cern.ch/work/e/eruizvel/private/MultiJetEdna/MultiJet
cd $WD


dir=root://eoscms//eos/cms$indir

out=$WD/$inlabel$infile

./dijetSkim_ppData $dir/$infile $out