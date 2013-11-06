/*
 * MyWaterLine.h
 *
 *  Created on: Nov 6, 2013
 *      Author: ei11120
 */

#ifndef MYWATERLINE_H_
#define MYWATERLINE_H_

#include "MyPrimitive.h"
#include "CGFshader.h"
#include <string>

using namespace std;

class MyWaterLine: public MyPrimitive {
	CGFshader shader;
	string heightmap;
	string bumpmap;
public:
	MyWaterLine();
	MyWaterLine(string heightmap, string bumpmap, string vert_shader, string frag_shader);
	virtual ~MyWaterLine();
	virtual void setAppearance(string appearance);
	virtual void draw();
};

#endif /* MYWATERLINE_H_ */
