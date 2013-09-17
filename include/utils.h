#ifndef UTILS_H
#define UTILS_H
#include <vector>

double DegToRad(double i);

double* getNewellsMethod(std::vector<double> x, std::vector<double> y, std::vector<double> z);
double* getNewellsMethodSecondForm(std::vector<double> x, std::vector<double> y, std::vector<double> z, double x_center,double y_center,double z_center);
double* getNewellsMethodAlternative(std::vector<double> x, std::vector<double> y, std::vector<double> z, double x_center,double y_center,double z_center);

#endif
