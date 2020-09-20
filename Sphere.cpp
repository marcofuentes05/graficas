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

Intersect Sphere::ray_intersect(double origin[3] , double direction[3] ){
  Intersect result;
  double *L = substract(this->center , origin , 3); //DELETE THIS
  double tca = dot(L, direction , 3);
  double l = norm(L,3);
  double d = sqrt(pow(l,2) - pow(tca , 2));
  if (d>radius){
    result.setIsNone(true);
    return result;
  }
  double thc = sqrt(pow(radius , 2) - pow(d , 2));
  double t0 = tca -thc;
  double t1 = tca + thc;
  if (t0 < 0){
    t0 = t1;
  }
  if (t0<0.1){
    result.setIsNone(true);
    return result;
  }
  double hit[3] = {
    origin[0] + t0 * direction[0],
    origin[1] + t0 * direction[1],
    origin[2] + t0 * direction[2]
  };
  double *normal= substract(hit , this->center , 3) ; //DELETE THIS
  double normalNormalized[3] = {
    normal[0] / norm(normal , 3),
    normal[1] / norm(normal , 3),
    normal[2] / norm(normal , 3)
  };

  Intersect r0(t0 , hit , normalNormalized );
  delete normal;
  delete L;
  
  return r0;
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