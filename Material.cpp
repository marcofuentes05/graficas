#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include "Material.hpp"
using namespace std;

Material::Material(){
  // cout << "Constructor vacío" << endl;
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