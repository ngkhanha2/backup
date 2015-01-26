/*
 * main.c
 *
 *  Created on: Oct 25, 2014
 *      Author: Khanh
 */

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#define FILE_IN "P1.IN"

void nhap(int **dongXu, int *k, int *n) {
	FILE *fi = fopen(FILE_IN, "rt");
	int i;

	fscanf(fi, "%d %d", n, k);
	*dongXu = (int*) calloc(*k, sizeof(int));
	for (i = 0; i < *k; ++i) {
		fscanf(fi, "%d", &(*dongXu)[i]);
	}

	fclose(fi);
}

int min(int a, int b) {
	return a > b ? b : a;
}

int doiTien(int *dongXu, int soDongXu, int giaTri, int c, int k, int n) {
	if (giaTri == n) {
		return soDongXu;
	}
	if (c == k) {
		return INT_MAX;
	}
	int i, minSoDongXu = INT_MAX;
	for (i = giaTri + dongXu[c]; i <= n; i += dongXu[c]) {
		++soDongXu;
		minSoDongXu = min(minSoDongXu,
				doiTien(dongXu, soDongXu, i, c + 1, k, n));
	}
	return minSoDongXu;
}

int main() {
	int n, k;
	int *dongXu = NULL;
	nhap(&dongXu, &k, &n);
	int ketQua = doiTien(dongXu, 0, 0, 0, k, n);
	if (ketQua == INT_MAX) {
		printf("-1");
	} else {
		printf("%d", ketQua);
	}
	free(dongXu);
	return 0;
}
