/*
 * Written by Dr Maryam Abo Tabik
*/

#include <stdio.h>
#include<stdlib.h>
#include<time.h>


int main() {
	int numVectorElements = 50000;
	int N = sizeof(float) * numVectorElements;

	float x[N], y[N], res[N];
	float A = 0.001;
	int i, myTiming;
	int Timings = 5000;
	clock_t _S, _E;
	double Timer;
	printf("\n load %d Vector elements...\n", numVectorElements);

	//init
	for (i = 0; i < N; i++)
	{
		x[i] = 1000.0 * rand() / RAND_MAX;
		y[i] = 0.1 * rand() / RAND_MAX;
	}

	printf("init complete...");

	//do 100 to warm processor
	int WarmUp = 100;
	for (myTiming = 0; myTiming < WarmUp; myTiming++)
	{
		for (i = 0; i < N; i++)
		{
			res[i] = A * x[i] + y[i];
		}
	}

	float MyTime = 0.0;
	_S = clock();
	for (myTiming = 0; myTiming < Timings; myTiming++)
	{
		for (i = 0; i < N; i++)
		{
			res[i] = A * x[i] + y[i];
		}
	}
	MyTime = (double)(clock() - _S) / CLOCKS_PER_SEC;
	printf("\n %f millisecods \n", 1000.0 * (float)MyTime);
	return 0;
}