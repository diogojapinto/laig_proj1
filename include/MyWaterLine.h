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
#include "Appearance.h"

using namespace std;

class MyWaterLine: public Plane {
	CGFshader shader;
	float prev_delta;
	float delta;
	Appearance height, text;
public:
	MyWaterLine();
	MyWaterLine(string heightmap, string texturemap, string vert_shader, string frag_shader);
	virtual ~MyWaterLine();
	virtual void setAppearance(string appearance);
	virtual void draw();
	void update(int i);
};

#endif /* MYWATERLINE_H_ */
