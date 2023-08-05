#include <stdio.h>
#include <stdlib.h>
#define ROW 25
#define COL 80
#define CELL '\xF0\x9F\x8F\xBE'

void get_dynamic_matrix(char ***matrix, int row, int col, int *no_err, int *is_alloc);
void free_dynamic_matrix(char **matrix, int *is_alloc);
void input(char **matrix, int row, int col, int *no_err);
void render_screen(char **matrix, int row, int col, int *no_err);

int main() {
    int no_err = 1;
    int is_alloc = 0;
    char **matrix;
    int row = ROW, col = COL;

    get_dynamic_matrix(&matrix, row, col, &no_err, &is_alloc);
    input(matrix, row, col, &no_err);
    if (no_err) {
        render_screen(matrix, row, col, &no_err);
    } else {
        printf("Данные хуйня. Поешь говна");
    }
    free_dynamic_matrix(matrix, &is_alloc);
    return 0;
}


void get_dynamic_matrix(char ***matrix, int row, int col, int *const no_err, int *is_alloc) {
    if (*no_err) {
        *matrix = malloc(row * col * sizeof(char) + row * sizeof(char *));
        char *ptr = (char *)(*matrix + row);

        for (int i = 0; i < row; i++) {
            (*matrix)[i] = ptr + col * i;
        }
        *is_alloc = 1;
    }
}

void free_dynamic_matrix(char **matrix, int *is_alloc) {
    if (*is_alloc) {
        free(matrix);
        *is_alloc = 0;
    }
}

void input(char **matrix, int row, int col, int *no_err) {
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
                        matrix[i][j] = (ch == '1' ? ch : ' ');
                    }
                }
            }
        }
    }
}

void render_screen(char **matrix, int row, int col, int *no_err) {
  int x, y;
  for (y = 0; y < row; y++) {
    for (x = 0; x < col; x++) {
        if (matrix[y][x] == '1') {
            printf("\xF0\x9F\x8D\x86");
        } else {
            printf("%c", matrix[y][x]);
        }
    }
    printf("\n");
  }
}
