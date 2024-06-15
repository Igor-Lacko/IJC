//htab_size.c, IJC DU2, priklad b) 
//autor: Igor Lacko, FIT (xlackoi00)
//prekladane gcc -g -std=c11 -pedantic -Wall -Wextra
//modul s funkciou htab_size (vrati pocet zaznamov v tabulke)

#include "htab_private.h"
size_t htab_size(const htab_t *t){
    return t -> size;
}