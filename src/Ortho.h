/*
 * Ortho.h
 *
 *  Created on: Oct 1, 2013
 *      Author: wso277
 */

#ifndef ORTHO_H_
#define ORTHO_H_

#include "Camera.h"
#include <string>

namespace std {

class Ortho: public Camera {
private:
	float left, right, top, bottom;
public:
	Ortho();
	Ortho(string id);
	void setLeft(float left);
	void setRight(float right);
	void setTop(float top);
	void setBottom(float bottom);
	float getLeft();
	float getRight();
	float getTop();
	float getBottom();
	void setCamera();
	virtual ~Ortho();
};

} /* namespace std */
#endif /* ORTHO_H_ */
