/*
 * Omnilight.cpp
 *
 *  Created on: Oct 8, 2013
 *      Author: knoweat
 */

#include "Omnilight.h"

Omnilight::Omnilight() {
}

Omnilight::~Omnilight() {
}

Omnilight::Omnilight(string id) :
		Light(id) {

}

Omnilight::Omnilight(string id, bool enabled) :
		Light(id, enabled) {

}
