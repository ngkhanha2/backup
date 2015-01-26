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

int josephus(int n) {
	if (n == 1) {
		return 1;
	}
	if (n % 2 == 0) {
		return 2 * josephus(n >> 1) - 1;
	}
	return 2 * josephus(n >> 1) + 1;
}

int main() {
	int n;
	FILE *fi = fopen(FILE_IN, "rt");
	fscanf(fi, "%d", &n);
	fclose(fi);
	FILE *fo = fopen(FILE_OUT, "wt");
	fprintf(fo, "%d", josephus(n));
	fclose(fo);
	return 0;
}
