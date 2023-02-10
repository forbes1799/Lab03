
#include <stdio.h>
#include <time.h>
int N = 99999;
int mat[99999][99999];

void main()

{
	int i, j;
	clock_t _S, _E;
	double d = 0.0;

	_S = clock();
	for (i = 0; i < N; i++)
		for (j = 0; j < N; j++)
			mat[i][j] = mat[i][j] + (mat[i][j] * mat[i][j]);

	_E = clock();
	d = (double)(_E - _S) / CLOCKS_PER_SEC;
	printf("row major run time is %lf milliseconds\n", 1000 * d);

	_S = clock();
	for (j = 0; j < N; j++)
		for (i = 0; i < N; i++)
			mat[i][j] = mat[i][j] + (mat[i][j] * mat[i][j]);

	_E = clock();
	d = (double)(_E - _S) / CLOCKS_PER_SEC;
	printf("column major run time is %lf milliseconds\n", 1000 * d);
}

