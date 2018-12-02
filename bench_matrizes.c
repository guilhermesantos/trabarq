#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int main() {


	int **a;
	int **b;
	int **c;
	int i, j, k;
	int size = 1000;
	
	a = malloc(sizeof(int*)*size);
	b = malloc(sizeof(int*)*size);
	c = malloc(sizeof(int*)*size);

	for(i=0; i < size; i++) {
		//printf("alocando %d\n", i);
		a[i] = malloc(sizeof(int)*size);
		b[i] = malloc(sizeof(int)*size);
		c[i] = malloc(sizeof(int)*size);
	}

	//printf("terminou de alocar\n");
	int value = 0;
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
	int mult_num = 3;//numero de vezes a realizar multiplicacao
	int cur_mult = 0;
	while(cur_mult < mult_num) {
		for(i=0; i<size; i++) {
			for(j=0; j<size; j++) {
				for(k=0; k<size; k++) {
					//printf("%d %d", i, j);
					c[i][j] += a[i][k] * b[k][j]; 
				}
			}
		}
		cur_mult++;
	}

	free(a);
	free(b);
	free(c);

	return 0;
}

