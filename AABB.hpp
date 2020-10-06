#ifndef AABB_H
#define AABB_H

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <limits>
#include "Material.hpp"
#include "Intersect.hpp"
#include "Plane.hpp"
using namespace std;
class Intersect;
class AABB
{
  double center[3];
  double normal[3];
  Material material;
  double size;
  vector<Plane> planes;
  Plane p0 ();
public:
  AABB();
  AABB(double center[3], double size , Material material);
  Intersect ray_intersect(double origin[3], double direction[3]);
  Material getMaterial();
  double *getCenter();
  double getSize();
};
#endif