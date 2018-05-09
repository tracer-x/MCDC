/********Software Analysis - FY2013*************/
/*
* File Name: redundant_cond.c
* Defect Classification
* ---------------------
* Defect Type: Inappropriate code
* Defect Sub-type: Redundant conditions
* Description: Defect Free Code to identify false positives in redundant condition
*/
#include<stdio.h>
#ifdef LLBMC
#include <llbmc.h>
#else
#include <klee/klee.h>
#endif
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<pthread.h>
#include<unistd.h>

# define PRINT_DEBUG 1

int vflag;

int vflag_copy;
int vflag_file;
int idx, sink;
double dsink;
void *psink;

int rand (void);

#include "HeaderFile.h"

int rand (void);


void redundant_cond_001 ()
{
	int a;
	int b = 0;
	int ret;


	klee_make_symbolic(&a, sizeof(int), "a");
	if ( a < 10 ) /*Tool should not detect this line as error*/ /*No ERROR:Redundant condition*/
	{
		b += a;
	}
	ret = b;
        sink = ret;
}


void redundant_cond_002 ()
{
	int a;
	int b = 0;
	int ret;

	klee_make_symbolic(&a, sizeof(int), "a");
	if (a < 5) /*Tool should not detect this line as error*/ /*No ERROR:Redundant condition*/
	{
		b += a;
	}
	ret = b;
        sink = ret;
}


void redundant_cond_003 ()
{
	int a;
	int b = 0;
	int ret;

	klee_make_symbolic(&a, sizeof(int), "a");
	if ( a < 10 ) /*Tool should not detect this line as error*/ /*No ERROR:Redundant condition*/
	{
		b += a;
	}
	ret = b;
        sink = ret;
}


void redundant_cond_004 ()
{
	int a;
	int b = 0;
	int ret;

	klee_make_symbolic(&a, sizeof(int), "a");
	if ( a < 10 )/*Tool should not detect this line as error*/ /*No ERROR:Redundant condition*/
	{
		b += a;
	}
	ret = b;
        sink = ret;
}


void redundant_cond_005 ()
{
	int a;
	int b = 0;
	int ret;

	klee_make_symbolic(&a, sizeof(int), "a");
	if (a < 10) /*Tool should detect this line as error*/ /*No ERROR:Redundant condition*/
	{
		b += a;
	}
	ret = b;
        sink = ret;
}


void redundant_cond_006 ()
{
	int a;
	int b = 0;
	int ret;

	klee_make_symbolic(&a, sizeof(int), "a");
	if (a < 10)  /*Tool should not detect this line as error*/ /*No ERROR:Redundant condition*/
	{
		b += a;

	}
	ret = b;
        sink = ret;
}


void redundant_cond_007 ()
{
	int a;
	int b;
	int ret;

	klee_make_symbolic(&a, sizeof(int), "a");
	  /*Tool should not detect this line as error*/ /*No ERROR:Redundant condition*/
	if (a < 10)
	{
	b = 0;
	}
	else
	{
	b = 1;
	}
	ret = b;
        sink = ret;
}


void redundant_cond_008 ()
{
	int a;
	int b = 0;
	int ret;

	for (a = 20; 10 < a; a --)  /*Tool should not detect this line as error*/ /*No ERROR:Redundant condition*/
	{
		b += a;
	}
	ret = b;
        sink = ret;
}


void redundant_cond_009 ()
{
	int a;
	int b = 0;
	int ret;

	klee_make_symbolic(&a, sizeof(int), "a");
	while (a < 10)  /*Tool should not detect this line as error*/ /*No ERROR:Redundant condition*/
	{
		b += a;
		a --;
	}
	ret = b;
        sink = ret;
}


void redundant_cond_010 ()
{
	int a;
	int b = 0;
	int ret;

	klee_make_symbolic(&a, sizeof(int), "a");
	while ((a < 5)) /*Tool should not detect this line as error*/ /*No ERROR:Redundant condition*/
	{
		b += a;
		a ++;
	}
	ret = b;
        sink = ret;
}


void redundant_cond_011 ()
{
	int a;
	int b = 0;
	int ret;

	klee_make_symbolic(&a, sizeof(int), "a");
	while ((a < 8))  /*Tool should not detect this line as error*/ /*No ERROR:Redundant condition*/
	{
		b += a;
		a ++;
	}
	ret = b;
        sink = ret;
}


void redundant_cond_012 ()
{
	int a;
	int b = 0;
	int ret;

	klee_make_symbolic(&a, sizeof(int), "a");
	while (a < 10)/*Tool should not detect this line as error*/ /*No ERROR:Redundant condition*/
	{
		b += a;
		a ++;
	}
	ret = b;
        sink = ret;
}


void redundant_cond_013 ()
{
	int a;
	int b = 0;
	int ret;

	klee_make_symbolic(&a, sizeof(int), "a");
	while ((a < 10))/*Tool should not detect this line as error*/ /*No ERROR:Redundant condition*/
	{
		b += a;
		a --;
	}
	ret = b;
        sink = ret;
}


void redundant_cond_014 ()
{
  int a;
  int b = 0;
  int ret;

  klee_make_symbolic(&a, sizeof(int), "a");
  do {
    // JDR: cast to unsigned to avoid UB
    b += (unsigned)a;
    a --;
  }
  while (10 < a); /*Tool should not detect this line as error*/ /*No ERROR:Redundant condition*/
  ret = b;
  sink = ret;
}


int main()
{
        
        klee_make_symbolic(&vflag_copy, sizeof(int), "vflag_copy");
        klee_make_symbolic(&vflag_file, sizeof(int), "vflag_file");
        klee_make_symbolic(&vflag, sizeof(int), "vflag");
        

	if (vflag_file == 37 || vflag_file == 888 )
	{
	if (vflag ==1 || vflag ==888)
	{
		redundant_cond_001();
	}

	if (vflag ==2 || vflag ==888)
	{
		redundant_cond_002();
	}

	if (vflag ==3 || vflag ==888)
	{
		redundant_cond_003();
	}

	if (vflag ==4 || vflag ==888)	/* Without test cases */
	{
		redundant_cond_004();
	}

	if (vflag ==5 || vflag ==888)	/* Without test cases */
	{
		redundant_cond_005();
	}

	if (vflag ==6 || vflag ==888)
	{
		redundant_cond_006();
	}

	if (vflag ==7 || vflag ==888)
	{
		redundant_cond_007();
	}

	if (vflag ==8 || vflag ==888)
	{
		redundant_cond_008();
	}

	if (vflag ==9 || vflag ==888)
	{
		redundant_cond_009();
	}

	if (vflag ==10 || vflag ==888)
	{
		redundant_cond_010();
	}

	if (vflag ==11 || vflag ==888)
	{
		redundant_cond_011();
	}

	if (vflag ==12 || vflag ==888)
	{
		redundant_cond_012();
	}

	if (vflag ==13 || vflag ==888)
	{
		redundant_cond_013();
	}

	if (vflag ==14 || vflag ==888)
	{
		redundant_cond_014();
	}
}
return 0;
}
