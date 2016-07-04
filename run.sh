indir=
infile=
inlabel=
inmode=
until [ -z "$1" ]; do
case "$1" in
-i|--input) shift; infile="$1"; shift ;;
-d|--dir) shift; indir="$1"; shift;;
-l|--label) shift; inlabel="$1"; shift;;
-m|--mode) shift; inmode="$1"; shift;;
-h|--help) shift; echo "sh run.sh -d(--dir) your/directory -i(--input) HiForest_0.root -l(--label) label for output name"; shift;;
-*) shift ;;
*) break ;;
esac
done
echo "Flags leidas"

WD=/afs/cern.ch/work/e/eruizvel/private/MultiJetEdna/MultiJet
cd $WD
echo "cambio de dir"

#g++ $WD/MJSkim.C `fastjet-install/bin/fastjet-config --cxxflags --libs --plugins` $(root-config --cflags --libs) -lNsubjettiness -Wall -O2 -o $WD/dijetSkim
#echo "MJSkim compliled"


#dir=root://eoscms//eos/cms/store/cmst3/group/hintt/mverweij/jetsPbPb/Run2/MC/PP/Pythia8_Dijet100_pp502_TuneCUETP8M1/crab_HiForestDijet100PP_v4/160510_111948/0000/
#dir=root://eoscms//eos/cms/store/group/cmst3/group/hintt/mverweij/CS/MC/PbPb/PYTHIA_QCD_TuneCUETP8M1_cfi_GEN_SIM_5020GeV/crab_HiForestDijet80CSV19/160329_171047/0000
#dir=root://eoscms//eos/cms/store/group/cmst3/group/hintt/mverweij/PP5TeV/data/HighPtJet80/crab_HighPtJet80_v2/160525_095945/mergePartialV2/
#dir=root://eoscms//eos/cms/store/group/cmst3/group/hintt/mverweij/jetsPbPb/Run2/MC/PP/Pythia6_Dijet100_pp502/local/zcutcombi/v1/
#dir=root://eoscms//eos/cms/store/group/cmst3/group/hintt/mverweij/PP5TeV/data/HighPtJet80/crab_HighPtJet80_v2/160525_095945/mergePartialV2/
dir=root://eoscms//eos/cms$indir

out=$WD/$inlabel$infile

echo | awk -v dataset=$dir/$infile -v  outfile=$out -v mode=$inmode '{print "./dijetSkim \""dataset"\" \""infile"\" \""outfile"\" \""mode"\""}' | bash