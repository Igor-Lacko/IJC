//htab_find.c, IJC DU2, priklad b) 
//autor: Igor Lacko, FIT (xlackoi00)
//prekladane gcc -g -std=c11 -pedantic -Wall -Wextra
//modul s funkciou htab_find (najde zadany zaznam v tabulke a vrati ukazatel na neho, ak nenajde vrati NULL)


#include "htab_private.h"
htab_pair_t *htab_find(const htab_t *t, htab_key_t key){

    unsigned long hash_index = htab_hash_function(key) % t -> arr_size;
    htab_item_t *tmp = NULL;

    if(t -> arr[hash_index] == NULL) return NULL;
    else tmp = t -> arr[hash_index];

    while(tmp != NULL){
        if(!strcmp(tmp -> data -> key,key)){
            return tmp -> data;
        }
        tmp = tmp -> next;
    }
    
    return NULL; //ak zadany zaznam nieje v tabulke
}