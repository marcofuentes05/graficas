#ifndef AMBIENTLIGHT_H
#define AMBIENTLIGHT_H
using namespace std;
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <limits>

class AmbientLight{
  double strength;
  double color[3];
  bool isNull = true;
  public:
    AmbientLight();
    AmbientLight(double strength , double color[3]);
    bool getIsNull();
    double getStrength();
    double *getColor();
};

#endif