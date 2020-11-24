// fill the matrix (snake)
#include <stdio.h>

int main() {
    int N;
    printf("Enter size: ");
    scanf("%d", &N);
    if (N <= 0) {
        printf("Size must be positive.\n");
        return 1;
    }

    int matrix[N][N];
    int max = N - 1;
    int min = 0;
    int el_amount = N - 1;
    int value = 0;

    if (N % 2 == 1) {
        matrix[N / 2][N / 2] = N * N;
    }

    for (int k = 0; k < N / 2; k++) {
        for (int i = 0; i < el_amount; i++) {
            matrix[min][min + i] = ++value;
            matrix[min + i][max] = value + el_amount;
            matrix[max][max - i] = value + el_amount * 2;
            matrix[max - i][min] = value + el_amount * 3;
        }
        value += 3 * el_amount;
        max--; 
        min++;
        el_amount -= 2;
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%4d", matrix[i][j]);
        }
        printf("\n");
    }   
}