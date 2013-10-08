/*
 * InvalidPreAttrException.cpp
 *
 *  Created on: Oct 8, 2013
 *      Author: knoweat
 */

#include "InvalidPreAttrException.h"

using namespace std;

InvalidPreAttrException::InvalidPreAttrException() {
}

InvalidPreAttrException::InvalidPreAttrException(string attr) {
	error_message = "Invalid \"" + attr + "\" defined. Exiting...\n";
}

InvalidPreAttrException::~InvalidPreAttrException() {
}

