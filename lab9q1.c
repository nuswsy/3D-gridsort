#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void multiply(int A[3][4], int B[4][3], int C[3][3])
{
	int i, j, k;
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
		{
			C[i][j] = 0;
			for (k = 0; k < 4; k++)
				C[i][j] += A[i][k] * B[k][j];
		}
	}
}

void transpose(int C[3][3], int D[3][3]) {
	int i, j;
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
			D[j][i] = C[i][j];
	}
}

void print(int C[3][3])
{
	int i, j;
	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 3; j++)
			printf("%4d", C[i][j]);
		printf("\n");
	}
}


main(void)
{
	int A[3][4] = { 1, 2,  3,  1,
					0, 1, -5,  2,
					6, 2,  0, -2 };

	int B[4][3] = { 1,  0, -1,
					0,  1,  1,
					2,  3,  4,
					0, -1,  0 };
	int C[3][3];
	int D[3][3];

	multiply(A, B, C);
	print(C);
	printf("\n");
	transpose(C, D);
	print(D);
	return 0;
}
