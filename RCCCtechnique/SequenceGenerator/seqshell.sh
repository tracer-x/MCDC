#Written by Sangharatna Godboley
#This shell script compiles and run "MCDC_Sequence_Generator.java", "Seq_For_Pred.java", and "SequenceFileGenerator.java" for a C program. "MCDC_Sequence_Generator.java" takes a C program and identifies atomic conditions and predicates and produces "Seq_For_Pred.java" which consists of all predicates with temporary variables such as A, B, and C for each conditions etc. Then, "Seq_For_Pred.java" produces all tables and finally MC/DC sequences for all predicates. To write truth values in terms of "1" for true, "0" for false, and "9" for don't care (x), we run "SequenceFileGenerator.java". This "SequenceFileGenerator.java" will also includes the truth values of each atomic conditions as well as all truth values of predicates. Finally, we get the total possible sequence (feasible and in feasible) according to MC/DC criterion, now we can supply them into "condition marker algorithm".
export BENCHMARK=$1
export TOOL=$2
javac MCDC_Sequence_Generator_multiple.java
java MCDC_Sequence_Generator_multiple "benchmarks/$1"
i=1;
for file in Seq_For_Pred****.java; do 
javac Seq_For_Pred$i.java;
java Seq_For_Pred$i;
echo $i
i=$((i+1));
done
javac SequenceFileGenerator.java
java SequenceFileGenerator 
mkdir "$1-seq-$2" 2> err.txt
cp exp/* "$1-seq-$2"
rm err.txt
