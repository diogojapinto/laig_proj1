/*
 * Camera.h
 *
 *  Created on: Oct 1, 2013
 *      Author: wso277
 */

#ifndef CAMERA_H_
#define CAMERA_H_

#include <string>

using namespace std;

class Camera {
private:
	string id;
	float near;
	float far;

public:
	Camera();
	virtual ~Camera();
};


#endif /* CAMERA_H_ */
