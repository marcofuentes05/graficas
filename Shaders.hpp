#ifndef SHADERS_H
#define SHADERS_H

#include <iostream>
#include <fstream>
#include <string>
#include "Shaders.hpp"
#include "Render.hpp"

using namespace std;
int *gourad(Render *render,
  double baryCoords[3], 
  bool hasTexture, 
  double **texCoords, 
  int **normals, 
  int color[3]);
#endif