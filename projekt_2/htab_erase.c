//htab_erase.c, IJC DU2, priklad b) 
//autor: Igor Lacko, FIT (xlackoi00)
//prekladane gcc -g -std=c11 -pedantic -Wall -Wextra
//modul s funkciou htab_erase (maze zadany zaznam v tabulke, vracia true pri uspechu a false pri neuspechu - napr. ak zaznam neexistuje)


#include "htab_private.h"
bool htab_erase(htab_t * t, htab_key_t key){
    unsigned long hash_index = htab_hash_function(key) % t -> arr_size; //ziskame index nech nemusime prehladavat celu tabulku
    if(t -> arr[hash_index] == NULL) return false;
    htab_item_t *item = t -> arr[hash_index];

    if(!strcmp(t -> arr[hash_index] -> data -> key, key)){ //ak je zadany zaznam hned prvy v danom indexe
        t -> arr[hash_index] = t -> arr[hash_index] -> next;
        item -> next = NULL;
        free((void *) item -> data -> key);
        free(item -> data); 
        free(item);                  
        t -> size --;
        return true;
    }

    while(item -> next != NULL){ 
        if(!strcmp(item -> next -> data -> key, key)){
            htab_item_t *tmp = item -> next;
            item -> next = tmp -> next;
            free((void *)tmp -> data -> key);
            free(tmp -> data);
            free(tmp);
            t -> size --;
            return true;
        }
            item = item -> next;
    }
    
    return false;
}
