#include <stdio.h>
#include <omp.h>
#include <stdlib.h>

#define N 2048
#define REPEATS 3

// define a test element to be output
#define NOUT 1
#define outputElement NOUT*N+NOUT

void mult(float*, float*, float*, int);

int main(void) {
	float *m1, *m2, *res;
	int batches = omp_get_max_threads();
  	int   matrixByte = batches*N*N*sizeof(float);
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
		mult(res, m1, m2, batches);
		timer[5] = omp_get_wtime();

		// output a val to avoid compiler removing
		printf("res[outputElement] = %f\n",res[outputElement]); 
		printf("MAT MAT MULT: %f milliseconds\n\n", 1000.0*(timer[5] - timer[4]));
	}
}

void mult(float *res, float *m1, float *m2, int batches) {
	int b,i,j,k;

	#pragma omp parallel default(none) private(b, i, j, k) shared(batches, res, m1, m2)
	{
		#pragma omp for  
		for (b=0; b < batches; b++){
			int batch_offset = b * N * N;
			for (i=0; i<N; i++) {
				for (j=0; j<N; j++) {
					int ij = batch_offset + i*N+j; 
					for (k=0; k<N; k++) {
						
						int ik = batch_offset + i*N+k;
						int kj = batch_offset + k*N+j;

						res[ij] += m1[ik] * m2[kj];
						
					}
				}
			}
		}
	}
}
