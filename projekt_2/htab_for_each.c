//htab_for_each.c, IJC DU2, priklad b) 
//autor: Igor Lacko, FIT (xlackoi00)
//prekladane gcc -g -std=c11 -pedantic -Wall -Wextra
//modul s funkciou htab_for_each (zavola na kazdy zaznam funkciu, ktorej ukazatel dostane ako parameter)
#include "htab_private.h"

//zavola funkciu f na kazdy par (key, value) v tabulke
void htab_for_each(const htab_t * t, void (*f)(htab_pair_t *data)){
    for(unsigned long i = 0; i < t -> arr_size; i++){
        htab_item_t *tmp = t -> arr[i];
        while(tmp != NULL){
            f(tmp -> data);
            tmp = tmp -> next;
        }
    }
}