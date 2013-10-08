/*
 * InvalidTexFile.cpp
 *
 *  Created on: Oct 8, 2013
 *      Author: knoweat
 */

#include "InvalidTexFile.h"

InvalidTexFile::InvalidTexFile(string filepath) {
	this->filepath = filepath;
}

InvalidTexFile::~InvalidTexFile() {
}

string InvalidTexFile::getFilePath() {
	return filepath;
}
