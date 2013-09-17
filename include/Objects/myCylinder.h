#ifndef MY_CYLINDER
#define MY_CYLINDER

#include "CGF/CGFobject.h"
#include "utils.h"
#include <vector>

using namespace std;

class myCylinder: public CGFobject {
	int slices;
	int stacks;
	bool smooth;
	double *xp;
	double *yp;
	double *zp;
public:
	myCylinder(int slices, int stacks, bool smooth);
	~myCylinder();
	void draw();
	void drawFlat();
};

#endif
