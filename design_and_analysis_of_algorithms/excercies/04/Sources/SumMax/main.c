/*
 * main.c
 *
 *  Created on: Nov 25, 2014
 *      Author: Khanh
 */

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define FILE_IN "INPUT.txt"
#define FILE_OUT "1212171.txt"

void input(int **array, int *n) {
	FILE *fi = fopen(FILE_IN, "rt");
	fscanf(fi, "%d", n);
	*array = (int*) calloc(*n, sizeof(int));
	int i;
	for (i = 0; i < *n; ++i) {
		fscanf(fi, "%d", &(*array)[i]);
	}
	fclose(fi);
}

int max(int a, int b) {
	return a > b ? a : b;
}

void sumMax(int *array, int left, int right, int *maxSum, int *leftResult,
		int *rightResult) {
	if (left == right) {
		if (array[left] > *maxSum) {
			*maxSum = array[left];
			*leftResult = left;
			*rightResult = left;
		}
		return;
	}
	int mid = (left + right) / 2;

	int temp, maxLeftPart, maxRightPart, pLeft, pRight, i;
	temp = 0;
	maxLeftPart = maxRightPart = INT_MIN;
	for (i = mid; i >= left; --i) {
		temp += array[i];
		if (temp > maxLeftPart) {
			maxLeftPart = temp;
			pLeft = i;
		}
	}
	temp = 0;
	for (i = mid + 1; i <= right; ++i) {
		temp += array[i];
		if (temp > maxRightPart) {
			maxRightPart = temp;
			pRight = i;
		}
	}
	temp = maxLeftPart + maxRightPart;
	if (temp > *maxSum) {
		*maxSum = temp;
		*leftResult = pLeft;
		*rightResult = pRight;
	}
	sumMax(array, left, mid, maxSum, leftResult, rightResult);
	sumMax(array, mid + 1, right, maxSum, leftResult, rightResult);
}

int main() {
	int n, maxSum, left, right;
	int *array = NULL;
	input(&array, &n);
	FILE *fo = fopen(FILE_OUT, "wt");
	maxSum = INT_MIN;
	sumMax(array, 0, n - 1, &maxSum, &left, &right);
	fprintf(fo, "%d", maxSum);
	if (maxSum != 0) {
		fprintf(fo, " %d %d", left, right);
	}
	fclose(fo);
	free(array);
	return 0;
}
