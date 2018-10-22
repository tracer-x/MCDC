# This shell script is written by Sangharatna Godboley
export BENCHMARK=$1
echo ${BENCHMARK}



clang `llvm-config --cxxflags` -D_GLIBCXX_USE_CXX11_ABI=0 -I /usr/local/include/ -c -O0 -emit-llvm -g ${BENCHMARK}.c
g++ -o markcond markcond.cpp `llvm-config-3.5 --cxxflags` `llvm-config-3.5 --ldflags` `llvm-config-3.5 --libs` -lpthread -lncurses -ldl
# Below code targets for all predicates
llvm-dis ${BENCHMARK}.bc
#let p=1
valuepred=$(ls -v ../SequenceGenerator/exp/predicateResults* | wc -l)
#for q in `ls -v ../SequenceGenerator/exp/predicateResults*`
for p in `seq 1 $valuepred`
do
cp ${BENCHMARK}.ll ${BENCHMARK}-$p-1.ll
let i=1
let j=0
for x in `ls -v ../SequenceGenerator/exp/Sequence-pred-$p-*`;  
do 
((j=i+1));
          #g++ -o markcond markcond.cpp `llvm-config-3.5 --cxxflags` `llvm-config-3.5 --ldflags` `llvm-config-3.5 --libs` -lpthread -lncurses -ldl
         ./markcond ${BENCHMARK}-$p-$i.ll $x 2> ${BENCHMARK}-$p-${j}.msg 1> ${BENCHMARK}-$p-${j}.ll
((i=i+1));
done
cp ${BENCHMARK}-$p-${j}.ll ${BENCHMARK}KAPPA-pred-$p.ll
#((p=p+1));
done
rm ${BENCHMARK}-*-*.ll
rm *.msg


# Below code targets for atomic conditions
llvm-dis ${BENCHMARK}.bc
let z=1
value=$(ls -v ../SequenceGenerator/exp/Sequence-atom-*-* | wc -l)
((value = $value / 2))
for w in `seq 1 $value`  
do 
cp ${BENCHMARK}.ll ${BENCHMARK}-$z-1.ll
let m=1
let n=0
for o in `ls -v ../SequenceGenerator/exp/Sequence-atom-$w-*`;  
do 
((n=m+1));
          #g++ -o markcond markcond.cpp `llvm-config-3.5 --cxxflags` `llvm-config-3.5 --ldflags` `llvm-config-3.5 --libs` -lpthread -lncurses -ldl
         ./markcond ${BENCHMARK}-$z-$m.ll $o 2> ${BENCHMARK}-$z-${n}.msg 1> ${BENCHMARK}-$z-${n}.ll
((m=m+1));
done
cp ${BENCHMARK}-$z-${n}.ll ${BENCHMARK}KAPPA-cond-$z.ll
((z=z+1));
done
rm ${BENCHMARK}-*-*.ll
rm *.msg







