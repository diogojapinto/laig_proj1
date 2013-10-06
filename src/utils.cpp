#include "utils.h"
#include <math.h>
#include <iostream>

float DegToRad(float i) {
	float pi = acos(-1);

	return i * pi / 180;
}

float* getNewellsMethod(vector<float> x, vector<float> y, vector<float> z) {
	if (x.size() != y.size() || x.size() != z.size())
		return NULL;

	float *normal = new float[3];
	unsigned int nVertices = x.size();

	for (unsigned int i = 0; i < 3; i++) {
		normal[i] = 0.0;
	}

	for (unsigned int i = 0; i < nVertices; i++) {
		int indiceNextVertex = (i + 1) % nVertices;

		normal[0] += (y[i] - y[indiceNextVertex])
		        * (z[i] + z[indiceNextVertex]);
		normal[1] += (z[i] - z[indiceNextVertex])
		        * (x[i] + x[indiceNextVertex]);
		normal[2] += (x[i] - x[indiceNextVertex])
		        * (y[i] + y[indiceNextVertex]);

	}

	double norma = sqrt(
	        pow(normal[0], 2) + pow(normal[1], 2) + pow(normal[2], 2));

	for (unsigned int i = 0; i < 3; i++) {
		normal[i] = normal[i] / norma;
	}

	return normal;
}
