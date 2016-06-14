g++ MJSkim.C `fastjet-install/bin/fastjet-config --cxxflags --libs --plugins` $(root-config --cflags --libs) -lNsubjettiness -Wall -O2 -o dijetSkim.exe

dir=root://eoscms//eos/cms/store/cmst3/group/hintt/mverweij/jetsPbPb/Run2/MC/PP/Pythia8_Dijet100_pp502_TuneCUETP8M1/crab_HiForestDijet100PP_v4/160510_111948/0000/
in=HiForestAOD_8.root
out=testnR.root

echo | awk -v dataset=$dir -v infile=$in -v outfile=$out '{print "./dijetSkim.exe \""dataset"\" \""infile"\" \""outfile"\""}' | bash
