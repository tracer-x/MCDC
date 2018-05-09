
#include<stdio.h>
#ifdef LLBMC
#include <llbmc.h>
#else
#include <klee/klee.h>
#endif

// method ids
int m_initSign = 1;
int m_initVerify = 2;
int m_Signature = 3;
int m_sign = 4;
int m_verify = 5;
int m_update = 6;
 
int kappa;
int main() 
{
kappa =0;
  int q, FLAG=0, i=0;
  klee_make_symbolic(&q, sizeof(int), "q");
  int method_id;

  // variables
    int this_state;
	klee_make_symbolic(&this_state, sizeof(int), "this_state");
	int a1,a2,a3,a4,a5,a6,a7,a8,a9,a10;
        int a11,a12,a13,a14,a15,a16,a17,a18,a19,a20,a21;
   klee_make_symbolic(&a1, sizeof(int), "a1");
   klee_make_symbolic(&a2, sizeof(int), "a2");
   klee_make_symbolic(&a3, sizeof(int), "a2");
   klee_make_symbolic(&a4, sizeof(int), "a4");
   klee_make_symbolic(&a5, sizeof(int), "a5");
   
   
   klee_make_symbolic(&a6, sizeof(int), "a6");
   klee_make_symbolic(&a7, sizeof(int), "a7");
   klee_make_symbolic(&a8, sizeof(int), "a8");
   klee_make_symbolic(&a9, sizeof(int), "a9");
   klee_make_symbolic(&a10, sizeof(int), "a10");
   
   klee_make_symbolic(&a11, sizeof(int), "a11");
   klee_make_symbolic(&a12, sizeof(int), "a12");
   klee_make_symbolic(&a13, sizeof(int), "a13");
   klee_make_symbolic(&a14, sizeof(int), "a14");
   klee_make_symbolic(&a15, sizeof(int), "a15");
   
   klee_make_symbolic(&a16, sizeof(int), "a16");
   klee_make_symbolic(&a17, sizeof(int), "a17");
   klee_make_symbolic(&a18, sizeof(int), "a18");
   klee_make_symbolic(&a19, sizeof(int), "a19");
   klee_make_symbolic(&a20, sizeof(int), "a20");
   
   klee_make_symbolic(&a21, sizeof(int), "a21");

  for (int FLAG=0;FLAG<5;FLAG++) {
     printf("\n\n*****Loop Iteration RASOOL : = %d*****\n\n",FLAG);
     i++;
     printf("\n\n*****Loop Iteration SANGHU : = %d*****\n\n",i);

  
   

    // parameters
        
    // states
        if (q == 0){      
                
                if(a1){
                  // assume guard
                  if ( 1 ){ 
                    // record method id
                    method_id = 3;
                    // non-conformance condition 
                    if ( 0 ) {
                      goto ERROR;
                    }
                    // state update
                    q = 2;
                    // post condition
                    this_state=0; 
                  }
                  continue;
                }

          continue;
        }
        if (q == 1){      
                
                if(a2){
                  // assume guard
                  if ( 1 ){ 
                    // record method id
                    method_id = 4;
                    // non-conformance condition 
                    if ( (this_state == 2) ) {
                      goto ERROR;
                    }
                    // state update
                    q = 1;
                    // post condition
                    break;
                  }
                  continue;
                }
               
                if(a3){
                  // assume guard
                  if ( 1 ){ 
                    // record method id
                    method_id = 5;
                    // non-conformance condition 
                    if ( (this_state == 3) ) {
                      goto ERROR;
                    }
                    // state update
                    q = 1;
                    // post condition
                    break;
                  }
                  continue;
                }
               
                if(a4){
                  // assume guard
                  if ( 1 ){ 
                    // record method id
                    method_id = 6;
                    // non-conformance condition 
                    if ( (((this_state == 2) && (this_state != 3)) || (this_state == 3)) ) {
                      goto ERROR;
                    }
                    // state update
                    q = 1;
                    // post condition
                    break;
                  }
                  continue;
                }

          continue;
        }
        if (q == 2){      
               
                if(a5){
                  // assume guard
                  if ( 1 ){ 
                    // record method id
                    method_id = 1;
                    // non-conformance condition 
                    if ( 0 ) {
                      goto ERROR;
                    }
                    // state update
                    q = 3;
                    // post condition
                    this_state=2; 
                  }
                  continue;
                }
               
                if(a6){
                  // assume guard
                  if ( 1 ){ 
                    // record method id
                    method_id = 2;
                    // non-conformance condition 
                    if ( 0 ) {
                      goto ERROR;
                    }
                    // state update
                    q = 4;
                    // post condition
                    this_state=3; 
                  }
                  continue;
                }
               
                if(a7){
                  // assume guard
                  if ( 1 ){ 
                    // record method id
                    method_id = 4;
                    // non-conformance condition 
                    if ( (this_state == 2) ) {
                      goto ERROR;
                    }
                    // state update
                    q = 1;
                    // post condition
                    break;
                  }
                  continue;
                }
               
                if(a8){
                  // assume guard
                  if ( 1 ){ 
                    // record method id
                    method_id = 5;
                    // non-conformance condition 
                    if ( (this_state == 3) ) {
                      goto ERROR;
                    }
                    // state update
                    q = 1;
                    // post condition
                    break;
                  }
                  continue;
                }
               
                if(a9){
                  // assume guard
                  if ( 1 ){ 
                    // record method id
                    method_id = 6;
                    // non-conformance condition 
                    if ( (((this_state == 2) && (this_state != 3)) || (this_state == 3)) ) {
                      goto ERROR;
                    }
                    // state update
                    q = 1;
                    // post condition
                    break;
                  }
                  continue;
                }

          continue;
        }
        if (q == 3){      
       
                if(a10){
                  // assume guard
                  if ( 1 ){ 
                    // record method id
                    method_id = 1;
                    // non-conformance condition 
                    if ( 0 ) {
                      goto ERROR;
                    }
                    // state update
                    q = 3;
                    // post condition
                    this_state=2; 
                  }
                  continue;
                }
              
                if(a11){
                  // assume guard
                  if ( 1 ){ 
                    // record method id
                    method_id = 2;
                    // non-conformance condition 
                    if ( 0 ) {
                      goto ERROR;
                    }
                    // state update
                    q = 4;
                    // post condition
                    this_state=3; 
                  }
                  continue;
                }
                
                if(a12){
                  // assume guard
                  if ( 1 ){ 
                    // record method id
                    method_id = 4;
                    // non-conformance condition 
                    if ( (this_state != 2) ) {
                      goto ERROR;
                    }
                    // state update
                    q = 3;
                    // post condition
                    this_state=this_state; 
                  }
                  continue;
                }
               
                if(a13){
                  // assume guard
                  if ( 1 ){ 
                    // record method id
                    method_id = 5;
                    // non-conformance condition 
                    if ( (this_state == 3) ) {
                      goto ERROR;
                    }
                    // state update
                    q = 1;
                    // post condition
                    break;
                  }
                  continue;
                }
                
                if(a14){
                  // assume guard
                  if ( 1&& (((this_state == 2) && (this_state != 3)) || ((this_state != 2) && (this_state != 3))) ){ 
                    // record method id
                    method_id = 6;
                    // non-conformance condition 
                    if ( ((this_state != 2) && (this_state != 3)) ) {
                      goto ERROR;
                    }
                    // state update
                    q = 3;
                    // post condition
                    this_state=this_state; 
                  }
                  continue;
                }
                
                if(a15){
                  // assume guard
                  if ( 1&& (((this_state == 2) && (this_state != 3)) || ((this_state != 2) && (this_state != 3)))&& ((this_state == 3) || ((this_state != 2) && (this_state != 3))) ){ 
                    // record method id
                    method_id = 6;
                    // non-conformance condition 
                    if ( ((this_state != 2) && (this_state != 3)) ) {
                      goto ERROR;
                    }
                    // state update
                    q = 3;
                    // post condition
                    this_state=this_state; 
                  }
                  continue;
                }

          continue;
        }
        if (q == 4){      
       
                if(a16){
                  // assume guard
                  if ( 1 ){ 
                    // record method id
                    method_id = 1;
                    // non-conformance condition 
                    if ( 0 ) {
                      goto ERROR;
                    }
                    // state update
                    q = 3;
                    // post condition
                    this_state=2; 
                  }
                  continue;
                }
                
                if(a17){
                  // assume guard
                  if ( 1 ){ 
                    // record method id
                    method_id = 2;
                    // non-conformance condition 
                    if ( 0 ) {
                      goto ERROR;
                    }
                    // state update
                    q = 4;
                    // post condition
                    this_state=3; 
                  }
                  continue;
                }
                
                if(a18){
                  // assume guard
                  if ( 1 ){ 
                    // record method id
                    method_id = 4;
                    // non-conformance condition 
                    if ( (this_state == 2) ) {
                      goto ERROR;
                    }
                    // state update
                    q = 1;
                    // post condition
                    break;
                  }
                  continue;
                }
              
                if(a19){
                  // assume guard
                  if ( 1 ){ 
                    // record method id
                    method_id = 5;
                    // non-conformance condition 
                    if ( (this_state != 3) ) {
                      goto ERROR;
                    }
                    // state update
                    q = 4;
                    // post condition
                    this_state=this_state; 
                  }
                  continue;
                }
               
                if(a20){
                  // assume guard
                  if ( 1&& (((this_state == 2) && (this_state != 3)) || ((this_state != 2) && (this_state != 3))) ){ 
                    // record method id
                    method_id = 6;
                    // non-conformance condition 
                    if ( ((this_state != 2) && (this_state != 3)) ) {
                      goto ERROR;
                    }
                    // state update
                    q = 4;
                    // post condition
                    this_state=this_state; 
                  }
                  continue;
                }
               
                if(a21){
                  // assume guard
                  if ( 1&& (((this_state == 2) && (this_state != 3)) || ((this_state != 2) && (this_state != 3)))&& ((this_state == 3) || ((this_state != 2) && (this_state != 3))) ){ 
                    // record method id
                    method_id = 6;
                    // non-conformance condition 
                    if ( ((this_state != 2) && (this_state != 3)) ) {
                      goto ERROR;
                    }
                    // state update
                    q = 4;
                    // post condition
                    this_state=this_state; 
                  }
                  continue;
                }

          continue;
        }
        
   
  
  } // end while

  

 ERROR:
  printf("error \n ");


 
 

 return 0;
}
