//htab_statistics.c, IJC DU 2, priklad b)
//Autor: Igor Lacko, FIT (xlackoi00)
//modul s funkciou htab_statistics.c, vypise zakladne statistiky tabulky (priemerna dlzka zaznamu, maximalna a minimalna dlzka)



#include "htab_private.h"


//min, max, avg na stderr
void htab_statistics(const htab_t * t){
    long double average =  t -> size / t -> arr_size; 
    unsigned long *sum_in_bucket = calloc(t -> arr_size, sizeof(unsigned long)); //alokacia pomocneho pola do ktoreho ulozime dlzku kazdeho zoznamu

    if(sum_in_bucket == NULL){ //kontrola alokacie
        fprintf(stderr, "Error: Memory allocation failed!\n");
        exit(1);
    }

    //naplnenie pola dlzkami kazdeho zoznamu na indexe i
    for(unsigned long i = 0; i < t -> arr_size; i++){
        htab_item_t *tmp = t -> arr[i];
        while(tmp != NULL){
            tmp = tmp -> next;
            sum_in_bucket[i] ++;
        }
    }
    //najdenie minima a maxima
    unsigned long min = sum_in_bucket[0];
    unsigned long max = sum_in_bucket[0];

    for(unsigned long j = 0; j < t -> arr_size; j++){
        if(sum_in_bucket[j] > max) max = sum_in_bucket[j];
        if(sum_in_bucket[j] < min) min = sum_in_bucket[j];
    }

    if(sum_in_bucket != NULL) free(sum_in_bucket); //uvolnenie pola
    
    //vypis statistik
    fprintf(stderr, "Average: %Lf\nMin: %lu\nMax: %lu\n", average, min, max);
}