/* 0 0 1
   0 1 1
   1 1 1 */

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
            if (i + j >= N - 1) {
                matrix[i][j] = 1;
            } else {
                matrix[i][j] = 0;
            }
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}