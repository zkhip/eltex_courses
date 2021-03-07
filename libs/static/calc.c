#include <stdio.h>
#include <stdlib.h>
#include "calc.h"

int main() {
    char buff[10];
    int action, a, b, result;

    do {
        printf("\n1 - add\n");
        printf("2 - sub\n");
        printf("3 - mul\n");
        printf("4 - div\n");
        printf("5 - exit\n");

        fgets(buff, 10, stdin);
        action = atoi(buff);

        switch (action) {
            case 1: // add
                printf("Enter 2 arguments line by line:\n");
                fgets(buff, 10, stdin);
                a = atoi(buff);
                fgets(buff, 10, stdin);
                b = atoi(buff);
                result = add(a, b);
                printf("%d + %d = %d\n", a, b, result);
                break;
            case 2: // sub
                printf("Enter 2 arguments line by line:\n");
                fgets(buff, 10, stdin);
                a = atoi(buff);
                fgets(buff, 10, stdin);
                b = atoi(buff);
                result = sub(a, b);
                printf("%d - %d = %d\n", a, b, result);
                break;
            case 3: // mul
                printf("Enter 2 arguments line by line:\n");
                fgets(buff, 10, stdin);
                a = atoi(buff);
                fgets(buff, 10, stdin);
                b = atoi(buff);
                result = mul(a, b);
                printf("%d * %d = %d\n", a, b, result);
                break;
            case 4: // div
                printf("Enter 2 arguments line by line:\n");
                fgets(buff, 10, stdin);
                a = atoi(buff);
                fgets(buff, 10, stdin);
                b = atoi(buff);
                result = division(a, b);
                printf("%d / %d = %d\n", a, b, result);
                break;
        }
    } while (action != 5);

    return 0;
}