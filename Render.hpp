#ifndef RENDER_H
#define RENDER_H

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <limits>
#include "OBJ.hpp"
#include "linearAlgebra.hpp"
#include "Texture.hpp"
#include "Matrix.hpp"
#include "Sphere.hpp"
#include "AmbientLight.hpp"
#include "PointLight.hpp"
using namespace std;

class Render
{
  int width, height, x_view, y_view, view_width, view_height;
  int ***matrix;
  double **zbuffer;
  int COLOR_CLEAR[3];
  int COLOR_VERTEX[3];
  double minZ =  std::numeric_limits<double>::infinity();
  double maxZ =  -1*std::numeric_limits<double>::infinity();
  Matrix camMatrix;
  Matrix viewPortMatrix;
  Matrix projectionMatrix;
  double camPosition[3] = {0,0,0};
  double fov;
  PointLight pointLight;
  AmbientLight ambientLight;
public:
  vector<Sphere> scene;
  Texture texture;
  double light[3]={0,0,0};
  void glInit();
  void glCreateWindow(int width, int height);
  void glViewPort(int x, int y, int width, int height);
  void glClear();
  int GDCtoPixels(double x, bool isX);
  void glClearColor(double r, double g, double b);
  void glVertex(double x, double y);
  void glVertexAbs(int x , int y , int *color);
  void glColor(double r, double g, double b);
  void glLine(double x0, double y0, double x1, double y1);
  void glLineAbs(int x0, int y0, int x1, int y1 , bool fromOBJ = false);
  void glFinish(string name);
  void glFinishZBuffer(string name);
  void lookAt(double eye[3] , double camPosition[3]);
  double *pointColor(Material material , Intersect intersect , Sphere sceneObject);
  void rtRender();
  void setAmbientLight(AmbientLight a);
  void setPointLight(PointLight p);
  ~Render();
};

#endif