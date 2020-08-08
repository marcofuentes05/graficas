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
  r.setTexture("models/model.bmp");

  // r.glClear();
  // r.glViewPort(1, 1 , 8, 8);
  // r.glLine(0,0,1,1);
  // r.glLine(0, 0, -1, -1);
  // r.glLine(0, 0, -1, 1);
  // PARA LA CARA DE ADULTO
  int transform[3] = {500, 500, 0};
  int scale[3] = {400, 400, 400};
  r.loadModel("models/model.obj", transform, scale, false , true);

  // PARA EL CARRITO DE JUGUETE
  // int transform[3] = {250, 30, 0};
  // int scale[3] = {2, 2, 2};
  // r.loadModel("models/toon_car.obj", transform, scale, false);

  //PARA LA COCA

  // int transform[3] = {250, 30, 0};
  // int scale[3] = {5, 5,5};
  // r.loadModel("models/coca.obj", transform, scale, false);
  
  r.glFinish("SR5.bmp");

  // Texture t("testFile.bmp");
  // t.read();
}