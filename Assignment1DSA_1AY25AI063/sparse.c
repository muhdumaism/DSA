/* Input format: first enter rows and cols,
   then enter the full matrix row by row (including zeros) */

#include <stdio.h>
#define MAX 101

typedef struct {
    int row, col, value;
} term;

void display(term a[]) {
    int i;
    printf("Row\tCol\tValue\n");
    for (i = 0; i <= a[0].value; i++)
        printf("%d\t%d\t%d\n", a[i].row, a[i].col, a[i].value);
}

void fast_transpose(term a[], term b[]) {
    int row_terms[MAX], starting_pos[MAX];
    int i, j;
    int num_cols = a[0].col, num_terms = a[0].value;

    b[0].row = num_cols;
    b[0].col = a[0].row;
    b[0].value = num_terms;

    if (num_terms > 0) {
        for (i = 0; i < num_cols; i++)
            row_terms[i] = 0;
        for (i = 1; i <= num_terms; i++)
            row_terms[a[i].col]++;

        starting_pos[0] = 1;
        for (i = 1; i < num_cols; i++)
            starting_pos[i] = starting_pos[i - 1] + row_terms[i - 1];

        printf("\nrow_terms[]    : ");
        for (i = 0; i < num_cols; i++)
            printf("%d ", row_terms[i]);
        printf("\nstarting_pos[] : ");
        for (i = 0; i < num_cols; i++)
            printf("%d ", starting_pos[i]);
        printf("\n");

        for (i = 1; i <= num_terms; i++) {
            j = starting_pos[a[i].col]++;
            b[j].row = a[i].col;
            b[j].col = a[i].row;
            b[j].value = a[i].value;
        }
    }
}

int main() {
    term a[MAX], b[MAX];
    int rows, cols, i, j, x, k = 1, ok = 1;

    printf("Enter rows and cols: ");
    scanf("%d %d", &rows, &cols);
    printf("Enter the matrix:\n");
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            scanf("%d", &x);
            if (x != 0) {
                a[k].row = i;
                a[k].col = j;
                a[k].value = x;
                k++;
            }
        }
    }
    a[0].row = rows;
    a[0].col = cols;
    a[0].value = k - 1;

    printf("\nOriginal triples:\n");
    display(a);

    fast_transpose(a, b);

    printf("\nTransposed triples:\n");
    display(b);

    /* check if b is in row-major order */
    for (i = 2; i <= b[0].value; i++) {
        if (b[i].row < b[i - 1].row ||
            (b[i].row == b[i - 1].row && b[i].col < b[i - 1].col))
            ok = 0;
    }
    if (ok == 1)
        printf("\nThe transposed triples are in row-major order.\n");
    else
        printf("\nThe transposed triples are NOT in row-major order.\n");

    return 0;
}
