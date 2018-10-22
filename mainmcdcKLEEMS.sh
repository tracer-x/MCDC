#!/bin/ksh
# This script is written by Sangharatna Godboley.
echo sanghu
export BENCHMARK=$1
rm $BENCHMARK-report.txt
rm TESTSUITE-$BENCHMARK.txt
cp $BENCHMARK.pre RCCCtechniqueKLEEMS/condition-marker/src/
cp $BENCHMARK.post RCCCtechniqueKLEEMS/condition-marker/src/
cat "$BENCHMARK".pre > "$BENCHMARK.c" 
cat "$BENCHMARK".post >> "$BENCHMARK.c"
cp  $BENCHMARK.c RCCCtechniqueKLEEMS/benchmarks/  
cp  $BENCHMARK.c RCCCtechniqueKLEEMS/SequenceGenerator/benchmarks/

cat RCCCtechniqueKLEEMS/condition-marker/src/"$BENCHMARK".pre > "RCCCtechniqueKLEEMS/condition-marker/$BENCHMARK.c" 
#echo "  klee_assert(kappa <= 0);"   >> "RCCCtechniqueKLEEMS/condition-marker/$BENCHMARK.c"
cat RCCCtechniqueKLEEMS/condition-marker/src/"$BENCHMARK".post >> "RCCCtechniqueKLEEMS/condition-marker/$BENCHMARK.c"

cd RCCCtechniqueKLEEMS
./mcdc.sh $BENCHMARK KLEE
cd ..
echo "*******************************************************"
echo "*******************************************************"
echo "*******************************************************"
echo "*******************************************************"
echo "*******************************************************"
echo "*******************************************************"
echo "*******************************************************"
cp /home/sanghu/RCCCtechniqueTX/RCCCtechniqueKLEEMS/condition-marker/$BENCHMARK-run-KLEE/TESTSUITE-$BENCHMARK.txt /home/sanghu/RCCCtechniqueTX/
#./separation.sh $BENCHMARK                   
#mv -v /home/sanghu/RCCCtechniqueTX/RCCCtechnique/condition-marker/llcode-$BENCHMARK-infeasible /home/sanghu/RCCCtechniqueTX/KLEE/
#mv -v /home/sanghu/RCCCtechniqueTX/RCCCtechnique/condition-marker/llcode-$BENCHMARK-feasible /home/sanghu/RCCCtechniqueTX/KLEE/
#cp -v /home/sanghu/RCCCtechniqueTX/RCCCtechniqueKLEEMS/condition-marker/llcode-$BENCHMARK /home/sanghu/RCCCtechniqueTX/KLEE/
TotalSequences=$(ls -v RCCCtechniqueKLEEMS/SequenceGenerator/exp/Sequence-*-*-* | wc -l)
validtestcase=$(ls -l | grep -c "ktest file : 'klee-new" TESTSUITE-$BENCHMARK.txt)
((invalidtestcase = ${TotalSequences} - ${validtestcase}))
#unknowntestcase=$(ls -l | grep -c "Elapsed: 00:3" RCCCtechniqueKLEEMS/condition-marker/maininfo.txt)
#((invalidtestcase = ${invalidtestcase} - ${unknowntestcase}))
((ratiotx = (${validtestcase} * 100) / ${TotalSequences}))

echo "******Final Result Report from KLEE******"
echo "******Final Result Report from KLEE******" >> $BENCHMARK-report.txt
echo "Total number of Reachable paths or valid test cases =: $validtestcase" 
echo "Total number of Reachable paths or valid test cases =: $validtestcase" >> $BENCHMARK-report.txt

echo "Total number of Unreachable paths or invalid test cases =:$invalidtestcase" 
echo "Total number of Unreachable paths or invalid test cases =:$invalidtestcase" >> $BENCHMARK-report.txt

#echo "Total number of Unknown paths or Unknown test cases =:$unknowntestcase" 
#echo "Total number of Unknown paths or Unknown test cases =:$unknowntestcase" >> $BENCHMARK-report.txt

echo "Total number of MC/DC Sequences =: $TotalSequences" 
echo "Total number of MC/DC Sequences =: $TotalSequences" >> $BENCHMARK-report.txt

echo "The Percentage of valid test cases =: $ratiotx%" 
echo "The Percentage of valid test cases =: $ratiotx%" >> $BENCHMARK-report.txt
echo "******The KLEE report Finished*******" 
echo "******The KLEE report Finished*******" >> $BENCHMARK-report.txt


#./delete.sh $BENCHMARK
echo "******The Execution Finished*******"
