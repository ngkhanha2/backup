/*
 * expression_collection.cpp
 *
 *  Created on: Apr 22, 2014
 *      Author: Khanh Nguyen
 */

#include "expression_collection.h"

EXPRESSION_COLLECTION* create_expression_collection() {
	EXPRESSION_COLLECTION *expression_collection = new EXPRESSION_COLLECTION;
	expression_collection->expressions = new vector<EXPRESSION*>(0);
	return expression_collection;
}

void add_expression(EXPRESSION_COLLECTION* expression_collection,
		EXPRESSION *expression) {
	if (expression == NULL) {
		return;
	}
	expression_collection->expressions->push_back(expression);
}

void add_expression_knowledge_base(EXPRESSION_COLLECTION *expression_collection,
		string *expression_string) {
	EXPRESSION *expression = create_expression(expression_string);
	add_expression(expression_collection, expression);
}

void add_expression_check(EXPRESSION_COLLECTION *expression_collection,
		string *expression_string) {
	unsigned int i = 0;
	string temp;
	while (i < expression_string->length()) {
		if ((*expression_string)[i] == '&') {
			EXPRESSION *expression = create_expression(&temp);
			add_expression(expression_collection, expression);
			temp.clear();
			++i;
		}
		temp.push_back((*expression_string)[i]);
		++i;
	}
	EXPRESSION *expression = create_expression(&temp);
	add_expression(expression_collection, expression);
}

void remove_expression(EXPRESSION_COLLECTION* expression_collection,
		EXPRESSION *expression) {
	for (unsigned int i = 0; i < expression_collection->expressions->size();
			++i) {
		if ((*(expression_collection->expressions))[i] == expression) {
			expression_collection->expressions->erase(
					expression_collection->expressions->begin() + i);
			delete_expression(expression);
			return;
		}
	}
}

void negative_expression_collecttion(
		EXPRESSION_COLLECTION *expression_collection) {
	for (unsigned int i = 0; i < expression_collection->expressions->size();
			++i) {
		negative_expression((*(expression_collection->expressions))[i]);
	}
}

void delete_expression_collection(
		EXPRESSION_COLLECTION* expression_collection) {
	for (unsigned int i = 0; i < expression_collection->expressions->size();
			++i) {
		delete_expression((*(expression_collection->expressions))[i]);
	}
	delete expression_collection->expressions;
	delete expression_collection;
}

EXPRESSION_COLLECTION* combine_expression_collections(
		EXPRESSION_COLLECTION * expression_collection_a,
		EXPRESSION_COLLECTION *expression_collection_b) {
	EXPRESSION_COLLECTION *expression_collection =
			create_expression_collection();
	for (unsigned int i = 0; i < expression_collection_a->expressions->size();
			++i) {
		expression_collection->expressions->push_back(
				copy_expression((*(expression_collection_a->expressions))[i]));
	}
	for (unsigned int i = 0; i < expression_collection_b->expressions->size();
			++i) {
		expression_collection->expressions->push_back(
				copy_expression((*(expression_collection_b->expressions))[i]));
	}
	return expression_collection;
}
