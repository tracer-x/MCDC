#Written by Sangharatna Godboley and Rasool
#This shell script automates the RCCC sequence generator algorithm and Condition Marker algorithm.
export BENCHMARK=$1
export TOOL=$2

rm -f SequenceGenerator/exp/* 
rm -f -R condition-marker/klee-out* 

cd SequenceGenerator/ 
./seqshell.sh "$BENCHMARK.c" "$TOOL"
cd ..
rm SequenceGenerator/Seq_For_Pred*



cd condition-marker/
./kappa.sh $BENCHMARK
mkdir llcode-$BENCHMARK
mkdir klee-new
mkdir $BENCHMARK-run-$TOOL
mkdir $BENCHMARK-ERROR-LIST-$TOOL
mkdir $BENCHMARK-KTEST-$TOOL
./txmcdc.sh $BENCHMARK
cd ..

#let s=1
#for x in `ls -v SequenceGenerator/exp/Sequence-pred-1-*`;  
#do 
    
    #mkdir condition-marker/llcode-"$1"
    #mv condition-marker/${BenchmarkName}1.ll condition-marker/llcode-"$1"/${BenchmarkName}$s.ll
    #((s =s+1));
#done
#For synchorinization of sequences and test cases.
for x in `ls -v condition-marker/$BENCHMARK-run-$TOOL/${BENCHMARK}KAPPA-*`; 
do 
 
     cat $x >> condition-marker/$BENCHMARK-run-$TOOL/TESTSUITE-$BENCHMARK.txt
done

./info.sh $BENCHMARK
#mkdir condition-marker/"$1-klee-run-$2"/
#mv condition-marker/klee-out-* condition-marker/"$1-klee-run-$2"
rm -r condition-marker/klee-out-*

