//wordcount.c, IJC DU2, priklad b) 
//autor: Igor Lacko, FIT (xlackoi00)
//prekladane gcc -g -std=c11 -pedantic -Wall -Wextra
//hlavny subor prikladu b, pomocou hash table vypisuje z textu slova a ich pocet vyskytu


#include <stdio.h>
#include "htab.h"
#include "io.h"
#include <stdlib.h>

//Najlepsie vysledky vykazoval wordcount okolo 45000, tak som vybral najblizsie prvocislo k tomu
//k zisteniu najblizsieho prvocisla sa dal velmi pekne vyuzit priklad a) z DU1 :)
#define HTAB_BUCKETS 45007

#define MAXLENGTH_STRING 256 //max dlzka slova + '/0'

//funkcia ktorou vypiseme dvojice kluc - hodnota (pomocou volanim htab_for_each)
void htab_print(htab_pair_t *data){
    printf("%s\t%d\n", data -> key, data -> value);
}

int main(){
    htab_t *table = htab_init(HTAB_BUCKETS); //vytvorenie tabulky
    if(table == NULL){
        fprintf(stderr, "Error: memory allocation failed!\n");
        return 1;
    }
    char *s = malloc(MAXLENGTH_STRING* sizeof(char)); //tu budeme ukladat slova
    if(s == NULL){
        fprintf(stderr, "Error: Memory allocation failed!\n");
        return 1;
    }
    htab_pair_t *data; //zaznam ktory budeme vytvarat htab_lookup_add
    while(read_word(s, MAXLENGTH_STRING, stdin) != EOF){ //citame vsetky slova zo subora 
        if((data = htab_lookup_add(table, s)) == NULL){ //ak sa nepodarilo alokovat
            fprintf(stderr, "Error: Memory allocation failed!\n");
            return 1;
        }
        data -> value ++; //inkrementujeme pocitadlo vyskytov (ak je to prvy vyskyt, je to nastavene na 0 cize mozme kludne inkrementovat na 1)
    }
    #ifdef STATISTICS
    htab_statistics(table);
    #endif

    
    if(s != NULL) free(s);
    htab_for_each(table, &htab_print); //vypis dvojic kluc - hodnota
    htab_free(table); //uvolnenie tabulky
    return 0;

}