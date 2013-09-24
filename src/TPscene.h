#ifndef TPSCENE_H
#define TPSCENE_H

#include "CGFscene.h"
#include "MyRectangle.h"
#include "MyTriangle.h"

class TPscene: public CGFscene {
	CGFappearance *house_walls_appearence, *floor_appearence, *fence_appearence,
			*door_appearence, *roof_appearence;


	// Initialize primitives

	MyRectangle rect;
	MyTriangle tri;
public:
	void init();
	void display();
};

#endif
