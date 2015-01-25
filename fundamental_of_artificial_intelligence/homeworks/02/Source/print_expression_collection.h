/*
 * print_expression_collection.h
 *
 *  Created on: Apr 22, 2014
 *      Author: Khanh Nguyen
 */

#ifndef PRINT_EXPRESSION_COLLECTION_H_
#define PRINT_EXPRESSION_COLLECTION_H_

#include <iostream>

#include "expression_collection.h"
#include "print_expression.h"

using namespace std;

void print_expression_collection(ostream &stream,
		EXPRESSION_COLLECTION *expression_collection, char operator_char);

#endif /* PRINT_EXPRESSION_COLLECTION_H_ */
