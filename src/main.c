#include <stdio.h>
#include <stdlib.h>
#define ROW 80
#define COL 25

void scanf_int(int *input, int *no_err);
void get_dynamic_matrix(int ***matrix, int row, int col, int *no_err, int *is_alloc);
void free_dynamic_matrix(int **matrix, int *is_alloc);
void input(int **matrix, int row, int col, int *no_err);

int main() {
    int no_err = 1;
    int is_alloc = 0;
    int **matrix;
    int row = ROW, col = COL;

    get_dynamic_matrix(&matrix, row, col, &no_err, &is_alloc);
    input(matrix, row, col, &no_err);



    free_dynamic_matrix(matrix, &is_alloc);

    return 0;
}

void scanf_int(int *input, int *no_err) {
    if (*no_err) {
        char temp = '\0';

        if (scanf("%d%c", input, &temp) < 1) {
            *no_err = 0;
        }

        if (temp != '\0' && temp != '\n' && temp != ' ') {
            *no_err = 0;
        }
    }
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
        for (int i = 0; i < row && (*no_err); i++) {
            for (int j = 0; j < col && (*no_err); j++) {
                scanf_int(&matrix[i][j], no_err);
            }
        }
    }
}

// void render_screen(int **matrix, int row, int col, int *no_err) {
//   int x, y;
//   for (y = 0; y <= FIELD_VER; y++) {
//     for (x = 0; x <= FIELD_HOR; x++) {
//         if (matrix[x][y] == 1) {
//             printf("o");
//         } else if (matrix[x][y] == 0) {
//             printf(" ");
//         }
//       }
//     }
//     printf("\n");
//   }
// }
//
