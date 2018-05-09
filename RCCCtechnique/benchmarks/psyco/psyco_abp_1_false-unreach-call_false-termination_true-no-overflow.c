
#include<stdio.h>
#ifdef LLBMC
#include <llbmc.h>
#else
#include <klee/klee.h>
#endif

// method ids
int m_Protocol = 1;
int m_msg_2 = 2;
int m_recv_ack_2 = 3;
int m_msg_1_1 = 4;
int m_msg_1_2 = 5;
int m_recv_ack_1_1 = 6;
int m_recv_ack_1_2 = 7;
 

int main() {

  int q;
  klee_make_symbolic(&q, sizeof(int), "q");
  int method_id;

  // variables
    int this_expect = 0;
    int this_buffer_empty = 0;
   

  while (1) {

    // parameters
        int P1;
        int P2;
        int P3;
        int P4;
        int P5;
        int P6;
        int P7;
        int P8;
        int P9;
        int a1,a2,a3,a4,a5,a6,a7,a8,a9,a10;
        int a11,a12,a13,a14,a15,a16,a17,a18,a19,a20;
        int a21,a22,a23,a24,a25,a26,a27,a28,a29,a30,a31;
        klee_make_symbolic(&P1, sizeof(int), "P1");
        klee_make_symbolic(&P2, sizeof(int), "P2");
        klee_make_symbolic(&P3, sizeof(int), "P3");
        klee_make_symbolic(&P4, sizeof(int), "P4");
        klee_make_symbolic(&P5, sizeof(int), "P5");
        
        klee_make_symbolic(&P6, sizeof(int), "P6");
        klee_make_symbolic(&P7, sizeof(int), "P7");
        klee_make_symbolic(&P8, sizeof(int), "P8");
        klee_make_symbolic(&P9, sizeof(int), "P9");

    
    //fix for overflow in this_expect 
        if(this_expect > 16){
          this_expect = -16;
        }

    // states
        if (q == 0){      
                klee_make_symbolic(&a1, sizeof(int), "a1");
                if(a1){
                  // assume guard
                  if ( 1 ){ 
                    // record method id
                    method_id = 1;
                    // non-conformance condition 
                    if ( 0 ) {
                      goto ERROR;
                    }
                    // state update
                    q = 1;
                    // post condition
                    this_expect=0; this_buffer_empty=1; 
                  }
                  continue;
                }

          continue;
        }
        if (q == 1){      
        klee_make_symbolic(&a2, sizeof(int), "a2");
                if(a2){
                  // assume guard
                  if ( !((P1 % 2) != (0 % 2)) ){ 
                    // record method id
                    method_id = 2;
                    // non-conformance condition 
                    if ( (((((P1 % 2) != (this_expect % 2)) && (this_buffer_empty == 1)) && !((P1 % 2) != (0 % 2))) || ((this_buffer_empty != 1) && !((P1 % 2) != (0 % 2)))) ) {
                      goto ERROR;
                    }
                    // state update
                    q = 3;
                    // post condition
                    this_expect=(this_expect + 1); this_buffer_empty=(1 - this_buffer_empty); 
                  }
                  continue;
                }
                klee_make_symbolic(&a3, sizeof(int), "a3");
                if(a3){
                  // assume guard
                  if ( !(P1 != (((0 + 1) - 1) % 2)) ){ 
                    // record method id
                    method_id = 3;
                    // non-conformance condition 
                    if ( (((P3 == ((this_expect - 1) % 2)) && (this_buffer_empty != 1)) && !(P3 != (((0 + 1) - 1) % 2))) ) {
                      goto ERROR;
                    }
                    // state update
                    q = 2;
                    // post condition
                    break;
                  }
                  continue;
                }
                klee_make_symbolic(&a4, sizeof(int), "a4");
                if(a4){
                  // assume guard
                  if ( (((P1 % 2) != (0 % 2)) && (((P1 % 2) != ((0 + 1) % 2)) && ((P1 % 2) != (0 % 2)))) ){ 
                    // record method id
                    method_id = 4;
                    // non-conformance condition 
                    if ( (((((P4 % 2) == (this_expect % 2)) && (this_buffer_empty == 1)) && ((P4 % 2) != (0 % 2))) && (((P4 % 2) != (0 % 2)) && (((P4 % 2) != ((0 + 1) % 2)) && ((P4 % 2) != (0 % 2))))) ) {
                      goto ERROR;
                    }
                    // state update
                    q = 2;
                    // post condition
                    break;
                  }
                  continue;
                }
                klee_make_symbolic(&a5, sizeof(int), "a5");
                if(a5){
                  // assume guard
                  if ( (((P1 % 2) != (0 % 2)) && !(((P1 % 2) != ((0 + 1) % 2)) && ((P1 % 2) != (0 % 2)))) ){ 
                    // record method id
                    method_id = 5;
                    // non-conformance condition 
                    if ( (((((P6 % 2) == (this_expect % 2)) && (this_buffer_empty == 1)) && ((P6 % 2) != (0 % 2))) && (((P6 % 2) != (0 % 2)) && !(((P6 % 2) != ((0 + 1) % 2)) && ((P6 % 2) != (0 % 2))))) ) {
                      goto ERROR;
                    }
                    // state update
                    q = 2;
                    // post condition
                    break;
                  }
                  continue;
                }
                klee_make_symbolic(&a6, sizeof(int), "a6");
                if(a6){
                  // assume guard
                  if ( ((P1 != (((0 + 1) - 1) % 2)) && ((P1 != ((((0 + 1) + 1) - 1) % 2)) && (P1 != (((0 + 1) - 1) % 2)))) ){ 
                    // record method id
                    method_id = 6;
                    // non-conformance condition 
                    if ( ((((P8 == ((this_expect - 1) % 2)) && (this_buffer_empty != 1)) && (P8 != (((0 + 1) - 1) % 2))) && ((P8 != (((0 + 1) - 1) % 2)) && ((P8 != ((((0 + 1) + 1) - 1) % 2)) && (P8 != (((0 + 1) - 1) % 2))))) ) {
                      goto ERROR;
                    }
                    // state update
                    q = 2;
                    // post condition
                    break;
                  }
                  continue;
                }
                klee_make_symbolic(&a7, sizeof(int), "a7");
                if(a7){
                  // assume guard
                  if ( ((P1 != (((0 + 1) - 1) % 2)) && !((P1 != ((((0 + 1) + 1) - 1) % 2)) && (P1 != (((0 + 1) - 1) % 2)))) ){ 
                    // record method id
                    method_id = 7;
                    // non-conformance condition 
                    if ( ((((P9 == ((this_expect - 1) % 2)) && (this_buffer_empty != 1)) && (P9 != (((0 + 1) - 1) % 2))) && ((P9 != (((0 + 1) - 1) % 2)) && !((P9 != ((((0 + 1) + 1) - 1) % 2)) && (P9 != (((0 + 1) - 1) % 2))))) ) {
                      goto ERROR;
                    }
                    // state update
                    q = 2;
                    // post condition
                    break;
                  }
                  continue;
                }

          continue;
        }
        if (q == 2){      
        klee_make_symbolic(&a8, sizeof(int), "a8");
                if(a8){
                  // assume guard
                  if ( !((P1 % 2) != (0 % 2)) ){ 
                    // record method id
                    method_id = 2;
                    // non-conformance condition 
                    if ( ((((P1 % 2) == (this_expect % 2)) && (this_buffer_empty == 1)) && !((P1 % 2) != (0 % 2))) ) {
                      goto ERROR;
                    }
                    // state update
                    q = 2;
                    // post condition
                    break;
                  }
                  continue;
                }
                klee_make_symbolic(&a9, sizeof(int), "a9");
                if(a9){
                  // assume guard
                  if ( !(P1 != (((0 + 1) - 1) % 2)) ){ 
                    // record method id
                    method_id = 3;
                    // non-conformance condition 
                    if ( (((P3 == ((this_expect - 1) % 2)) && (this_buffer_empty != 1)) && !(P3 != (((0 + 1) - 1) % 2))) ) {
                      goto ERROR;
                    }
                    // state update
                    q = 2;
                    // post condition
                    break;
                  }
                  continue;
                }
                klee_make_symbolic(&a10, sizeof(int), "a10");
                if(a10){
                  // assume guard
                  if ( (((P1 % 2) != (0 % 2)) && (((P1 % 2) != ((0 + 1) % 2)) && ((P1 % 2) != (0 % 2)))) ){ 
                    // record method id
                    method_id = 4;
                    // non-conformance condition 
                    if ( (((((P4 % 2) == (this_expect % 2)) && (this_buffer_empty == 1)) && ((P4 % 2) != (0 % 2))) && (((P4 % 2) != (0 % 2)) && (((P4 % 2) != ((0 + 1) % 2)) && ((P4 % 2) != (0 % 2))))) ) {
                      goto ERROR;
                    }
                    // state update
                    q = 2;
                    // post condition
                    break;
                  }
                  continue;
                }
                klee_make_symbolic(&a11, sizeof(int), "a11");
                if(a11){
                  // assume guard
                  if ( (((P1 % 2) != (0 % 2)) && !(((P1 % 2) != ((0 + 1) % 2)) && ((P1 % 2) != (0 % 2)))) ){ 
                    // record method id
                    method_id = 5;
                    // non-conformance condition 
                    if ( (((((P6 % 2) == (this_expect % 2)) && (this_buffer_empty == 1)) && ((P6 % 2) != (0 % 2))) && (((P6 % 2) != (0 % 2)) && !(((P6 % 2) != ((0 + 1) % 2)) && ((P6 % 2) != (0 % 2))))) ) {
                      goto ERROR;
                    }
                    // state update
                    q = 2;
                    // post condition
                    break;
                  }
                  continue;
                }
                klee_make_symbolic(&a12, sizeof(int), "a12");
                if(a12){
                  // assume guard
                  if ( ((P1 != (((0 + 1) - 1) % 2)) && ((P1 != ((((0 + 1) + 1) - 1) % 2)) && (P1 != (((0 + 1) - 1) % 2)))) ){ 
                    // record method id
                    method_id = 6;
                    // non-conformance condition 
                    if ( ((((P8 == ((this_expect - 1) % 2)) && (this_buffer_empty != 1)) && (P8 != (((0 + 1) - 1) % 2))) && ((P8 != (((0 + 1) - 1) % 2)) && ((P8 != ((((0 + 1) + 1) - 1) % 2)) && (P8 != (((0 + 1) - 1) % 2))))) ) {
                      goto ERROR;
                    }
                    // state update
                    q = 2;
                    // post condition
                    break;
                  }
                  continue;
                }
                klee_make_symbolic(&a13, sizeof(int), "a13");
                if(a13){
                  // assume guard
                  if ( ((P1 != (((0 + 1) - 1) % 2)) && !((P1 != ((((0 + 1) + 1) - 1) % 2)) && (P1 != (((0 + 1) - 1) % 2)))) ){ 
                    // record method id
                    method_id = 7;
                    // non-conformance condition 
                    if ( ((((P9 == ((this_expect - 1) % 2)) && (this_buffer_empty != 1)) && (P9 != (((0 + 1) - 1) % 2))) && ((P9 != (((0 + 1) - 1) % 2)) && !((P9 != ((((0 + 1) + 1) - 1) % 2)) && (P9 != (((0 + 1) - 1) % 2))))) ) {
                      goto ERROR;
                    }
                    // state update
                    q = 2;
                    // post condition
                    break;
                  }
                  continue;
                }

          continue;
        }
        if (q == 3){      
        klee_make_symbolic(&a14, sizeof(int), "a14");
                if(a14){
                  // assume guard
                  if ( !((P1 % 2) != (0 % 2)) ){ 
                    // record method id
                    method_id = 2;
                    // non-conformance condition 
                    if ( ((((P1 % 2) == (this_expect % 2)) && (this_buffer_empty == 1)) && !((P1 % 2) != (0 % 2))) ) {
                      goto ERROR;
                    }
                    // state update
                    q = 2;
                    // post condition
                    break;
                  }
                  continue;
                }
                klee_make_symbolic(&a15, sizeof(int), "a15");
                if(a15){
                  // assume guard
                  if ( !(P1 != (((0 + 1) - 1) % 2)) ){ 
                    // record method id
                    method_id = 3;
                    // non-conformance condition 
                    if ( (((this_buffer_empty == 1) && !(P3 != (((0 + 1) - 1) % 2))) || (((P3 != ((this_expect - 1) % 2)) && (this_buffer_empty != 1)) && !(P3 != (((0 + 1) - 1) % 2)))) ) {
                      goto ERROR;
                    }
                    // state update
                    q = 4;
                    // post condition
                    this_expect=this_expect; this_buffer_empty=(1 - this_buffer_empty); 
                  }
                  continue;
                }
                klee_make_symbolic(&a16, sizeof(int), "a16");
                if(a16){
                  // assume guard
                  if ( (((P1 % 2) != (0 % 2)) && (((P1 % 2) != ((0 + 1) % 2)) && ((P1 % 2) != (0 % 2)))) ){ 
                    // record method id
                    method_id = 4;
                    // non-conformance condition 
                    if ( (((((P4 % 2) == (this_expect % 2)) && (this_buffer_empty == 1)) && ((P4 % 2) != (0 % 2))) && (((P4 % 2) != (0 % 2)) && (((P4 % 2) != ((0 + 1) % 2)) && ((P4 % 2) != (0 % 2))))) ) {
                      goto ERROR;
                    }
                    // state update
                    q = 2;
                    // post condition
                    break;
                  }
                  continue;
                }
                klee_make_symbolic(&a17, sizeof(int), "a17");
                if(a17){
                  // assume guard
                  if ( (((P1 % 2) != (0 % 2)) && !(((P1 % 2) != ((0 + 1) % 2)) && ((P1 % 2) != (0 % 2)))) ){ 
                    // record method id
                    method_id = 5;
                    // non-conformance condition 
                    if ( (((((P6 % 2) == (this_expect % 2)) && (this_buffer_empty == 1)) && ((P6 % 2) != (0 % 2))) && (((P6 % 2) != (0 % 2)) && !(((P6 % 2) != ((0 + 1) % 2)) && ((P6 % 2) != (0 % 2))))) ) {
                      goto ERROR;
                    }
                    // state update
                    q = 2;
                    // post condition
                    break;
                  }
                  continue;
                }
                klee_make_symbolic(&a18, sizeof(int), "a18");
                if(a18){
                  // assume guard
                  if ( ((P1 != (((0 + 1) - 1) % 2)) && ((P1 != ((((0 + 1) + 1) - 1) % 2)) && (P1 != (((0 + 1) - 1) % 2)))) ){ 
                    // record method id
                    method_id = 6;
                    // non-conformance condition 
                    if ( ((((P8 == ((this_expect - 1) % 2)) && (this_buffer_empty != 1)) && (P8 != (((0 + 1) - 1) % 2))) && ((P8 != (((0 + 1) - 1) % 2)) && ((P8 != ((((0 + 1) + 1) - 1) % 2)) && (P8 != (((0 + 1) - 1) % 2))))) ) {
                      goto ERROR;
                    }
                    // state update
                    q = 2;
                    // post condition
                    break;
                  }
                  continue;
                }
                klee_make_symbolic(&a19, sizeof(int), "a19");
                if(a19){
                  // assume guard
                  if ( ((P1 != (((0 + 1) - 1) % 2)) && !((P1 != ((((0 + 1) + 1) - 1) % 2)) && (P1 != (((0 + 1) - 1) % 2)))) ){ 
                    // record method id
                    method_id = 7;
                    // non-conformance condition 
                    if ( ((((P9 == ((this_expect - 1) % 2)) && (this_buffer_empty != 1)) && (P9 != (((0 + 1) - 1) % 2))) && ((P9 != (((0 + 1) - 1) % 2)) && !((P9 != ((((0 + 1) + 1) - 1) % 2)) && (P9 != (((0 + 1) - 1) % 2))))) ) {
                      goto ERROR;
                    }
                    // state update
                    q = 2;
                    // post condition
                    break;
                  }
                  continue;
                }

          continue;
        }
        if (q == 4){  
        klee_make_symbolic(&a20, sizeof(int), "a20");    
                if(a20){
                  // assume guard
                  if ( !((P1 % 2) != (0 % 2)) ){ 
                    // record method id
                    method_id = 2;
                    // non-conformance condition 
                    if ( ((((P1 % 2) == (this_expect % 2)) && (this_buffer_empty == 1)) && !((P1 % 2) != (0 % 2))) ) {
                      goto ERROR;
                    }
                    // state update
                    q = 2;
                    // post condition
                    break;
                  }
                  continue;
                }
                klee_make_symbolic(&a21, sizeof(int), "a21");
                if(a21){
                  // assume guard
                  if ( !(P1 != (((0 + 1) - 1) % 2)) ){ 
                    // record method id
                    method_id = 3;
                    // non-conformance condition 
                    if ( (((P3 == ((this_expect - 1) % 2)) && (this_buffer_empty != 1)) && !(P3 != (((0 + 1) - 1) % 2))) ) {
                      goto ERROR;
                    }
                    // state update
                    q = 2;
                    // post condition
                    break;
                  }
                  continue;
                }
                klee_make_symbolic(&a22, sizeof(int), "a22");
                if(a22){
                  // assume guard
                  if ( (((P1 % 2) != (0 % 2)) && (((P1 % 2) != ((0 + 1) % 2)) && ((P1 % 2) != (0 % 2)))) ){ 
                    // record method id
                    method_id = 4;
                    // non-conformance condition 
                    if ( (((((P4 % 2) == (this_expect % 2)) && (this_buffer_empty == 1)) && ((P4 % 2) != (0 % 2))) && (((P4 % 2) != (0 % 2)) && (((P4 % 2) != ((0 + 1) % 2)) && ((P4 % 2) != (0 % 2))))) ) {
                      goto ERROR;
                    }
                    // state update
                    q = 2;
                    // post condition
                    break;
                  }
                  continue;
                }
                klee_make_symbolic(&a23, sizeof(int), "a23");
                if(a23){
                  // assume guard
                  if ( (((P1 % 2) != (0 % 2)) && !(((P1 % 2) != ((0 + 1) % 2)) && ((P1 % 2) != (0 % 2)))) ){ 
                    // record method id
                    method_id = 5;
                    // non-conformance condition 
                    if ( ((((((P6 % 2) != (this_expect % 2)) && (this_buffer_empty == 1)) && ((P6 % 2) != (0 % 2))) && (((P6 % 2) != (0 % 2)) && !(((P6 % 2) != ((0 + 1) % 2)) && ((P6 % 2) != (0 % 2))))) || (((this_buffer_empty != 1) && ((P6 % 2) != (0 % 2))) && (((P6 % 2) != (0 % 2)) && !(((P6 % 2) != ((0 + 1) % 2)) && ((P6 % 2) != (0 % 2)))))) ) {
                      goto ERROR;
                    }
                    // state update
                    q = 5;
                    // post condition
                    this_expect=(this_expect + 1); this_buffer_empty=(1 - this_buffer_empty); 
                  }
                  continue;
                }
                klee_make_symbolic(&a24, sizeof(int), "a24");
                if(a24){
                  // assume guard
                  if ( ((P1 != (((0 + 1) - 1) % 2)) && ((P1 != ((((0 + 1) + 1) - 1) % 2)) && (P1 != (((0 + 1) - 1) % 2)))) ){ 
                    // record method id
                    method_id = 6;
                    // non-conformance condition 
                    if ( ((((P8 == ((this_expect - 1) % 2)) && (this_buffer_empty != 1)) && (P8 != (((0 + 1) - 1) % 2))) && ((P8 != (((0 + 1) - 1) % 2)) && ((P8 != ((((0 + 1) + 1) - 1) % 2)) && (P8 != (((0 + 1) - 1) % 2))))) ) {
                      goto ERROR;
                    }
                    // state update
                    q = 2;
                    // post condition
                    break;
                  }
                  continue;
                }
                klee_make_symbolic(&a25, sizeof(int), "a25");
                if(a25){
                  // assume guard
                  if ( ((P1 != (((0 + 1) - 1) % 2)) && !((P1 != ((((0 + 1) + 1) - 1) % 2)) && (P1 != (((0 + 1) - 1) % 2)))) ){ 
                    // record method id
                    method_id = 7;
                    // non-conformance condition 
                    if ( ((((P9 == ((this_expect - 1) % 2)) && (this_buffer_empty != 1)) && (P9 != (((0 + 1) - 1) % 2))) && ((P9 != (((0 + 1) - 1) % 2)) && !((P9 != ((((0 + 1) + 1) - 1) % 2)) && (P9 != (((0 + 1) - 1) % 2))))) ) {
                      goto ERROR;
                    }
                    // state update
                    q = 2;
                    // post condition
                    break;
                  }
                  continue;
                }

          continue;
        }
        if (q == 5){     
        klee_make_symbolic(&a26, sizeof(int), "a26"); 
                if(a26){
                  // assume guard
                  if ( !((P1 % 2) != (0 % 2)) ){ 
                    // record method id
                    method_id = 2;
                    // non-conformance condition 
                    if ( ((((P1 % 2) == (this_expect % 2)) && (this_buffer_empty == 1)) && !((P1 % 2) != (0 % 2))) ) {
                      goto ERROR;
                    }
                    // state update
                    q = 2;
                    // post condition
                    break;
                  }
                  continue;
                }
                klee_make_symbolic(&a27, sizeof(int), "a27");
                if(a27){
                  // assume guard
                  if ( !(P1 != (((0 + 1) - 1) % 2)) ){ 
                    // record method id
                    method_id = 3;
                    // non-conformance condition 
                    if ( (((P3 == ((this_expect - 1) % 2)) && (this_buffer_empty != 1)) && !(P3 != (((0 + 1) - 1) % 2))) ) {
                      goto ERROR;
                    }
                    // state update
                    q = 2;
                    // post condition
                    break;
                  }
                  continue;
                }
                klee_make_symbolic(&a28, sizeof(int), "a28");
                if(a28){
                  // assume guard
                  if ( (((P1 % 2) != (0 % 2)) && (((P1 % 2) != ((0 + 1) % 2)) && ((P1 % 2) != (0 % 2)))) ){ 
                    // record method id
                    method_id = 4;
                    // non-conformance condition 
                    if ( (((((P4 % 2) == (this_expect % 2)) && (this_buffer_empty == 1)) && ((P4 % 2) != (0 % 2))) && (((P4 % 2) != (0 % 2)) && (((P4 % 2) != ((0 + 1) % 2)) && ((P4 % 2) != (0 % 2))))) ) {
                      goto ERROR;
                    }
                    // state update
                    q = 2;
                    // post condition
                    break;
                  }
                  continue;
                }
                klee_make_symbolic(&a29, sizeof(int), "a29");
                if(a29){
                  // assume guard
                  if ( (((P1 % 2) != (0 % 2)) && !(((P1 % 2) != ((0 + 1) % 2)) && ((P1 % 2) != (0 % 2)))) ){ 
                    // record method id
                    method_id = 5;
                    // non-conformance condition 
                    if ( (((((P6 % 2) == (this_expect % 2)) && (this_buffer_empty == 1)) && ((P6 % 2) != (0 % 2))) && (((P6 % 2) != (0 % 2)) && !(((P6 % 2) != ((0 + 1) % 2)) && ((P6 % 2) != (0 % 2))))) ) {
                      goto ERROR;
                    }
                    // state update
                    q = 2;
                    // post condition
                    break;
                  }
                  continue;
                }
                klee_make_symbolic(&a30, sizeof(int), "a30");
                if(a30){
                  // assume guard
                  if ( ((P1 != (((0 + 1) - 1) % 2)) && ((P1 != ((((0 + 1) + 1) - 1) % 2)) && (P1 != (((0 + 1) - 1) % 2)))) ){ 
                    // record method id
                    method_id = 6;
                    // non-conformance condition 
                    if ( ((((P8 == ((this_expect - 1) % 2)) && (this_buffer_empty != 1)) && (P8 != (((0 + 1) - 1) % 2))) && ((P8 != (((0 + 1) - 1) % 2)) && ((P8 != ((((0 + 1) + 1) - 1) % 2)) && (P8 != (((0 + 1) - 1) % 2))))) ) {
                      goto ERROR;
                    }
                    // state update
                    q = 2;
                    // post condition
                    break;
                  }
                  continue;
                }
                klee_make_symbolic(&a31, sizeof(int), "a31");
                if(a31){
                  // assume guard
                  if ( ((P1 != (((0 + 1) - 1) % 2)) && !((P1 != ((((0 + 1) + 1) - 1) % 2)) && (P1 != (((0 + 1) - 1) % 2)))) ){ 
                    // record method id
                    method_id = 7;
                    // non-conformance condition 
                    if ( ((((this_buffer_empty == 1) && (P9 != (((0 + 1) - 1) % 2))) && ((P9 != (((0 + 1) - 1) % 2)) && !((P9 != ((((0 + 1) + 1) - 1) % 2)) && (P9 != (((0 + 1) - 1) % 2))))) || ((((P9 != ((this_expect - 1) % 2)) && (this_buffer_empty != 1)) && (P9 != (((0 + 1) - 1) % 2))) && ((P9 != (((0 + 1) - 1) % 2)) && !((P9 != ((((0 + 1) + 1) - 1) % 2)) && (P9 != (((0 + 1) - 1) % 2)))))) ) {
                      goto ERROR;
                    }
                    // state update
                    q = 1;
                    // post condition
                    this_expect=this_expect; this_buffer_empty=(1 - this_buffer_empty); 
                  }
                  continue;
                }

          continue;
        }
   

  } // end while

  return 0;

 ERROR:  
 printf("error \n");
}
