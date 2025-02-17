#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

#define N 2048
#define REPEATS 5

// define a test element to be output
#define NOUT 1
#define outputElement NOUT*N+NOUT

void mult(float*, float*, float*);

int main(void) {
	float *m1, *m2, *res;
  	int   matrixByte = N*N*sizeof(float);
	int i,j,k;
	double timer[8];

	printf("\n\n R U N N I N G ... ... \n\n");
	printf("N=%d\n", N);

	// malloc everybody
	m1 = (float*)malloc(matrixByte);
	m2 = (float*)malloc(matrixByte);
	res = (float*)malloc(matrixByte);

	// initialise
	for (i=0; i<N*N; i++) {
		m1[i] = (float) rand()/(float) RAND_MAX;
		m2[i] = (float) rand()/(float) RAND_MAX;
	}
 
	// mat mat mult
	// repeat a number of times
	int repeat;
	for (repeat=0; repeat<REPEATS; repeat++) {
		printf("Run %d\n", repeat+1);
		
		// set/reset res
		for (i=0; i<N*N; i++) {
			res[i] = 0.0;
		}

		timer[4] = omp_get_wtime();
		mult(res, m1, m2);
		timer[5] = omp_get_wtime();

		// output a val to avoid compiler removing
		printf("res[outputElement] = %f\n",res[outputElement]); 
		printf("MAT MAT MULT: %f milliseconds\n\n", 1000.0*(timer[5] - timer[4]));
	}
}

void mult(float *res, float *m1, float *m2) {
	int i,j,k;

	for (i=0; i<N; i++) {
		for (j=0; j<N; j++) { 
			for (k=0; k<N; k++) {

				int ij = i*N+j;
				int ik = i*N+k;
				int kj = k*N+j;

				//res[i][j] += m1[i][k] * m2[k][j];
				res[ij] += m1[ik] * m2[kj];
				
			}
		}
	}
}
