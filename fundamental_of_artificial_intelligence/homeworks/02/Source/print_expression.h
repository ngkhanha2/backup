/*
 * print_expression.h
 *
 *  Created on: Apr 22, 2014
 *      Author: Khanh Nguyen
 */

#ifndef PRINT_EXPRESSION_H_
#define PRINT_EXPRESSION_H_

#include <iostream>

#include "expression.h"
#include "print_variable.h"

using namespace std;

void print_expression(ostream &stream, EXPRESSION *expression,
		char operator_char);

#endif /* PRINT_EXPRESSION_H_ */
