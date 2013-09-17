#pragma once

#include "CGFobject.h"
#include "OS.h"
#include <GL/glu.h>
class Plane {
public:
	Plane(void);
	Plane(int);
	~Plane(void);
	void draw();
	void drawUndistorted(int x_res, int y_res);
	void drawRepeated();
	void drawCentered();
	void drawWithTexLimits(double s_init, double s_end, double t_init, double t_end);
private:
	int _numDivisions; // Number of triangles that constitute rows/columns
};

