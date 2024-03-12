#include "map.h"

#define N 100

int main(){
    Map<int> test;
    for (int i = 1; i < N; i++)
        test.insert(i, i);

    return 0;
}