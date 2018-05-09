#This shell script is written by Sangharatna Godboley. This is to exclude the test*.early and it's test*.ktest file. 
export BENCHMARK=$1
mkdir /home/sanghu/NORMAL-KLEE/trialprogram/klee-out-$BENCHMARK
mkdir /home/sanghu/NORMAL-KLEE/trialprogram/klee-out-early-$BENCHMARK
for s in  klee-out-$BENCHMARK/*.ktest
do
    
  echo Copying ktest files
  echo $s
  cp "$s" /home/sanghu/NORMAL-KLEE/trialprogram/klee-out-$BENCHMARK/
done
for s1 in klee-out-$BENCHMARK/*.early
do
  echo Copying early files
  echo $s1
  cp "$s1" /home/sanghu/NORMAL-KLEE/trialprogram/klee-out-early-$BENCHMARK/
  s1=${s1##*/}
  rm /home/sanghu/NORMAL-KLEE/trialprogram/klee-out-$BENCHMARK/${s1%.early}.ktest 
done

