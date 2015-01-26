/*
 * main.c
 *
 *  Created on: Nov 13, 2014
 *      Author: Khanh
 */

#include <stdio.h>
#include <stdlib.h>

#define FILE_IN "INPUT.txt"
#define FILE_OUT "1212171.txt"

int findPath(char **maze, int r, int c, int m, int n) {
	if (r < 0 || r >= m || c < 0 || c >= n) {
		return 0;
	}
	switch (maze[r][c]) {
	case 'G':
		return 1;
	case 'x':
		return 0;
	case '#':
		return 0;
	}
	maze[r][c] = 'x';
	if (findPath(maze, r - 1, c, m, n)) {
		return 1;
	}
	if (findPath(maze, r, c + 1, m, n)) {
		return 1;
	}
	if (findPath(maze, r + 1, c, m, n)) {
		return 1;
	}
	if (findPath(maze, r, c - 1, m, n)) {
		return 1;
	}
	maze[r][c] = '.';
	return 0;
}

char** initializeBoard(int m, int n) {
	int i;
	char **board = (char **) calloc(m, sizeof(char*));
	for (i = 0; i < m; ++i) {
		board[i] = (char *) calloc(n, sizeof(char));
	}
	return board;
}

void deleteBoard(char **board, int n) {
	int i;
	for (i = 0; i < n; ++i) {
		free(board[i]);
	}
	free(board);
}

void input(char ***maze, int *m, int *n, int *r0, int *c0) {
	int i, j;
	char c;
	FILE *fi = fopen(FILE_IN, "rt");
	fscanf(fi, "%d %d", m, n);
	*maze = initializeBoard(*m, *n);
	for (i = 0; i < *m; ++i) {
		for (j = 0; j < *n; ++j) {
			fscanf(fi, "%c", &c);
			switch (c) {
			case 'S':
				*r0 = i;
				*c0 = j;
				break;
			case 'G':
			case '#':
			case '.':
				(*maze)[i][j] = c;
				break;
			default:
				--j;
				break;
			}
		}
	}
	fclose(fi);
}

void output(char **maze, int m, int n, int result) {
	int i, j;
	FILE *fo = fopen(FILE_OUT, "wt");
	fprintf(fo, "%d\n", result);
	if (result) {
		for (i = 0; i < m; ++i) {
			for (j = 0; j < n; ++j) {
				fprintf(fo, "%c", maze[i][j]);
			}
			fprintf(fo, "\n");
		}
	}
	fclose(fo);
}

int main() {
	int m, n, r0, c0;
	char **maze = NULL;
	input(&maze, &m, &n, &r0, &c0);
	int result = findPath(maze, r0, c0, m, n);
	maze[r0][c0] = 'S';
	output(maze, m, n, result);
	deleteBoard(maze, m);
	return 0;
}
