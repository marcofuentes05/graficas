#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include "Intersect.hpp"
using namespace std;

Intersect::Intersect(){
};

Intersect::Intersect(double distance){
  this->distance = distance;
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