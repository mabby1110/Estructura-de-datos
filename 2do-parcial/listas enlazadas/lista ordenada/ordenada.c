// ya que el tipo de dato son numeros enteros
// se hara la busqueda de los elementos acorde

#include <stdio.h>
#include <stdlib.h>

typedef struct Nodo {
    int dato;
    struct Nodo *sig, *ant;
} Nodo;

void append(int dato, Nodo **lista);
void printList(Nodo *lista);
void popFirst(Nodo **lista);
void popLast(Nodo *lista);
void insertOrdered(int dato, Nodo **lista);
void deleteByValue(int dato, Nodo **lista);

int main() {
    Nodo *lista = malloc(sizeof(Nodo));

    insertOrdered(4, &lista);
    insertOrdered(5, &lista);
    insertOrdered(10, &lista);
    insertOrdered(11, &lista);
    insertOrdered(2, &lista);
    insertOrdered(8, &lista);

    deleteByValue(10, &lista);
    deleteByValue(11, &lista);
    deleteByValue(8, &lista);
    

    insertOrdered(3, &lista);

    // debe imprimir una lista ordenada del 3 al 5
    printList(lista);
    return 0;
}

void append(int dato, Nodo **lista) {
    if (!(*lista)->dato) {
        (*lista)->dato = dato;
    } else {
        Nodo *aux = *lista;
        Nodo *nuevo = malloc(sizeof(Nodo));

        while (aux->sig) {
            aux = aux->sig;
        }

        nuevo->dato = dato;
        nuevo->ant = aux;
        aux->sig = nuevo;
    }
}

void printList(Nodo *lista) {
    Nodo *aux = lista;

    while (aux) {
        printf("nodo: %p\n", aux);
        printf("dato: %d\n", aux->dato);
        printf("siguiente: %p\n", aux->sig);
        printf("anterior: %p\n\n", aux->ant);
        aux = aux->sig;
    }
}

void popLast(Nodo *lista) {
    Nodo *aux = lista;

    while (aux->sig->sig) {
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
    if (*lista != NULL) {
        (*lista)->ant = NULL;
    }
    free(aux);
}

void insertOrdered(int dato, Nodo **lista) {
    if(!(*lista)->dato){
        (*lista)->dato = dato;
    } else {
        Nodo *nuevo = malloc(sizeof(Nodo));
        Nodo *aux = *lista;
        nuevo->dato = dato;

        if(aux->dato > dato){
            nuevo->sig = *lista;
            (*lista)->ant = nuevo;
            *lista = nuevo;
        } else{
            while (aux->sig && dato > aux->sig->dato) {
                aux = aux->sig;
            }

            nuevo->sig = aux->sig;
            if (aux->sig != NULL) {
                aux->sig->ant = nuevo;
            }
            aux->sig = nuevo;
            nuevo->ant = aux;
        }
    }
}

void deleteByValue(int dato, Nodo **lista) {
    if (*lista == NULL) {
        return; // La lista está vacía, no hay elementos para eliminar.
    }

    Nodo *aux = *lista;

    while (aux && aux->dato != dato) {
        aux = aux->sig;
    }

    if (aux == NULL) {
        return; // No se encontró el elemento en la lista.
    }

    if (aux->ant == NULL) {
        *lista = aux->sig;
        if (*lista != NULL) {
            (*lista)->ant = NULL;
        }
    } else {
        aux->ant->sig = aux->sig;
        if (aux->sig != NULL) {
            aux->sig->ant = aux->ant;
        }
    }

    free(aux);
}
