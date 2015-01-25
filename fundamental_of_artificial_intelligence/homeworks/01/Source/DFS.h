/*
 * DFS.h
 *
 *  Created on: Apr 1, 2014
 *      Author: khanh
 */

#ifndef DFS_H_
#define DFS_H_

#include <stack>
#include <climits>

#include "get_time.h"
#include "blind_search.h"

using namespace std;

class DFS: public BLIND_SEARCH {
private:
public:
	DFS(STATE *source_state);

	virtual double solve(double time_limit);
};

#endif /* DFS_H_ */
