/*
 * expression.cpp
 *
 *  Created on: Apr 22, 2014
 *      Author: Khanh Nguyen
 */

#include "expression.h"

using namespace std;

int is_operator(char chr) {
	return (chr == '&' || chr == '|');
}

int variable_exist(EXPRESSION *expression, string *variable_string) {
	for (unsigned int i = 0; i < expression->variables->size(); ++i) {
		if ((*(expression->variables))[i]->value->compare(*variable_string)
				== 0) {
			return i;
		}
	}
	return -1;
}

EXPRESSION* create_expression(string *expression_string) {
	EXPRESSION *expression = new EXPRESSION;
	expression->variables = new vector<VARIABLE*>();
	for (unsigned int i = 0; i < expression_string->length();) {
		string variable_string;
		char negative = 0;
		if ((*expression_string)[i] == '~') {
			negative = 1;
			++i;
		}
		unsigned int j = i;
		while (j < expression_string->length()
				&& is_operator((*expression_string)[j]) == 0) {
			variable_string.push_back((*expression_string)[j]);
			++j;
		}
		int p = variable_exist(expression, &variable_string);
		if (p >= 0) {
			if ((*(expression->variables))[p]->negative != negative) {
				delete_expression(expression);
				expression = NULL;
				break;
			}
		} else {
			expression->variables->push_back(
					create_variable(&variable_string, negative));
			i = j + 1;
		}
	}
	return expression;
}

VARIABLE* find_variable(EXPRESSION *expression, string *variable_string) {
	for (unsigned int i = 0; i < expression->variables->size(); ++i) {
		if ((*(expression->variables))[i]->value->compare(*variable_string)
				== 0) {
			return (*(expression->variables))[i];
		}
	}
	return NULL;
}

void remove_variable(EXPRESSION *expression, VARIABLE *variable) {
	for (unsigned int i = 0; i < expression->variables->size(); ++i) {
		if ((*(expression->variables))[i] == variable) {
			expression->variables->erase(expression->variables->begin() + i);
			delete_variable(variable);
			return;
		}
	}
}

void negative_expression(EXPRESSION *expression) {
	for (unsigned int i = 0; i < expression->variables->size(); ++i) {
		negative_variable((*(expression->variables))[i]);
	}
}

void delete_expression(EXPRESSION *expression) {
	for (unsigned int i = 0; i < expression->variables->size(); ++i) {
		delete_variable((*(expression->variables))[i]);
	}
	delete expression->variables;
	delete expression;
}

EXPRESSION* copy_expression(EXPRESSION *expression) {
	EXPRESSION *new_expression = new EXPRESSION;
	new_expression->variables = new vector<VARIABLE*>();
	for (unsigned int i = 0; i < expression->variables->size(); ++i) {
		new_expression->variables->push_back(
				copy_variable((*(expression->variables))[i]));
	}
	return new_expression;
}

EXPRESSION* combine_expression(EXPRESSION *expression_a,
		EXPRESSION *expression_b) {
	EXPRESSION *expression = new EXPRESSION;
	expression->variables = new vector<VARIABLE*>();
	for (unsigned int i = 0; i < expression_a->variables->size(); ++i) {
		expression->variables->push_back(
				copy_variable((*(expression_a->variables))[i]));
	}
	for (unsigned int i = 0; i < expression_b->variables->size(); ++i) {
		expression->variables->push_back(
				copy_variable((*(expression_b->variables))[i]));
	}
	return expression;
}
