#This shell script is written by Sangharatna Godboley
echo sanghu
export BENCHMARK=$1
echo "********Deleting files started*******"
#rm -r KLEE/klee-out-$BENCHMARK
rm -r KLEE/llcode-$BENCHMARK
rm -r KLEE/*.ll
rm -r KLEE/*.c
rm -r KLEE/*.txt
echo "********Deleting files finsihed*******"

