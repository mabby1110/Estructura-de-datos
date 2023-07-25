#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

int isValidSimbol(char *p){
    if(*p == '+' || *p == '-' || *p == '*' || *p == '/'){
        return 1;
    }
    return 0;
}

int main(){
    char cadena[] = "oh4na = f4milia";
    char *p;
    int estdo = 1;

    p = cadena;

    while(*p != '\0'){ // mientras p no sea fin de cadena
        if(*p != ' '){ // ignora los espacios

            printf("%c\t", *p);
            printf("%d\t", isalpha(*p));

            switch(estado){
                case 1: // inicio id
                    if(isalpha(*p) != 0){
                        estado++;
                    } else {
                        return 1;
                    }
                    break;
                case 2: // resto del id
                    if(!isalpha(*p) || !isdigit(*p) || *p != '-' || *p != '_'){
                        if(*p == '='){
                            estado ++;
                        } else if (isValidSimbol(p)){
                            return 1;
                        }
                    }
                case 3: // pasando el =
                    if(isalpha(*p) != 0){
                        estado++;
                    } else {
                        return 1;
                    }
                    break;
                case 4:
                    if(isValidSimbol(p)){
                        estado++;
                    }
                    break;
            }
        }
        p++;
    }

    return 0;
}