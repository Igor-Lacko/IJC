//htab_size.c, IJC DU2, priklad b) 
//autor: Igor Lacko, FIT (xlackoi00)
//prekladane gcc -g -std=c11 -pedantic -Wall -Wextra
//modul s funkciou htab_bucket_count (vrati pocet poloziek v poli zaznamov v tabulke)

#include "htab_private.h"
size_t htab_bucket_count(const htab_t *t){
    return t -> arr_size;
}