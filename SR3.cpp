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
  r.glViewPort(1, 1 , 995, 995);
  int transform[2] = {500, 250};
  int scale[2] = {20 , 20};

  for (double i = 0.0 ; i<1;i = i + 0.0051){
    double ld[2] = { -1 , -1  +2*i };
    double lu[2] = {-1 + 2 * i , 1 };
    double ru[2] = { 1 , 1  - 2*i  };
    double rd[2] = {1 - 2 * i, -1};
    r.glDrawSquare(ld ,lu ,rd, ru);
  }

  r.loadModel("face.obj" , transform , scale);
  //Guardo el archivo
  r.glFinish();
}
