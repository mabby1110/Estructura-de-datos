#include <stdio.h>
#include <string.h>

#define MAX_SIZE 5

typedef struct Contacto {
    char apodo[15];
    char nombre[50];
    char tel[10];
    char correo[30];
} Contacto;

typedef struct Lista{
    Contacto contactos[MAX_SIZE];
    int top;
} Lista;

void ver(Lista lista){
    // imprime todos los contactos de la lista
    for(int i=0; i<lista.top; i++){
        printf("\n\napodo: %s", lista.contactos[i].apodo);
        printf("\nnombre: %s", lista.contactos[i].nombre);
        printf("\ntel: %s", lista.contactos[i].tel);
        printf("\ncorreo: %s", lista.contactos[i].correo);
    }
}

void agregar(Lista *lista){
    char apodo[15], nombre[50], tel[10], correo[30];
    // agregue este gets para evitar que el scanf del menu lo salte
    gets(apodo);

    printf("\napodo:");
    gets(apodo);
    strcpy(lista->contactos[lista->top].apodo, apodo);

    printf("\nnombre:");
    gets(nombre);
    strcpy(lista->contactos[lista->top].nombre, nombre);
    
    printf("\ntelefono:");
    gets(tel);
    strcpy(lista->contactos[lista->top].tel, tel);

    printf("\ncorreo:");
    gets(correo);
    strcpy(lista->contactos[lista->top].correo, correo);

    lista->top++;
    printf("\n-------------\n");
}

int main(){
    Lista lista_amigos = {{"jp", "Juan Pablo mejia", "2354678912", "jp@gmail.com"}, 1};
    char opc;

    while(1){
        printf("Tus contactos");
        ver(lista_amigos);
        printf("\n\npresiona...\n[a] gregar contacto\n[s] alir\n");
        scanf("%c", &opc);
        fflush(stdin);

        switch(opc){
            case 'a':
                agregar(&lista_amigos);
                break;
            case 's':
                return 0;
            default:
                printf("selecciona una opcion disponible");
        }
        system("clear");
    }

    return 0;
}