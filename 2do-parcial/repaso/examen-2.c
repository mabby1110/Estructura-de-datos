#include <stdio.h>
#include <string.h>

// pregunta 1 & 2

typedef struct Nodo{
    char nombre[20];
    char inicio[6];
    char fin[6];

    struct Nodo *next;
    struct Nodo *prev;
} Clase;


int main(){
    // pregunta 3
    x++;
    strcpy(x->inicio, "15:00");
    strcpy(x->fin, "17:00");
    x = lista_clases;

    for(int i = 0; i<5; i++){
        if(!strcmp(x->inicio, "8:00")){
            printf("Clase: %s", x->nombre);
            printf("inicio: %s", x->inicio);
            printf("fin: %s", x->fin);
        }
        x++;
    }

    // pregunta 5, x es el aux
    while(x && x->num != 9){
        x=x->next;
    }

    x->prev->next = x->next;
    if(x->next){
        x->next->prev = x->prev;
    }

    free(x);
    
    aux = inicio;

    while(aux->sig != x){
        // ya estamos untes de X
        aux = aux->sig;
    }

    // insertar nuevo
    Nodo nuevo = malloc(sizeof(Nodo));
    
    nuevo->sig = x;
    aux->sig = nuevo;

    // pregunta 7
    // imprime desde el 50 hasta el 0 de 10 en 10
    


    return 0;
}