#include <stdio.h>

int main(void) {
  int a = 5;
  int *a_ptr = &a;

  printf( "&a     : %p : 0x%012x : a\n", &a, a );
  printf( "&a_ptr : %p : %p : a_ptr\n", &a_ptr, a_ptr );
  return 0;
}
 
/*Note that the code originally had casting to void pointers involved, seemingly unnecessarily. 
When deleted it didn't change anything.*/