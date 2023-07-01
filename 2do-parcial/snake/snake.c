#include "util.h"
#include <unistd.h>
#include <time.h>
#include <ncurses.h>

#define WIDTH 40
#define HEIGHT 40

#define CABEZA  1
#define CUERPO  2
#define MANZANA 3

#define DERECHA     1
#define ARRIBA      2
#define IZQUIERDA   3
#define ABAJO       4

typedef struct {
    int x, y, tipo;
} Nodo;

typedef struct Culebra{
    Nodo nodo;
    int dir;
    struct Culebra *ant, *sig;
} Culebra;

void setup(Culebra *culebra, Nodo *fruta);
void draw(Culebra *culebra, Nodo *fruta);
void grow(Culebra *culebra, Nodo *fruta);

int main(){
    Culebra culebra;
    Nodo fruta;

    setup(&culebra, &fruta);
    grow(&culebra, &fruta);
    grow(&culebra, &fruta);
    grow(&culebra, &fruta);

    while(1){
        while(!kbhit()){
            draw(&culebra, &fruta);
            switch(culebra.dir){
                case DERECHA:
                    culebra.nodo.x++;
                    break;
                case ARRIBA:
                    culebra.nodo.y--;
                    break; 
                case IZQUIERDA:
                    culebra.nodo.x--;
                    break;
                case ABAJO:
                    culebra.nodo.y++;
                    break;
            }
            usleep(100000);
        }
        
        // cambio de direccion
        char tecla = getch();
        mvprintw(HEIGHT + 4, 2, "direccion: %c", tecla);
        switch(tecla){
            case 'd':
                culebra.dir = DERECHA;
                break;
            case 'w':
                culebra.dir = ARRIBA;
                break; 
            case 'a':
                culebra.dir = IZQUIERDA;
                break;
            case 's':
                culebra.dir = ABAJO;
                break;
            default:
                continue;
        }
    }

    return 0;
}

void setup(Culebra *culebra, Nodo *fruta){
    initscr();
    noecho();
    curs_set(0);

    srand(time(NULL));

    culebra->nodo.x = WIDTH / 2;
    culebra->nodo.y = HEIGHT / 2;
    culebra->nodo.tipo = CABEZA;
    culebra->dir = DERECHA;
    culebra->sig = NULL;
    culebra->ant = NULL;

    fruta->x = rand() % WIDTH;
    fruta->y = rand() % HEIGHT;
    fruta->tipo = MANZANA;
}

void draw(Culebra *culebra, Nodo *fruta){
    Culebra *aux = malloc(sizeof(struct Culebra));
    aux = culebra;
    clear();

    // bordes
    for (int i = 0; i < WIDTH + 2; i++)
        mvprintw(0, i, "-");
    for (int i = 0; i < HEIGHT + 2; i++)
        mvprintw(i, 0, "|");
    for (int i = 0; i < HEIGHT + 2; i++)
        mvprintw(i, WIDTH + 1, "|");
    for (int i = 0; i < WIDTH + 2; i++)
        mvprintw(HEIGHT + 1, i, "-");

    // fruta
    mvprintw(fruta->y, fruta->x, "*");

    // culebra
    while(aux){
        mvprintw(aux->nodo.y, aux->nodo.x, "@");
        aux = aux->ant;
    }

    mvprintw(HEIGHT + 3, 2, "direccion: %d", culebra->dir);

    refresh();
}

void grow(Culebra *culebra, Nodo *fruta){
    Culebra *nuevo = malloc(sizeof(struct Culebra));
    fruta->tipo = CUERPO;
    nuevo->nodo = *fruta;
    nuevo->ant = NULL;

    while(culebra->ant)
        culebra = culebra->ant;
    
    nuevo->sig = culebra;
    culebra->ant = nuevo;
}