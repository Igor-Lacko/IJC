//hitab_init.c, IJC DU 2, priklad b)
//Autor: Igor Lacko, FIT (xlackoi00)
//modul s funkciou htab_init.c, vytvori a inicializuje tabulku 
#include "htab_private.h"

htab_t *htab_init(const size_t n){
    htab_t* table = malloc(sizeof(htab_t) + n * sizeof(htab_item_t*)); //alokacia tabulky 
    if(table == NULL){ //kontrola alokacie
        return NULL;
    }
    table -> arr_size = n; //inicializacia poloziek v poli 
    table -> size = 0;
    for(unsigned long i = 0; i < table -> arr_size; i++){ //nastavime vsetky prvky zoznamu na NULL
        table -> arr[i] = NULL;
    }
    return table;
}
