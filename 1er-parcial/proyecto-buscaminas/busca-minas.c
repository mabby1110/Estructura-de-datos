#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define GRID_SIZE 15
#define NUM_MINES 10
#define WIN_CONDITION (GRID_SIZE*GRID_SIZE)-NUM_MINES

typedef struct {
    bool mine;
    bool revealed;
} Cell;

typedef struct {
    char tag[10];
    int maxScore;
    int levelScore;
    int level;
} Game;

void generateMines(Cell grid[GRID_SIZE][GRID_SIZE]) {
    int count = 0;
    while (count < NUM_MINES) {
        int x = rand() % GRID_SIZE;
        int y = rand() % GRID_SIZE;
        if (!grid[x][y].mine) {
            grid[x][y].mine = true;
            count++;
        }
    }
}

int countAdjacentMines(Cell grid[GRID_SIZE][GRID_SIZE], int x, int y) {
    int count = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            int nx = x + i;
            int ny = y + j;
            if (nx >= 0 && nx < GRID_SIZE && ny >= 0 && ny < GRID_SIZE && grid[nx][ny].mine) {
                count++;
            }
        }
    }
    return count;
}

void revealCell(Cell grid[GRID_SIZE][GRID_SIZE], int x, int y) {
    if (x < 0 || x >= GRID_SIZE || y < 0 || y >= GRID_SIZE || grid[x][y].revealed) {
        return;
    }
    
    grid[x][y].revealed = true;
    
    if (grid[x][y].mine) {
        // Mostrar el mensaje de juego perdido
        mvprintw(GRID_SIZE + 2, 0, "¡Has perdido! Presiona cualquier tecla para salir...");
        refresh();
        getch();
        endwin();
        exit(0);
    }
    
    int adjacentMines = countAdjacentMines(grid, x, y);
    
    if (adjacentMines > 0) {
        mvprintw(y, x, "%d", adjacentMines);
    } else {
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                int nx = x + i;
                int ny = y + j;
                if (nx >= 0 && nx < GRID_SIZE && ny >= 0 && ny < GRID_SIZE) {
                    revealCell(grid, nx, ny);
                }
            }
        }
    }
}

void drawGrid(Cell grid[GRID_SIZE][GRID_SIZE], Game *player) {
    clear();
    player->levelScore = 0;
    
    for (int y = 0; y < GRID_SIZE; y++) {
        for (int x = 0; x < GRID_SIZE; x++) {
            if (grid[x][y].revealed) {
                if (grid[x][y].mine) {
                    mvprintw(y+2, x, "*");
                } else {
                    int adjacentMines = countAdjacentMines(grid, x, y);
                    if (adjacentMines > 0) {
                        mvprintw(y+2, x, "%d", adjacentMines);
                    } else {
                        mvprintw(y+2, x, " ");
                    }
                    
                    player->levelScore ++;
                }
            } else {
                mvprintw(y+2, x, ".");
            }
        }
    }
    refresh();
}

void saveScore(Game jugador, int archivo) {
    char buffer[50];
    int bytesEscritos;
    sprintf(buffer, "%s %d\n", jugador.tag, jugador.maxScore);
    bytesEscritos = write(archivo, buffer, strlen(buffer));
    if (bytesEscritos == -1) {
        printf("Error al escribir en el archivo.\n");
        exit(1);
    }
}

void sortScore(Game *jugadores, int maxHighscores) {
    int i, j;
    Game temp;
    for (i = 0; i < maxHighscores - 1; i++) {
        for (j = 0; j < maxHighscores - i - 1; j++) {
            if (jugadores[j].maxScore < jugadores[j + 1].maxScore) {
                temp = jugadores[j];
                jugadores[j] = jugadores[j + 1];
                jugadores[j + 1] = temp;
            }
        }
    }
}

void readHighscores(int archivo) {
    char buffer[50];
    int bytesLeidos;
    while ((bytesLeidos = read(archivo, buffer, sizeof(buffer))) > 0) {
        mvprintw(6, 0, "%.*s", bytesLeidos, buffer);
    }
    if (bytesLeidos == -1) {
        printf("Error al leer el archivo.\n");
        exit(1);
    }
}

void updateHighscores(Game jugador, Game *jugadores, int *maxHighscores) {
    // Si la lista está llena y el jugador no supera el puntaje máximo
    if (*maxHighscores >= 3 && jugador.maxScore <= jugadores[2].maxScore) {
        return;
    }

    // Si el jugador supera el puntaje máximo y la lista no está llena
    if (*maxHighscores < 3) {
        jugadores[*maxHighscores] = jugador;
        (*maxHighscores)++;
        sortScore(jugadores, *maxHighscores);
    } else { // Si el jugador supera el puntaje máximo y la lista está llena
        jugadores[2] = jugador;
        sortScore(jugadores, *maxHighscores);
    }
}

int main() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    // menu
    mvprintw(0, 0, "Buscaminas");
    mvprintw(2, 0, "puntaje mas alto");
        // aqui voy a abrir el archivo con los puntajes
    mvprintw(4, 0, "presiona culquier tecla para empezar");

    Game player[3] = {{"mabby", 0, 0, 0},{"ybbam", 0, 0, 0}};
    int archivo;
    int maxHighscores = 0;

    archivo = open("jugadores.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (archivo == -1) {
        printf("Error al abrir el archivo.\n");
        exit(1);
    }
    
    updateHighscores(player[0], player, &maxHighscores);
    updateHighscores(player[1], player, &maxHighscores);
    for (int i = 0; i < maxHighscores; i++) {
        saveScore(player[i], archivo);
    }
    close(archivo);

    archivo = open("jugadores.txt", O_RDONLY);
    if (archivo == -1) {
        printf("Error al abrir el archivo.\n");
        exit(1);
    }

    readHighscores(archivo);

    close(archivo);

    getch();
    do {
        Cell grid[GRID_SIZE][GRID_SIZE] = {0};

        generateMines(grid);

        int x = 0;
        int y = 2;

        while (1) {
            drawGrid(grid, &player[0]);

            if(player[0].levelScore == WIN_CONDITION){
                player[0].level ++;
                player[0].maxScore = player[0].maxScore + player[0].levelScore;
                mvprintw(0, 0, "NIVEL COMPLETADO ...");
                refresh();
                sleep(2);
                break;
            } else{
                mvprintw(0, 0, "Puntos: %d\tnivel: %d", player[0].maxScore + player[0].levelScore, player[0].level+1);
                mvprintw(GRID_SIZE + 3, 0, "Utiliza las teclas de dirección para moverte y la barra espaciadora para revelar una casilla.");
                mvprintw(y, x, "");
            }
            refresh();
            
            int ch = getch();
            
            if (ch == KEY_UP && y > 2) {
                y--;
            } else if (ch == KEY_DOWN && y < GRID_SIZE + 1) {
                y++;
            } else if (ch == KEY_LEFT && x > 0) {
                x--;
            } else if (ch == KEY_RIGHT && x < GRID_SIZE - 1) {
                x++;
            } else if (ch == ' ') {
                revealCell(grid, x, y-2);
            }
        }
    } while(1);
    
    endwin();
    return 0;
}
