#This shell script is written by Sangharatna Godboley
res1=$(date +%s.%N)
export BENCHMARK=$1
clang -emit-llvm -c -g ${BENCHMARK}.c
/home/sanghu/TracerX/tracerx/Release+Asserts/bin/klee --max-memory=30000 --max-time=600 --search=random-path $BENCHMARK.bc &> KLEElogoutput-$BENCHMARK.txt

res2=$(date +%s.%N)
dt=$(echo "$res2 - $res1" | bc)
dd=$(echo "$dt/86400" | bc)
dt2=$(echo "$dt-86400*$dd" | bc)
dh=$(echo "$dt2/3600" | bc)
dt3=$(echo "$dt2-3600*$dh" | bc)
dm=$(echo "$dt3/60" | bc)
ds=$(echo "$dt3-60*$dm" | bc)
printf "Total runtime: %d:%02d:%02d:%02.4f\n" $dd $dh $dm $ds
mkdir klee-out-$BENCHMARK
cp -r klee-out-0/*.ktest klee-out-$BENCHMARK/
rm -r klee-out-0
let m=1
for file in klee-out-$BENCHMARK/test******.ktest
do
  mv "$file" klee-out-$BENCHMARK/test${m}.ktest
  ((m = m + 1))
done


kleetestcases=`find klee-out-$BENCHMARK/ -type f | wc -l`
TotalSequences=`find llcode-$BENCHMARK/ -type f | wc -l`
echo "$kleetestcases" 
cd llcode-$BENCHMARK
cp *.ll ../
cd ..
./mcdcchecker.sh $BENCHMARK $kleetestcases $TotalSequences
foundsequences=$(ls -l | grep -c "Sequence" mcdc-$BENCHMARK.txt)
((notfoundsequences=$TotalSequences - $foundsequences))
((ratioklee = ($foundsequences * 100) / $TotalSequences))

echo "******Final Result Report from KLEE******"
echo "KLEE generated Test cases := $kleetestcases"

echo "Total number of Reachable paths or valid test cases or found sequences are =: $foundsequences" 
echo "Total number of Reachable paths or valid test cases are =: $foundsequences" >> $BENCHMARK-report.txt

echo "Total number of Unreachable paths or invalid test cases or not found sequences are =:$notfoundsequences" 
echo "Total number of Unreachable paths or invalid test cases or not found sequences are =:$notfoundsequences" >> $BENCHMARK-report.txt

echo "Total number of MC/DC Sequences are =: $TotalSequences" 
echo "Total number of MC/DC Sequences are =: $TotalSequences" >> $BENCHMARK-report.txt

echo "The Percentage of valid test cases is =: $ratioklee%" 
echo "The Percentage of valid test cases is =: $ratioklee%" >> $BENCHMARK-report.txt
echo "******The KLEE report Finished*******" 
echo "******The KLEE report Finished*******" >> $BENCHMARK-report.txt
#./delete.sh $BENCHMARK
echo "******The Execution Finished*******"

