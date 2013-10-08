
#ifndef OMNILIGHT_H_
#define OMNILIGHT_H_

#include "Light.h"

class Omnilight: public Light {
public:
	Omnilight();
	virtual ~Omnilight();
	Omnilight(string id);
	Omnilight(string id, bool enabled);
};

#endif /* OMNILIGHT_H_ */
