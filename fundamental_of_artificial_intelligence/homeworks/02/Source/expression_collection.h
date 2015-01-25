/*
 * expression_collection.h
 *
 *  Created on: Apr 22, 2014
 *      Author: Khanh Nguyen
 */

#ifndef EXPRESSION_COLLECTION_H_
#define EXPRESSION_COLLECTION_H_

#include <string>
#include <vector>

#include "expression.h"

using namespace std;

typedef struct {
	vector<EXPRESSION*> *expressions;
} EXPRESSION_COLLECTION;

EXPRESSION_COLLECTION* create_expression_collection();

void add_expression_knowledge_base(EXPRESSION_COLLECTION *expression_collection,
		string *expression_string);

void add_expression_check(EXPRESSION_COLLECTION *expression_collection,
		string *expression_string);

void remove_expression(EXPRESSION_COLLECTION* expression_collection,
		EXPRESSION *expression);

void negative_expression_collecttion(
		EXPRESSION_COLLECTION *expression_collection);

void delete_expression_collection(EXPRESSION_COLLECTION* expression_collection);

EXPRESSION_COLLECTION* combine_expression_collections(
		EXPRESSION_COLLECTION * expression_collection_a,
		EXPRESSION_COLLECTION *expression_collection_b);

#endif /* EXPRESSION_COLLECTION_H_ */
