#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 32768

void Swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

int Partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] <= pivot) {
            i++;
            Swap(&arr[i], &arr[j]);
        }
    }
    Swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void QuickSort(int arr[], int low, int high) {
    if (low < high) {
        int p = Partition(arr, low, high);
        QuickSort(arr, low, p - 1);
        QuickSort(arr, p + 1, high);
    }
}


int main(int argc, char *argv[]) {
    int array[N];
    for (unsigned i = 0; i < N; i++) {
        array[i] = rand() % 512;
    }
    long sum = 0;
    QuickSort(array, 0, N - 1);
    for (unsigned i = 0; i < N; i++) {
        if (array[i] >= 256)
            sum += array[i];
    }
    printf("%ld\n", sum);
    return 0;
}