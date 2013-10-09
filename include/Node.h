/*
 * Node.h
 *
 *  Created on: Sep 29, 2013
 *      Author: wso277
 */

#ifndef NODE_H_
#define NODE_H_

#include <string>
#include <vector>
#include "Appearance.h"

using namespace std;

class Node;

class MyPrimitive;

class Node {
private:
	string id;
	float transforms[16];
	vector<string> refs;
	string nodeAppearance;
	vector<MyPrimitive *> prims;

public:
	Node();
	Node(string id);
	Node(string id, float transforms[16]);
	void addRef(string ref);
	void setAppearance(string appearance);
	void setTransform(float transforms[16]);
	void resetTransform();
	void addTranslate(float x, float y, float z);
	void addScale(float x, float y, float z);
	void addRotation(float angle, char axis);
	void addPrimitive(MyPrimitive *prim);
	const float* getTransform();
	Appearance *getAppearance();
	vector<string> getRefs();
	string getId();
	virtual ~Node();
};

#endif /* NODE_H_ */
