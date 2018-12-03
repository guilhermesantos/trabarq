#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main() {
	double **a;
	double **b;
	double **c;
	int i, j, k;
	int size = 1000;
	
	a = malloc(sizeof(double*)*size);
	b = malloc(sizeof(double*)*size);
	c = malloc(sizeof(double*)*size);

	for(i=0; i < size; i++) {
		//printf("alocando %d\n", i);
		a[i] = malloc(sizeof(double)*size);
		b[i] = malloc(sizeof(double)*size);
		c[i] = malloc(sizeof(double)*size);
	}

	//printf("terminou de alocar\n");
	double value = 0;
	for(i=0; i <size; i++) {
		for(j=0; j < size; j++) {
			//printf("criando %d %d\n", i, j);
			a[i][j] = value;
			b[i][j] = 2*value;
			c[i][j] = 0;
			value++;
		}
	}

	//printf("terminou de criar\n");
	int mult_num = 10;//numero de vezes a realizar multiplicacao
	int cur_mult = 0;
	//while(cur_mult < mult_num) {
	for(i=0; i<size; i++) {
		for(j=0; j<size; j++) {
			for(k=0; k<size; k++) {
				//printf("%d %d", i, j);
				c[i][j] += a[i][k] * b[k][j]; 
			}
		}
	}
	//	cur_mult++;
	//}

	free(a);
	free(b);
	free(c);

	return 0;
}

