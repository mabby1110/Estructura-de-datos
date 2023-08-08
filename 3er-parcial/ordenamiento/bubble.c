#include <stdio.h>

void cambiar(char *p);
void bubblesort(char *p);

int main(){
    char dato[] = "Bernardo";
    char *p;

    p = dato;

    while(*p){
        printf("%c %i\n", *p, *p);

        if(*p > *(p+1)){
            cambiar(p);
        }
        p++;
    }

    return 0;
}

void cambiar(char *p){
    char temp;
    
    temp = *p;
    *p = *(p+1);
    *(p+1) = temp;
}