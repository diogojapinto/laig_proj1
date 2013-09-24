#include "utils.h"
#include <math.h>
#include <iostream>

double DegToRad(double i) {
	double pi = 3.14159265359;

	return i * pi / 180;
}

double* getNewellsMethod(std::vector<double> x, std::vector<double> y, std::vector<double> z)
{
	if (x.size() != y.size() || x.size() != z.size())
		return NULL;

	double *normal = new double[3];
	unsigned int nVertices = x.size();
	
	for (unsigned int i = 0; i < 3; i++)
	{
		normal[i] = 0.0;
	}

	for (unsigned int i = 0; i < nVertices; i++)
	{
		int indiceNextVertex = (i+1) % nVertices;
		
		normal[0] += (y[i] - y[indiceNextVertex]) * (z[i] + z[indiceNextVertex]);
		normal[1] += (z[i] - z[indiceNextVertex]) * (x[i] + x[indiceNextVertex]);
		normal[2] += (x[i] - x[indiceNextVertex]) * (y[i] + y[indiceNextVertex]);
		
	}
	
	double norma = sqrt(pow(normal[0],2) + pow(normal[1],2) + pow(normal[2],2));

	for (unsigned int i = 0; i < 3; i++)
	{
		normal[i] = normal[i]/norma;
	}	

	return normal;
}

double* getNewellsMethodSecondForm(std::vector<double> x, std::vector<double> y, std::vector<double> z, double x_center,double y_center,double z_center)
{
	if (x.size() != y.size() || x.size() != z.size())
		return NULL;

	std::vector <double> normais_x, normais_y, normais_z;
	double *normal = new double[3];
	unsigned int nVertices = x.size();
	
	for (unsigned int i = 0; i < 3; i++)
	{
		normal[i] = 0.0;
	}

	for (unsigned int i = 0; i < nVertices; i++)
	{
		int indiceNextVertex = (i+1) % nVertices;
		double Ux = (x[i] - x_center), Uy = (y[i] - y_center), Uz = (z[i] - z_center);
		double Vx = (x[indiceNextVertex] - x_center), Vy = (y[indiceNextVertex] - y_center), Vz = (z[indiceNextVertex] - z_center);
		normais_x.push_back((Uy*Vz) - (Uz*Vy));
		normais_y.push_back((Uz*Vx) - (Ux*Vz));
		normais_z.push_back((Ux*Vy) - (Uy*Vx));
	}


	for (unsigned int i = 0; i < normais_x.size(); i++)
	{
		normal[0] += normais_x[i];
		normal[1] += normais_y[i];
		normal[2] += normais_z[i];
	}

	double norma = sqrt(pow(normal[0],2) + pow(normal[1],2) + pow(normal[2],2));

	for (unsigned int i = 0; i < 3; i++)
	{
		normal[i] = normal[i]/norma;
	}

	return normal;

}


double* getNewellsMethodAlternative(std::vector<double> x, std::vector<double> y, std::vector<double> z, double x_center,double y_center,double z_center)
{
	if (x.size() != y.size() || x.size() != z.size())
		return NULL;

	double *normal = new double[3];
	unsigned int nVertices = x.size();
	
	for (unsigned int i = 0; i < 3; i++)
	{
		normal[i] = 0.0;
	}

	for (unsigned int i = 0; i < nVertices-1; i++)
	{
		double a[3] = {0.0,0.0,0.0};
		double b[3] = {0.0,0.0,0.0};

		a[0] = x[i] - x_center;
		a[1] = y[i] - y_center;
		a[2] = z[i] - z_center;

		b[0] = x[i+1] - x_center;
		b[1] = y[i+1] - y_center;
		b[2] = z[i+1] - z_center;

		normal[0] +=  (a[1]*b[2]) - (b[1]*a[2]);
		normal[1] +=  (a[2]*b[0]) - (b[2]*a[0]);
		normal[2] +=  (a[0]*b[1]) - (b[0]*a[1]);



	}

	double norma = sqrt(pow(normal[0],2) + pow(normal[1],2) + pow(normal[2],2));

	for (unsigned int i = 0; i < 3; i++)
	{
		normal[i] = normal[i]/norma;
	}
	
	return normal;
}
