/*  1. print all bytes
    2. change third byte  */

#include <stdio.h>

int main() {
    unsigned int x = 0x17AB18CD;
    printf("Original number: %X\n\n", x);

    int byte = 0;
    for (int i = 0; i < 4; i++) {
        byte = (x >> (8 * i)) & 0xFF;
        printf("%d byte: %X\n", i+1, byte);
    }

    unsigned int new_byte;
    printf("\nEnter new 3 byte: ");
    scanf("%X", &new_byte);
    if (new_byte < 0 || new_byte > 0xFF) {
        printf("\nError! Allowable interval [0; 0xFF].\n");
        return 1;
    }
    unsigned int new_x = (x & 0xFF00FFFF) | (new_byte << 16);
    printf("\nNew number: %X\n", new_x);

    return 0;
}