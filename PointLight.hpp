#ifndef POINTLIGHT_H
#define POINTLIGHT_H
using namespace std;
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <limits>

class PointLight{
  double intensity;
  double position[3];
  double color[3];
  bool isNull = true;
  public:
    PointLight();
    PointLight(double intensity , double position[3] , double color[3]);
    bool getIsNull();
    double *getPosition();
    double *getColor();
    double getIntensity();
};

#endif|