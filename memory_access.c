
#include <stdio.h>
#include <time.h>
#include <omp.h>
int N = 48000;
int mat[48000][48000];

void main()

{
	int i, j;
	clock_t _S, _E;
	double d = 0.0;

	_S = omp_get_wtime();
	for (i = 0; i < N; i++)
		for (j = 0; j < N; j++)
			mat[i][j] = mat[i][j] + (mat[i][j] * mat[i][j]);

	_E = omp_get_wtime();
	d = (double)(_E - _S);
	printf("row major run time is %lf milliseconds\n", 1000 * d);

	_S = omp_get_wtime();
	for (j = 0; j < N; j++)
		for (i = 0; i < N; i++)
			mat[i][j] = mat[i][j] + (mat[i][j] * mat[i][j]);

	_E = omp_get_wtime();
	d = (double)(_E - _S);
	printf("column major run time is %lf milliseconds\n", 1000 * d);
}

