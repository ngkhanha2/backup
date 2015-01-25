/*
 * main.cpp
 *
 *  Created on: Apr 1, 2014
 *      Author: khanh
 */

#include <fstream>
#include <iostream>
#include <vector>

#include "BFS.h"
#include "DFS.h"
#include "blind_search.h"

#define TIME_LIMIT 20

#define USE_BFS '1'
#define USE_DFS '2'

using namespace std;

void solve(char mode, char *input_file, char *output_file) {
	if (mode < USE_BFS || mode > USE_DFS) {
		return;
	}

	ifstream fi(input_file);
	int n;
	fi >> n;
	STATE *source_state = new STATE(n, n);
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < n; ++j) {
			int temp;
			fi >> temp;
			source_state->set_value(i, j, temp);
		}
	}
	fi.close();

	BLIND_SEARCH *search = NULL;
	switch (mode) {
	case USE_BFS:
		search = new BFS(source_state);
		break;
	case USE_DFS:
		search = new DFS(source_state);
		break;
	}

	STATE *destination_state = new STATE(n, n);
	n *= n;
	for (int i = 0; i < n; ++i) {
		destination_state->set_value(i, i);
	}
	search->add_destination_state(destination_state);

	for (int i = 1; i <= n; ++i) {
		destination_state->set_value(i - 1, i % n);
	}
	search->add_destination_state(destination_state);
	double time = search->solve(TIME_LIMIT);

	ofstream fo(output_file);
	search->output(fo);
	fo.close();

	delete search;
	cout << time;
}

int main(int argc, char **argv) {
	if (argc != 4) {
		return 0;
	}
	solve(argv[1][0], argv[2], argv[3]);
	return 0;
}
