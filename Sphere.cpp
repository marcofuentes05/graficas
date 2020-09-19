#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <math.h>
#include "Sphere.hpp"
#include "linearAlgebra.hpp"
using namespace std;

Sphere::Sphere(){
  cout << "Constructor Vacio" << endl;
};

Sphere::Sphere(double cent[3], double rad, Material m){
  center[0] = cent[0];
  center[1] = cent[1];
  center[2] = cent[2];
  radius = rad;
  material = m;  
};

Intersect* Sphere::ray_intersect(double origin[3] , double direction[3] ){
  Intersect result0;
  Intersect* result = &result0;
  double *L = substract(this->center , origin , 3); //DELETE THIS
  double tca = dot(L, direction , 3);
  double l = norm(L,3);
  double d = pow( (l*l - tca*tca) ,0.5);
  if (d>radius){
    result->setIsNone(true);
    return result;
  }
  double thc = pow( radius * radius - d*d , 0.5);
  double t0 = tca -thc;
  double t1 = tca + thc;
  if (t0 < 0){
    t0 = t1;
  }
  if (t0<0){
    result->setIsNone(true);
    return result;
  }
  double hit[3] = {
    origin[0] + t0 * direction[0],
    origin[1] + t0 * direction[1],
    origin[2] + t0 * direction[2]
  };

  double *normal= substract(hit , center , 3) ; //DELETE THIS
  double *normalNormalized = normalize( normal , 3);

  Intersect r0(t0 , hit , normalNormalized );
  Intersect *ret = &r0;
  return ret;
}

Material Sphere::getMaterial(){
  return this-> material;
}

double Sphere::getRadius(){
  return this->radius;
}

double *Sphere::getCenter(){
  return this->center;
}