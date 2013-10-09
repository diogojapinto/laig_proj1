/*
 * InvalidTexRef.h
 *
 *  Created on: Oct 9, 2013
 *      Author: wso277
 */

#ifndef INVALIDTEXREF_H_
#define INVALIDTEXREF_H_

#include <string>

using namespace std;

class InvalidTexRef {
	string ref;
public:
	InvalidTexRef(string ref);
	virtual ~InvalidTexRef();
	string getRef();
};

#endif /* INVALIDTEXREF_H_ */
