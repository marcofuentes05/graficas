#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <math.h>
#include <cmath>
#include "Plane.hpp"
#include "linearAlgebra.hpp"
using namespace std;

Plane::Plane()
{
  cout << "Constructor Vacio" << endl;
};

Plane::Plane(double cent[3], double norm[3], Material m)
{
  center[0] = cent[0];
  center[1] = cent[1];
  center[2] = cent[2];

  normal[0] = norm[0];
  normal[1] = norm[1];
  normal[2] = norm[2];
  material = m;
};

Intersect Plane::ray_intersect(double origin[3], double direction[3]){
  Intersect result;
  double denominador = dot( direction , normal , 3);
  if (abs(denominador) > 0.0001){
    double *resta = substract(center, origin,3); //DELETE THIS
    double t = dot(normal, resta, 3) / denominador;
    if (t>0){
      double hit[3] = {
        (t * direction[0]) + origin[0],
        (t * direction[1]) + origin[1],
        (t * direction[2]) + origin[2]
      };
      Intersect i( t , hit , normal);
      return i;
    }
    delete resta;
  }
  result.setIsNone(true);
  return result;
}

Material Plane::getMaterial()
{
  return this->material;
}

double *Plane::getCenter()
{
  return this->center;
}