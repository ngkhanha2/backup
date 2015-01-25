/*
 * get_time.cpp
 *
 *  Created on: Apr 1, 2014
 *      Author: khanh
 */

#include "get_time.h"

float get_time() {
	return ((float) clock()) / CLOCKS_PER_SEC;
}

