/*
 * slide.cpp
 *
 *  Created on: Apr 1, 2014
 *      Author: khanh
 */

#include "slide.h"

SLIDE::SLIDE() {
	this->initialize();
}

void SLIDE::initialize() {
	this->move_directions = new vector<MOVE_DIRECTION>();
	move_directions->push_back(this->create_direction(0, -1, 'E'));
	move_directions->push_back(this->create_direction(0, 1, 'W'));
	move_directions->push_back(this->create_direction(-1, 0, 'S'));
	move_directions->push_back(this->create_direction(1, 0, 'N'));
}

int SLIDE::directions() {
	return this->move_directions->size();
}

int SLIDE::slide(STATE *state, int direction) {
	if (state == NULL || direction < 0
			|| direction >= (int) this->move_directions->size()) {
		return 0;
	}
	int opx = state->get_zero_position_x();
	int opy = state->get_zero_position_y();
	int npx = opx + (*move_directions)[direction].delta_x;
	int npy = opy + (*move_directions)[direction].delta_y;
	if (state->check_position(npx, npy) == 0) {
		return 0;
	}
	int value = state->get_value(npx, npy);
	state->set_value(opx, opy, value);
	state->set_value(npx, npy, 0);
	state->set_move_direction((*move_directions)[direction].sign);
	return 1;
}

SLIDE::MOVE_DIRECTION SLIDE::create_direction(int delta_x, int delta_y,
		char sign) {
	MOVE_DIRECTION direction;
	direction.delta_x = delta_x;
	direction.delta_y = delta_y;
	direction.sign = sign;
	return direction;
}

SLIDE::~SLIDE() {
	delete this->move_directions;
}
