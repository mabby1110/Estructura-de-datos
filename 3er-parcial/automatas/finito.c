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
    int estado = 1;
    int punto = 0;

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
                        printf("\ncadena incorrecta");
                        return 1;
                    }
                    break;
                case 2: // resto del id
                    if(!isalpha(*p) || !isdigit(*p) || *p != '-' || *p != '_'){
                        if(*p == '='){
                            estado ++;
                        } else {
                            printf("\ncadena incorrecta");
                            return 1;
                        }
                        break;
                    }
                case 3: // pasando el = saber si es numero o variable
                    if(isalpha(*p)){ // es variable
                        estado = 4;
                    } else if(isdigit(*p)){
                        estado = 5;
                    }
                    break;
                case 4: // terminar variable
                    if(!isalpha(*p) || !isdigit(*p) || *p != '-' || *p != '_'){
                        if(isValidSimbol(p)){
                            estado = 3;
                        } else {
                            printf("\ncadena incorrecta");
                            return 1;
                        }
                        break;
                    }
                case 5: // terminar numero
                    if(!isdigit(*p) && *p != '.'){
                        if(isValidSimbol(p)){
                            estado = 3;
                        } else {
                            printf("\ncadena incorrecta");
                            return 1;
                        }
                    } else if(*p == '.' && punto == 1){
                        printf("\ncadena incorrecta");
                        return 1;
                    }
                    break;
            }
        }
        p++;
    }

    printf("\ncadena correcta");

    return 0;
}