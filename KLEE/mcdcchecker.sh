#Shell script written by Sangharatna Godboley to validate the MC/DC sequences using klee
res1=$(date +%s.%N)
export BENCHMARK=$1
export TOTALTESTCASES=$2
export TOTALSEQ=$3
export LD_LIBRARY_PATH=/home/sanghu/TracerX/tracerx/Release+Asserts/lib/:$LD_LIBRARY_PATH
echo > stats.txt
echo > mcdc.txt
#mkdir $BENCHMARK-processed-TCs
for s in `seq 1 $TOTALSEQ`
do
  llvm-as $BENCHMARK$s.ll
  llc -filetype=obj $BENCHMARK$s.bc
  gcc -L /home/sanghu/TracerX/tracerx/Release+Asserts/lib/ $BENCHMARK$s.o -lkleeRuntest
  mv a.out a$s.out
done

for t in `seq 1 $TOTALTESTCASES | sort -V`
do
echo "test case  no.: $t"
  for s in `seq 1 $TOTALSEQ | sort -V`
  do
    echo "Seq no.: $s"
    if [ -e a$s.out ]
    then  
      KTEST_FILE=klee-out-$BENCHMARK/test$t.ktest ./a$s.out &> output.txt
      value=$( grep -ic "kappa" output.txt )
      if [ $value -eq 1 ]
      then
         echo ready to remove
         echo Sequence $s, Testcase $t >> mcdc-$BENCHMARK.txt
         rm $BENCHMARK$s.ll
         rm $BENCHMARK$s.bc
         rm $BENCHMARK$s.o
         rm ./a$s.out    
      fi
    fi
    
  done
  rm output.txt
  #mv klee-out-$BENCHMARK/test$t.ktest /$BENCHMARK-processed-TCs/
  export rem=`echo "$t % 100" | bc`
  if [ $rem -eq 0 ]
  then
     export remSeq=`ls ${BENCHMARK}*.ll | wc -l`
     export foundSeq=$(($TOTALSEQ-$remSeq))
     echo "Reached $t test cases" >> stats-$BENCHMARK.txt 
     echo "Total sequences are:  $TOTALSEQ" >> stats-$BENCHMARK.txt
     echo "Found sequences are:  $foundSeq" >> stats-$BENCHMARK.txt
     echo >> stats-$BENCHMARK.txt
  fi
done
rm $BENCHMARK*.bc
rm $BENCHMARK*.o
rm ./a*.out 

res2=$(date +%s.%N)
dt=$(echo "$res2 - $res1" | bc)
dd=$(echo "$dt/86400" | bc)
dt2=$(echo "$dt-86400*$dd" | bc)
dh=$(echo "$dt2/3600" | bc)
dt3=$(echo "$dt2-3600*$dh" | bc)
dm=$(echo "$dt3/60" | bc)
ds=$(echo "$dt3-60*$dm" | bc)
printf "Total runtime: %d:%02d:%02d:%02.4f\n" $dd $dh $dm $ds   
