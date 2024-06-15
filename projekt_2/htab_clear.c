//htab_clear.c, IJC DU2, priklad b) 
//autor: Igor Lacko, FIT (xlackoi00)
//prekladane gcc -g -std=c11 -pedantic -Wall -Wextra
//modul s funkciou htab_clear (maze zaznamy v tabulke, tabulka ostane prazdna)


#include "htab_private.h"
void htab_clear(htab_t *t){
    for(unsigned long i = 0; i < t -> arr_size; i++){ //pre kazdy ukazatel na zoznam zaznamov chceme uvolnit vsetky jeho polozky 
        if(t -> arr[i] != NULL){
            htab_item_t *tmp = t -> arr[i]; htab_item_t *next;
            while(tmp != NULL){
                next = tmp -> next;
                if(tmp -> data -> key != NULL) free((void *)tmp -> data -> key);
                if(tmp -> data != NULL) free(tmp -> data);
                free(tmp); 
                tmp = next;
            }
            t -> arr[i] = NULL;
        }
    }
    t -> size = 0;
}