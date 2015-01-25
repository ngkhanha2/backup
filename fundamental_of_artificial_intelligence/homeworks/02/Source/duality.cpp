/*
 * duality.cpp
 *
 *  Created on: Apr 22, 2014
 *      Author: Khanh Nguyen
 */

#include "duality.h"

using namespace std;

int duality_clauses_exist(EXPRESSION *source, EXPRESSION *pattern) {
	int count = 0;
	for (unsigned int i = 0; i < pattern->variables->size(); ++i) {
		VARIABLE *variable = find_variable(source,
				(*(pattern->variables))[i]->value);
		if (variable != NULL
				&& variable->negative != (*(pattern->variables))[i]->negative) {
			++count;
		}
	}
	return count;
}

void delete_duality_clauses(EXPRESSION *source, EXPRESSION *pattern) {
	for (unsigned int i = 0; i < pattern->variables->size(); ++i) {
		VARIABLE *variable = find_variable(source,
				(*(pattern->variables))[i]->value);
		if (variable != NULL
				&& variable->negative != (*(pattern->variables))[i]->negative) {
			remove_variable(source, variable);
			remove_variable(pattern, (*(pattern->variables))[i]);
			--i;
		}
	}
}
