/*
 * Point.cpp
 *
 *  Created on: Oct 22, 2013
 *      Author: wso277
 */

#include "Point.h"

Point::Point() {
	// TODO Auto-generated constructor stub

}

Point::Point(float x, float y, float z) {
	this->x = x;
	this->y = y;
	this->z = z;
}

float Point::getX() {
	return x;
}

float Point::getY() {
	return y;
}

float Point::getZ() {
	return z;
}

Point::~Point() {
	// TODO Auto-generated destructor stub
}

