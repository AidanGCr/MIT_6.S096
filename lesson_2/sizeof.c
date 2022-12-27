#include <stdio.h>
#include <stdlib.h>

void stack_array(void) {
  int array[10];
  // size of array  IN BYTES
  printf( "OK: array holds %zu bytes\n\n", sizeof( array ) );
}

void heap_array(void) {
  int *array = malloc( 10 * sizeof( int ) );
  printf( "WRONG: array holds %zu bytes\n", sizeof( array ) );
  printf( "^nope- that's the size of the pointer\n" );
  // note that putting the pointer in here and de-referencing the array will also not work 
  // since the array will decay to the first element of the array - an int of 4 bytes
  free( array );
}

int main(void) {
  stack_array();
  heap_array();
  return 0;
}
