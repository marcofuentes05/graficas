#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
using namespace std;
/*----------------------------------------------------------------
Idea de ***matrix obtenida de Stack Overflow:
https://stackoverflow.com/questions/32675730/matrix-pointer-c
----------------------------------------------------------------*/
class Render
{
  int width, height, x_view, y_view, view_width, view_height;
  int ***matrix;
  int COLOR_CLEAR[3];
  int COLOR_VERTEX[3];

public:
  void glInit();
  void glCreateWindow(int width, int height);
  void glViewPort(int x, int y, int width, int height);
  void glClear();
  void glClearColor(double r, double g, double b);
  void glVertex(double x, double y);
  void glColor(double r, double g, double b);
  void glLine(double x0, double y0, double x1, double y1);
  void glLineAbs(int x0, int y0, int x1, int y1);
  void glDrawSquare(double *ld, double *lu, double *rd, double *ru);
  void glDrawPolygon(int vertices[][2], int size);
  void loadModel(string name , int translate[2] , int scale[2]);
  void glFinish();
  string toString();
  string getMatrix();
  int GDCtoPixels(double x, bool isX);
  ~Render();
};

void swap(int *a, int *b);
int abs(int m);
