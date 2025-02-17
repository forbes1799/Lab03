#include <stdio.h>
#include <math.h>
#include <omp.h>
#include <stdlib.h>
#include <mkl_cblas.h>

#define N 2048
#define REPEATS 5

// define a test element to be output
#define NOUT 1
#define outputElement NOUT*N+NOUT

int main(void) {
	float *m1, *m2, *res;
	int   matrixByte = N*N*sizeof(float);
	int i,j,k;
	double timer[8];

	printf("\n\n R U N N I N G ... ... \n\n");
	printf("N=%d\n", N);

	// malloc everybody
	m1 = malloc(matrixByte);
	m2 = malloc(matrixByte);
	res = malloc(matrixByte);

	// initialise
	for (i=0; i<N*N; i++) {
		m1[i] = (float) rand()/(float) RAND_MAX;
		m2[i] = (float) rand()/(float) RAND_MAX;
		res[i] = 0.0;
	}

	// mat mat mult
	// repeat a number of times
	int repeat;
	for (repeat=0; repeat<REPEATS; repeat++) {
		printf("Run %d\n", repeat+1);
		
		// reset res
		for (i=0; i<N*N; i++) {
			res[i] = 0.0;
		}

		timer[4] = omp_get_wtime();

		// mat mat mult LIBRARY
		// float => single precision -> sgemm
		// sgemm is very generalised call sgemm. from `man sgemm`
		// sgemm (TRANSA, TRANSB, M, N, K, ALPHA, A, LDA, B, LDB, BETA, C, LDC)
		// to form C = alpha*A*B + beta*C
		cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, N,N,N, 1.0, m1, N, m2, N, 0.0, res,N);

		timer[5] = omp_get_wtime();

		// output a val to avoid compiler removing res
		printf("res[outputElement] = %f\n",res[outputElement]); 
		printf("MAT MAT MULT: %f milliseconds\n\n", 1000.0*(timer[5]-timer[4]));
	}
}