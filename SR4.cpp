#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include "Render.hpp"
#include "OBJ.hpp"
#include "linearAlgebra.hpp"
using namespace std;
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
  r.glViewPort(1, 1 , 995, 995);
  int transform[2] = {500, 500};
  int scale[2] = {300, 300};
  r.loadModel("models/model.obj", transform, scale, false);
  r.glFinish("SR4.bmp");
}