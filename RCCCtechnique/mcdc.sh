#Written by Sangharatna Godboley and Rasool.
#This shell script automates the RCCC sequence generator algorithm and Condition Marker algorithm.
export BenchmarkName=$1
export TOOL=$2

rm -f SequenceGenerator/exp/* 
rm -f -R condition-marker/klee-out* 

cd SequenceGenerator/ 
./seqshell.sh "$BenchmarkName.c" "$TOOL"
cd ..
rm SequenceGenerator/Seq_For_Pred*

res1=$(date +%s.%N)
let s=1
for x in `ls -v SequenceGenerator/exp/Sequence*`; 
do 
    condition-marker/run.sh $BenchmarkName $x $TOOL;
    mkdir condition-marker/llcode-"$1"
    mv condition-marker/${BenchmarkName}1.ll condition-marker/llcode-"$1"/${BenchmarkName}$s.ll
    mkdir condition-marker/Messages-"$1"
    mv condition-marker/${BenchmarkName}1.msg condition-marker/Messages-"$1"/${BenchmarkName}$s.msg
    ((s =s+1));
done
#For synchorinization of sequences and test cases.
for x in `ls -v condition-marker/$BenchmarkName-run-$TOOL/Sequence*`; 
do 
 
     cat $x >> condition-marker/$BenchmarkName-run-$TOOL/TESTSUITE.txt
done

res2=$(date +%s.%N)
dt=$(echo "$res2 - $res1" | bc)
dd=$(echo "$dt/86400" | bc)
dt2=$(echo "$dt-86400*$dd" | bc)
dh=$(echo "$dt2/3600" | bc)
dt3=$(echo "$dt2-3600*$dh" | bc)
dm=$(echo "$dt3/60" | bc)
ds=$(echo "$dt3-60*$dm" | bc)

printf "Total runtime: %d:%02d:%02d:%02.4f\n" $dd $dh $dm $ds
mkdir condition-marker/"$1-run-$2"/"$2"
mv condition-marker/klee-out* condition-marker/"$1-run-$2"/"$2"

