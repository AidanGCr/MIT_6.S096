#include <stdio.h> 

int main(void) { 
    int a = 5; 
    int *a_ptr = &a; 
    printf("%d, %d\n", a, *a_ptr); 
    return 0; 
}