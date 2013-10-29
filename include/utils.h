#ifndef UTILS_H
#define UTILS_H
#include <vector>

float DegToRad(float i);

float* getNewellsMethod(std::vector<float> x, std::vector<float> y,
        std::vector<float> z);
float* getNewellsMethodSecondForm(std::vector<float> x, std::vector<float> y,
        std::vector<float> z, float x_center, float y_center,
        float z_center);
float* getNormalsAlternative(std::vector<float> x, std::vector<float> y,
        std::vector<float> z, float x_center, float y_center,
        float z_center);

char *strdup(char *str1, const char *str2);

float distanceTwoPoints(Point* p1, Point* p2);

#endif
