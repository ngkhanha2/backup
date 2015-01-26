/*
 * main.c
 *
 *  Created on: Oct 25, 2014
 *      Author: Khanh
 */

#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#define FILE_IN "P3.IN"

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

int tinhGiaTri(DIEM *diemA, DIEM *diemB, DIEM *diem) {
	double a = diemB->y - diemA->y, b = diemA->x - diemB->x;
	double t = a * (diem->x - diemA->x) + b * (diem->y - diemA->y);
	if (t > 0) {
		return 1;
	}
	if (t < 0) {
		return -1;
	}
	return 0;
}

void timDinhBaoLoi(DIEM **diem, int *dinhBaoLoi, int n) {
	int i, j, k, dau;
	double giaTri;
	for (i = 0; i < n; ++i) {
		dinhBaoLoi[i] = 0;
	}

	for (i = 0; i < n; ++i) {
		for (j = i + 1; j < n; ++j) {
			dau = 0;
			for (k = 0; k < n; ++k) {
				giaTri = tinhGiaTri(diem[i], diem[j], diem[k]);
				if (dau != 0) {
					if (dau * giaTri < 0) {
						dau = -2;
						break;
					}
				} else {
					dau = giaTri;
				}
			}
			if (dau != -2) {
				dinhBaoLoi[i] = 1;
				dinhBaoLoi[j] = 1;
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

void xuat(int *dinhBaoLoi, int n) {
	int i;
	for (i = 0; i < n; ++i) {
		if (dinhBaoLoi[i] == 1) {
			printf("%d ", i);
		}
	}
}

int main() {
	int n;
	DIEM **diem = NULL;
	nhap(&diem, &n);
	int *dinhBaoLoi = (int*) calloc(n, sizeof(int));
	timDinhBaoLoi(diem, dinhBaoLoi, n);
	xuat(dinhBaoLoi, n);
	xoaDuLieu(diem, n);
	free(dinhBaoLoi);
	return 0;
}
