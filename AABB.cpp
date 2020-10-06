#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <math.h>
#include <cmath>
#include "Plane.hpp"
#include "linearAlgebra.hpp"
#include "AABB.hpp"
using namespace std;
AABB::AABB(){

}

double AABB::getSize(){
  return size;
}

double *AABB::getCenter(){
  return center;
}

Material AABB::getMaterial(){
  return material;
}

AABB::AABB(double cent[3],double size , Material material){

  this->center[0] = cent[0];
  this->center[1] = cent[1];
  this->center[2] = cent[2];

  this->size = size;
  double halfSize = size/2.0;

  double position0[3] = {
      center[0] + halfSize,
      center[1],
      center[2]
  };
  double normal0[3] = {1,0,0};
  Plane plane0(position0,normal0,material);
  planes.push_back(plane0);

  double position1[3] = {
      center[0] - halfSize,
      center[1],
      center[2]};
  double normal1[3] = {-1, 0, 0};
  Plane plane1(position1, normal1, material);
  planes.push_back(plane1);

  double position2[3] = {
      center[0],
      center[1] + halfSize,
      center[2]};
  double normal2[3] = {0, 1, 0};
  Plane plane2(position2, normal2, material);
  planes.push_back(plane2);

  double position3[3] = {
      center[0],
      center[1] - halfSize,
      center[2]};
  double normal3[3] = {0, -1, 0};
  Plane plane3(position3, normal3, material);
  planes.push_back(plane3);

  double position4[3] = {
      center[0],
      center[1],
      center[2] + halfSize};
  double normal4[3] = {0, 0, 1};
  Plane plane4(position4, normal4, material);
  planes.push_back(plane4);

  double position5[3] = {
      center[0],
      center[1],
      center[2] - halfSize};
  double normal5[3] = {0, 0, -1};
  Plane plane5(position5, normal5, material);
  planes.push_back(plane5);
};

Intersect AABB::ray_intersect(double origin[3], double direction[3]){
  double epsilon = 0.001;

  double boundsMin[3] = {0,0,0};
  double boundsMax[3] = {0,0,0};
  for (int i = 0; i < 3; i++){
    boundsMin[i] = this->center[i] - (epsilon + (size/2.0));
    boundsMax[i] = this->center[i] + (epsilon + (size/2.0));
  }
  double t = std::numeric_limits<double>::infinity();
  Intersect intercept;
  for (auto plane : planes){
    Intersect planeIntercept = plane.ray_intersect(origin,direction); 
    if (!planeIntercept.getIsNone()){
      // Para ver si estoy dentro de Bounded Box
      double *p = planeIntercept.getPoint();
      if (p[0] >= boundsMin[0] && p[0] <= boundsMax[0] 
          && p[1] >= boundsMin[1] && p[1] <= boundsMax[1] 
          && p[2] >= boundsMin[2] && p[2] <= boundsMax[2]){
        if (planeIntercept.getDistance() < t) {
          t=planeIntercept.getDistance();
          intercept.copyConstructor(
            planeIntercept.getDistance(),
            planeIntercept.getPoint(),
            planeIntercept.getNormal()
          ); 
        }
      }
    }
  }
  return intercept;
} 