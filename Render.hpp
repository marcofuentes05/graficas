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
public:
  Texture texture;
  // Shaders shader;
  double light[3]={0,0,0};
  void glInit();
  void glCreateWindow(int width, int height);
  void glViewPort(int x, int y, int width, int height);
  void glClear();
  void glClearColor(double r, double g, double b);
  void glVertex(double x, double y);
  void glVertexAbs(int x , int y , int *color);
  void glColor(double r, double g, double b);
  void glLine(double x0, double y0, double x1, double y1);
  void glLineAbs(int x0, int y0, int x1, int y1 , bool fromOBJ = false);
  void glLineAbsZBuffer(int x0, int y0, double z0 , int x1, int y1 , double z1);
  void glDrawSquare(double *ld, double *lu, double *rd, double *ru);
  void glDrawPolygon(int vertices[][2], int size);
  void loadModel(string name, double transform[3], double scale[3] , double rotate[3] ,bool isWireframe = true, bool hasTexture = false, string shader = "gouradShader");
  void glFinish(string name);
  void glFinishZBuffer(string name);
  void createViewMatrix(double camPosition[3] , double camRotation[3]);
  Matrix createModelMatrix(double translate[3]  , double scale[3] , double rotate[3] );
  Matrix createRotationMatrix( double rotate[3]);
  double *transform(double vector[3] , Matrix matriz);
  double *dirTransform(double vector[3] , Matrix vMatrix);
  double *baryCoords(double *v1 , double* v2 , double *v3 , double *punto);
  void triangle_bc(double v1[3] , 
    double v2[3] , 
    double v3[3] ,
    int color[3] , 
    double **texcoords, 
    bool hasTexture , 
    double intensity , 
    double**normals,
    string shader);
  void setZBuffer(int x , int y , double value);
  string toString();
  string getMatrix();
  string getSom();
  int GDCtoPixels(double x, bool isX);
  void setTexture(string t);
  Texture getTexture();
  ~Render();
  int * gouradShader(double baryCoords[3],
      bool hasTexture,
      double **texCoords,
      double **normals,
      int color[3]);
  int * toonShader(double baryCoords[3],
      bool hasTexture,
      double **texCoords,
      double **normals,
      int color[3]);
  int *randomShader(double baryCoords[3],
      bool hasTexture,
      double **texCoords,
      double **normals,
      int color[3]);
  int *unlitShader(double baryCoords[3],
      bool hasTexture,
      double **texCoords,
      double **normals,
      int color[3]);
  int *inverseShader(double baryCoords[3],
      bool hasTexture,
      double **texCoords,
      double **normals,
      int color[3]);
  int *randomChannelShader(double baryCoords[3],
      bool hasTexture,
      double **texCoords,
      double **normals,
      int color[3]);
    int * toonShaderGold(double baryCoords[3],
      bool hasTexture,
      double **texCoords,
      double **normals,
      int color[3]);
  void PostProcessEffect(string, string);
};

#endif