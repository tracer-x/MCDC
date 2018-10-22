echo sanghu

#This shell script is written by Sangharatna Godboley

export BENCHMARK=$1


res1=$(date +%s.%N)
let dt=0
let m=1
for w in `ls -v ${BENCHMARK}KAPPA*`;  
do 

if [ "$dt" -lt 3600 ]
then
clang -c -emit-llvm -g $w
/home/sanghu/TracerX/tracerx/Release+Asserts/bin/klee --max-memory=30000 --max-time=1800 --search=random-path ${w%.ll}.bc
#/home/sanghu/TracerX/tracerx/Release+Asserts/bin/klee --max-memory=30000 --max-time=1800 ${w%.ll}.bc
#/home/sanghu/TracerX/tracerx/Release+Asserts/bin/klee --max-memory=30000 --max-time=1800 -solver-backend=z3 --search=dfs ${w%.ll}.bc
#/home/sanghu/TracerX/tracerx/Release+Asserts/bin/klee --max-memory=30000 --max-time=1800 -solver-backend=z3 --search=dfs -emit-all-errors ${w%.ll}.bc
#/home/sanghu/TracerX/tracerx/Release+Asserts/bin/klee --max-memory=30000 --max-time=1800 -solver-backend=z3 --search=dfs -write-cov -subsumed-test -emit-all-errors ${w%.ll}.bc
#/home/sanghu/TracerX/tracerx/Release+Asserts/bin/klee --max-memory=30000 -subsumed-test --max-time=1800 ${w%.ll}.bc
#/home/sanghu/TracerX/tracerx/Release+Asserts/bin/klee --max-memory=30000 -write-cov -subsumed-test -emit-all-errors --max-time=1800 ${w%.ll}.bc
#/home/sanghu/TracerX/tracerx/Release+Asserts/bin/klee --max-memory=30000 -write-cov -emit-all-errors --max-time=1800 ${w%.ll}.bc
#ls -d -1 $PWD/klee-last/*.* |grep -A2 assert.err > klee-last/Errlist.txt
#cat klee-last/Errlist.txt | xargs cp -t klee-new/
for z in `find klee-last/*.assert.err -type f`;  
do
echo $z 
cp ${z%.assert.err}.* klee-new 
done


echo $w >  "$BENCHMARK-ERROR-LIST-KLEE/$(basename $w)"
sed -n '/Error: ASSERTION FAIL: kappa violation /p' klee-new/test******.assert.err >> $BENCHMARK-ERROR-LIST-KLEE/$(basename $w)
echo '()' >>  "$BENCHMARK-ERROR-LIST-KLEE/$(basename $w)"


/home/sanghu/TracerX/tracerx/Release+Asserts/bin/ktest-tool klee-new/test******.ktest > "$BENCHMARK-run-KLEE/$(basename $w)"
echo '()' >>  "$BENCHMARK-run-KLEE/$(basename $w)"


mv $w llcode-$BENCHMARK/


for file in klee-new/test******.ktest
do
  mv "$file" $BENCHMARK-KTEST-KLEE/test${m}.ktest
  ((m = m + 1))
done
rm klee-new/*.*
fi
res2=$(date +%s.%N)
dt=$(echo "$res2 - $res1" | bc)

done

for y in `ls -v $BENCHMARK-ERROR-LIST-KLEE/${BENCHMARK}KAPPA*`;   
do 
 
     cat $y >> $BENCHMARK-ERROR-LIST-KLEE/FOUND-SEQUENCES-$BENCHMARK.txt

done




dd=$(echo "$dt/86400" | bc)
dt2=$(echo "$dt-86400*$dd" | bc)
dh=$(echo "$dt2/3600" | bc)
dt3=$(echo "$dt2-3600*$dh" | bc)
dm=$(echo "$dt3/60" | bc)
ds=$(echo "$dt3-60*$dm" | bc)

echo "****************Time Analysis Report - Start**************************" >> timeTx-$BENCHMARK.txt 
echo "***Total runtime in seconds" $dt >> timeTx-$BENCHMARK.txt
printf "Total runtime: %d:%02d:%02d:%02.4f\n" $dd $dh $dm $ds >> timeTx-$BENCHMARK.txt




