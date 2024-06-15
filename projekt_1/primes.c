//primes.c
//riesenie IJC DU 1, priklad a 
//autor: Igor Lacko, FIT (Xlackoi00)
//prekladane s gcc, parametre -O2 -g -std=c11 -pedantic -Wall -Werror -Wextra (a linknute s matematickou kniznicou cez -lm)
//main subor pre implementaciu eratosthenovho sita 
#include <stdio.h> 
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <stdarg.h>
#include <limits.h>
#include <assert.h>
#include <string.h>
#include "bitset.h"
#include "eratosthenes.h"                   
#include "error.h"
#include <time.h>




int main(void){
    clock_t start = clock();                                             
    bitset_create(p, 666000000);                           
    p[0] = 666000000;                                                                                                                                                                                                                                                                                  
    Eratosthenes(p);
    fprintf(stderr, "Time=%.3g\n", (double)(clock()-start)/CLOCKS_PER_SEC);
}