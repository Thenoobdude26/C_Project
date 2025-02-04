#include <stdio.h>

int main() {

        int num = 42; //variable

        int *p = &num; //pointer

        printf("The value of num is: %d\n", num);
        printf("The address of num is: %p\n", &num);
        printf("The value of p is: %p\n", p);
        printf("The value of *p is: %d\n", *p);
    
    
    
    
    return 0;
}