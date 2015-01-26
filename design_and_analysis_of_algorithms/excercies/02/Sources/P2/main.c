/*
 * main.c
 *
 *  Created on: Oct 25, 2014
 *      Author: Khanh
 */

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#define FILE_IN "P2.IN"

typedef struct {
	double x, y;
} DIEM;

void nhap(DIEM ***diem, int *n) {
	FILE *fi = fopen(FILE_IN, "rt");
	int i;

	fscanf(fi, "%d", n);
	*diem = (DIEM**) calloc(*n, sizeof(DIEM*));
	for (i = 0; i < *n; ++i) {
		(*diem)[i] = (DIEM*) malloc(sizeof(DIEM));
		fscanf(fi, "%lf %lf", &((*diem)[i]->x), &((*diem)[i]->y));
	}

	fclose(fi);
}

double tinhKhoangCach(DIEM *diemA, DIEM *diemB) {
	return (diemA->x - diemB->x) * (diemA->x - diemB->x)
			+ (diemA->y - diemB->y) * (diemA->y - diemB->y);
}

void timHaiDiemGanNhat(DIEM **diem, int n, int *diemA, int *diemB) {
	int i, j;
	double khoangCach, khoangCachNhoNhat = (double) INT_MAX;

	for (i = 0; i < n; ++i) {
		for (j = i + 1; j < n; ++j) {
			khoangCach = tinhKhoangCach(diem[i], diem[j]);
			if (khoangCach < khoangCachNhoNhat) {
				khoangCachNhoNhat = khoangCach;
				*diemA = i;
				*diemB = j;
			}
		}
	}
}

void xoaDuLieu(DIEM **diem, int n) {
	int i;
	for (i = 0; i < n; ++i) {
		free(diem[i]);
	}
	free(diem);
}

int main() {
	int n;
	DIEM **diem = NULL;
	nhap(&diem, &n);
	int diemA = -1, diemB = -1;
	timHaiDiemGanNhat(diem, n, &diemA, &diemB);
	if (diemA == -1) {
		printf("-1");
	} else {
		printf("%d %d", diemA, diemB);
	}

	xoaDuLieu(diem, n);
	return 0;
}
