#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main() {

//	matr_mult_benchmark(100000);

	int **a;
	int **b;
	int **c;
	int i, j, k;
	int max_iter = 100000;
	int size = 100000;
	//for(size=10; size< max_iter; size *= 10) {
	a = malloc(sizeof(int)*size);
	b = malloc(sizeof(int)*size);
	c = malloc(sizeof(int)*size);

	for(i=0; i<size; i++) {
		a[i] = malloc(sizeof(int)*size);
		b[i] = malloc(sizeof(int)*size);
		c[i] = malloc(sizeof(int)*size);
	}

	int value = 0;
	for(i=0; i<size; i++) {
		for(j=0; j<size; j++) {
			a[i][j] = value;
			b[i][j] = 2*value;
			c[i][j] = 0;
			value++;
		}
	}


	for(i=0; i<size; i++) {
		for(j=0; j<size; j++) {
			for(k=0; k<size; k++) {
				c[i][j] += a[i][k] * b[k][j]; 
			}
		}
	}

	free(a);
	free(b);
	free(c);
	//}

	return 0;
}

/*void matr_mult_benchmark(int max_iter) {
	int **a;
	int **b;
	int **c;
	int i;
	for(size=10; size< max_iter; size *= 10) {
		a = malloc(sizeof(int)*size);
		b = malloc(sizeof(int)*size);
		c = malloc(sizeof(int)*size);

		for(i=0; i<size; i++) {
			a[i] = malloc(sizeof(int)*size);
			b[i] = malloc(sizeof(int)*size);
			c[i] = malloc(sizeof(int)*size);
		}



		free(a);
		free(b);
		free(c);
	}
}*/