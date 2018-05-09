#Written by Sangharatna Godboley
#This shell script takes the list of predicates extracted from C program and listed in "predicatesextracted.txt"v file. Then it replaces all the atomic conditions with '@' and a new list of predicates is get created. The new list is named as "new.txt". Now, a c++ code has been written to rename all the atomic conditions with incremental A..B..C characters and finally a new list of predicates is get created i.e. "finalpredicate.txt". Now, we have to use this file in "Sequence.java" program to find all "seq.txt" files.   
sed -e 's/<=/@/g' -e 's/>=/@/g' -e 's/>/@/g' -e 's/</@/g' -e 's/!=/@/g' -e 's/==/@/g' predicatesextracted.txt | sed 's/[[:alnum:]]\+//g' | sed 's/\_//g' > new.txt 
g++ naming.cpp
./a.out > finalpredicate.txt

