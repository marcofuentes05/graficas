#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <algorithm>
#include <stdlib.h>
#include <math.h>
#include "AmbientLight.hpp"
using namespace std;

AmbientLight::AmbientLight(){

}

AmbientLight::AmbientLight(double strength , double color[3]){
  this->isNull = false;
  this->strength = strength;
  this->color[0] = color[0];
  this->color[1] = color[1];
  this->color[2] = color[2];
}

bool AmbientLight::getIsNull(){
  return this->isNull;
}

double AmbientLight::getStrength(){
  return this->strength;
}

double *AmbientLight::getColor(){
  return this->color;
}