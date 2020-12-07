/*  1. print all bytes
    2. change third byte  */

#include <stdio.h>

int main() {
    unsigned int x = 0xA1B2C3D4;
    printf("Original number: %X\n\n", x);

    unsigned char* ptr = (unsigned char*)&x;
    for (int i = 0; i < 4; i++) {
        printf("%d byte: %X\n", i + 1, *(ptr + i));
    } 

    unsigned int new_byte;
    printf("\nEnter new 3 byte: ");
    scanf("%X", &new_byte);
    if (new_byte < 0 || new_byte > 0xFF) {
        printf("\nError! Allowable interval [0; 0xFF].\n");
        return 1;
    }
    ptr += 2;
    *ptr = new_byte;
    printf("\nNew number: %X\n", x);

    return 0;
}