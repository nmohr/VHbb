#take as input the directory where the step2ntuples are stored and it created soft link such a way that all the root file that make_histo.cxx produces are in histo folder and not mixed with the original files

echo "As input it takes as input the dir where the ntuple are stored"

DIR=${1}
VERSION=${2}
mkdir histos
cd histos
ls ${DIR}*${VERSION}*root | grep -v histos >> fileList.txt
#find ${DIR} -type f -print | grep -v histos >> fileList.txt
while read line
do ln -s $line ${line/*ZllH/ZllH} 
done < fileList.txt 
cd -
