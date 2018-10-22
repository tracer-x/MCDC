#!/bin/ksh
export BENCHMARK=$1
mkdir condition-marker/info
let s=1
for x in `ls -v condition-marker/klee-out-*/info`; 
do  
    cp $x condition-marker/info/info$s
    grep "Acutual time:" $x >> condition-marker/maininfo.txt
    ((s =s+1));
done
sed 's/Acutual time: //g' condition-marker/maininfo.txt > condition-marker/maininfo1.txt
Total_Search_time=$(grep . condition-marker/maininfo1.txt | paste -sd+ | bc)
echo "Total time for Searching Sequences: " ${Total_Search_time}
echo "Total time for Searching Sequences: " ${Total_Search_time} >> condition-marker/timeTx-$BENCHMARK.txt
echo "****************Time Analysis Report - End**************************"
echo "****************Time Analysis Report - End**************************" >> condition-marker/timeTx-$BENCHMARK.txt

