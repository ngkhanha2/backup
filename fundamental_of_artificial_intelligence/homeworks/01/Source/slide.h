/*
 * slide.h
 *
 *  Created on: Apr 1, 2014
 *      Author: khanh
 */

#ifndef SLIDE_H_
#define SLIDE_H_

#include <cstdlib>

#include "state.h"

class SLIDE {
private:
	typedef struct {
		int delta_x;
		int delta_y;
		char sign;
	} MOVE_DIRECTION;

	vector<MOVE_DIRECTION> *move_directions = NULL;

	MOVE_DIRECTION create_direction(int delta_x, int delta_y, char sign);

	void initialize();
public:
	SLIDE();

	int directions();

	int slide(STATE *state, int direction);

	~SLIDE();
};

#endif /* SLIDE_H_ */
