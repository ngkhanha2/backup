/*
 * state.h
 *
 *  Created on: Apr 1, 2014
 *      Author: khanh
 */

#ifndef STATE_H_
#define STATE_H_

#include <vector>
#include <cstdlib>

using namespace std;

class STATE {
private:
	int width;

	int height;

	vector<int> *value;

	STATE *previous_state;

	int zero_position_x;

	int zero_position_y;

	char move_direction;
public:
	STATE(int width, int height);

	STATE(STATE *source_state);

	int get_zero_position_x();

	int get_zero_position_y();

	int get_width();

	int get_height();

	int get_value(int position_x, int position_y);

	int get_value(int position);

	STATE* get_previous_state();

	char get_move_direction();

	int check_position(int position_x, int position_y);

	int check_position(int index);

	void set_previous_state(STATE *state);

	void set_value(int position_x, int position_y, int value);

	void set_value(int index, int value);

	void set_move_direction(char value);

	int compare(STATE *state);

	~STATE();
};

#endif /* STATE_H_ */
