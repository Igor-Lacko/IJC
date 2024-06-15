//bitset.h 
//riesenie IJC DU 1, priklad a 
//autor: Igor Lacko, FIT (Xlackoi00)
//prekladane s gcc, parametre -O2 -g -std=c11 -pedantic -Wall -Werror -Wextra (a linknute s matematickou kniznicou cez -lm)
//definicie makier a inline funkcii pouzite v implementacii eratosthenovho sita
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include "error.h"
typedef unsigned long bitset_index_t;
typedef bitset_index_t* bitset_t;

#define bit_num(index) (index + (sizeof(bitset_index_t) * CHAR_BIT)) % (sizeof(bitset_index_t) * CHAR_BIT)
//pomocne makro ktorym ziskame "index" daneho bitu v konkretnej polozky v poli (napr. index 64 bitsetu je bit 0 danej hodnoty)
#define num_elements(velikost) velikost / (CHAR_BIT * sizeof(bitset_index_t)) + 1 + (velikost < CHAR_BIT * sizeof(bitset_index_t)) + ((velikost) % (CHAR_BIT * sizeof(bitset_index_t)) != 0)

#define array_index(velikost, index) ((index + 1) / (sizeof(bitset_index_t) * CHAR_BIT)) + ((index + 1) % (CHAR_BIT * sizeof(unsigned long)) != 0) + (velikost < (CHAR_BIT * sizeof(bitset_index_t))) 

#define bitset_create(jmeno_pole,velikost) \
static_assert(((unsigned long)velikost <= ULONG_MAX) && ((long)velikost > 0), "ERROR: Invalid bitfield size!!!\n"); \
bitset_index_t jmeno_pole[num_elements(velikost)] = {0};

#define bitset_alloc(jmeno_pole, velikost) bitset_t jmeno_pole = NULL; \
do{ \
    assert(((unsigned long)velikost <= ULONG_MAX) && ((long)velikost > 0)); \
    unsigned long size = sizeof(bitset_index_t) + (velikost / CHAR_BIT); \
    short r = (size % sizeof(bitset_index_t) == 0) ? 0 : 1; \
    jmeno_pole = calloc(size / sizeof(bitset_index_t) + r, sizeof(bitset_index_t)); \
    if(jmeno_pole == NULL) error_exit("bitset_alloc: Chyba alokace paměti"); \
} while(0)

#if !defined(USE_INLINE) //podmieneny preklad, ak NIE JE definovane USE_INLINE vytvori sa default verzia s makrami


#define bitset_free(jmeno_pole) free(jmeno_pole)
#define bitset_size(jmeno_pole) jmeno_pole[0]



#define bitset_fill(jmeno_pole, bool_vyraz){ \
    /*ulozime si velkost pola do docasnej premennej*/ bitset_index_t size = jmeno_pole[0]; \
    /*zistime pocet prvkov v poli longov (nie bitset)*/bitset_index_t num_elements = num_elements(size);\
    (bool_vyraz == true) ? memset(jmeno_pole, ~0, num_elements * sizeof(bitset_index_t)) : memset(jmeno_pole, 0, num_elements * sizeof(bitset_index_t)); \
    /*cez memset si nastavime kazdy prvok v poli bud na 0, alebo invertovanu 0 (tj vsetky bity na 1) */ \
    jmeno_pole[0] = size; \
}

#define bitset_getbit(jmeno_pole, index) \
((unsigned long)index < jmeno_pole[0]) ? \
/*pomocou posuvu si posunieme bit ktory chceme zistit na LSB a porovname s 1 cez logicky AND*/\
1UL & ((jmeno_pole[array_index(jmeno_pole[0], index)]) >> ((CHAR_BIT * sizeof(bitset_index_t)) - bit_num(index) - 1)) \
:\
(error_exit("bitset_getbit: Index %lu mimo rozsah 0..%lu", (unsigned long) index, jmeno_pole[0] - 1), 2)



#define bitset_setbit(jmeno_pole, index, bool_vyraz)do{\
    if((unsigned long)index >= jmeno_pole[0]){\
        error_exit("bitset_setbit: Index %lu mimo rozsah 0..%lu", (unsigned long) index, jmeno_pole[0] - 1);\
    }\
    /*zistime v akom indexe v poli (longov, nie bitsete) sa dany bit nachadza*/\
    unsigned long arr_index = array_index(jmeno_pole[0], index);\
    /*je mozne ze bit je na danu hodnotu uz nastaveny, preto tu pridame jednu podmienku (a zistime hodnotu bitu)*/ \
    int bit_value = bitset_getbit(jmeno_pole, index);\
    /*pouzijeme posuv cisla 1 a XOR na nastavenie bitu (ak bola 0, zmeni sa na 1, ak 1 zmeni sa na 0)*/\
    if(bit_value != bool_vyraz){\
        jmeno_pole[arr_index] = jmeno_pole[arr_index] ^ (1UL << (CHAR_BIT * sizeof(bitset_index_t) - bit_num(index) - 1));\
    }\
} while(0)

#else 


inline void bitset_free(bitset_t jmeno_pole){
    free(jmeno_pole);
}

inline bitset_index_t bitset_size(bitset_t jmeno_pole){
    return jmeno_pole[0];
}

inline void bitset_fill(bitset_t jmeno_pole, int bool_vyraz){
    /*ulozime si velkost pola do docasnej premennej*/ 
    bitset_index_t size = jmeno_pole[0]; 
    /*zistime pocet prvkov v poli longov (nie bitset)*/
    bitset_index_t num_elements = num_elements(size);
    bool_vyraz ? memset(jmeno_pole, ~0, num_elements * sizeof(bitset_index_t)) : memset(jmeno_pole, 0, num_elements * sizeof(bitset_index_t)); 
    /*cez memset si nastavime kazdy prvok v poli bud na 0, alebo invertovanu 0 (tj vsetky bity na 1) */ 
    jmeno_pole[0] = size; 
}

inline bitset_index_t bitset_getbit(bitset_t jmeno_pole, bitset_index_t index){
    if((unsigned long)index >= jmeno_pole[0]) error_exit("bitset_getbit: Index %lu mimo rozsah 0..%lu", (unsigned long) index, jmeno_pole[0] - 1);
    return 1UL & ((jmeno_pole[array_index(jmeno_pole[0], index)]) >> ((CHAR_BIT * sizeof(bitset_index_t)) - bit_num(index) - 1));
}

inline void bitset_setbit(bitset_t jmeno_pole, bitset_index_t index, int bool_vyraz){
    if((unsigned long)index >= jmeno_pole[0]) error_exit("bitset_setbit: Index %lu mimo rozsah 0..%lu", (unsigned long) index, jmeno_pole[0] - 1);
    /*zistime v akom indexe v poli (longov, nie bitsete) sa dany bit nachadza*/
    int arr_index = array_index(jmeno_pole[0], index);
    /*je mozne ze bit je na danu hodnotu uz nastaveny, preto tu pridame jednu podmienku (a zistime hodnotu bitu)*/ 
    int bit_value = bitset_getbit(jmeno_pole, index);
    /*pouzijeme posuv cisla 1 a XOR na nastavenie bitu (ak bola 0, zmeni sa na 1, ak 1 zmeni sa na 0)*/
    if(bit_value != bool_vyraz){
        jmeno_pole[arr_index] = jmeno_pole[arr_index] ^ (1UL << (CHAR_BIT * sizeof(bitset_index_t) - bit_num(index) - 1));
    }
}

#endif