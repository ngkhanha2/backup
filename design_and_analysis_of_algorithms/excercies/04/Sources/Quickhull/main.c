/*
 * main.c
 *
 *  Created on: Nov 25, 2014
 *      Author: Khanh
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

#define FILE_IN "INPUT.txt"
#define FILE_OUT "1212171.txt"

typedef struct {
	double x, y;
} POINT;

double detVal(POINT *p1, POINT *p2, POINT *p3) {
	return p1->x * p2->y + p2->x * p3->y + p3->x * p1->y - p3->x * p2->y
			- p2->x * p1->y - p1->x * p3->y;
}

void deleteRight(POINT **S, POINT *p1, POINT *pN, int n, POINT ***leftArea,
		int *leftAreaSize) {
	int i;
	*leftArea = (POINT**) calloc(n, sizeof(POINT*));
	(*leftArea)[0] = p1;
	(*leftArea)[1] = pN;
	*leftAreaSize = 2;
	for (i = 0; i < n; ++i) {
		if (S[i] != p1 && S[i] != pN) {
			if (detVal(p1, pN, S[i]) > 0) {
				(*leftArea)[*leftAreaSize] = S[i];
				++(*leftAreaSize);
			}
		}
	}
}

POINT* getPointMax(POINT **S, int n) {
	POINT *p1 = S[0];
	POINT *pN = S[1];
	POINT *pMax = NULL;
	int i;
	double maxArea = 0, area;
	for (i = 2; i < n; ++i) {
		area = detVal(p1, pN, S[i]);
		area = area >= 0 ? area : -area;
		if (area > maxArea) {
			maxArea = area;
			pMax = S[i];
		}
	}
	return pMax;
}

void hullUnion(POINT **hull, int *hullSize, POINT *p) {
	int i;
	for (i = 0; i < *hullSize; ++i) {
		if (hull[i] == p) {
			return;
		}
	}
	hull[*hullSize] = p;
	++(*hullSize);
}

void quickHull(POINT **S, int n, POINT **hull, int *hullSize) {
	if (n <= 2) {
		return;
	}
	if (n == 3) {
		hullUnion(hull, hullSize, S[2]);
		return;
	}
	POINT **S00 = NULL;
	POINT **S02 = NULL;
	POINT *p1 = S[0];
	POINT *pN = S[1];
	POINT *pMax = getPointMax(S, n);
	int countS00, countS02;
	deleteRight(S, p1, pMax, n, &S00, &countS00);
	quickHull(S00, countS00, hull, hullSize);
	hullUnion(hull, hullSize, pMax);
	deleteRight(S, pMax, pN, n, &S02, &countS02);
	quickHull(S02, countS02, hull, hullSize);
	free(S00);
	free(S02);
}

void input(POINT ***P, int *n) {
	FILE *fi = fopen(FILE_IN, "rt");
	fscanf(fi, "%d", n);
	*P = (POINT**) calloc(*n, sizeof(POINT*));
	int i;
	for (i = 0; i < *n; ++i) {
		(*P)[i] = (POINT*) malloc(sizeof(POINT));
		fscanf(fi, "%lf %lf", &(*P)[i]->x, &(*P)[i]->y);
	}
	fclose(fi);
}

void clearPoints(POINT **P, int n) {
	int i;
	for (i = 0; i < n; ++i) {
		free(P[i]);
	}
	free(P);
}

int compare(const void *a, const void *b) {
	double xa = (*((POINT**) a))->x;
	double xb = (*((POINT**) b))->x;
	if (xa < xb) {
		return -1;
	}
	if (xa > xb) {
		return 1;
	}
	double ya = (*((POINT**) a))->y;
	double yb = (*((POINT**) b))->y;
	if (ya < yb) {
		return -1;
	}
	return 1;
}

void solve(POINT **P, int n) {
	POINT **hull = (POINT**) calloc(n, sizeof(POINT*));
	int hullSize = 0;
	qsort(P, n, sizeof(POINT*), compare);
	hullUnion(hull, &hullSize, P[0]);
	POINT **S0 = NULL;
	POINT **S1 = NULL;
	int countS0, countS1;
	deleteRight(P, P[0], P[n - 1], n, &S0, &countS0);
	deleteRight(P, P[n - 1], P[0], n, &S1, &countS1);
	quickHull(S0, countS0, hull, &hullSize);
	hullUnion(hull, &hullSize, P[n - 1]);
	quickHull(S1, countS1, hull, &hullSize);
	free(S0);
	free(S1);
	FILE *fo = fopen(FILE_OUT, "wt");
	int i;
	for (i = 0; i < hullSize; ++i) {
		fprintf(fo, "%lf %lf\n", hull[i]->x, hull[i]->y);
	}
	fclose(fo);
	free(hull);
}

int main() {
	int n;
	POINT **P = NULL;
	input(&P, &n);
	solve(P, n);
	clearPoints(P, n);
	return 0;
}
