#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 10
#define MINAS 5


void inicializa(char grid[SIZE+2][SIZE+2]){
    for(int j = 0; j<SIZE+2; j++){
        for(int i = 0; i<SIZE+2; i++){
            grid[j][i] = '.'; 
        }
    }
}



void ver(char grid[SIZE+2][SIZE+2]){
    for(int j = 0; j<SIZE+2; j++){
        for(int i = 0; i<SIZE+2; i++){
            if(grid[j][i] >= 0 && grid[j][i] < 9){
                printf("%i", grid[j][i]);
            } else{
                printf("%c", grid[j][i]);
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

int checar(char grid[SIZE+2][SIZE+2],int x,int y){
    int contador = 0;
    if(grid[y][x] == 'x' ){
        printf("Perdiste\n");
        exit(0);
    }
    else{
        if(grid[y-1][x] == 'x')
            contador++;
        
        else if(grid[y-1][x+1] == 'x')
                contador++;
             else if(grid[y][x+1] == 'x')
                    contador++;
               else if(grid[y+1][x+1] == 'x')
                        contador++;
                   else if(grid[y+1][x] == 'x')
                            contador++;
                       else if(grid[y+1][x-1] == 'x')
                                contador++;
                           else if(grid[y][x-1] == 'x')
                                    contador++;
                                else if(grid[y-1][x-1] == 'x')
                                        contador++;
        //ASIGNACION
        grid[y][x] = contador; 
    }
    
    


    return 0;
}

int main(){
    int coor_x, coor_y;

    // inicializar arreglo vacio
    char grid[SIZE+2][SIZE+2];
    
    inicializa(grid); 
    for(int i = 0; i<MINAS; i++){
        int x = rand() % SIZE+1;
        int y = rand() % SIZE+1;

        grid[y][x] = 'x';
    }
    
    while(1){
        // printf mapa
        ver(grid);
    
        // seleccionar casilla
        seleccionar(&coor_x, &coor_y);
    
        // checar al rededor
        checar(grid, coor_x, coor_y);
    }
    return 0;
}