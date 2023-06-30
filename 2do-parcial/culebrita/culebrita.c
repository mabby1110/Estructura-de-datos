/******************************************************************************
culebrita
*******************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "conio4Linux.h"
#define ESC 27

struct Vibora{
  int x;
  int y;
  struct Vibora *sig,*ant;
};

void verVibora(struct Vibora *vibora){
    while(vibora){
        gotoxy(vibora->x, vibora->y);
        printf("@");
        vibora = vibora->ant;
    }
}

void actualizarVibora(struct Vibora *vibora){
    while(vibora->ant){
        vibora->ant->x = vibora->x;
        vibora->ant->y = vibora->y;
        vibora = vibora->ant;
    }
}

int main()
{
    struct Vibora *inicio,*nuevo, *aux;
    int dir=1; //derecha
    char tecla;
    inicio=malloc(sizeof(struct Vibora));

    srand(time(NULL));
    int x = rand() % 80 + 1, y = rand() % 40 + 1;

    inicio->x = rand() % 80 + 1;
    inicio->y = rand() % 40 + 1;
    inicio->sig = NULL;
    inicio->ant = NULL;

    clrscr();

   do{
        do{
            actualizarVibora(inicio);
            
            switch(dir)
            {
                case 1: 
                    if(inicio->x < 80){
                        inicio->x++;
                    } else{
                        inicio->x = 1;
                    }
                    break;
                case 2: 
                    if(inicio->y < 40){
                        inicio->y++;
                    } else{
                        inicio->y = 1;
                    }
                    break; 
                case 3:
                    if(inicio->x > 1){
                    inicio->x--; 
                    } else{
                        inicio->x = 80;
                    }
                        break; 
                case 4:
                    
                    if(inicio->y > 1){
                        inicio->y--;
                    } else{
                        inicio->y = 40;
                    }
                    break; 
            }
            clrscr();
            // manzana
            textcolor(RED);
            gotoxy(x, y);
            printf("m");

            // vibora
            textcolor(YELLOW);
            verVibora(inicio);

            // la vibora ha topado una manzana
            if((inicio->x == x)&&(inicio->y == y)){
                // se incrementa el tamanio de la culera
                nuevo = malloc(sizeof(struct Vibora));
                aux = malloc(sizeof(struct Vibora));

                aux = inicio;
                if(!aux->ant){
                    aux->ant = nuevo;
                } else {
                    while(aux->ant){
                        aux = aux->ant;
                    }
                }
                nuevo->sig = aux;
                nuevo->ant = NULL;
                
                // manzana nueva
                x = rand() % 80 + 1;
                y = rand() % 40 + 1;
            }
            system("sleep 0.3");
        // mientras no se presiones ninguna tecla, la culebra avanza en la direccion especificada
        } while(!kbhit());

        // cambio de direccion
        tecla=getch();
        switch(tecla){
            case 's':dir=2; break;
            case 'w': dir =4; break; 
            case 'a': dir =3; break;
            case 'd': dir=1;
        }
    } while(tecla!=ESC);
    return 0;
}
