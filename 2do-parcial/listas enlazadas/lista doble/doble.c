#include <stdio.h>
#include <stdlib.h>

typedef struct Nodo {
    int dato;
    struct Nodo *sig, *ant;
} Nodo;

void append(int dato, Nodo *lista);
void printList(Nodo *lista);

// cola
void popFirst(Nodo **lista);

// pila
void popLast(Nodo *lista);

int main(){
    Nodo *lista = malloc(sizeof(Nodo));

    append(5, lista);
    append(6, lista);
    append(7, lista);
    append(8, lista);
    append(9, lista);

    popFirst(&lista);

    popLast(lista);

    // debe imprimir solo el 6, 7 & 8
    printList(lista);
    return 0;
}

void append(int dato, Nodo *lista){
    if(!lista->dato){
        lista->dato = dato;
    } else {
        Nodo *aux = lista;
        Nodo *nuevo = malloc(sizeof(Nodo));

        while(aux->sig){
            aux = aux->sig;
        }

        nuevo->dato = dato;
        nuevo->ant = aux;
        aux->sig = nuevo;
    }
}

void printList(Nodo *lista){
    Nodo *aux = lista;

    while(aux){
        printf("nodo: %p\n", aux);
        printf("dato: %d\n", aux->dato);
        printf("siguiente: %p\n", aux->sig);
        printf("anterior: %p\n\n", aux->ant);
        aux = aux->sig;
    }
}

void popLast(Nodo *lista){
    Nodo *aux = lista;

    while(aux->sig->sig){
        aux = aux->sig;
    }
    
    free(aux->sig);
    aux->sig = NULL;

}

void popFirst(Nodo **lista) {
    if (*lista == NULL) {
        return; // La lista está vacía, no hay elementos para eliminar.
    }

    Nodo *aux = *lista;
    *lista = (*lista)->sig;
    (*lista)->ant = NULL;
    free(aux);
}