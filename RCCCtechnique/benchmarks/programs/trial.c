#include<stdio.h>
#ifdef LLBMC
#include <llbmc.h>
#else
#include <klee/klee.h>
#endif
int main()
{
int  a,b,c;

klee_make_symbolic(&a, sizeof(int), "a");
klee_make_symbolic(&b, sizeof(int), "b");
klee_make_symbolic(&c, sizeof(int), "c");

if ((a > 5)  && ((b == 3) || (c >100)))
{
printf("sanghu");
}
else
{
printf("rasool");
}

return 0;
}
