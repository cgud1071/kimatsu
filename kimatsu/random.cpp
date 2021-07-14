#include <stdlib.h>

void shuffle(int array[], int size) {
    for (int i = 0; i < size; i++) {
        int j = rand() % size;
        int t = array[i];
        array[i] = array[j];
        array[j] = t;
    }
}