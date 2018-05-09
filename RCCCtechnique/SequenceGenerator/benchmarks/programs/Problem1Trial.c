
#include <assert.h>
#ifdef LLBMC
#include <llbmc.h>
#else
#include <klee/klee.h>
#endif
#include <stdio.h> 

#include <math.h>


	int calculate_output(int input,int a17,int a7,int a20,int a8,int a12,int a16,int a21) {
	    if((((a8==15)&&(((((a21==1)&&(((a16==5)||(a16==6))&&(input==1)))&&(a20==1))&&(a17==1))&&!(a7==1)))&&(a12==8))){
	    	a16 = 5;
	    	a20 = 0;
	    	return 24;
	    } else if((((((((input==5)&&((((a16==6)&&(a17==1))||(!(a17==1)&&(a16==4)))||(!(a17==1)&&(a16==5))))&&(a20==1))&&(a12==8))&&(a7==1))&&!(a21==1))&&(a8==13))){
	    	a20 = 0;
	    	a16 = 6;
	    	a17 = 0;
	    	a8 = 15;
	    	a7 = 0;
	    	a21 = 1;
	    	return 26;
	    } 
	    if(((((((!(a17==1)&&(a7==1))&&!(a20==1))&&(a8==14))&&(a12==8))&&(a16==4))&&(a21==1))){
	    	//error_20: assert(0);
printf("error 20");
	    } 
	    
	    return -2; 
	}



	int a17;
	int a7;
	int a20;
	int a8;
	int a12;
	int a16;
	int a21;

int main()
{
    // default output
    int output = -1;

    // main i/o-loop
    
        // read input
        int input;
          klee_make_symbolic(&input, sizeof(int), "input");
          klee_make_symbolic(&a17, sizeof(int), "a17");
          klee_make_symbolic(&a7, sizeof(int), "a7");
          klee_make_symbolic(&a20, sizeof(int), "a20");
          klee_make_symbolic(&a8, sizeof(int), "a8");
          klee_make_symbolic(&a12, sizeof(int), "a12");
          klee_make_symbolic(&a16, sizeof(int), "a16");
          klee_make_symbolic(&a21, sizeof(int), "a21");        

        // operate eca engine
        output = calculate_output(input, a17, a7, a20, a8, a12, a16, a21);

        if(output == -2)
        	fprintf(stderr, "Invalid input: %d\n", input);
        else if(output != -1)
			printf("%d\n", output);
    
}
