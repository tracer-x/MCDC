# This script is written by Sangharatna Godboley.
echo sanghu
export BENCHMARK=$1
rm $BENCHMARK-report.txt
rm TESTSUITE.txt
cp $BENCHMARK.pre RCCCtechnique/condition-marker/src/
cp $BENCHMARK.post RCCCtechnique/condition-marker/src/
cat "$BENCHMARK".pre > "$BENCHMARK.c" 
cat "$BENCHMARK".post >> "$BENCHMARK.c"
cp  $BENCHMARK.c RCCCtechnique/benchmarks/  
cp  $BENCHMARK.c RCCCtechnique/SequenceGenerator/benchmarks/
cp  $BENCHMARK.c KLEE
cd RCCCtechnique
./mcdc.sh $BENCHMARK tx
cd ..
echo "*******************************************************"
echo "*******************************************************"
echo "*******************************************************"
echo "*******************************************************"
echo "*******************************************************"
echo "*******************************************************"
echo "*******************************************************"
cp /home/sanghu/RCCCtechniqueTX/RCCCtechnique/condition-marker/$BENCHMARK-run-tx/TESTSUITE.txt /home/sanghu/RCCCtechniqueTX/
mv -v /home/sanghu/RCCCtechniqueTX/RCCCtechnique/condition-marker/llcode-$BENCHMARK /home/sanghu/RCCCtechniqueTX/KLEE/


validtestcase=$(ls -l | grep -c "ktest file : 'klee-new" TESTSUITE.txt)
invalidtestcase=$(ls -l | grep -c "ERROR: file" TESTSUITE.txt)
((TotalSequences = $validtestcase + $invalidtestcase))
((ratiotx = ($validtestcase * 100) / $TotalSequences))



echo "******Final Result Report from Tracer-x******"
echo "Total number of Reachable paths or valid test cases are =: $validtestcase" 
echo "Total number of Reachable paths or valid test cases are =: $validtestcase" >> $BENCHMARK-report.txt

echo "Total number of Unreachable paths or invalid test cases are =:$invalidtestcase" 
echo "Total number of Unreachable paths or invalid test cases are =:$invalidtestcase" >> $BENCHMARK-report.txt

echo "Total number of MC/DC Sequences are =: $TotalSequences" 
echo "Total number of MC/DC Sequences are =: $TotalSequences" >> $BENCHMARK-report.txt

echo "The Percentage of valid test cases is =: $ratiotx%" 
echo "The Percentage of valid test cases is =: $ratiotx%" >> $BENCHMARK-report.txt
echo "******The Tracer-x report Finished*******" 
echo "******The Tracer-x report Finished*******" >> $BENCHMARK-report.txt


./delete.sh $BENCHMARK
echo "******The Execution Finished*******"
