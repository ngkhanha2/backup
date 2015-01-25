/*
 * blind_search.cpp
 *
 *  Created on: Apr 1, 2014
 *      Author: khanh
 */

#include "blind_search.h"

using namespace std;

BLIND_SEARCH::BLIND_SEARCH(STATE *source_state) {
	this->source_state = new STATE(source_state);
	this->destination_states = new vector<STATE*>();
	this->tries = new TRIES_FOR_BLIND_SEARCH(
			source_state->get_width() * source_state->get_height());
	this->tries->find_and_add_state(this->source_state);
	this->slide = new SLIDE();
}

void BLIND_SEARCH::output(ostream &stream) {
	STATE *destination_state = NULL;
	;
	for (unsigned int i = 0; i < this->destination_states->size(); ++i) {
		if ((*this->destination_states)[i]->get_previous_state() != NULL) {
			destination_state = (*this->destination_states)[i];
			break;
		}
	}

	if (destination_state == NULL) {
		stream << "No solution.";
		return;
	}

	stack<STATE*> *output_stack = new stack<STATE*>();
	output_stack->push(destination_state);
	bool pushing = true;
	while (!output_stack->empty()) {
		STATE *state = output_stack->top();
		if (pushing == false) {
			if (state->get_move_direction() != 0) {
				stream << "(" << state->get_zero_position_x() << ", "
						<< state->get_zero_position_y() << ") "
						<< state->get_move_direction() << endl;
			}
			output_stack->pop();
		} else {
			if (state->get_previous_state() == NULL) {
				pushing = false;
			} else {
				output_stack->push(state->get_previous_state());
			}
		}
	}
	delete output_stack;
}

void BLIND_SEARCH::add_destination_state(STATE *state) {
	STATE *new_state = new STATE(state);
	this->destination_states->push_back(new_state);
}

BLIND_SEARCH::~BLIND_SEARCH() {
	delete this->tries;
	for (unsigned int i = 0; i < this->destination_states->size(); ++i) {
		delete (*this->destination_states)[i];
	}
	delete this->destination_states;
}

int BLIND_SEARCH::check(STATE *state, int move_direction) {
	if (this->slide->slide(state, move_direction) == 0) {
		return -1;
	}
	if (this->tries->find_and_add_state(state) != 0) {
		return -1;
	}
	for (unsigned int i = 0; i < this->destination_states->size(); ++i) {
		if ((*this->destination_states)[i]->compare(state) == 0) {
			(*this->destination_states)[i]->set_previous_state(
					state->get_previous_state());
			(*this->destination_states)[i]->set_move_direction(
					state->get_move_direction());
			return 1;
		}
	}
	return 0;
}
