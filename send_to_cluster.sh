

WD=/afs/cern.ch/work/e/eruizvel/private/MuliJetEdna/MultiJet


indir=/store/group/cmst3/group/hintt/mverweij/PP5TeV/data/HighPtJet80/crab_HighPtJet80_v2/160525_095945/mergePartialV2

echo $indir
FILES=$(eos ls $indir)

for f in ${FILES[@]}
do
    echo $f
done

echo "FIN"