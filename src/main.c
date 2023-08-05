#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define ROW 25
#define COL 80
#define CELL "\xF0\x9F\xA6\xA0"
#define FIRST_SPEED 50000
#define SECOND_SPEED 100000
#define THIRD_SPEED 500000

void get_dynamic_matrix(int ***matrix, int row, int col, int *no_err, int *is_alloc);
void free_dynamic_matrix(int **matrix, int *is_alloc);
void input(int **matrix, int row, int col, int *no_err);
void render_screen(int **matrix, int row, int col, int *no_err);
void update(int **field, int **next);
int count_neighbors(int **field, int x, int y);

int main(int argc, char **argv) {
    int no_err = 1;
    int is_alloc = 0;
    int **matrix;
    int row = ROW, col = COL;

    get_dynamic_matrix(&matrix, row, col, &no_err, &is_alloc);
    input(matrix, row, col, &no_err);
    if (no_err || argc > 2) {
        int **next = malloc(row * col * sizeof(int) + row * sizeof(int *));
        int *ptr = (int *)(next + row);

        for (int i = 0; i < row; i++) {
            next[i] = ptr + col * i;
        }
        while (1) {
            int speed, correct_speed = 0;
            if (*argv[1] == '1') {
                speed = FIRST_SPEED;
                correct_speed = 1;
            }
            if (*argv[1] == '2') {
                speed = SECOND_SPEED;
                correct_speed = 1;
            }
            if (*argv[1] == '3') {
                speed = SECOND_SPEED;
                correct_speed = 1;
            }
            if (correct_speed == 1) {
                render_screen(matrix, row, col, &no_err);
                update(matrix, next);
                usleep(speed);
            } else {
                printf("Скорость хуйня, куда еще медленее? Иди нахуй.");
                return 0;
            }
        }
        free(next);
        
    } else {
        printf("Данные хуйня. Поешь говна.");
    }
    free_dynamic_matrix(matrix, &is_alloc);
    return 0;
}


void get_dynamic_matrix(int ***matrix, int row, int col, int *const no_err, int *is_alloc) {
    if (*no_err) {
        *matrix = malloc(row * col * sizeof(int) + row * sizeof(int *));
        int *ptr = (int *)(*matrix + row);

        for (int i = 0; i < row; i++) {
            (*matrix)[i] = ptr + col * i;
        }
        *is_alloc = 1;
    }
}

void free_dynamic_matrix(int **matrix, int *is_alloc) {
    if (*is_alloc) {
        free(matrix);
        *is_alloc = 0;
    }
}

void input(int **matrix, int row, int col, int *no_err) {
    if (*no_err) {
        char ch;
        for (int i = 0; i < row && (*no_err); i++) {
            for (int j = 0; j < col && (*no_err); j++) {
                scanf("%c", &ch);
                if (ch != '0' && ch != '1' && ch != '\n' && ch != '\0') {
                    *no_err = 0;
                }
                if (*no_err) {
                    if (ch == '1' || ch == '0') {
                        matrix[i][j] = (ch == '1' ? 1 : 0);
                    }
                }
            }
        }
    }
}

void render_screen(int **matrix, int row, int col, int *no_err) {
  int x, y;
  for (y = 0; y < row; y++) {
    for (x = 0; x < col; x++) {
        if (matrix[y][x] == 1) {
            printf(CELL);
        } else {
            printf(" ");
        }
    }
    printf("\n");
  }
}

int count_neighbors(int **field, int x, int y) {
    int neighbors = 0;
    int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    int dy[] = {-1, 0, 1, -1, 1, -1, 0, 1};
    for (int i = 0; i < 8; i++) {
        int new_x = (x + dx[i] + ROW) % ROW;
        int new_y = (y + dy[i] + COL) % COL;
        if (field[new_x][new_y] == 1){
            neighbors++;
        }

    }
    return neighbors;

}


void update(int **field, int **next) {
    for (int i = 0; i < ROW; i++) {

        for (int j = 0; j < COL; j++) {

            int neighbors = count_neighbors(field, i, j);
            if (field[i][j] == 1) {
                next[i][j] = (char)(neighbors == 2 || neighbors == 3);

            } else {
                next[i][j] = (char)(neighbors == 3);
            }

        }

    }

    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COL; j++) {
            field[i][j] = next[i][j];
        }
    }

}
