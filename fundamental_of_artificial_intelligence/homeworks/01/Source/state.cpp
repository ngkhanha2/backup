/*
 * state.cpp
 *
 *  Created on: Apr 1, 2014
 *      Author: khanh
 */

#include "state.h"

using namespace std;

STATE::STATE(int width, int height) {
	this->width = width;
	this->height = height;
	this->value = new vector<int>(this->width * this->height);
	this->previous_state = NULL;
	this->zero_position_x = 0;
	this->zero_position_y = 0;
	this->move_direction = 0;
}

STATE::STATE(STATE *source_state) {
	this->width = source_state->width;
	this->height = source_state->height;
	this->previous_state = source_state->previous_state;
	this->move_direction = 0;
	this->value = new vector<int>();
	for (unsigned int i = 0; i < source_state->value->size(); ++i) {
		this->value->push_back((*source_state->value)[i]);
	}
	this->zero_position_x = source_state->zero_position_x;
	this->zero_position_y = source_state->zero_position_y;
}

void STATE::set_previous_state(STATE *state) {
	this->previous_state = state;
}

STATE* STATE::get_previous_state() {
	return this->previous_state;
}

int STATE::get_width() {
	return this->width;
}

int STATE::get_height() {
	return this->height;
}

int STATE::get_zero_position_x() {
	return this->zero_position_x;
}

int STATE::get_zero_position_y() {
	return this->zero_position_y;
}

void STATE::set_value(int position_x, int position_y, int value) {
	if (this->check_position(position_x, position_y) == 0) {
		return;
	}
	int position = position_x * this->width + position_y;
	(*this->value)[position] = value;
	if (value == 0) {
		this->zero_position_x = position_x;
		this->zero_position_y = position_y;
	}
}

void STATE::set_value(int index, int value) {
	if (this->check_position(index) == 0) {
		return;
	}
	(*this->value)[index] = value;
	if (value == 0) {
		this->zero_position_x = index / this->width;
		this->zero_position_y = index % this->width;
	}
}

int STATE::get_value(int position_x, int position_y) {
	if (this->check_position(position_x, position_y) == 0) {
		return -1;
	}
	return (*this->value)[position_x * this->width + position_y];
}

int STATE::get_value(int index) {
	if (this->check_position(index) == 0) {
		return -1;
	}
	return (*this->value)[index];
}

int STATE::check_position(int position_x, int position_y) {
	if (position_x < 0 || position_x >= this->height || position_y < 0
			|| position_y >= this->width) {
		return 0;
	}
	return 1;
}

int STATE::check_position(int index) {
	if (index < 0 || index >= (int) this->value->size()) {
		return 0;
	}
	return 1;
}

char STATE::get_move_direction() {
	return this->move_direction;
}

void STATE::set_move_direction(char value) {
	this->move_direction = value;
}

STATE::~STATE() {
	delete this->value;
	this->previous_state = NULL;
}

int STATE::compare(STATE *state) {
	for (unsigned int i = 0; i < this->value->size(); ++i) {
		if ((*this->value)[i] != (*state->value)[i]) {
			return 1;
		}
	}
	return 0;
}
