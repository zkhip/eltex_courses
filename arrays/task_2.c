// output reverse array
#include <stdio.h>

int main() {
    int N;
    printf("Enter size: ");
    scanf("%d", &N);
    int array[N];
    if (N <= 0) {
        printf("Size must be positive.\n");
        return 1;
    }
    printf("Enter array: ");
    for (int i = 0; i < N; i++) {
        scanf("%d", &array[i]);
    }
    printf("Result: ");
    for (int i = N - 1; i >= 0; i--) {
        printf("%d ", array[i]);
    }
    printf("\n");
}