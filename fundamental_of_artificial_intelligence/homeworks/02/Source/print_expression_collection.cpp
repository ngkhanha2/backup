/*
 * print_expression_collection.cpp
 *
 *  Created on: Apr 22, 2014
 *      Author: Khanh Nguyen
 */

#include "print_expression_collection.h"

using namespace std;

void print_expression_collection(ostream &stream,
		EXPRESSION_COLLECTION *expression_collection, char operator_char) {
	unsigned int n = expression_collection->expressions->size() - 1;
	for (unsigned int i = 0; i < n; ++i) {
		print_expression(stream, (*(expression_collection->expressions))[i],
				operator_char);
		stream << ", ";
	}
	print_expression(stream, (*(expression_collection->expressions))[n],
			operator_char);
}

