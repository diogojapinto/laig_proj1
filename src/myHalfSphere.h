#ifndef MY_HALFSPHERE
#define MY_HALFSPHERE

#include "CGF/CGFobject.h"
#include "utils.h"

class myHalfSphere: public CGFobject {
	int slices;
	int stacks;
	bool smooth;
	double *x1p;
	double *y1p;
	double *z1p;
	double *x2p;
	double *y2p;
	double *z2p;
	double *x3p;
	double *y3p;
	double *z3p;
	double *x4p;
	double *y4p;
	double *z4p;
public:
	myHalfSphere(int slices, int stacks, bool smooth);
	void draw();
};

#endif
