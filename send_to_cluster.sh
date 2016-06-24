

WD=/afs/cern.ch/work/e/eruizvel/private/MuliJetEdna/MultiJet


indir=

until [ -z "$1" ]; do
    case "$1" in
    -d|--dir) shift; indir="$1"; shift ;;
    -h|--help) shift; echo "sh send_to_cluster.sh -d(--dir) /your/directory "; shift;;
    -*) shift ;;
    *) break ;;
    esac
done


FILES=$(ls $indir/*.root)

echo ${FILES[@]}