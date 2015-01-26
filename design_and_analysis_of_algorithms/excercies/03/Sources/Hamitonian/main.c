/*
 * main.c
 *
 *  Created on: Nov 13, 2014
 *      Author: Khanh
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define FILE_IN "INPUT.txt"
#define FILE_OUT "1212171.txt"

int promising(int **G, int *path, int pos, int v, int n) {
	int i;
	if (pos == n - 1 && G[v][path[0]] == 0) {
		return 0;
	}
	if (G[path[pos - 1]][v] == 0) {
		return 0;
	}
	for (i = 0; i < pos; ++i) {
		if (path[i] == v) {
			return 0;
		}
	}
	return 1;
}

void print(FILE *fo, int *path, int n) {
	int i;
	fprintf(fo, "%d", path[0] + 1);
	for (i = 1; i < n; ++i) {
		fprintf(fo, " -> %d", path[i] + 1);
	}
	fprintf(fo, "\n");
}

void Hamiltonian(FILE *fo, int **G, int *path, int pos, int n) {
	int v;
	if (pos == n) {
		print(fo, path, n);
	} else {
		for (v = 0; v < n; ++v) {
			if (promising(G, path, pos, v, n)) {
				path[pos] = v;
				Hamiltonian(fo, G, path, pos + 1, n);
			}
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

void input(int ***G, int *n) {
	FILE *fi = fopen(FILE_IN, "rt");
	fscanf(fi, "%d", n);
	*G = initializeBoard(*n);
	int i, j;
	for (i = 0; i < *n; ++i) {
		for (j = 0; j < *n; ++j) {
			fscanf(fi, "%d", &(*G)[i][j]);
		}
	}
	fclose(fi);
}

int main() {
	int n;
	int **G = NULL;
	int *path = NULL;
	input(&G, &n);
	path = (int*) calloc(n + 1, sizeof(int));
	path[0] = 0;
	FILE *fo = fopen(FILE_OUT, "wt");
	Hamiltonian(fo, G, path, 1, n);
	fclose(fo);
	deleteBoard(G, n);
	free(path);
	return 0;
}
