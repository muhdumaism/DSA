#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char name[20];
    int emp_id;
    enum { FULL_TIME, CONTRACT } type;
    union {
        float salary;
        struct { float hourly_rate; int hours_worked; } contract_info;
    } pay;
} Employee;

int main() {
    int n, i, t;
    float pay, bill = 0;
    Employee *e;

    printf("Enter number of employees: ");
    scanf("%d", &n);

    e = malloc(n * sizeof(Employee));
    if (e == NULL) return 1;

    for (i = 0; i < n; i++) {
        printf("\nEnter name and emp id: ");
        scanf("%19s %d", e[i].name, &e[i].emp_id);
        printf("Enter type (0 = Full-time, 1 = Contract): ");
        scanf("%d", &t);

        if (t == 0) {
            e[i].type = FULL_TIME;
            printf("Enter monthly salary: ");
            scanf("%f", &e[i].pay.salary);
        } else {
            e[i].type = CONTRACT;
            printf("Enter hourly rate and hours worked: ");
            scanf("%f %d", &e[i].pay.contract_info.hourly_rate,
                  &e[i].pay.contract_info.hours_worked);
        }
    }

    printf("\n----- PAYSLIPS -----\n");
    for (i = 0; i < n; i++) {
        printf("\nName: %s\n", e[i].name);
        printf("Emp ID: %d\n", e[i].emp_id);

        if (e[i].type == FULL_TIME) {
            printf("Type: Full-time\n");
            pay = e[i].pay.salary;
        } else {
            printf("Type: Contract\n");
            pay = e[i].pay.contract_info.hourly_rate *
                  e[i].pay.contract_info.hours_worked;
        }

        printf("Total pay: %.2f\n", pay);
        bill = bill + pay;
    }

    printf("\nTotal salary bill: %.2f\n", bill);

    free(e);
    return 0;
}
