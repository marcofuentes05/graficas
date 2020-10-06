#ifndef PLANE_H
#define PLANE_H

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <limits>
#include "Material.hpp"
#include "Intersect.hpp"
using namespace std;
class Intersect;
class Plane
{
  double center[3];
  double normal[3];
  Material material;
public:
  Plane();
  Plane(double center[3],double normal[3] , Material material);
  Intersect ray_intersect(double origin[3], double direction[3]);
  Material getMaterial();
  double *getCenter();
};
#endif