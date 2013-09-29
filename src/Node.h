/*
 * Node.h
 *
 *  Created on: Sep 29, 2013
 *      Author: wso277
 */

#ifndef NODE_H_
#define NODE_H_

#include <string>
#include <list>
#include "CGFappearance.h"

using namespace std;

class Node {
private:
	string id;
	float transforms[4][4];
	list<Node*> refs;
	CGFappearance* nodeAppearance;

public:
	Node();
	virtual ~Node();
};

#endif /* NODE_H_ */
