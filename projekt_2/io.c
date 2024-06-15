//io.c, IJC DU2, priklad b) 
//autor: Igor Lacko, FIT (xlackoi00)
//prekladane gcc -g -std=c11 -pedantic -Wall -Wextra
//modul s funkciou read_word
#include "io.h"

int warning = 0; //aby sme mohli vraciat dlzku skrateneho slova a zaroven vypisali varovanie len raz


//nacita slovo o dlzke < max - 1 do pola s zo subora f
int read_word(char *s, int max, FILE *f){
    int c, index = 0; int state; 
    if(isspace(c = getc(f))) state = 1; //sme vo whitespacoch
    else if(c == EOF) return EOF; //koniec subora
    else state = 0; //sme v slove
    ungetc(c, f);
    while((c = getc(f)) != EOF){
        switch(state){ //budeme potrebovat 3 stavy: whitespace, cast slova ktoru citame a cast slova ktoru treba odrezat
            case 0: //citame slovo
                if(isspace(c)){
                    s[index] = '\0';
                    return index;
                }
                s[index ++] = c;
                if((index == max - 1) && (!isspace(c = getc(f))) && (c != EOF)){ //ak sme na poslednom indexe a nenachadzame sa na medzere (alebo EOF), slovo je prilis dlhe
                    s[index] = '\0';
                    if(!warning){
                        fprintf(stderr, "Warning: Word length exceeds limit!\n");
                        warning = 1; 
                    }
                    ungetc(c, f); 
                    state = 2; //ak treba odrezat zbytok slova, vojdeme do tohto stavu
                    break;
                }
                else if(isspace(c)){
                    return index;
                }
                break;
            
            case 1: //nacitavame whitespace kym nedojdeme k zaciatku slova
                if(!isspace(c)){
                    s[index ++] = c;
                    state = 0; 
                    break;
                }
                break;
            case 2: //stav kedy odrezavame zbytok slova
                if(isspace(c)){
                    return index;
                }
                break;
                
        }
    }
    if(state == 1) return EOF; //ak je stav 1 uz nebudeme citat ziadne slovo kedze sme na konci suboru, cize mozme vratit EOF
    else{ //v opacnom pripade chceme vratit dlzku slova, teda vratime naspat znak a vratime dlzku (EOF vrati podmienka na zaciatku pri dalsom volani funkcie)
        s[index] = '\0';
        ungetc(c, f);
        return index;
    }
}


