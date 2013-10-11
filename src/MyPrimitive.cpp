/*
 * MyPrimitive.cpp
 *
 *  Created on: Sep 24, 2013
 *      Author: knoweat
 */

#include "MyPrimitive.h"
#include "Node.h"

MyPrimitive::MyPrimitive() : Node(){

}

MyPrimitive::~MyPrimitive() {
}

void MyPrimitive::setAppearance(string appearance) {
	Node::setAppearance(appearance);
}

void MyPrimitive::clearAppearance() {
	this->nodeAppearance = "default";
}
