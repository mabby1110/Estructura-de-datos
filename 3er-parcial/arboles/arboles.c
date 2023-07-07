#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 8

struct AG{
    char nombre[20];
    struct AG *hijo[MAX];
};

void addNode(struct AG **nodo);
void readNode(struct AG *nodo);

int main(){
    struct AG *raiz;

    addNode(&raiz);

    addNode(&raiz);
    strcpy(raiz->nombre, "María");

    addNode(&raiz->hijo[0]);
    strcpy(raiz->hijo[0]->nombre, "Bernardo");

    addNode(&raiz->hijo[1]);
    strcpy(raiz->hijo[1]->nombre, "Mauricio");

    addNode(&raiz->hijo[2]);
    strcpy(raiz->hijo[2]->nombre, "Samuel");

    readNode(raiz);
    return 0;
}

void addNode(struct AG **nodo){
    *nodo = malloc(sizeof(struct AG));

    if (*nodo==NULL){
        perror("");
        exit(1);
    }

    for (int i=0;i<MAX;i++)
      (*nodo)->hijo[i]=NULL;
}

void readNode(struct AG *nodo){
    printf("nodo padre:\t%s\n\n", nodo->nombre);

    for (int i=0;i<MAX;i++){
        if(nodo->hijo[i]){
            printf("nodo hijo:\t%s\n", nodo->hijo[i]->nombre);
        }
    }
}