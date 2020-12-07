#include <stdio.h>

int main() {
    char str[10] = {'A', 0, 0, 0, 0, 'B', 0, 0, 0, 0};

    struct test_packed {
        char a;
        int b;
    } __attribute__((packed));

    struct test_packed test_1;
    struct test_packed* ptr_1;
    ptr_1 = (struct test_packed*)str;
    printf("1. test_packed.a = %c\ttest_packed.b = %X\n", (*ptr_1).a, (*ptr_1).b);
    ptr_1++;
    printf("2. test_packed.a = %c\ttest_packed.b = %X\n", (*ptr_1).a, (*ptr_1).b);

    struct test {
        char a;
        int b;
    };

    struct test test_2;
    struct test* ptr_2;
    
    ptr_2 = (struct test*)str;
    printf("\n1. test.a = %c\ttest.b = %X\n", (*ptr_2).a, (*ptr_2).b);

    ptr_2++;
    printf("2. test.a = %c\ttest.b = %X\n", (*ptr_2).a, (*ptr_2).b);

    return 0;
}