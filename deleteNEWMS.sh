#!/bin/ksh
#This shell script is written by Sangharatna Godboley
echo sanghu
export BENCHMARK=$1
mkdir result-$BENCHMARK-tx
echo "********Deleting files started*******"
rm RCCCtechniqueNEWMS/benchmarks/$BENCHMARK.c
rm RCCCtechniqueNEWMS/SequenceGenerator/benchmarks/$BENCHMARK.c
mv RCCCtechniqueNEWMS/SequenceGenerator/$BENCHMARK.c-seq-tx result-$BENCHMARK-tx/
rm -r RCCCtechniqueNEWMS/SequenceGenerator/exp/*.txt

rm -r RCCCtechniqueNEWMS/condition-marker/src/$BENCHMARK.post
rm -r RCCCtechniqueNEWMS/condition-marker/src/$BENCHMARK.pre
mv RCCCtechniqueNEWMS/condition-marker/$BENCHMARK-run-tx result-$BENCHMARK-tx/
mv RCCCtechniqueNEWMS/condition-marker/llcode-$BENCHMARK result-$BENCHMARK-tx/
mv RCCCtechniqueNEWMS/condition-marker/$BENCHMARK-ERROR-LIST-tx result-$BENCHMARK-tx/
mv RCCCtechniqueNEWMS/condition-marker/$BENCHMARK-KTEST-tx result-$BENCHMARK-tx/


mv RCCCtechniqueNEWMS/condition-marker/info result-$BENCHMARK-tx/
mv RCCCtechniqueNEWMS/condition-marker/maininfo.txt result-$BENCHMARK-tx/
mv RCCCtechniqueNEWMS/condition-marker/maininfo1.txt result-$BENCHMARK-tx/
rm -r RCCCtechniqueNEWMS/condition-marker/*.ll
rm -r RCCCtechniqueNEWMS/condition-marker/*.c
rm -r RCCCtechniqueNEWMS/condition-marker/*.bc
mv RCCCtechniqueNEWMS/condition-marker/timeTx-$BENCHMARK.txt result-$BENCHMARK-tx/
rm $BENCHMARK.c 
mv $BENCHMARK-report.txt result-$BENCHMARK-tx/
mv TESTSUITE-$BENCHMARK.txt result-$BENCHMARK-tx/
mv nohup.out result-$BENCHMARK-tx/
echo "********Deleting files finsihed*******"
#delete later from here and put in code mcdc.sh
#mv RCCCtechniqueNEWMS/condition-marker/$BENCHMARK-klee-run-tx result-$BENCHMARK-tx/

