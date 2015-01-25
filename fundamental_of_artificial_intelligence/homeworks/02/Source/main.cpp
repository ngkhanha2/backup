/*
 * main.cpp
 *
 *  Created on: Apr 22, 2014
 *      Author: Khanh Nguyen
 */

#include <iostream>
#include <fstream>

#include "expression.h"
#include "expression_collection.h"
#include "print_expression_collection.h"
#include "robinson_algorithm.h"

#define KB "KB"
#define ENDKB "ENDKB"

#define INPUT_FILE "input.txt"
#define OUTPUT_FILE "1212171.txt"

using namespace std;

EXPRESSION_COLLECTION *knowledge_base;
EXPRESSION_COLLECTION *check_clause;
EXPRESSION_COLLECTION *main_clause;

void initialize() {
	knowledge_base = create_expression_collection();
	check_clause = create_expression_collection();
}

void input() {
	ifstream fi(INPUT_FILE);
	string clause;
	while (!0) {
		clause.clear();
		getline(fi, clause);
		if (clause.compare(KB) == 0) {
			continue;
		}
		if (clause.compare(ENDKB) == 0) {
			break;
		}
		add_expression_knowledge_base(knowledge_base, &clause);
		clause.clear();
	}
	while (!fi.eof()) {
		clause.clear();
		getline(fi, clause);
		add_expression_check(check_clause, &clause);
	}
	fi.close();
}

void solve() {
	ofstream fo(OUTPUT_FILE);
	print_expression_collection(fo, check_clause, '^');
	fo << endl;
	negative_expression_collecttion(check_clause);
	main_clause = combine_expression_collections(knowledge_base, check_clause);
	print_expression_collection(fo, main_clause, '|');
	fo << endl;
	robinson_algorithm(fo, main_clause);
	fo.close();
	delete_expression_collection(main_clause);
	delete_expression_collection(check_clause);
	delete_expression_collection(knowledge_base);
}

int main() {
	initialize();
	input();
	solve();
	return 0;
}
