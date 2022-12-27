#include <stdio.h> 

int main(void) { 

    struct IntPair_s {
    int first;
    int second;
    };

    // in code:
    struct IntPair_s pair;
    pair.first = 1;
    pair.second = 2;
    struct IntPair_s *pairPtr = &pair;

    // use pairPtr->first and pairPtr->second
    // to access elements

    printf("%d, %d\n", pairPtr->first, pairPtr->second); 
} 