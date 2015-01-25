/*
 * tries_for_blind_search.cpp
 *
 *  Created on: Apr 1, 2014
 *      Author: khanh
 */

#include "tries_for_blind_search.h"

using namespace std;

TRIES_FOR_BLIND_SEARCH::TRIES_NODE* TRIES_FOR_BLIND_SEARCH::create_tries_node(
		int size) {
	TRIES_NODE *node = new TRIES_NODE;
	node->key = NULL;
	node->nodes = new vector<TRIES_NODE*>((unsigned int) size, NULL);
	return node;
}

TRIES_FOR_BLIND_SEARCH::TRIES_FOR_BLIND_SEARCH(int size_of_array) {
	this->root = this->create_tries_node(size_of_array);
}

int TRIES_FOR_BLIND_SEARCH::find_and_add_state_to_the_nodes(STATE *state) {
	TRIES_NODE *node = this->root;
	int index = 0;
	while (1) {
		if (state->check_position(index) == 0) {
			return 1;
		}
		if ((*node->nodes)[state->get_value(index)] != NULL) {
			node = (*node->nodes)[state->get_value(index)];
			++index;
			continue;
		}
		break;
	}
	//Add state to the node
	while (1) {
		if (state->check_position(index) == 0) {
			node->key = state;
			break;
		}
		(*node->nodes)[state->get_value(index)] = this->create_tries_node(
				node->nodes->size());
		node = (*node->nodes)[state->get_value(index)];
		++index;
	}
	return 0;
}

int TRIES_FOR_BLIND_SEARCH::find_and_add_state(STATE *state) {
	if (state == NULL) {
		return -1;
	}
	return this->find_and_add_state_to_the_nodes(state);
}

void TRIES_FOR_BLIND_SEARCH::delete_tries_node(TRIES_NODE *node) {
	if (node == NULL) {
		return;
	}
	for (unsigned int i = 0; i < node->nodes->size(); ++i) {
		this->delete_tries_node((*node->nodes)[i]);
		(*node->nodes)[i] = NULL;
	}
	if (node->key != NULL) {
		delete node->key;
	}
	delete node->nodes;
	delete node;
}

TRIES_FOR_BLIND_SEARCH::~TRIES_FOR_BLIND_SEARCH() {

	delete_tries_node(this->root);
}
