#ifndef INTERSECT_H
#define INTERSECT_H

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <limits>
#include "Sphere.hpp"
using namespace std;

class Intersect{
  double distance;
  double point[3];
  double normal[3];
  Sphere sceneObject;
  bool isNone = false;
  public:
    Intersect();
    Intersect(double distance, double point[3]);
    void setIsNone(bool i);
    bool getIsNone();
    double getDistance();
    double *getPoint();
    double *getNormal();
    Sphere getSceneObject();
};
#endif