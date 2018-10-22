#!/bin/ksh
#This shell script is written by Sangharatna Godboley
echo sanghu
export BENCHMARK=$1
mkdir result-$BENCHMARK-KLEE
echo "********Deleting files started*******"
rm RCCCtechniqueKLEEMS/benchmarks/$BENCHMARK.c
rm RCCCtechniqueKLEEMS/SequenceGenerator/benchmarks/$BENCHMARK.c
mv RCCCtechniqueKLEEMS/SequenceGenerator/$BENCHMARK.c-seq-KLEE result-$BENCHMARK-KLEE/
rm -r RCCCtechniqueKLEEMS/SequenceGenerator/exp/*.txt

rm -r RCCCtechniqueKLEEMS/condition-marker/src/$BENCHMARK.post
rm -r RCCCtechniqueKLEEMS/condition-marker/src/$BENCHMARK.pre
mv RCCCtechniqueKLEEMS/condition-marker/$BENCHMARK-run-KLEE result-$BENCHMARK-KLEE/
mv RCCCtechniqueKLEEMS/condition-marker/llcode-$BENCHMARK result-$BENCHMARK-KLEE/
mv RCCCtechniqueKLEEMS/condition-marker/$BENCHMARK-ERROR-LIST-KLEE result-$BENCHMARK-KLEE/
mv RCCCtechniqueKLEEMS/condition-marker/$BENCHMARK-KTEST-KLEE result-$BENCHMARK-KLEE/


mv RCCCtechniqueKLEEMS/condition-marker/info result-$BENCHMARK-KLEE/
mv RCCCtechniqueKLEEMS/condition-marker/maininfo.txt result-$BENCHMARK-KLEE/
mv RCCCtechniqueKLEEMS/condition-marker/maininfo1.txt result-$BENCHMARK-KLEE/
rm -r RCCCtechniqueKLEEMS/condition-marker/*.ll
rm -r RCCCtechniqueKLEEMS/condition-marker/*.c
rm -r RCCCtechniqueKLEEMS/condition-marker/*.bc
mv RCCCtechniqueKLEEMS/condition-marker/timeTx-$BENCHMARK.txt result-$BENCHMARK-KLEE/
rm $BENCHMARK.c 
mv $BENCHMARK-report.txt result-$BENCHMARK-KLEE/
mv TESTSUITE-$BENCHMARK.txt result-$BENCHMARK-KLEE/
mv nohup.out result-$BENCHMARK-KLEE/
echo "********Deleting files finsihed*******"
#delete later from here and put in code mcdc.sh
#mv RCCCtechniqueKLEEMS/condition-marker/$BENCHMARK-klee-run-tx result-$BENCHMARK-tx/

