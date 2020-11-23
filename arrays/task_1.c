// output of square matrix
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
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            matrix[i][j] = i * N + j + 1;
            printf("%3d ", matrix[i][j]);
        }
        printf("\n");
    }
}