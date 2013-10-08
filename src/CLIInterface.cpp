/*
 * Interface.cpp
 *
 *  Created on: Oct 5, 2013
 *      Author: wso277
 */

#include <iostream>
#include <string>

using namespace std;

void setPaths() {
	string yaf_path;
	string texture_path;

	cout << "Insert path to yaf file: ";
	cin >> yaf_path;
	cout << endl << "Insert path to texture folder: ";
	cin >> texture_path;
}

string getTexturePath(string texture_path, string texture_file) {
	string tex_path;

	tex_path = texture_path + "/" + texture_file;

	return tex_path;
}

