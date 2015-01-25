/*
 * variable.cpp
 *
 *  Created on: Apr 22, 2014
 *      Author: Khanh Nguyen
 */

#include "variable.h"

using namespace std;

VARIABLE* create_variable(string *variable_string, char negative) {
	VARIABLE *variable = new VARIABLE;
	variable->negative = negative;
	variable->value = new string(*variable_string);
	return variable;
}

void negative_variable(VARIABLE *variable) {
	variable->negative ^= 1;
}

VARIABLE* copy_variable(VARIABLE *variable) {
	VARIABLE *new_variable = new VARIABLE;
	new_variable->negative = variable->negative;
	new_variable->value = new string(*variable->value);
	return new_variable;
}

void delete_variable(VARIABLE *variable) {
	delete variable->value;
	delete variable;
}
