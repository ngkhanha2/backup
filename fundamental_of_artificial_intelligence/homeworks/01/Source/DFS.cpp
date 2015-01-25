/*
 * DFS.cpp
 *
 *  Created on: Apr 1, 2014
 *      Author: khanh
 */

#include "DFS.h"

DFS::DFS(STATE *source_state) :
		BLIND_SEARCH(source_state) {
}

double DFS::solve(double time_limit) {
	for (unsigned int i = 0; i < this->destination_states->size(); ++i) {
		if ((*this->destination_states)[i]->compare(source_state) == 0) {
			return 0;
		}
	}

	stack<STATE*> *dfs_stack = new stack<STATE*>();
	dfs_stack->push(source_state);

	double start_time = get_time();
	double time = 0;
	while (!dfs_stack->empty()) {
		STATE *state = dfs_stack->top();
		dfs_stack->pop();

		for (int i = 0; i < this->slide->directions(); ++i) {
			STATE *new_state = new STATE(state);
			new_state->set_previous_state(state);
			int check = this->check(new_state, i);
			switch (check) {
			case -1:
				delete new_state;
				continue;
			case 1:
				goto end;
			}
			dfs_stack->push(new_state);
		}
		time = get_time() - start_time;
		if (time_limit != NO_TIME_LIMIT && time > time_limit) {
			break;
		}
	}
	end: delete dfs_stack;
	return time;
}
