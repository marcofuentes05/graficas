#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include "Render.hpp"
#include "OBJ.hpp"
#include "linearAlgebra.hpp"
#include "Texture.hpp"
using namespace std;

int main()
{
  // Implementacion
  Render r;
  r.glInit();
  r.glClearColor(0.0, 0.0, 0.0);
  r.glColor(1.0, 1.0, 1.0);
  r.glCreateWindow(1000, 1000);
  r.glClear();
  // PARA EL PLANETA
  // r.setTexture("models/earthDay.bmp");
  // int transform[3] ={ 500, 500, 500 };
  // int scale[3] = {1, 1, 1};
  // r.loadModel("models/earth.obj", transform, scale, false, true);
  
  // PARA EL MODELO
  r.setTexture("models/model.bmp");
  int transform[3] = {500, 500,0};
  int scale[3] = {500, 500, 500};
  r.loadModel("models/model.obj", transform, scale, false, true);
  
  // int transform[3] = {250, 30, 0};
  // int scale[3] = {5, 5,5};
  // r.loadModel("models/coca.obj", transform, scale, false , false);


  r.glFinish("SR5.bmp");
}