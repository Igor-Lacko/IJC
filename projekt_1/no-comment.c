//no_comment.c
//riesenie IJC DU 1, priklad b
//autor: Igor Lacko, FIT (Xlackoi00)
//prekladane s gcc, parametre -O2 -g -std=c11 -pedantic -Wall -Werror -Wextra 
//implementacia stavoveho automatu ktory vyfiltruje poznamky zo zdrojoveho kodu jazyka C
#include <stdio.h>
#include <stdlib.h>
#include "error.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>


//skontroluje pomocou funkcie fstat ci nebol vstupny subor presmerovany do seba pomocou porovnania i-uzlov
void RedirectionCheck(char *filename){
    int fd = open(filename, O_RDONLY);
    if(fd == -1) error_exit("Subor %s sa nepodarilo otvorit!\n", filename);
    struct stat f; 
    struct stat s;
    if((fstat(fd, &f) != -1) && (fstat(1, &s) != -1)){
        if(s.st_ino == f.st_ino){
            close(fd);
            error_exit("Subor %s bol presmerovany sam do seba!\n", filename);
        }
    }
    else{
        close(fd);
        error_exit("Subor %s sa nepodarilo otvorit!\n", filename);
    }
    close(fd);
}

//funkcia ktora implementuje stavovy automat na odstranenie komentarov
int RemoveComments(FILE *src){
    int state = 0; //stavova premenna
    int c; //znak ktory budeme citat
    while((c=getc(src)) != EOF){ //kym niesme na konci suboru
        switch(state){
            case 0:             //default stav, kym nedostaneme znak '/' (mozny zaciatok komentara), alebo "/'
                if(c == '\"'){
                    putchar(c);
                    state = 1;
                    break;
                }
                else if(c == '\''){
                    putchar(c);
                    state = 3;
                    break;
                }
                else if(c == '/'){
                    state = 6;
                    break;
                }
                putchar(c);
                break;
            case 1:
                if(c == '\"'){
                    putchar(c);
                    state = 0;
                    break;
                }
                else if(c == '\\'){
                    putchar(c);
                    state = 2;
                    break;
                }
                else if(c == '\n'){
                    state = -1;
                    break;
                }
                putchar(c);
                break;
            case 2:
                putchar(c);
                state = 1;
                break;
            case 3:
                if(c == '\\'){
                    putchar(c);
                    state = 4;
                    break;
                }
                else if(c == '\''){
                    putchar(c);
                    state = 0;  
                    break;
                }
                putchar(c);
                state = 5;
                break;
            case 4:
                putchar(c);
                state = 5;
                break;
            case 5:
                if(c == '\''){
                    putchar(c);
                    state = 0;
                    break;
                }
                state = -1;
                break;
            case 6:
                if(c == '/'){
                    state = 7;
                    break;
                }
                else if(c == '*'){
                    state = 8;  
                    break;
                }
                putchar('/');
                putchar(c);
                state = 0;
                break;
            case 7:
                if(c == '\n'){
                    putchar('\n'); 
                    state = 0;
                    break;
                }
                else if(c == '\\'){
                    state = 10;
                    break;
                }
                break;
            case 8:
                if(c == '*'){
                    state = 9;
                    break;
                }
                break;
            case 9:
                if(c == '/'){
                    putchar(' ');
                    state = 0;
                    break;
                }
                else if(c == '*'){
                    break;
                }
                state = 8;
                break;
            case 10:
                state = 7;
                break;
            case -1:
                fclose(src);
                putchar('\n');
                error_exit("Neplatny format vstupneho suboru!\n");
                break;
        }
    }
    fclose(src);
    return state;
}

int main(int argc, char **argv)
{
    FILE *src = NULL;
    if(argc > 2){
        error_exit("Nespravny pocet argumentov!\n"); //osetrenie spravneho poctu argumentov, chceme len jeden zdrojak
    }
    else if(argc < 2){ 
        src = stdin;
    }
    else{
        RedirectionCheck(argv[1]);
        src = fopen(argv[1], "r"); 
        if(src == NULL){
            error_exit("Subor %s sa nepodarilo otvorit!\n", argv[1]);
        }
    }
    if(RemoveComments(src) != 0){
        putchar('\n');
        error_exit("Neplatny format vstupneho suboru!\n"); 
    }
    return 0;
}