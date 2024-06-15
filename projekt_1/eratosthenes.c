//eratosthenes.c
//riesenie IJC DU 1, priklad a 
//autor: Igor Lacko, FIT (Xlackoi00)
//prekladane s gcc, parametre -O2 -g -std=c11 -pedantic -Wall -Werror -Wextra (a linknute s matematickou kniznicou cez -lm)
//implementacia algoritmu eratosthenovho sita pouzita v subore primes.c
#include "bitset.h"
#include <stdio.h>
#include "eratosthenes.h"           
#include <limits.h> 
#include <string.h>
#include <math.h>
#include <stdbool.h>                        

void Eratosthenes(bitset_t pole){
    //ziskame velkost pola z prveho indexu
    bitset_index_t size = pole[0];
    //nastavime bitset na jednotky a postupne skrtame (0. a 1. bit nastavime na 0) 
    bitset_setbit(pole, 0, false); bitset_setbit(pole, 1, false);
    bitset_fill(pole, true); 
    //bitset_setbit(pole, 0, false); bitset_setbit(pole, 1, false);
    for(bitset_index_t i = 3; i <= sqrt(size); i += 2){ //0 a 1 nie su prvocisla, zaroven mozme ignorovat vsetky nasobky 2, tj zacneme od 3
        //zaroven preskocime nasobky par malych prvocisel pre optimalizaciu (okrem ich samotnych)

        if(bitset_getbit(pole, i)){ //najmensie i take, ze pole[i] == 1 => i je prvocislo
            for(bitset_index_t j = (3 * i); j < size; j +=  (2 * i)){ //j = oznacime vsetky nasobky daneho bitu i
                if(j < size) bitset_setbit(pole, j, false); //"vyskrtame" vsetky nasobky - niesu to prvocisla, ale nasobky nejakeho mensieho prvocisla
                else break;
            }
        }
        if(i + 2 >= sqrt(size)) break;
        }
    //touto eliminaciou zostali bity s hodnotou 1 na prvociselnych indexoch
    //chceme najvyssich 10, preto ideme od hora
    //deklarujeme si pole kde chceme ulozit prvocisla kedze je rychlejsie ist odzadu a vypisujeme vzostupne
    bitset_index_t primes[10];
    int p_index = 0;
    for(bitset_index_t k = !((size - 1) % 2) ? size - 2: size - 1; k >= 2; k-=2){ 
        if(bitset_getbit(pole, k)){
            primes[p_index] = k; p_index ++;
            if(p_index == 10) break;
        }
    }
    //vypis prvocisel
    if(p_index != 10) printf("2\n");
    for(int i = p_index == -1 ? 9 : p_index - 1; i >= 0 ; i--){
        printf("%lu\n",primes[i]);
    }
}