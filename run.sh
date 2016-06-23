

infile=

until [ -z "$1" ]; do
    case "$1" in
        -i|--input) shift; infile="$1"; shift ;;
        -h|--help) shift; echo "sh run.sh -i(--input) HiForest_0.root "; shift;;
        -*) shift ;;
        *) break ;;
    esac
done

g++ MJSkim_no_N.C `fastjet-install/bin/fastjet-config --cxxflags --libs --plugins` $(root-config --cflags --libs) -lNsubjettiness -Wall -O2 -o dijetSkim

#dir=root://eoscms//eos/cms/store/cmst3/group/hintt/mverweij/jetsPbPb/Run2/MC/PP/Pythia8_Dijet100_pp502_TuneCUETP8M1/crab_HiForestDijet100PP_v4/160510_111948/0000/
#dir=root://eoscms//eos/cms/store/group/cmst3/group/hintt/mverweij/CS/MC/PbPb/PYTHIA_QCD_TuneCUETP8M1_cfi_GEN_SIM_5020GeV/crab_HiForestDijet80CSV19/160329_171047/0000
#dir=root://eoscms//eos/cms/store/group/cmst3/group/hintt/mverweij/PP5TeV/data/HighPtJet80/crab_HighPtJet80_v2/160525_095945/mergePartialV2/
#dir=root://eoscms//eos/cms/store/group/cmst3/group/hintt/mverweij/jetsPbPb/Run2/MC/PP/Pythia6_Dijet100_pp502/local/zcutcombi/v1/
dir=root://eoscms//eos/cms/store/group/cmst3/group/hintt/mverweij/PP5TeV/data/HighPtJet80/crab_HighPtJet80_v2/160525_095945/mergePartialV2/

out=MJSkim_pp_Jet80.root

echo | awk -v dataset=$dir/$infile -v  outfile=$out '{print "./dijetSkim \""dataset"\" \""infile"\" \""outfile"\""}' | bash
