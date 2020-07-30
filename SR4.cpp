#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include "Render.hpp"
#include "OBJ.hpp"
using namespace std;
using namespace std;

int main()
{
  //Implementacion
  Render r;
  r.glInit();
  r.glClearColor(0.0, 0.0, 0.0);
  r.glColor(1.0, 1.0, 1.0);
  r.glCreateWindow(1000, 1000);
  r.glClear();
  // r.glViewPort(1, 1 , 995, 995);
  int transform[2] = {250, 30};
  int scale[2] = {5, 5};
  r.loadModel("coca.obj", transform, scale);
  r.glFinish();
}