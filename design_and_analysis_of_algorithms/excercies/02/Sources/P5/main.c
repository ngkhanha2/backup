/*
 * main.c
 *
 *  Created on: Oct 25, 2014
 *      Author: Khanh
 */

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#define FILE_IN "P5.IN"

typedef struct {
	int w, v;
} MONDO;

void nhap(MONDO ***monDo, int *W, int *n) {
	FILE *fi = fopen(FILE_IN, "rt");
	int i;

	fscanf(fi, "%d %d", W, n);
	*monDo = (MONDO**) calloc(*n, sizeof(MONDO*));
	for (i = 0; i < *n; ++i) {
		(*monDo)[i] = (MONDO*) malloc(sizeof(MONDO));
		fscanf(fi, "%d %d", &((*monDo)[i]->w), &((*monDo)[i]->v));
	}

	fclose(fi);
}

void xepDo(MONDO **monDo, int *cachXep, int p, int W, int n, int *cachXepToiUu,
		int *giaTriLonNhat) {
	int i;
	if (p == n) {
		int giaTri = 0;
		int khoiLuong = 0;
		for (i = 0; i < n; ++i) {
			if (cachXep[i] == 1) {
				khoiLuong += monDo[i]->w;
				if (khoiLuong > W) {
					return;
				}
				giaTri += monDo[i]->v;
			}
			if (giaTri > *giaTriLonNhat) {
				*giaTriLonNhat = giaTri;
				for (i = 0; i < n; ++i) {
					cachXepToiUu[i] = cachXep[i];
				}
			}
		}
		return;
	}
	for (i = 0; i < 2; ++i) {
		cachXep[p] = i;
		xepDo(monDo, cachXep, p + 1, W, n, cachXepToiUu, giaTriLonNhat);
	}
}

int main() {
	int n, W, giaTriLonNhat, i;
	int *cachXep, *cachXepToiUu;
	MONDO **monDo = NULL;
	nhap(&monDo, &W, &n);

	cachXep = (int*) calloc(n, sizeof(int));
	cachXepToiUu = (int*) calloc(n, sizeof(int));
	giaTriLonNhat = 0;
	xepDo(monDo, cachXep, 0, W, n, cachXepToiUu, &giaTriLonNhat);

	if (giaTriLonNhat == 0) {
		printf("-1");
	} else {
		printf("%d\n", giaTriLonNhat);
		for (i = 0; i < n; ++i) {
			if (cachXepToiUu[i] == 1) {
				printf("%d ", i);
			}
		}
	}
	free(cachXep);
	free(cachXepToiUu);
	for (i = 0; i < n; ++i) {
		free(monDo[i]);
	}
	free(monDo);
	return 0;
}
