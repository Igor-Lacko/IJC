//IJC, DU2, priklad a) 
//Autor: Igor Lacko, FIT (xlackoi00)
//tail.c = podla parametrov vypisuje posledne riadky textoveho suboru 
//prekladane gcc -g -std=c11 -pedantic -Wall -Wextra
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#define MAXLENGTH 2047

//definicia struktury ktora reprezentuje kruhovy buffer a jeho metadata
typedef struct{
    char **lines; //samotny kruhovy buffer
    unsigned long capacity; //pocet prvkov
    unsigned long readindex; //start
    unsigned long writeindex; //end 
} cbuf_t;

//pomocne funkcie pre prehladnost, test plnosti/prazdnosi kruhoveho bufferu podla polozky current_size

//kontrola ci je buffer prazdny, ak ano indexy sa rovnaju 
bool IsEmpty(cbuf_t buf){
    return buf.writeindex == buf.readindex;
}

//kontrola ci je buffer plny, ak ano writeindex (tail) je o jeden index za readindexom (head)
bool IsFull(cbuf_t buf){
    return (buf.writeindex + 1 == buf.readindex) || ((buf.readindex == 0) && (buf.writeindex + 1 == buf.capacity));
}

//strlen ale nepocita '\n'
unsigned long LineLength(char *line){
    unsigned long i = 0; 
    while((line[i] != '\0') && (line[i] != '\n')) i++;
    return i;
}

//vytvori kruhovy buffer
cbuf_t cbuf_create(unsigned long n){
    //inicializacia premennych
    cbuf_t buf; buf.readindex = 0; buf.writeindex = 0; 
    buf.capacity = n + 1; //nastavime velkost bufferu na n + 1 aby sme mohli kontrolovat prazdnost/plnost podla indexov a zaroven dodrzali povodnu velkost
    //alokacia priestoru na r
    buf.lines = malloc((buf.capacity) * sizeof(char *)); //alokacia priestoru na pole riadkov 
    //kontrola alokacie
    if(buf.lines == NULL){
        fprintf(stderr, "Error: Memory allocation failed!\n");
        exit(1);
    }
    //alokacia individualnych riadkov
    for(unsigned long i = 0; i < buf.capacity; i ++){
        buf.lines[i] = malloc((MAXLENGTH + 2) * sizeof(char));
        if(buf.lines[i] == NULL){
            fprintf(stderr, "Error: Memory allocation failed!\n");
            exit(1);
        }
    }
    return buf; 
}

//vlozi polozku line na writeindex pola lines v strukture reprezentujucej buffer, vracia int kvoli erroru (ak dlzka riadku > MAXLENGTH)
int cbuf_put(cbuf_t *buf, char *line){
    //kontrola dlzky riadku
    if(strlen(line) > MAXLENGTH) return 1;
    if(IsFull(*buf)){ //ak je buffer plny (teda nieco prepisujeme) tak inkrementujeme/nulujeme readindex, velkost zostava rovnaka
        buf -> readindex = buf -> readindex + 1 >= buf -> capacity ? 0 : buf -> readindex + 1; 
    }
    //zapis do bufferu 
    strcpy(buf -> lines[buf -> writeindex], line); 
    //musime inkrementovat writeindex
    buf -> writeindex = buf -> writeindex + 1 >= buf -> capacity ? 0 : buf -> writeindex + 1; 
    return 0;
}

//vrati najstarsiu polozku z bufferu
char *cbuf_get(cbuf_t *buf){
    if(IsEmpty(*buf)){ //ak je buffer prazdny, nastane chyba a ukoncime program
        fprintf(stderr, "Error: Can't read from empty buffer!!\n");
        exit(1);
    }
    else{ //ak nie, mozme postupovat normalne, teda zmensime velkost, inkrementujeme/nulujeme readindex a vratime polozku na povodnom readindexe
        //inkrementacia alebo nulovanie readindexu
        unsigned long tmp = buf -> readindex; //odlozime si readindex, kedze ho chceme menit a nevieme ako, ale chceme vratit prvok s povodnym indexom
        buf -> readindex = buf -> readindex + 1 >= buf -> capacity ? 0 : buf -> readindex + 1; 
        return buf -> lines[tmp];
    }
}

//uvolni vsetky polozky v kruhovom bufferi a neskor samotny buffer
void cbuf_free(cbuf_t *buf){
    //uvolnenie poloziek
    for(unsigned long i = 0; i < buf -> capacity; i++){
        if(buf -> lines[i] != NULL) free(buf -> lines[i]);
    }
    //uvolnenie bufferu
    if(buf -> lines != NULL) free(buf -> lines);
}


//nacitava riadky do bufferu
void LoadFile(cbuf_t *buf, FILE *src){
    char *str = malloc((MAXLENGTH + 2) * sizeof(char)); //alokujeme maxlength + 1, miesto na '\0' a '\n'
    if(str == NULL){
        fprintf(stderr, "Error: Memory allocation failed!\n");
        exit(1);
    }
    bool warning = false; //flag aby sme vedeli ci sme uz napisali varovanie, kedze ma byt len pri prvom poruseni limitu
    while(fgets(str, MAXLENGTH + 2, src) != NULL){ 
        //ak prekroci riadok dlzku, vypiseme varovanie na stderr a odrezeme zbytok riadku 
        if(strlen(str) > MAXLENGTH){
            if(!warning){
                fprintf(stderr, "Warning: Line length exceeds limit!\n"); 
                warning = true;
            }
            int c;
            if(str[strlen(str) - 1] != '\n'){
                while(((c = getc(src)) != '\n') && (c != '\0') && (c != EOF)){
                    continue;
                }
            }
            str[MAXLENGTH] = '\0';
            cbuf_put(buf, str);
        }
        else cbuf_put(buf, str);
    }
    free(str);
}

//vypise riadky na stdout
void LinePrint(cbuf_t *buf){
    while(!IsEmpty(*buf)){
        char *c;
        printf("%s",c = cbuf_get(buf));
        if(c[strlen(c) - 1] != '\n') putchar('\n');
    }
}


int main(int argc, char **argv){
    unsigned long numlines = 10; //default hodnota, pripadne menime podla argumentu n
    FILE *src = NULL; //vstupny subor, ak zadane s -n cita stdin   
    bool zeroflag = false;
    //parsovanie argumentov
    if(argc > 4){ //nevalidny pocet
        fprintf(stderr, "Error: Invalid amount of arguments!\n");
        return 1;
    }
    //pomocou switchu obsluzime rozne pripady spustenia programu
    switch(argc){
        case 1: //pripad spustenia ./tail <stdin
            src = stdin; 
            break;
        case 2: //pripad spustenia ./tail subor
            src = fopen(argv[1], "r"); 
            if(src == NULL){ //kontrola spravnosti suboru
                fprintf(stderr, "Error: Couldn't open file %s!\n",argv[1]);
                return 1;
            }
            break;
        case 3: //pripad spustenia ./tail -n num <stdin
            if(strcmp(argv[1], "-n")){ //ak mame dva argumenty, musia to byt -n a cislo, najprv skontrolujeme ci bolo spravne zadane -n
                fprintf(stderr, "Error: Invalid argument entered!\n");
                return 1;
            }
            if(strcmp(argv[2], "0")){
                char *ptr;
                numlines = strtoul(argv[2], &ptr, 10); //konvertovanie na unsigned long 
                if((numlines == 0) || (strlen(ptr) != 0)){ //kontrola formatu cisla alebo ci neni nula
                    fprintf(stderr, "Error: Invalid argument entered!\n");
                    return 1;
                }
            }
            else zeroflag = true; 
            src = stdin; //citame z stdin
            break;
        case 4: //dve pripady spustenia:  ./tail -n num subor alebo ./tail subor -n num
            if(!strcmp(argv[1], "-n")){ //ak ide o prvy pripad (./tail -n num subor)
                if(strcmp(argv[2], "0")){
                    char *ptr; 
                    numlines = strtoul(argv[2], &ptr, 10); //konvertovanie a kontrola cisla
                    if((numlines == 0) || (strlen(ptr) != 0)){
                        fprintf(stderr, "Error: Invalid argument entered!\n");
                        return 1;
                    }
                }
                else zeroflag = true; 
                //ak nebola chyba, otvarame treti argument ako subor
                src = fopen(argv[3], "r");
                if(src == NULL){
                    fprintf(stderr, "Error: Couldn't open file %s!\n", argv[3]);
                    return 1;
                }
                else break; //ak prebehlo otvorenie v poriadku, mozme pokracovat dalej
                }
            else if(!strcmp(argv[2], "-n")){ //druhy pripad spustenia (./tail subor -n num)
                if(strcmp(argv[3], "0")){
                    char *ptr; 
                    numlines = strtoul(argv[3], &ptr, 10); //konvertovanie a kontrola cisla
                    if((numlines == 0) || (strlen(ptr) != 0)){
                        fprintf(stderr, "Error: Invalid argument entered!\n");
                        return 1;
                    }
                }
                else zeroflag = true;
                //ak vsetko prebehlo v poriadku 
                src = fopen(argv[1], "r");
                if(src == NULL){
                    fprintf(stderr, "Error: Couldn't open file %s!\n",argv[1]);
                    return 1;
                }
                else break;
                
            }
            }        

    if(zeroflag) return 0;
    cbuf_t buf = cbuf_create(numlines);
    LoadFile(&buf, src);
    LinePrint(&buf);
    cbuf_free(&buf);
    fclose(src);
    return 0;
}