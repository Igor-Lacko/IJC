//bitset.c
//riesenie IJC DU 1, priklad a 
//autor: Igor Lacko, FIT (Xlackoi00)
//prekladane s gcc, parametre -O2 -g -std=c11 -pedantic -Wall -Werror -Wextra (a linknute s matematickou kniznicou cez -lm)
//externe deklaracie funkcii ktore su nadefinovane ako inline v bitset.h, pre pouzitie v inline variante implementacie eratosthenovho sita
#include "bitset.h"
#ifdef USE_INLINE              
extern void bitset_free(bitset_t jmeno_pole);
extern bitset_index_t bitset_size(bitset_t jmeno_pole);
extern void bitset_fill(bitset_t jmeno_pole, int bool_vyraz);
extern bitset_index_t bitset_getbit(bitset_t jmeno_pole, bitset_index_t index);
extern void bitset_setbit(bitset_t jmeno_pole, bitset_index_t index, int bool_vyraz);
#endif                                                                                                                                                               