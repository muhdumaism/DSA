#include <stdio.h>

typedef struct {
    int degree;
    float coef[101];   /* coef[i] = coefficient of x^(degree-i) */
} polynomial;

polynomial read_poly() {
    polynomial p;
    int i;
    printf("Enter degree: ");
    scanf("%d", &p.degree);
    printf("Enter %d coefficients (highest power first): ", p.degree + 1);
    for (i = 0; i <= p.degree; i++)
        scanf("%f", &p.coef[i]);
    return p;
}

polynomial add(polynomial a, polynomial b) {
    polynomial c;
    int i;

    if (a.degree > b.degree)
        c.degree = a.degree;
    else
        c.degree = b.degree;

    for (i = 0; i <= c.degree; i++)
        c.coef[i] = 0;

    /* shift each polynomial so that same powers come in same place */
    for (i = 0; i <= a.degree; i++)
        c.coef[c.degree - a.degree + i] += a.coef[i];
    for (i = 0; i <= b.degree; i++)
        c.coef[c.degree - b.degree + i] += b.coef[i];

    return c;
}

void display(polynomial p) {
    int i, power, first = 1;
    float c;

    for (i = 0; i <= p.degree; i++) {
        c = p.coef[i];
        power = p.degree - i;

        if (c == 0)
            continue;

        if (first == 0) {
            if (c < 0) {
                printf(" - ");
                c = -c;
            } else {
                printf(" + ");
            }
        }

        if (power == 0)
            printf("%g", c);
        else
            printf("%gx^%d", c, power);

        first = 0;
    }
    if (first == 1)
        printf("0");
    printf("\n");
}

int main() {
    polynomial a, b, c;

    printf("Polynomial A\n");
    a = read_poly();
    printf("Polynomial B\n");
    b = read_poly();

    c = add(a, b);

    printf("\nA(x) = ");
    display(a);
    printf("B(x) = ");
    display(b);
    printf("Sum  = ");
    display(c);

    return 0;
}
