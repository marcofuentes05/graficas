#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include "Intersect.hpp"
using namespace std;

Intersect::Intersect(){
  this->isNone=true;
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

  this->isNone = false;
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

  this->isNone = false;
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

void Intersect::toString(){
  cout << "distance: " << to_string(distance) << endl;
  cout << "point0: " << to_string(point[0]) << endl;
  cout << "point1: " << to_string(point[1]) << endl;
  cout << "point2: " << to_string(point[2]) << endl;
  cout << "normal0: " << to_string(normal[0]) << endl;
  cout << "normal1: " << to_string(normal[1]) << endl;
  cout << "normal2: " << to_string(normal[2]) << endl;
  cout << "isNone: " << to_string(isNone) << endl;
}