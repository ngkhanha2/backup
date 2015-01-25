/*
 * expression.h
 *
 *  Created on: Apr 22, 2014
 *      Author: Khanh Nguyen
 */

#ifndef EXPRESSION_H_
#define EXPRESSION_H_

#include <string>
#include <vector>

#include "variable.h"

using namespace std;

typedef struct {
	vector<VARIABLE*> *variables;
} EXPRESSION;

EXPRESSION* create_expression(string *expression_string);

void negative_expression(EXPRESSION *expression);

VARIABLE* find_variable(EXPRESSION *expression, string *variable_string);

void remove_variable(EXPRESSION *expression, VARIABLE *variable);

void delete_expression(EXPRESSION *expression);

EXPRESSION* copy_expression(EXPRESSION *expression);

EXPRESSION* combine_expression(EXPRESSION *expression_a,
		EXPRESSION *expression_b);
#endif /* EXPRESSION_H_ */
