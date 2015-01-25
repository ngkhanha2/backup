/*
 * tries_for_blind_search.h
 *
 *  Created on: Apr 1, 2014
 *      Author: khanh
 */

#ifndef TRIES_FOR_BLIND_SEARCH_H_
#define TRIES_FOR_BLIND_SEARCH_H_

#include <vector>
#include <stack>

#include "state.h"

using namespace std;

class TRIES_FOR_BLIND_SEARCH {
private:
	typedef struct TRIES_NODE {
		vector<struct TRIES_NODE*> *nodes;
		STATE *key;
	} TRIES_NODE;

	TRIES_NODE* create_tries_node(int size);

	int find_and_add_state_to_the_nodes(STATE *state);

	void delete_tries_node(TRIES_NODE *node);

	TRIES_NODE *root;
public:
	TRIES_FOR_BLIND_SEARCH(int size_of_array);

	int find_and_add_state(STATE *state);

	~TRIES_FOR_BLIND_SEARCH();
};

#endif /* TRIES_FOR_BLIND_SEARCH_H_ */
