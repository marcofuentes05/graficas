#ifndef INTERSECT_H
#define INTERSECT_H

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <limits>
using namespace std;

class Intersect{
  double distance;
  bool isNone = false;
  public:
    Intersect();
    Intersect(double distance);
    void setIsNone(bool i);
    bool getIsNone();
    double getDistance();
};
#endif