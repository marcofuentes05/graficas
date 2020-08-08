#ifndef SHADERS_H
#define SHADERS_H
#include "Render.hpp"

using namespace std;
class Shaders{
  Render render;
  public:
    Shaders();
    Shaders(Render r);
    void gourad(double baryCoords[3], double color[3]  );
};
#endif