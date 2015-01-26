/*
 * main.c
 *
 *  Created on: Dec 6, 2014
 *      Author: Khanh
 */

#include <stdio.h>
#include <stdlib.h>

#define FILE_IN "INPUT.txt"
#define FILE_OUT "1212171.txt"

void swap(char *a, char *b) {
	char t = *a;
	*a = *b;
	*b = t;
}

int nextPerm(char *a, int n) {
	int k = n - 1;
	while (a[k] > a[k + 1]) {
		--k;
		if (k == 0) {
			return 0;
		}
	}
	int i = n;
	while (a[k] > a[i]) {
		--i;
	}
	swap(&a[k], &a[i]);
	int r = n;
	int s = k + 1;
	while (r > s) {
		swap(&a[r], &a[s]);
		--r;
		++s;
	}
	return 1;
}

void output(FILE *fo, char *a, int n) {
	int i;
	for (i = 1; i <= n; ++i) {
		fprintf(fo, "%c", a[i]);
	}
	fprintf(fo, "\n");
}

void lexicographicOrder(FILE *fo, char *a, int n) {
	do {
		output(fo, a, n);
	} while (nextPerm(a, n));
}

void input(char **a, int *n) {
	FILE *fi = fopen(FILE_IN, "rt");
	char c;
	*n = 0;
	while (1) {
		if (fscanf(fi, "%c", &c) > 0) {
			if (c != '\n') {
				++(*n);
			} else {
				break;
			}
		} else {
			break;
		}
	}
	fclose(fi);
	*a = (char*) calloc(*n + 1, sizeof(char));
	fi = fopen(FILE_IN, "rt");
	int i;
	for (i = 1; i <= *n; ++i) {
		fscanf(fi, "%c", &(*a)[i]);
	}
	fclose(fi);
}

int compare(const void *a, const void *b) {
	return (int) (*(char*) a - *(char*) b);
}

int main() {
	int n;
	char *a = NULL;
	input(&a, &n);
	a[0] = 0;
	qsort(a, n + 1, sizeof(char), compare);
	FILE *fo = fopen(FILE_OUT, "wt");
	lexicographicOrder(fo, a, n);
	fclose(fo);
	free(a);
	return 0;
}
