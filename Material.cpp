#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include "Material.hpp"
using namespace std;

Material::Material(){
  diffuse[0] = 1.0;
  diffuse[1] = 1.0;
  diffuse[2] = 1.0;
  spec = 0;
}

void Material::setDiffuse(double b, double g, double r){
  diffuse[0] = r;
  diffuse[1] = g;
  diffuse[2] = b;  
}

double* Material::getDiffuse(){
  return this->diffuse;
}

double Material::getSpec(){
  return this->spec;
}

void Material::setSpec(double spec){
  this->spec = spec;
}