#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include "Intersect.hpp"
using namespace std;

Intersect::Intersect(){
};

Intersect::Intersect(double distance, 
  double point[3], 
  double normal[3])
{
  this->distance = distance;
  this->point[0] = point[0];
  this->point[1] = point[1];
  this->point[2] = point[2];

  this->normal[0] = normal[0];
  this->normal[1] = normal[1];
  this->normal[2] = normal[2];
};

void Intersect::copyConstructor(double distance, 
  double point[3], 
  double normal[3])
{
  this->distance = distance;
  this->point[0] = point[0];
  this->point[1] = point[1];
  this->point[2] = point[2];

  this->normal[0] = normal[0];
  this->normal[1] = normal[1];
  this->normal[2] = normal[2];
};

void Intersect::setIsNone(bool i){
  this->isNone = i;
}

bool Intersect::getIsNone(){
  return this->isNone;
}

double Intersect::getDistance(){
  return this->distance;
}

double *Intersect::getPoint(){
  return this->point;
}

double *Intersect::getNormal(){
  return this->normal;
}
// Sphere Intersect::getSceneObject(){
//   return this->sceneObject;
// }