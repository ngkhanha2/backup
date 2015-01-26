/*
 * main.c
 *
 *  Created on: Oct 4, 2014
 *      Author: Khanh
 */

#include <time.h>
#include <stdio.h>

#define FILE_RESULT "result.csv"

int fibonacci_recursion(int n) {
	if (n <= 1) {
		return 1;
	}
	return fibonacci_recursion(n - 1) + fibonacci_recursion(n - 2);
}

int fibonacci_matrix_multiplication(int n) {
	int i = 1, j = 0, k = 0, h = 1, t;
	++n;
	while (n) {
		if (n % 2) {
			t = j * h;
			j = i * h + j * k + t;
			i = i * k + t;
		}
		t = h * h;
		h = 2 * k * h + t;
		k = k * k + t;
		n = n >> 1;
	}
	return j;
}

int main() {
	clock_t start, end;
	double duration;
	int i;
	int n;

	scanf("%d", &n);

	FILE *fo = fopen(FILE_RESULT, "wt");

	fprintf(fo, "Recursion, Matrix Multiplication\n");
	for (i = 1; i <= n; ++i) {
		start = clock();
		fibonacci_recursion(i);
		end = clock();

		duration = ((double) (end - start)) / CLOCKS_PER_SEC;

		fprintf(fo, "%lf, ", duration);

		start = clock();
		fibonacci_matrix_multiplication(i);
		end = clock();

		duration = ((double) (end - start)) / CLOCKS_PER_SEC;

		fprintf(fo, "%lf\n", duration);
	}

	fclose(fo);

	return 0;
}
