#ifndef MATERIAL_H
#define MATERIAL_H
using namespace std;
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <limits>

class Material
{
  double diffuse[3] = {1,1,1};
  public:
    Material();
    void setDiffuse(double r, double g, double b);
    double *getDiffuse();
};
#endif