/*
 * main.c
 *
 *  Created on: Nov 13, 2014
 *      Author: Khanh
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define FILE_IN "INPUT.txt"
#define FILE_OUT "1212171.txt"

int promising(int *col, int i) {
	int j = 1;
	while (j < i) {
		if (col[i] == col[j] || abs(col[i] - col[j]) == i - j) {
			return 0;
		}
		++j;
	}
	return 1;
}

void print(FILE *fo, int *col, int n) {
	int i;
	for (i = 1; i < n; ++i) {
		fprintf(fo, "(%d; %d); ", i, col[i]);
	}
	fprintf(fo, "(%d; %d)\n", n, col[n]);
}

void n_Queens(FILE *fo, int *col, int i, int n) {
	int j;
	for (j = 1; j <= n; ++j) {
		col[i] = j;
		if (promising(col, i)) {
			if (i == n) {
				print(fo, col, n);
			} else {
				n_Queens(fo, col, i + 1, n);
			}
		}
	}
}

int main() {
	int n;
	FILE *fi = fopen(FILE_IN, "rt");
	fscanf(fi, "%d", &n);
	fclose(fi);
	int *col = (int*) calloc(n + 1, sizeof(int));
	memset(col, 0, sizeof(int) * (n + 1));
	FILE *fo = fopen(FILE_OUT, "wt");
	n_Queens(fo, col, 1, n);
	fclose(fo);
	free(col);
	return 0;
}
