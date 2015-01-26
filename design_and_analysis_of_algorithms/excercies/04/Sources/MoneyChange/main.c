/*
 * main.c
 *
 *  Created on: Nov 25, 2014
 *      Author: Khanh
 */

#include <stdio.h>
#include <stdlib.h>

#define FILE_IN "INPUT.txt"
#define FILE_OUT "1212171.txt"

void input(int **coins, int *k, int *n) {
	FILE *fi = fopen(FILE_IN, "rt");
	fscanf(fi, "%d", k);
	*coins = (int*) calloc(*k, sizeof(int));
	int i;
	for (i = 0; i < *k; ++i) {
		fscanf(fi, "%d", &(*coins)[i]);
	}
	fscanf(fi, "%d", n);
	fclose(fi);
}

int moneyChange(int* coins, int k, int money) {
	int minCoins = money;
	int i;
	for (i = k; i >= 0; --i) {
		if (coins[i] == money) {
			return 1;
		}
	}
	int tempSum;
	for (i = k; i >= 0; --i) {
		if (money > coins[i]) {
			tempSum = 1 + moneyChange(coins, i, money - coins[i]);
			if (tempSum < minCoins) {
				minCoins = tempSum;
			}
		}
	}
	return minCoins;
}

int compare(const void *a, const void *b) {
	return *((int*) a) - *((int*) b);
}

int main() {
	int k, n;
	int *coins = NULL;
	input(&coins, &k, &n);
	FILE *fo = fopen(FILE_OUT, "wt");
	qsort(coins, k, sizeof(int), compare);
	fprintf(fo, "%d", moneyChange(coins, k - 1, n));
	fclose(fo);
	return 0;
}
