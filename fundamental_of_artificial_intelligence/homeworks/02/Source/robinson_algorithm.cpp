/*
 * robinson_algorithm.cpp
 *
 *  Created on: Apr 22, 2014
 *      Author: Khanh Nguyen
 */

#include "robinson_algorithm.h"

using namespace std;

void robinson_algorithm(ostream &stream, EXPRESSION_COLLECTION *clause) {
	while (!0) {
		int i = (int) clause->expressions->size() - 1;
		while (i > 0) {
			int j = i - 1;
			unsigned int count = 0;
			while (j >= 0) {
				EXPRESSION *expression_i = (*(clause->expressions))[i];
				EXPRESSION *expression_j = (*(clause->expressions))[j];
				count = duality_clauses_exist(expression_j, expression_i);
				if (count != 0) {
					if (count == expression_i->variables->size()
							&& count == expression_j->variables->size()) {
						stream << "True";
						return;
					}
					delete_duality_clauses(expression_i, expression_j);
					if (expression_i->variables->size() > 0
							&& expression_j->variables->size() > 0) {
						(*(clause->expressions))[i] = combine_expression(
								expression_i, expression_j);
						remove_expression(clause, expression_i);
						remove_expression(clause, expression_j);
					} else {
						if (expression_i->variables->size() == 0) {
							remove_expression(clause, expression_i);
						}
						if (expression_j->variables->size() == 0) {
							remove_expression(clause, expression_j);
						}
					}
					print_expression_collection(stream, clause, '|');
					stream << endl;
					break;
				}
				--j;
			}
			if (count != 0) {
				break;
			}
			--i;
		}
		if (i == 0) {
			stream << "False";
			return;
		}
	}
}

