#ifndef LightingScene_H
#define LightingScene_H

#include "CGFscene.h"
#include "CGFappearance.h"
#include "MyRectangle.h"
#include "MyTriangle.h"
#include "MyCylinder.h"
#include "MySphere.h"
#include "MyTorus.h"

class LightingScene : public CGFscene
{

public:
	void init();
	void display();

	CGFlight* light0;
	CGFlight* light1;
	CGFlight* light2;
	CGFlight* light3;
	CGFlight* light4;

	MyRectangle *rect;
	MyTriangle *tri;
	MyCylinder *cyl;
	MySphere *sph;
	MyTorus *tor;

	CGFappearance *house_walls_appearence, *floor_appearence, *fence_appearence,
				*door_appearence, *roof_appearence;

	~LightingScene();
};

#endif
