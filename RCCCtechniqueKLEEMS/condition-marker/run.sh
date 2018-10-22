#!/usr/bin/env bash
#Written by Sangharatna Godboley and Rasool
# This shell script is to generate test inputs for the symbolic variables present in a C program for each sequence with truth values have been provided. That sequence is according to MC/DC criterion. For each sequence we will get each test case. Type command "./run.sh tcas.c Sequence#.txt" in terminal. Also, you need to edit the "seq" name in markcond.cpp program for this version of impelementation. The markcond.cpp program will insert the "kappa incrementation" at suitable location where the truth values of seq files have suggested to insert. Kappa veryfier is there to check the condition to terminate the process of marking.  

export BENCHMARK=$1
export SEQUENCE=$2
export TOOL=run-$3
#export TESTCASE="$BENCHMARK-$TOOL/$(basename $SEQUENCE)"

let KAPPA=0
while IFS= read -r var
do
  if [ "$var" -lt 9 ]
  then
      let "KAPPA++"
  fi
done < $SEQUENCE

echo "$KAPPA markings in the sequence."
cat condition-marker/src/"$BENCHMARK".pre > "condition-marker/$BENCHMARK.c" 
echo "  klee_assert(kappa < $KAPPA);"   >> "condition-marker/$BENCHMARK.c"  
cat condition-marker/src/"$BENCHMARK".post >> "condition-marker/$BENCHMARK.c"   

echo $TOOL
#Here we need to add one for loop to make it more synchronise...to select seq1 seq2 seq 3 and so on...
#make $TOOL BENCHMARK=$BENCHMARK SEQUENCE="../$SEQUENCE"
cd condition-marker/
./kappa.sh $BENCHMARK
./txmcdc.sh $BENCHMARK

mkdir $BENCHMARK-$TOOL
mkdir klee-new
ls -d -1 $PWD/klee-last/*.* |grep -A2 assert.err > klee-last/Errlist.txt
cat klee-last/Errlist.txt | xargs cp -t klee-new/

/usr/local/lib/tracerx/Release+Asserts/bin/ktest-tool klee-new/test******.ktest > TESTSUITE-$BENCHMARK.txt
#ktest-tool klee-new/test******.ktest > $TESTCASE
echo '()' >>  TESTSUITE-$BENCHMARK.txt


#cat $BENCHMARK-$TOOL/Sequence*.txt > $BENCHMARK-$TOOL/TESTSUITE.txt
rm klee-new/*.*
cd ..


