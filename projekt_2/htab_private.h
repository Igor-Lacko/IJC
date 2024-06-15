//IJC, DU2, priklad b), htab_private.h
//privatni hlavickovy subor obsahujuci definicie struktur a niektore includy

#ifndef _HTAB_PRIVATE_H
#define _HTAB_PRIVATE_H


#include "htab.h"

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>


//struktura htab_item
typedef struct htab_item{
    struct htab_item *next; 
    htab_pair_t *data;
} htab_item_t;

typedef struct htab{
    unsigned long size; //pocet celkovych zaznamov
    unsigned long arr_size; //pocet poloziek v poli
    htab_item_t *arr[]; 
} htab_t;


#endif


