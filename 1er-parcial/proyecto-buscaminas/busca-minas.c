#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 10
#define MINAS 5

void ver(char grid[SIZE+2][SIZE+2]){
    for(int j = 0; j<SIZE+2; j++){
        for(int i = 0; i<SIZE+2; i++){
            if(grid[j][i] == '\0'){
                printf(".");
            } else{
                printf("%c  ", grid[j][i]);
            }
        }
        printf("\n");
    }
}

void seleccionar(int *x, int *y){
    printf("x: ");
    scanf("%d", x);

    printf("y: ");
    scanf("%d", y);
}

int checar(char grid[SIZE+2][SIZE+2], int x, int y){
    // if(grid[y][x] == "x"){
    //     return -1;
    // } else {
    for(int j=3; j>0; j--){
        for(int i=3; i>0; i--){
            printf("y: %d\t", y+2-j);
            printf("x: %d\n", x+2-i);
        }
    }

    // }

    return 0;
}

int main(){
    int coor_x, coor_y;

    // inicializar arreglo vacio
    char grid[SIZE+2][SIZE+2] = {
        {""}
    };

    for(int i = 0; i<MINAS; i++){
        int x = rand() % SIZE+1;
        int y = rand() % SIZE+1;

        grid[y][x] = 'x';
    }
    
    // printf mapa
    ver(grid);

    // seleccionar casilla
    seleccionar(&coor_x, &coor_y);

    // checar al rededor
    checar(grid, coor_x, coor_y);

    return 0;
}