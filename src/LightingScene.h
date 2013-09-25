#ifndef LightingScene_H
#define LightingScene_H

#include "CGFscene.h"
#include "CGFappearance.h"
#include "MyRectangle.h"
#include "MyTriangle.h"

class LightingScene : public CGFscene
{

public:
	void init();
	void display();

	CGFlight* light0;
	CGFlight* light1;
	CGFlight* light2;
	CGFlight* light3;

	MyRectangle *rect;
	MyTriangle *tri;

	CGFappearance *house_walls_appearence, *floor_appearence, *fence_appearence,
				*door_appearence, *roof_appearence;

	~LightingScene();
};

#endif
