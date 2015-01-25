/*
 * duality.h
 *
 *  Created on: Apr 22, 2014
 *      Author: Khanh Nguyen
 */

#ifndef DUALITY_H_
#define DUALITY_H_

#include "variable.h"
#include "expression.h"
#include "expression_collection.h"

int duality_clauses_exist(EXPRESSION *source, EXPRESSION *pattern);

void delete_duality_clauses(EXPRESSION *source, EXPRESSION *pattern);

#endif /* DUALITY_H_ */
