/*
 * robinson_algorithm.h
 *
 *  Created on: Apr 22, 2014
 *      Author: Khanh Nguyen
 */

#ifndef ROBINSON_ALGORITHM_H_
#define ROBINSON_ALGORITHM_H_

#include <iostream>

#include "expression_collection.h"
#include "print_expression_collection.h"
#include "duality.h"

using namespace std;

void robinson_algorithm(ostream &stream, EXPRESSION_COLLECTION *clause);

#endif /* ROBINSON_ALGORITHM_H_ */
