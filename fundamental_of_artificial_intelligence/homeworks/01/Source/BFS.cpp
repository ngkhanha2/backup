/*
 * BFS.cpp
 *
 *  Created on: Apr 1, 2014
 *      Author: khanh
 */

#include "BFS.h"

BFS::BFS(STATE *source_state) :
		BLIND_SEARCH(source_state) {

}

double BFS::solve(double time_limit) {
	for (unsigned int i = 0; i < this->destination_states->size(); ++i) {
		if ((*this->destination_states)[i]->compare(source_state) == 0) {
			return 0;
		}
	}

	queue<STATE*> *bfs_queue = new queue<STATE*>();
	bfs_queue->push(this->source_state);

	double start_time = get_time();
	double time = get_time();
	while (!bfs_queue->empty()) {
		STATE *state = bfs_queue->front();
		bfs_queue->pop();
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
			bfs_queue->push(new_state);
		}
		time = get_time() - start_time;
		if (time_limit != NO_TIME_LIMIT && time > time_limit) {
			break;
		}
	}
	end: delete bfs_queue;
	return time;
}

