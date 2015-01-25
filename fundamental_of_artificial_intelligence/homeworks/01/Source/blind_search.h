/*
 * blind_search.h
 *
 *  Created on: Apr 1, 2014
 *      Author: khanh
 */

#ifndef BLIND_SEARCH_H_
#define BLIND_SEARCH_H_

#include <vector>
#include <stack>
#include <iostream>

#include "state.h"
#include "slide.h"
#include "tries_for_blind_search.h"

#define NO_TIME_LIMIT 0

using namespace std;

class BLIND_SEARCH {
protected:
	STATE *source_state;

	vector<STATE*> *destination_states;

	SLIDE *slide;

	TRIES_FOR_BLIND_SEARCH *tries;

	int check(STATE *state, int move_direction);
public:
	BLIND_SEARCH(STATE *source_state);

	virtual double solve(double time_limit) = 0;

	void output(ostream &stream);

	void add_destination_state(STATE *state);

	virtual ~BLIND_SEARCH();
};

#endif /* BLIND_SEARCH_H_ */
