

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


#include <stdio.h>



int error, tempDisplay, warnLED, tempIn, chainBroken, warnLight, temp, limit, init;


void display(int tempdiff, int warning)
{
	tempDisplay = tempdiff;
	warnLED = warning;
}

int vinToCels(int kelvin)
{
	if (temp < 0) 
	{
		error = 1;
		display(kelvin - 273, error);
	}
	return kelvin -273;
}

void coolantControl()
{
	int otime, time = 0;
	while(1)
	{
		otime = time;
		time = otime + 1;
		tempIn;
		klee_make_symbolic(&tempIn, sizeof(int), "tempIn");
		temp = vinToCels(tempIn);
		if(temp > limit) 
		{
			chainBroken = 1;
		} 
	}
}

int main()
{
 init = 0;
    tempDisplay = 0;
    warnLED = 1;
    tempIn = 0;
    error = 0;
    chainBroken = 0;
    warnLight = 0;
    temp = 0;
    limit = 8;
    init = 1;
    int try = 0;
	
	while(1)
	{
		int limit;
		klee_make_symbolic(&limit, sizeof(int), "limit");
		if(limit < 10 && limit > -273)
		{
			error = 0;
			display(0, error);
			break;
		} else {
			error = 1;
			display(0, error);
		}	
		if (try >= 3) {
			limit = 7;
			break;
		}
		try++;
	}
	
	init = 3;
	coolantControl();	
}
