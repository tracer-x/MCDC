# Copyright 2017 National University of Singapore
#
# See LICENSE.md for license information.

CC=clang
CXX=clang++
CXXFLAGS=`llvm-config --cxxflags` -std=c++11 -D_GLIBCXX_USE_CXX11_ABI=0
LDFLAGS=`llvm-config --ldflags`
LDLIBS=`llvm-config --libs` -lpthread -lncurses -ldl
EXAMPLES=${BENCHMARK}.bc
EXAMPLES2=${BENCHMARK}.ll
Z3_DIR=/home/sanghu/TracerX/z3/build
TARGETS=markcond ${EXAMPLES}
TARGETS2= ${EXAMPLES2}
TARGETS3= ${BENCHMARK}1.bc

all: ${TARGETS}

run: all ${TARGETS2}
	./markcond ${BENCHMARK}.ll ${SEQUENCE} 2> ${BENCHMARK}1.msg 1> ${BENCHMARK}1.ll
   

${TARGETS3}: run
	${CC} ${CFLAGS} -c -emit-llvm -g ${BENCHMARK}1.ll 
	

run-klee: ${TARGETS3}
	#LD_LIBRARY_PATH=${Z3_DIR} /home/paella/TracerX/tracerx/Release+Asserts/bin/klee -max-memory=10000 --max-time 600 -exit-on-error --search=random-path ${BENCHMARK}1.bc    
run-tx: ${TARGETS3}
	LD_LIBRARY_PATH=${Z3_DIR} /home/sanghu/TracerX/tracerx/Release+Asserts/bin/klee --max-memory=30000 --max-time=600 -solver-backend=z3 -exit-on-error-type=Assert --search=dfs ${BENCHMARK}1.bc 

clean:
	rm -f ${TARGETS} *.bc *.ll

.SUFFIXES: .bc .ll

.c.bc:
	${CC} ${CFLAGS} -I /usr/local/include/ -c -O0 -emit-llvm -g $< 

.bc.ll:
	llvm-dis $<
