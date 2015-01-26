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

int compareX(const void *a, const void *b) {
	double xa = (*((POINT**) a))->x;
	double xb = (*((POINT**) b))->x;
	return xa < xb ? -1 : 1;
}

int compareY(const void *a, const void *b) {
	double ya = (*((POINT**) a))->y;
	double yb = (*((POINT**) b))->y;
	return ya < yb ? -1 : 1;
}

POINT** clonePointArray(POINT** array, int start, int end) {
	POINT **result = (POINT**) calloc(end - start + 1, sizeof(POINT*));
	int i, j;
	j = 0;
	for (i = start; i <= end; ++i) {
		result[j] = array[i];
		++j;
	}
	return result;
}

double min(double a, double b) {
	return a > b ? b : a;
}

double distanceSqr(POINT *p1, POINT *p2) {
	double dx = p1->x - p2->x;
	double dy = p1->y - p2->y;
	return dx * dx + dy * dy;
}

double absolute(double d) {
	return d >= 0 ? d : -d;
}

double ClosestPairRec(POINT **P, POINT **Q, int n) {
	int i, j, mid, k;
	double median, delta, deltaMin, d;
	if (n <= 3) {
		deltaMin = (double) INT_MAX;
		for (i = n - 1; i > 0; --i) {
			for (j = 0; j < i; ++j) {
				d = distanceSqr(P[i], P[j]);
				if (d < deltaMin) {
					deltaMin = d;
				}
			}
		}
		return deltaMin;
	}
	mid = n / 2;
	POINT **PLeft = clonePointArray(P, 0, mid);
	POINT **QLeft = clonePointArray(Q, 0, mid);
	POINT **PRight = clonePointArray(P, mid + 1, n - 1);
	POINT **QRight = clonePointArray(Q, mid + 1, n - 1);
	delta = min(ClosestPairRec(PLeft, QLeft, mid),
			ClosestPairRec(PLeft, QLeft, n - mid - 1));
	free(PLeft);
	free(QLeft);
	free(PRight);
	free(QRight);
	median = P[mid]->x;
	POINT **S = (POINT**) calloc(n, sizeof(POINT*));
	k = 0;
	for (i = 0; i < n; ++i) {
		if (absolute(Q[i]->x - median) < delta) {
			S[k] = Q[i];
			++k;
		}
	}
	--k;
	deltaMin = delta;
	for (i = 0; i < k; ++i) {
		for (j = i + 1; j <= k && absolute(S[i]->y - S[j]->y) < deltaMin; ++j) {
			d = distanceSqr(S[i], S[j]);
			if (d < deltaMin) {
				deltaMin = d;
			}
		}
	}
	free(S);
	return deltaMin;
}

double ClosestPair(POINT **P, int n) {
	POINT **Q = clonePointArray(P, 0, n - 1);
	qsort(P, n, sizeof(POINT*), compareX);
	qsort(Q, n, sizeof(POINT*), compareY);

	double result = ClosestPairRec(P, Q, n);
	free(Q);
	return sqrt(result);
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

int main() {
	int n;
	POINT **P = NULL;
	input(&P, &n);
	FILE *fo = fopen(FILE_OUT, "wt");
	fprintf(fo, "%lf", ClosestPair(P, n));
	fclose(fo);
	clearPoints(P, n);
	return 0;
}
