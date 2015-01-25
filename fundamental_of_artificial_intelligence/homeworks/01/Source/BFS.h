/*
 * BFS.h
 *
 *  Created on: Apr 1, 2014
 *      Author: khanh
 */

#ifndef BFS_H_
#define BFS_H_

#include <queue>
#include <climits>

#include "get_time.h"
#include "blind_search.h"

using namespace std;

class BFS: public BLIND_SEARCH {
public:
	BFS(STATE *source_state);

	virtual double solve(double time_limit);
};

#endif /* BFS_H_ */
