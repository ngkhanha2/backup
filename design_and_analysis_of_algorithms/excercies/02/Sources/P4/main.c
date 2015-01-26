/*
 * main.c
 *
 *  Created on: Oct 25, 2014
 *      Author: Khanh
 */

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#define FILE_IN "P4.IN"

void nhap(int ***khoangCach, int *n) {
	FILE *fi = fopen(FILE_IN, "rt");
	int i, j;

	fscanf(fi, "%d", n);
	*khoangCach = (int**) calloc(*n, sizeof(int*));
	for (i = 0; i < *n; ++i) {
		(*khoangCach)[i] = (int *) calloc(*n, sizeof(int));
	}

	for (i = 0; i < *n; ++i) {
		for (j = 0; j < *n; ++j) {
			fscanf(fi, "%d", &(*khoangCach)[i][j]);
		}
	}

	fclose(fi);
}

int doDaiChuTrinh(int *chuTrinh, int **khoangCach, int n) {
	int i;
	int doDai = 0;
	for (i = 0; i < n - 1; ++i) {
		doDai += khoangCach[chuTrinh[i]][chuTrinh[i + 1]];
	}
	return doDai + khoangCach[chuTrinh[n - 1]][0];
}

void timChuTrinhNganNhat(int *chuTrinh, int *danhDau, int **khoangCach, int p,
		int n, int *chuTrinhNganNhat, int *doDaiNhoNhat) {
	int i;
	int doDai;
	if (p == n) {
		if (khoangCach[chuTrinh[n - 1]][0] > 0) {
			doDai = doDaiChuTrinh(chuTrinh, khoangCach, n);
			if (doDai < *doDaiNhoNhat) {
				*doDaiNhoNhat = doDai;
				for (i = 0; i < n; ++i) {
					chuTrinhNganNhat[i] = chuTrinh[i];
				}
			}
		}
		return;
	}
	for (i = 0; i < n; ++i) {
		if (danhDau[i] == 0 && khoangCach[chuTrinh[p]][i] > 0) {
			danhDau[i] = 1;
			chuTrinh[p] = i;
			timChuTrinhNganNhat(chuTrinh, danhDau, khoangCach, p + 1, n,
					chuTrinhNganNhat, doDaiNhoNhat);
			danhDau[i] = 0;
		}
	}
}

int main() {
	int n, doDaiNhoNhat;
	int **khoangCach = NULL;
	int *chuTrinh = NULL, *chuTrinhNganNhat = NULL, *danhDau = NULL;
	int i;

	nhap(&khoangCach, &n);

	chuTrinh = (int*) calloc(n, sizeof(int));
	chuTrinhNganNhat = (int*) calloc(n, sizeof(int));
	danhDau = (int*) calloc(n, sizeof(int));
	for (i = 0; i < n; ++i) {
		danhDau[i] = 0;
	}
	danhDau[0] = 1;
	chuTrinh[0] = 0;
	doDaiNhoNhat = INT_MAX;
	timChuTrinhNganNhat(chuTrinh, danhDau, khoangCach, 1, n, chuTrinhNganNhat,
			&doDaiNhoNhat);
	if (doDaiNhoNhat == INT_MAX) {
		printf("-1");
	} else {
		printf("%d\n", doDaiNhoNhat);
		for (i = 0; i < n; ++i) {
			printf("%d ", chuTrinhNganNhat[i]);
		}
	}
	free(chuTrinh);
	free(chuTrinhNganNhat);
	free(danhDau);
	for (i = 0; i < n; ++i) {
		free(khoangCach[i]);
	}
	free(khoangCach);
	return 0;
}
