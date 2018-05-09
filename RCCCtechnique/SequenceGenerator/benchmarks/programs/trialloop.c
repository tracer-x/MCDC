
#include <klee/klee.h>
#include <stdio.h>

int main()
{
int i,j,k,l=0;
  klee_make_symbolic(&i, sizeof(int), "i");
  klee_make_symbolic(&j, sizeof(int), "j");
  klee_make_symbolic(&k, sizeof(int), "k");


  
  
  while(l<100)
  {
  if ((i > 5) && ((j < 10) || (k == 50)))
  {
  printf("sanghu");
  }
  else
  {
  printf("rasool");
  }
  l++;
  
  }
  

return 0;
}

 
