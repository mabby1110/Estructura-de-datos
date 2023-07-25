#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int opciones();

int main(){
    int matriz[5][5] = {
       {0,  4,  1, -1, -1},
       {3,  0, -1,  2, -1},
       {1,  2,  0,  1,  1},
       {2, -1, -1,  0,  3},
       {4, -1,  3,  1,  0}
    };

    int run = 1;
    int origen, destino;


    while(run){
        system("clear");

        printf("origen: ");
        origen = opciones() - 1;

        switch(origen){
            case -1: 
                exit(0);
                break;
            default:
                printf("destino: ");
                destino = opciones() - 1;

                if(matriz[origen][destino]>0){
                    printf("hay conexion de %i\n\n", matriz[origen][destino]);
                    sleep("1");
                }
                break;
        }
    }
}

int opciones(){
    int  temp = 0;

    printf("\n\n1. moscou\n");
    printf("2. venecia\n");
    printf("3. atenas\n");
    printf("4. sidney\n");
    printf("5. gdl\n\n");
    printf("0. salir\n\n");

    scanf("%i", &temp);
    system("clear");

    return temp;
}

