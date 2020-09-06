#ifndef SPHERE_H
#define SPHERE_H

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <limits>
#include "Material.hpp"
#include "Intersect.hpp"
using namespace std;

class Sphere{ 
  double center[3];
  double radius;
  Material material;
  public: 
    Sphere();
    Sphere(double center[3] , double radius  , Material material);
    Intersect ray_intersect(double origin[3] , double direction[3]);
    Material getMaterial();
};
#endif