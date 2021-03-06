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
  double spec=0;
  public:
    Material();
    void setDiffuse(double r, double g, double b);
    void setSpec(double spec);
    double *getDiffuse();
    double getSpec();
};
#endif