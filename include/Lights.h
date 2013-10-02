/*
 * Lights.h
 *
 *  Created on: Oct 2, 2013
 *      Author: wso277
 */

#ifndef LIGHTS_H_
#define LIGHTS_H_

#include <string>

using namespace std;

class Lights {
protected:
	string id;
	bool ready;
	bool enabled;
	float loc_x, loc_y, loc_z;
	float amb_x, amb_y, amb_z, amb_a;
	float dif_x, dif_y, dif_z, dif_a;
	float spec_x, spec_y, spec_z, spec_a;
public:
	Lights();
	Lights(string id);
	Lights(string id, bool enabled);
	void setLocation(float loc_x, float loc_y, float loc_z);
	void setAmbient(float amb_x, float amb_y, float amb_z, float amb_a);
	void setDiffuse(float dif_x, float dif_y, float dif_z, float dif_a);
	void setSpecular(float spec_x, float spec_y, float spec_z, float spec_a);
	virtual void readyLights(int index);
	void toggleLight(int index);
	virtual ~Lights();
};

#endif /* LIGHTS_H_ */
