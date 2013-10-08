/*
 * Appearance.h
 *
 *  Created on: Oct 8, 2013
 *      Author: wso277
 */

#ifndef APPEARANCE_H_
#define APPEARANCE_H_

#include <string>
#include "CGFappearance.h"

using namespace std;

class Appearance: public CGFappearance {
protected:
	string id;
	float emi_x, emi_y, emi_z, emi_a;
public:
	Appearance();
	Appearance(string id);
	Appearance(string id, string tex, int s, int t);
	void setEmissive(float emi_x, float emi_y, float emi_z, float emi_a);
	int getSWrap();
	int getTWrap();
	void applyEmissive();
	virtual ~Appearance();
};

#endif /* APPEARANCE_H_ */
