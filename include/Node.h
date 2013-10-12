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
#include <map>
#include <stack>

using namespace std;

class MyPrimitive;

/**
 * super class containing all the information about one node, including appearance, children, and primitives
 */
class Node {
protected:

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
	virtual void setAppearance(string appearance);
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
	void processNode(stack<string> apps_stack);
	void drawPrims(stack<string> apps_stack);
};

#endif /* NODE_H_ */
