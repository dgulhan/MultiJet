

indir=
infile=
inlabel=

until [ -z "$1" ]; do
case "$1" in
-i|--input) shift; infile="$1"; shift ;;
-d|--dir) shift; indir="$1"; shift;;
-l|--label) shift; inlabel="$1"; shift;;
-h|--help) shift; echo "sh run.sh -d(--dir) your/directory -i(--input) HiForest_0.root -l(--label) label for output name"; shift;;
-*) shift ;;
*) break ;;
esac
done
echo "Flags leidas"


WD=/afs/cern.ch/work/e/eruizvel/private/MultiJetEdna/MultiJet
cd $WD

#g++ $WD/MJSkim.C `fastjet-install/bin/fastjet-config --cxxflags --libs --plugins` $(root-config --cflags --libs) -lNsubjettiness -Wall -O2 -o $WD/dijetSkim
dir=root://eoscms//eos/cms$indir

out=$WD/$inlabel$infile

./dijetSkim $dir/$infile $out

#echo | awk -v dataset=$dir/$infile -v  outfile=$out '{print "./dijetSkim \""dataset"\" \""infile"\" \""outfile"\""}' | bash