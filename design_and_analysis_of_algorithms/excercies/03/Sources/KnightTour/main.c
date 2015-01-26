/*
 * main.c
 *
 *  Created on: Nov 13, 2014
 *      Author: Khanh
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_IN "INPUT.txt"
#define FILE_OUT "1212171.txt"

#define MAX_D 8

const int dx[8] = { -2, -2, -1, 1, 2, 2, 1, -1 };
const int dy[8] = { -1, 1, 2, 2, 1, -1, -2, -2 };

typedef struct {
	int x, y;
} POSITION;

void print(FILE *fo, POSITION *t, int n) {
	int i, k = n * n - 1;
	for (i = 0; i < k; ++i) {
		fprintf(fo, "(%d; %d) -> ", t[i].x + 1, t[i].y + 1);
	}
	fprintf(fo, "(%d; %d)\n", t[k].x + 1, t[k].y + 1);
}

void KnightTour(FILE *fo, int **h, POSITION *t, int i, int r, int c, int n) {
	int u, v, k;
	for (k = 0; k < MAX_D; ++k) {
		u = r + dx[k];
		v = c + dy[k];
		if (u >= 0 && u < n && v >= 0 && v < n && h[u][v] == 0) {
			h[u][v] = i;
			t[i - 1].x = u;
			t[i - 1].y = v;
			if (i == n * n) {
				print(fo, t, n);
			} else {
				KnightTour(fo, h, t, i + 1, u, v, n);
			}
			h[u][v] = 0;
		}
	}
}

int** initializeBoard(int n) {
	int i;
	int **board = (int **) calloc(n, sizeof(int*));
	for (i = 0; i < n; ++i) {
		board[i] = (int *) calloc(n, sizeof(int));
		memset(board[i], 0, sizeof(int) * n);
	}
	return board;
}

void deleteBoard(int **board, int n) {
	int i;
	for (i = 0; i < n; ++i) {
		free(board[i]);
	}
	free(board);
}

int main() {
	int n, r, c;
	FILE *fi = fopen(FILE_IN, "rt");
	fscanf(fi, "%d %d %d", &n, &r, &c);
	fclose(fi);
	int **h = initializeBoard(n);
	POSITION *t = (POSITION*) calloc(n * n, sizeof(POSITION));
	--r;
	--c;
	t[0].x = r;
	t[0].y = c;
	h[r][c] = 1;
	FILE *fo = fopen(FILE_OUT, "wt");
	KnightTour(fo, h, t, 2, r, c, n);
	fclose(fo);
	deleteBoard(h, n);
	free(t);
	return 0;
}
