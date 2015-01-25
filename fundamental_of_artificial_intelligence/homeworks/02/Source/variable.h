/*
 * variable.h
 *
 *  Created on: Apr 22, 2014
 *      Author: Khanh Nguyen
 */

#ifndef VARIABLE_H_
#define VARIABLE_H_

#include <string>

using namespace std;

typedef struct {
	string *value;
	char negative;
} VARIABLE;

VARIABLE* create_variable(string *variable_string, char negative);

void negative_variable(VARIABLE *variable);

void delete_variable(VARIABLE *variable);

VARIABLE* copy_variable(VARIABLE *variable);

#endif /* VARIABLE_H_ */
