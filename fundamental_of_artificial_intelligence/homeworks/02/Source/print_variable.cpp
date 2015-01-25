/*
 * print_variable.cpp
 *
 *  Created on: Apr 22, 2014
 *      Author: Khanh Nguyen
 */

#include "print_variable.h"

void print_variable(ostream &stream, VARIABLE *variable) {
	if (variable->negative){
		stream << '~';
	}
	stream << *variable->value;
}

