/*
 * MySphere.h
 *
 *  Created on: Sep 25, 2013
 *      Author: wso277
 */

#ifndef MYSPHERE_H_
#define MYSPHERE_H_

#include "MyPrimitive.h"

class MySphere: public MyPrimitive {
public:
	MySphere();
	virtual ~MySphere();
	void draw();
};

#endif /* MYSPHERE_H_ */
