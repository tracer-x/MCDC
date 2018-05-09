#include <assert.h>
#ifdef LLBMC
#include <llbmc.h>
#else
#include <klee/klee.h>
#endif
#include <stdio.h> 

#include <math.h>

int p1;
int p2;
int p3;

int t1;
int t2;
int t3;

int N;
int Nr;

int main()
{

klee_make_symbolic(&p1, sizeof(int), "p1");
klee_make_symbolic(&p2, sizeof(int), "p2");
klee_make_symbolic(&p3, sizeof(int), "p3");
klee_make_symbolic(&t1, sizeof(int), "t1");
klee_make_symbolic(&t2, sizeof(int), "t2");
klee_make_symbolic(&t3, sizeof(int), "t3");
klee_make_symbolic(&N, sizeof(int), "N");
klee_make_symbolic(&Nr, sizeof(int), "Nr");


if((((((p1 < 150) && (p2 < 150)) || ((p1 < 150) && (p3 < 150)) || ((p2 < 150) || (p3 < 150)))  &&  (((t1 > 260) && (t2 > 260)) || ((t1 > 260) && (t3 > 260)) || ((t2 > 260) || (t3 > 260))) && ((75 * N) >= Nr)) || ((((p1 < 140) && (p2 < 140)) || ((p1 < 140) && (p3 < 140)) || ((p2 < 140) || (p3 < 140))) && (((t1 > 280) && (t2 > 280)) || ((t1 > 280) && (t3 > 280)) || ((t2 > 280) || (t3 > 280))))))
{
printf("This is if body");
}
else
{
printf("This is else body");
}

return 0;
}
