#ifndef SHADERS_H
#define SHADERS_H
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <limits>
#include "Render.hpp"
#include "Texture.hpp"

using namespace std;
class Shader{
  Render render;
  public:
    Shader();
    Shader(Render *r);
    void setRenderer(Render r);
    void gourad( double baryCoords[3], double texCoords[][3] , double normals[][3], double color[3] , Texture t );
};
#endif