/*
 * InvalidPreAttrException.h
 *
 *  Created on: Oct 8, 2013
 *      Author: knoweat
 */

#ifndef INVALIDPREATTREXCEPTION_H_
#define INVALIDPREATTREXCEPTION_H_

#include <string>

using namespace std;

class InvalidPreAttrException {
	string error_message;
public:
	InvalidPreAttrException();
	InvalidPreAttrException(string attr);
	virtual ~InvalidPreAttrException();
	string getErrMessg();
};

#endif /* INVALIDPREATTREXCEPTION_H_ */
