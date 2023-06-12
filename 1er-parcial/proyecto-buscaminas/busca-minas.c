#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <fcntl.h>
#include <unistd.h>

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

void save(Game *player){
    int file;
    file = open("highScores.txt",O_WRONLY | O_CREAT);
    if (file == -1){
        printf("no fue posible crear o modificar el archivo ...");
        exit(1);
    } else{
        write (file, player, sizeof(Game));
        close(file);
    }
}

void open(Game *player){
    int file;
    file = open("highScores.txt", O_RDONLY );
    if (file == -1){
        printf("no fue posible abrir el archivo o no existe ...");
        exit(1);
    } else{
        read (file, Datos, sizeof(struct ejemplo)*3);
        close(file);
    }
}

int main() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    mvprintw(0, 0, "Buscaminas");
    mvprintw(2, 0, "puntaje mas alto");
    // aqui voy a abrir el archivo con los puntajes
    mvprintw(4, 0, "presiona culquier tecla para empezar");
    getch();

    Game player = {"mabby", 0, 0, 0};
    save(&player);

    do {
        Cell grid[GRID_SIZE][GRID_SIZE] = {0};

        generateMines(grid);

        int x = 0;
        int y = 2;

        while (1) {
            drawGrid(grid, &player);

            if(player.levelScore == WIN_CONDITION){
                player.level ++;
                player.maxScore = player.maxScore + player.levelScore;
                mvprintw(0, 0, "NIVEL COMPLETADO ...");
                refresh();
                sleep(2);
                break;
            } else{
                mvprintw(0, 0, "Puntos: %d\tnivel: %d", player.maxScore + player.levelScore, player.level+1);
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
