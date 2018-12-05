#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 10000

int main(int argc, char *argv[]) {
    int array[N];
    for (unsigned i = 0; i < N; i++) {
        array[i] = rand() % 512;

        for (unsigned j = 0; j < N; j++) { //waw
            array[j] = array[j] * i;
            array[j] = array[j] + j;
        }

        for (unsigned k = 0; k < N; k++) { //RAW
            int a = 3;
            array[k] = 3;
            a = array[k];
        }

        for (unsigned k = 0; k < N; k++) { //WAR
            int a = array[k];
            array[k] = a;
        }
    }
    for (unsigned i = 0; i < N; i++) {
//        printf("%d", array[i]);
    }
    return 0;
}
