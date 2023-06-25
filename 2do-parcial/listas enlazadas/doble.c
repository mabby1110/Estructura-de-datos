#include <stdio.h>

typedef struct {
    int num;
    struct Lista *sig;
    struct Lista *ant;
} Lista;

void ver(Lista *lista){
    printf("num: %d\n", lista->num);
    printf("anterior: %p\n", lista->sig);
    printf("sig: %p", lista->sig);
}

void nuevo(){
    
}

int main(){
    Lista lista = {0, NULL, NULL};
    ver(&lista);

    return 0;
}