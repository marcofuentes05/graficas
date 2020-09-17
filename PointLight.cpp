#include "PointLight.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <algorithm>
#include <stdlib.h>
#include <math.h>
using namespace std;

PointLight::PointLight(){
  cout << "POINT LIGHT CONSTRUCTOR VACIO" << endl;
}

PointLight::PointLight(double intensity, double position[3], double color[3]){
  isNull=false;

  this->intensity = intensity;
  this->position[0] = position[0];
  this->position[1] = position[1];
  this->position[2] = position[2];

  this->color[0] = color[0];
  this->color[1] = color[1];
  this->color[2] = color[2];
}

bool PointLight::getIsNull(){
  return this->isNull;
}

double PointLight::getIntensity(){
  return this->intensity;
}

double *PointLight::getColor(){
  return this->color;
}

double *PointLight::getPosition(){
  return this->position;
}