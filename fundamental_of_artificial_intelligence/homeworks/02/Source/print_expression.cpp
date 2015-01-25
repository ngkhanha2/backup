/*
 * print_expression.cpp
 *
 *  Created on: Apr 22, 2014
 *      Author: Khanh Nguyen
 */

#include "print_expression.h"

using namespace std;

void print_expression(ostream &stream, EXPRESSION *expression,
		char operator_char) {
	unsigned int n = expression->variables->size() - 1;
	for (unsigned int i = 0; i < n; ++i) {
		print_variable(stream, (*(expression->variables))[i]);
		stream << ' ' << operator_char << ' ';
	}
	print_variable(stream, (*(expression->variables))[n]);
}

