#include <stdio.h>
#include <stdlib.h>

struct Student {
    int roll_no;
    char name[20];
    float marks;
};

void read(struct Student *p, int n) {
    for (int i = 0; i < n; i++) {
        printf("Enter roll, name, marks: ");
        scanf("%d %19s %f", &(p+i)->roll_no,
              (p+i)->name, &(p+i)->marks);
    }
}

float average(struct Student *p, int n) {
    float sum = 0;
    for (int i = 0; i < n; i++)
        sum += (p+i)->marks;
    return sum / n;
}

void topper(struct Student *p, int n) {
    int max = 0;
    for (int i = 1; i < n; i++)
        if ((p+i)->marks > (p+max)->marks)
            max = i;
    printf("Topper: %s (Roll %d, Marks %.2f)\n",
           (p+max)->name, (p+max)->roll_no,
           (p+max)->marks);
}

int main() {
    int n;
    char choice;
    struct Student *p, *temp;

    printf("Enter number of students: ");
    scanf("%d", &n);
    if (n <= 0) return 1;

    p = malloc(n * sizeof(struct Student));
    if (p == NULL) return 1;

    read(p, n);
    printf("\nAverage marks: %.2f\n", average(p, n));
    topper(p, n);

    printf("\nAdd 2 more students? (y/n): ");
    scanf(" %c", &choice);

    if (choice == 'y' || choice == 'Y') {
        temp = realloc(p, (n+2) * sizeof(struct Student));
        if (temp == NULL) {
            free(p);
            return 1;
        }
        p = temp;
        read(p+n, 2);
        n += 2;
        printf("Updated average marks: %.2f\n", average(p, n));
    }

    free(p);
    return 0;
}
