//htab_lookup_add.c, IJC DU2, priklad b) 
//autor: Igor Lacko, FIT (xlackoi00)
//prekladane gcc -g -std=c11 -pedantic -Wall -Wextra
//modul s funkciou htab_lookup_add (najde zadany zaznam v tabulke a vrati ukazatel na neho, ak nenajde tak prida do tabulky)
#include "htab_private.h"

htab_pair_t * htab_lookup_add(htab_t * t, htab_key_t key){
    htab_pair_t *ptr;
    if((ptr = htab_find(t, key)) == NULL){ //najprv vytvorime dany zaznam
        unsigned long hash_index = htab_hash_function(key) % (t -> arr_size); //ziskanie indexu v tabulke 
        
        htab_item_t *item = malloc(sizeof(htab_item_t));
        if(item == NULL){
            return NULL;
        }
        
        item -> data = malloc(sizeof(htab_pair_t));
        if(item -> data == NULL){
            return NULL;
        }
        item -> next = NULL;
        item -> data -> value = 0;
        
        item -> data -> key = malloc((strlen(key) + 1) * sizeof(char));
        if(item->data->key == NULL){
            return NULL;
        }
        strcpy((void*)item->data->key, key);
        item -> data -> value = 0;
        
        //pridanie zaznamu do pola 
        if(t -> arr[hash_index] == NULL){//ak je to prvy prvok, proste ho nastavime na item a dalsi prvok item na NULL
            t -> arr[hash_index] = item;
        } 
        else{ //ak nie tak ho pridame na zaciatok zoznamu (rychlejsie ako na koniec)
            item -> next = t -> arr[hash_index];
            t -> arr[hash_index] = item; 
        }
        t -> size ++;
        return item -> data;
    }
    else{ //ak je zadany zaznam v tabulke, vratime ukazatel
        return ptr;
    }
}