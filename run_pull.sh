

indir=
infile=
inlabel=
inmode=
inmatch=

until [ -z "$1" ]; do
case "$1" in
-i|--input) shift; infile="$1"; shift ;;
-d|--dir) shift; indir="$1"; shift;;
-l|--label) shift; inlabel="$1"; shift;;
-m|--mode) shift; inmode="$1"; shift;;
-a|--akmatch) shift; inmatch="$1"; shift;;
-h|--help) shift; echo "sh run_pull.sh -d(--dir) your/directory -i(--input) HiForest_0.root -l(--label) label for output name -m ppMC or PbPbData f.e -a true or false for match to akt "; shift;;
-*) shift ;;
*) break ;;
esac
done



WD=/afs/cern.ch/work/e/eruizvel/private/MultiJetEdna/MultiJet
cd $WD


dir=root://eoscms//eos/cms$indir

out=$WD/$inlabel$infile

echo "./dijetPull $dir/$infile $out $inmode $inmatch"
./dijetPull $dir/$infile $out $inmode true