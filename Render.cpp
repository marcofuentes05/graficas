/* -------------------------------------------------------------------  
Render.cpp
Algoritmo que escribe un archivo BMP con el nombre de 'SR5.bmp',
representando un wireframde de un modelo OBJ.
Marco Fuentes - 18188
Gráficas por computadora - Segundo Semestre 2020 - UVG
------------------------------------------------------------------- */
#include "Render.hpp"
#include "Texture.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <algorithm>
#include <stdlib.h>
#include <math.h>
using namespace std;
#define PI 3.14159265
// Sobrecarga de operadores para matrices
Matrix operator*(Matrix  &m0 , Matrix &m1){
  Matrix result;
  for (int i = 0; i < 4 ; i ++){
    for (int j = 0 ; j < 4 ; j++){
      double contador = 0 ;
      for (int x  = 0 ; x < 4 ; x++){
        contador = contador + (m1.getItem(x, j) * m0.getItem(i, x));
      }
      result.setValue(i,j,contador); 
    }
  }
  return result;
}

double* operator*(Matrix &m, double* &v ){
  double *result = new double[4];
  for (int i = 0 ; i < 4 ; i ++){
    double contador = 0 ;
    for (int j = 0 ; j <4 ; j++){
      contador = contador + m.getItem(i,j) * v[i];
    }
    result[i] = contador;
  }
  return result;
}

double* multiplyVM(Matrix m , double* v){
  double *result = new double[4];
  for (int i = 0 ; i < 4 ; i ++){
    double contador = 0 ;
    for (int j = 0 ; j <4 ; j++){
      contador = contador + m.getItem(i,j) * v[j];
    }
    result[i] = contador;
  }
  return result;
}

//Helper functions.
int abs(int m)
{
  return (m < 0) ? -m : m;
}
void swap(int *a, int *b)
{
  int ta = *a;
  int tb = *b;
  *a = tb;
  *b = ta;
}
void Render::glInit()
{
  width = 0;
  height = 0;
  x_view = 0;
  y_view = 0;
  view_width = 0;
  view_height = 0;
  glClearColor(0.0, 0.0, 0.0);
  glColor(0.0, 0.0, 0.0);
};
void Render::glCreateWindow(int width, int height)
{
  // Limpiar memoria en caso exista anteriormente
  int w = this->width;
  int h = this->height;
  if (this->width > 0){
    for (int i = 0; i < w; i++){
      for (int j = 0; j < h; j++){
        delete[] matrix[i][j];
      }
      delete[] matrix[i];
      delete[] zbuffer[i];
    }
    delete[] matrix;
    delete[] zbuffer;
  }



  // BMP solo acepta dimensiones multiplos de 4
  int modw = width % 4;
  int modh = width % 4;
  if (modw == 0)
  {
    this->width = width;
    this->view_width = width;
  }
  else
  {
    this->width = width + (4 - modw);
    this->view_width = width + (4 - modw);
  }
  if (modh == 0)
  {
    this->height = height;
    this->view_height = height;
  }
  else
  {
    this->height = height + (4 - modh);
    this->view_height = height + (4 - modh);
  }

  //Crear nueva matriz dinamica
  matrix = new int **[this->width];
  zbuffer = new double*[this->width];
  for (int i = 0; i < this->width; i++)
  {
    matrix[i] = new int *[this->height];
    zbuffer[i] = new double [this->height];
    for (int j = 0; j < this->height; j++)
    {
      matrix[i][j] = new int[3];
    };
  };
};
void Render::glViewPort(int x, int y, int width, int height){
  try
  {
    if ((x + width <= this->width) && (y + height <= this->height))
    {
      x_view = x;
      y_view = y;
      view_height = height;
      view_width = width;
    }
    else
    {
      throw 1;
    }
  }
  catch (int error)
  {
    if (error == 1)
    {
      cout << "ERROR: Viewport no puede salirse de la ventana" << endl;
      exit(0);
    }
  }
}
void Render::glClearColor(double r, double g, double b)
{
  this->COLOR_CLEAR[2] = int(r * 255);
  this->COLOR_CLEAR[1] = int(g * 255);
  this->COLOR_CLEAR[0] = int(b * 255);
};
void Render::glColor(double r, double g, double b)
{
  this->COLOR_VERTEX[2] = (r * 255);
  this->COLOR_VERTEX[1] = (g * 255);
  this->COLOR_VERTEX[0] = (b * 255);
};
string Render::toString()
{
  return "Width: " + to_string(width) + "\nHeight: " + to_string(height);
}
string Render::getMatrix()
{
  string r = "MATRIZ: \n";
  for (int i = 0; i < height; i++)
  {
    for (int j = 0; j < width; j++)
    {
      r += "(";
      for (int k = 0; k < 3; k++)
      {
        r += to_string(matrix[j][i][k]) + " , ";
      };
      r += ")  ";
    };
    r += "\n";
  };
  return r;
}
void Render::glClear()
{
  for (int i = 0; i < height; i++)
  {
    for (int j = 0; j < width; j++){
      zbuffer[i][j] = -1 * std::numeric_limits<double>::infinity();
      for (int k = 0; k < 3; k++)
      {
        matrix[j][i][k] = COLOR_CLEAR[k];
      };
    };
  };
}
int Render::GDCtoPixels(double x, bool isX)
{
  return isX ? (int)(x_view + ((x + 1) * view_width / 2)) : (int)(y_view + ((x + 1) * view_height / 2));
}
void Render::glVertex(double x, double y)
{
  //x,y son decimales pertenecientes a [-1,1]
  int x_coor, y_coor = 0;
  x_coor = GDCtoPixels(x, true);
  y_coor = GDCtoPixels(y, false);
  matrix[y_coor][x_coor][0] = COLOR_VERTEX[0];
  matrix[y_coor][x_coor][1] = COLOR_VERTEX[1];
  matrix[y_coor][x_coor][2] = COLOR_VERTEX[2];
};
void Render::glLine(double x0, double y0, double x1, double y1)
{
  //Convertir coordenadas en pixeles
  int x_0, x_1, y_0, y_1;
  x_0 = GDCtoPixels(x0, true);
  x_1 = GDCtoPixels(x1, true);
  y_0 = GDCtoPixels(y0, false);
  y_1 = GDCtoPixels(y1, false);

  int dx = abs(x_1 - x_0);
  int dy = abs(y_1 - y_0);

  bool esV = dy > dx;
  if (esV)
  {
    swap(x_0, y_0);
    swap(x_1, y_1);
  }

  if (x_0 > x_1)
  {
    swap(x_0, x_1);
    swap(y_0, y_1);
  }

  double offset = 0.0;
  double limit = 0.5;

  dx = abs(x_1 - x_0);
  dy = abs(y_1 - y_0);

  double m;
  m = double(dy) / double(dx);
  int y = y_0;

  for (int x = x_0; x < x_1 + 1; x++)
  {
    if (esV)
    {
      matrix[y][x][0] = COLOR_VERTEX[0];
      matrix[y][x][1] = COLOR_VERTEX[1];
      matrix[y][x][2] = COLOR_VERTEX[2];
    }
    else
    {
      matrix[x][y][0] = COLOR_VERTEX[0];
      matrix[x][y][1] = COLOR_VERTEX[1];
      matrix[x][y][2] = COLOR_VERTEX[2];
    }
    offset = offset + m;
    if (offset > limit)
    {
      if (y_0 < y_1)
      {
        y = y + 1;
      }
      else
      {
        y = y - 1;
      }

      limit = limit + 1;
    }
  }
}
void Render::glLineAbs(int x_0, int y_0, int x_1, int y_1 , bool fromOBJ){
  int dx = abs(x_1 - x_0);
  int dy = abs(y_1 - y_0);

  bool esV = dy > dx;
  if (esV){
    swap(x_0, y_0);
    swap(x_1, y_1);
  }
  if (x_0 > x_1){
    swap(x_0, x_1);
    swap(y_0, y_1);
  }
  double offset = 0.0;
  double limit = 0.5;

  dx = abs(x_1 - x_0);
  dy = abs(y_1 - y_0);

  double m;
  m = double(dy) / double(dx);
  int y = y_0;

  for (int x = x_0; x < x_1 + 1; x++){
    if (esV){
      matrix[y][x][0] = COLOR_VERTEX[0];
      matrix[y][x][1] = COLOR_VERTEX[1];
      matrix[y][x][2] = COLOR_VERTEX[2];
    }
    else{
      matrix[x][y][0] = COLOR_VERTEX[0];
      matrix[x][y][1] = COLOR_VERTEX[1];
      matrix[x][y][2] = COLOR_VERTEX[2];
    }
    offset = offset + m;
    if (offset > limit){
      if (y_0 < y_1){
        y = y + 1;
      }else{
        y = y - 1;
      }
      limit = limit + 1;
    }
  }
}
void Render::glVertexAbs(int x , int y, int *color){
  matrix[y][x][0] = color[0];
  matrix[y][x][1] = color[1];
  matrix[y][x][2] = color[2];
};
void Render::glLineAbsZBuffer(int x_0, int y_0, double z0 ,int x_1, int y_1, double z1)
{
  int dx = abs(x_1 - x_0);
  int dy = abs(y_1 - y_0);

  bool esV = dy > dx;
  if (esV){
    swap(x_0, y_0);
    swap(x_1, y_1);
  }
  if (x_0 > x_1){
    swap(x_0, x_1);
    swap(y_0, y_1);
  }
  double offset = 0.0;
  double limit = 0.5;

  dx = abs(x_1 - x_0);
  dy = abs(y_1 - y_0);

  double m;
  m = double(dy) / double(dx);
  int y = y_0;

  for (int x = x_0; x < x_1 + 1; x++){
    if (esV){
      matrix[y][x][0] = COLOR_VERTEX[0];
      matrix[y][x][1] = COLOR_VERTEX[1];
      matrix[y][x][2] = COLOR_VERTEX[2];
    }else{
      matrix[x][y][0] = COLOR_VERTEX[0];
      matrix[x][y][1] = COLOR_VERTEX[1];
      matrix[x][y][2] = COLOR_VERTEX[2];
    }
    offset = offset + m;
    if (offset > limit){
      if (y_0 < y_1){
        y = y + 1;
      }else
      {
        y = y - 1;
      }
      limit = limit + 1;
    }
  }
}
void Render::glDrawSquare(double *ld, double *lu, double *rd, double *ru)
{
  //Todos son arrays de dos elementos indicando las coordenadas del vertice
  glLine(ld[0], ld[1], lu[0], lu[1]);
  glLine(lu[0], lu[1], ru[0], ru[1]);
  glLine(ru[0], ru[1], rd[0], rd[1]);
  glLine(rd[0], rd[1], ld[0], ld[1]);
}
void Render::glDrawPolygon(int vertices[][2], int size)
{
  for (int i = 0; i < size; i++)
  {
    glLineAbs(vertices[i][0], vertices[i][1], vertices[(i + 1) % size][0], vertices[(i + 1) % size][1]);
  }
}
void Render::glFinish(string name){
  // Crear archivo
  ofstream archivo;
  archivo.open(name, ios::binary);
  // File type data
  char B = 'B';
  char M = 'M';
  int size = 14 + 40 + (width * height * 3);
  int reserved = 0;
  int pixelDataOffset = 14 + 40;
  archivo.write((char *)&B, sizeof(B));
  archivo.write((char *)&M, sizeof(M));
  archivo.write((char *)&size, sizeof(size));                       // 14+40+(w*h*3)
  archivo.write((char *)&reserved, sizeof(reserved));               //0
  archivo.write((char *)&pixelDataOffset, sizeof(pixelDataOffset)); //54

  //Image information data
  int headerSize = 40;
  short planes = 1;
  short bitsPerPixel = 24;
  int compression = 0;
  int imageSize = width * height * 3;
  int varios = 0;
  archivo.write((char *)&headerSize, sizeof(headerSize)); //40
  archivo.write((char *)&width, sizeof(width));
  archivo.write((char *)&height, sizeof(height));
  archivo.write((char *)&planes, sizeof(planes));             //1
  archivo.write((char *)&bitsPerPixel, sizeof(bitsPerPixel)); //24
  archivo.write((char *)&compression, sizeof(compression));   //0
  archivo.write((char *)&imageSize, sizeof(imageSize));       // w *h*3
  archivo.write((char *)&varios, sizeof(varios));             //0
  archivo.write((char *)&varios, sizeof(varios));             //0
  archivo.write((char *)&varios, sizeof(varios));             //0
  archivo.write((char *)&varios, sizeof(varios));             //0
  //Color pallete (NONE)

  //Raw pixel data
  for (int i = 0; i < height; i++)
  {
    for (int j = 0; j < width; j++)
    {
      for (int k = 0; k < 3; k++)
      {
        int valor = matrix[j][i][k];
        archivo.write((char *)&valor, 1);
      }
    }
  }
  archivo.close();
};
void Render::glFinishZBuffer(string name){
  // Crear archivo
  ofstream archivo;
  archivo.open(name, ios::binary);
  // File type data
  char B = 'B';
  char M = 'M';
  int size = 14 + 40 + (width * height * 3);
  int reserved = 0;
  int pixelDataOffset = 14 + 40;
  archivo.write((char *)&B, sizeof(B));
  archivo.write((char *)&M, sizeof(M));
  archivo.write((char *)&size, sizeof(size));                       // 14+40+(w*h*3)
  archivo.write((char *)&reserved, sizeof(reserved));               //0
  archivo.write((char *)&pixelDataOffset, sizeof(pixelDataOffset)); //54

  //Image information data
  int headerSize = 40;
  short planes = 1;
  short bitsPerPixel = 24;
  int compression = 0;
  int imageSize = width * height * 3;
  int varios = 0;
  archivo.write((char *)&headerSize, sizeof(headerSize)); //40
  archivo.write((char *)&width, sizeof(width));
  archivo.write((char *)&height, sizeof(height));
  archivo.write((char *)&planes, sizeof(planes));             //1
  archivo.write((char *)&bitsPerPixel, sizeof(bitsPerPixel)); //24
  archivo.write((char *)&compression, sizeof(compression));   //0
  archivo.write((char *)&imageSize, sizeof(imageSize));       // w *h*3
  archivo.write((char *)&varios, sizeof(varios));             //0
  archivo.write((char *)&varios, sizeof(varios));             //0
  archivo.write((char *)&varios, sizeof(varios));             //0
  archivo.write((char *)&varios, sizeof(varios));             //0
  //Color pallete (NONE)

  //Raw pixel data
  for (int i = 0; i < height; i++){
    for (int j = 0; j < width; j++){
      for (int k = 0 ; k < 3 ; k ++){
        int valor = 0;
        if (zbuffer[j][i] <= maxZ && zbuffer[j][i] >= minZ){
          valor = zbuffer[j][i]-minZ;
          valor = int((double(valor)/(maxZ - minZ))*255);
          // valor = int(double);
          // valor = int((double(zbuffer[j][i]-minZ ) * 255) / (double)(maxZ - minZ) );
        }
        archivo.write((char *)&valor, sizeof(char));
      }
    }
  }
  archivo.close();
};

double * Render::transform(double vector[3] , Matrix matriz){ 
  double augVertex[4];
  augVertex[0] = vector[0];
  augVertex[1] = vector[1];
  augVertex[2] = vector[2];
  augVertex[3] = 1;

  double *tranVertex = new double[4];
  tranVertex = multiplyVM(matriz , augVertex);
  double *result = new double[3];
  // exit(1);
  result[0] = tranVertex[0]/tranVertex[3];
  result[1] = tranVertex[1]/tranVertex[3];
  result[2] = tranVertex[2]/tranVertex[3];

  delete tranVertex;
  return result;
}

Matrix Render::createModelMatrix(double translate[3]  , double scale[3] , double rotate[3]){
  double translateMatrix[4][4] = {
    {1, 0, 0 , translate[0]},
    {0, 1, 0 , translate[1]},
    {0, 0, 1 , translate[2]},
    {0, 0, 0 , 1}
  };
  double scaleMatrix[4][4] = {
    {scale[0] , 0 , 0 , 0},
    {0 , scale[1] , 0 , 0},
    {0 , 0 , scale[2] , 0},
    {0 , 0 , 0 , 1}
  };
  Matrix translateM(translateMatrix);
  Matrix scaleM(scaleMatrix);
  Matrix rotationM = createRotationMatrix(rotate);

  Matrix mul1 = (translateM * rotationM);
  Matrix mul2 =  mul1 * scaleM;
  return mul2;
}

double toRad(double deg){
  return deg * PI / 180;
}

Matrix Render::createRotationMatrix(double rotate[3]){
  double pitch = toRad(rotate[0]);
  double yaw = toRad(rotate[1]);
  double roll = toRad(rotate[2]);

  double rotationX[4][4] = {
    {1, 0, 0, 0},
    {0, cos(pitch), -sin(pitch), 0},
    {0, sin(pitch), cos(pitch), 0},
    {0,0,0,1}
  };
  Matrix rx(rotationX);

  double rotationY[4][4] = {
    {cos(yaw), 0, sin(yaw), 0},
    {0, 1, 0, 0},
    {-sin(yaw), 0, cos(yaw), 0},
    {0, 0, 0, 1}
  };
  Matrix ry(rotationY);

  double rotationZ[4][4] = {
    {cos(roll), -sin(roll), 0, 0},
    {sin(roll), cos(roll), 0, 0},
    {0, 0, 1, 0},
    {0, 0, 0, 1}
  };
  Matrix rz(rotationZ);

  Matrix m0 = rx * ry;
  Matrix m1 = m0 * rz;
  return m1;
}

double *Render::baryCoords( double *v1 , double* v2 , double *v3 , double *punto ){
  double *result = new double[3];
  try{
    result[0] = (((v2[1] - v3[1]) * (punto[0] - v3[0]) + (v3[0] - v2[0]) * (punto[1] - v3[1])) / 
                ((v2[1] - v3[1]) * (v1[0] - v3[0]) + (v3[0] - v2[0]) * (v1[1] - v3[1])));
    result[1] = ( ((v3[1] - v1[1])*(punto[0] - v3[0]) + (v1[0] - v3[0])*(punto[1] - v3[1]) ) /
                ((v2[1] - v3[1])*(v1[0] - v3[0]) + (v3[0] - v2[0])*(v1[1] - v3[1])) );
    result[2] = 1 - result[0] - result[1];
  }catch(...){
    result[0] = -1;
    result[1] = -1;
    result[2] = -1;
  }
  return result;
};

void Render::triangle_bc(double v1[3] , 
    double v2[3] , 
    double v3[3] , 
    int color[3] , 
    double**texcoords , 
    bool hasTexture , 
    double intensity,
    double **normals,
    string shader){
  int *_color = new int[3];
  int minx = int(min(v1[0] , min(v2[0], v3[0])));
  int miny = int(min(v1[1], min(v2[1], v3[1])));

  int maxx = int(max(v1[0], max(v2[0], v3[0])));
  int maxy = int(max(v1[1], max(v2[1], v3[1])));
  for (int i = minx; i <= maxx; i++){      
    for (int j = miny; j <= maxy; j++){
      double p[2] = {(double)i, (double)j};
      double *bary = baryCoords(v1, v2, v3, p); // DELETE[] THIS
      if (bary[0] >= 0 && bary[1] >= 0 && bary[2] >= 0){
        double z = v1[2] * bary[0] + v2[2] * bary[1] + v3[2] * bary[2];
        if (z >= zbuffer[i][j] && intensity >=0){
          if (shader == "toonShader"){
            _color = toonShader(bary , hasTexture , texcoords, normals , color );
          }else if (shader == "gouradShader"){
            _color = gouradShader(bary , hasTexture , texcoords, normals , color );
          }else if (shader == "random"){
            _color = randomShader(bary , hasTexture , texcoords, normals , color );
          }else if (shader == "unlit"){
            _color = unlitShader(bary, hasTexture, texcoords, normals, color);
          }else if(shader == "inverse"){
            _color = inverseShader(bary, hasTexture, texcoords, normals, color);
          }else if(shader == "randomChannel"){
            _color = randomChannelShader(bary, hasTexture, texcoords, normals, color);
          }else if (shader == "toonGold"){
            _color = toonShaderGold(bary, hasTexture, texcoords, normals, color);
          }else{
            _color[0] = int(double(color[0]) * intensity);
            _color[1] = int(double(color[1]) * intensity);
            _color[2] = int(double(color[2]) * intensity);
            if(hasTexture){
              double tx = texcoords[0][0] * bary[0] + texcoords[1][0] * bary[1] + texcoords[2][0]*bary[2];
              double ty = texcoords[0][1] * bary[0] + texcoords[1][1] * bary[1] + texcoords[2][1]*bary[2];
              int* texColor = texture.getColor(tx,ty);
              _color[0] = _color[0] * (double(texColor[0]) / double(255));
              _color[1] = _color[1] * (double(texColor[1]) / double(255));
              _color[2] = _color[2] * (double(texColor[2]) / double(255));
              delete [] texColor;
            }
          }
          glVertexAbs(j, i, _color );
        }
        if (z > zbuffer[i][j]){
          zbuffer[i][j] = z;
        }
      }
      delete[] bary;
    }
  }
}

void Render::loadModel(string name , double transform[3] , double scale[3] , double rotate[3] , bool isWireframe , bool hasTexture, string shader){
  OBJ obj(name);
  obj.read();
  int numFaces = obj.getNumFaces();
  int* facesLen = obj.getFacesLen();
  int *** faces = obj.getFaces();
  double** vertices = obj.getVertices();
  double ** texCoords = obj.getTexCoords();
  double ** normals = obj.getNormals();
  Matrix modelMatrix = createModelMatrix(transform, scale, rotate);
  Matrix rotationMatrix = createRotationMatrix(rotate);
  double v0[3];
  double v1[2];
  for(int i = 0 ; i < numFaces ; i++){
    for(int j = 0 ; j<facesLen[i]; j ++){
      v0[0] = vertices[faces[i][j][0] - 1][0];
      v0[1] = vertices[faces[i][j][0] - 1][1];
      v0[2] = vertices[faces[i][j][0] - 1][2];
      int x0 = int(v0[0] * scale[0] + transform[0]) % width;
      int y0 = int(v0[1] * scale[1] + transform[1]) % height;
      double z0 = v0[2] * scale[2] + transform[2];
      if (z0 <= minZ){
        minZ = z0;
      }
      if(z0>=maxZ){
        maxZ = z0;
      }
    }
  }
  for (int i = 0 ; i < numFaces ; i++){
      double v0[3];
      double v1[3];
      double v2[3];
      light[0] = 00 ; //x
      light[1] = 0;  //y
      light[2] = 100;//z
      v0[0] = vertices[ faces[i][0][0] - 1 ][0];
      v0[1] = vertices[ faces[i][0][0] - 1 ][1];
      v0[2] = vertices[ faces[i][0][0] - 1 ][2];
      
      double *v0T = this->transform(v0 , modelMatrix);
      v0[0] =  v0T[0];//(v0[0]*scale[0] +transform[0]);
      v0[1] =  v0T[1];//(v0[1]*scale[1] +transform[1]);
      v0[2] =  v0T[2];//(v0[2]*scale[2] +transform[2]);
      delete v0T;

      v1[0] = vertices[ faces[i][1][0] - 1][0];
      v1[1] = vertices[ faces[i][1][0] - 1][1];
      v1[2] = vertices[ faces[i][1][0] - 1][2];
      
      double *v1T = this->transform(v1, modelMatrix);
      v1[0] = v1T[0];// (v1[0]*scale[0] +transform[0]);
      v1[1] = v1T[1];// (v1[1]*scale[1] +transform[1]);
      v1[2] = v1T[2];// (v1[2]*scale[2] +transform[2]);
      delete v1T;

      v2[0] = vertices[ faces[i][2][0] - 1][0];
      v2[1] = vertices[ faces[i][2][0] - 1][1];
      v2[2] = vertices[ faces[i][2][0] - 1][2];

      double *v2T = this->transform(v2, modelMatrix);
      v2[0] = v2T[0];// (v2[0]*scale[0] +transform[0]);
      v2[1] = v2T[1];// (v2[1]*scale[1] +transform[1]);
      v2[2] = v2T[2];// (v2[2]*scale[2] +transform[2]);
      delete v2T;

      double vt0[2];
      double vt1[2];
      double vt2[2];
      double vt3[2];
      double **tcoords = new double*[4];
      tcoords[0] = new double[2];
      tcoords[0][0]=0;
      tcoords[0][1]=0;
      tcoords[1] = new double[2];
      tcoords[1][0]=0;
      tcoords[1][1]=0;
      tcoords[2] = new double[2];
      tcoords[2][0]=0;
      tcoords[2][1]=0;
      tcoords[3] = new double[2];
      tcoords[3][0]=0;
      tcoords[3][1]=0;
      if(hasTexture){
        vt0[0] = texCoords[faces[i][0][1] - 1 ][0];
        vt0[1] = texCoords[faces[i][0][1] - 1 ][1];

        vt1[0] = texCoords[faces[i][1][1] - 1 ][0];
        vt1[1] = texCoords[faces[i][1][1] - 1 ][1];

        vt2[0] = texCoords[faces[i][2][1] - 1 ][0];
        vt2[1] = texCoords[faces[i][2][1] - 1 ][1];
        tcoords[0][0] = vt0[0];
        tcoords[0][1] = vt0[1];
        
        tcoords[1][0] = vt1[0];
        tcoords[1][1] = vt1[1];

        tcoords[2][0] = vt2[0];
        tcoords[2][1] = vt2[1];

        if (facesLen[i]>3){
          vt3[0] = texCoords[faces[i][3][1] - 1 ][0];
          vt3[1] = texCoords[faces[i][3][1] - 1 ][1];
        }
      }

      double *d1 = substract(v1, v0, 3); // MUST DELETE[] THIS
      double *d2 = substract(v2, v0, 3); // MUST DELETE[] THIS
      double *normal = cross(d1, d2); // MUST DELETE[] THIS
      double *nnormal = normalize(normal , 3); // MUST DELETE[] THIS
      double *nlight = normalize(light, 3);    // MUST DELETE[] THIS
      light[0] = nlight[0];
      light[1] = nlight[1];
      light[2] = nlight[2];
      double intensity = dot(nnormal , nlight , 3);
      
    // AQUI NORMALS
      double ** thisNormals = new double*[3];
      thisNormals[0] = new double[3];
      thisNormals[0][0] = normals[faces[i][0][2] - 1][0];
      thisNormals[0][1] = normals[faces[i][0][2] - 1][1];
      thisNormals[0][2] = normals[faces[i][0][2] - 1][2];
      double * transNormals0 = this->transform(thisNormals[0] , rotationMatrix);
      thisNormals[0][0] = transNormals0[0];
      thisNormals[0][1] = transNormals0[1];
      thisNormals[0][2] = transNormals0[2];
      delete transNormals0;

      thisNormals[1] = new double[3];
      thisNormals[1][0] = normals[faces[i][1][2] - 1][0];
      thisNormals[1][1] = normals[faces[i][1][2] - 1][1];
      thisNormals[1][2] = normals[faces[i][1][2] - 1][2];
      double* transNormals1 = this->transform(thisNormals[1], rotationMatrix);
      thisNormals[1][0] = transNormals1[0];
      thisNormals[1][1] = transNormals1[1];
      thisNormals[1][2] = transNormals1[2];
      delete transNormals1;

      thisNormals[2] = new double[3];
      thisNormals[2][0] = normals[faces[i][2][2] - 1][0];
      thisNormals[2][1] = normals[faces[i][2][2] - 1][1];
      thisNormals[2][2] = normals[faces[i][2][2] - 1][2];
      double* transNormals2 = this->transform(thisNormals[2], rotationMatrix);
      thisNormals[2][0] = transNormals2[0];
      thisNormals[2][1] = transNormals2[1];
      thisNormals[2][2] = transNormals2[2];
      delete transNormals2;
      triangle_bc(v0,v1,v2, COLOR_VERTEX , tcoords , hasTexture , intensity , thisNormals, shader);
      if (facesLen[i] > 3){
        double *v3 = new double[3];
        v3[0] = vertices[faces[i][3][0] - 1][0];
        v3[1] = vertices[faces[i][3][0] - 1][1];
        v3[2] = vertices[faces[i][3][0] - 1][2];
        double *v3T = this->transform(v3 , modelMatrix);
        v3[0] = v3T[0];
        v3[1] = v3T[1];
        v3[2] = v3T[2];
        delete v3T;
        tcoords[1][0] = tcoords[2][0];
        tcoords[1][1] = tcoords[2][1];

        tcoords[2][0] = vt3[0];
        tcoords[2][1] = vt3[1];
        triangle_bc(v0, v2,v3, COLOR_VERTEX , tcoords , hasTexture , intensity , thisNormals, shader) ;
      }

      delete[] d1;
      delete[] d2;
      delete[] normal;
      delete[] nnormal;
      delete[] nlight;
      if(hasTexture){
        delete[] tcoords[0];
        delete[] tcoords[1];
        delete[] tcoords[2];
        delete[] tcoords[3];
        delete[] tcoords;
      }
    // }
  }
  if(!isWireframe){
    glFinishZBuffer("results/zbuffer.bmp");
  };
};

void Render::setTexture(string t){
  texture.openFile(t);
  texture.read();
};
//DESTRUCTOR
Render::~Render(){
  for (int i = 0; i < width; i++)
  {
    for (int j = 0; j < height; j++)
    {
      delete[] matrix[i][j];
    }
    delete[] matrix[i];
    delete[] zbuffer[i];
  }
  delete[] matrix;
  delete[] zbuffer;
};

string Render::getSom(){
  return "WIDTH: "+to_string(width)+"\nHEIGHT: "+to_string(height)+"\nFROM SHADER";
}

int* Render::gouradShader(double baryCoords[3],
      bool hasTexture,
      double **texcoords,
      double **normals,
      int color[3]){
  int b=color[0];
  int g=color[1];
  int r=color[2];
  if(hasTexture){
    double tx = texcoords[0][0] * baryCoords[0] + texcoords[1][0] * baryCoords[1] + texcoords[2][0]*baryCoords[2];
    double ty = texcoords[0][1] * baryCoords[0] + texcoords[1][1] * baryCoords[1] + texcoords[2][1]*baryCoords[2];
    int* texColor = texture.getColor(tx,ty);
    b = double(texColor[0]);//b * (double(texColor[0]) / double(255));
    g = double(texColor[1]);//g * (double(texColor[1]) / double(255));
    r = double(texColor[2]);//r * (double(texColor[2]) / double(255));
    delete [] texColor;
  }
  double normal[3];
  normal[0] = normals[0][0]*baryCoords[0] + normals[1][0]*baryCoords[1] + normals[2][0] * baryCoords[2];
  normal[1] = normals[0][1]*baryCoords[0] + normals[1][1]*baryCoords[1] + normals[2][1] * baryCoords[2];
  normal[2] = normals[0][2]*baryCoords[0] + normals[1][2]*baryCoords[1] + normals[2][2] * baryCoords[2];
  double *nnormal = normalize(normal,3);
  double intensity = dot(nnormal, light , 3);
    b = b * intensity;
    g = g * intensity;
    r = r * intensity;
  delete[] nnormal;
  int *finalColor = new int[3];//{int(r), int(g), int(b)};
  finalColor[2] = r;  
  finalColor[1] = g;
  finalColor[0] = b;  
  if(intensity<=0){
    finalColor[0] = 0;
    finalColor[1] = 0;
    finalColor[2] = 0;
  }
  return finalColor;
}

int* Render::toonShader(double baryCoords[3],
      bool hasTexture,
      double **texcoords,
      double **normals,
      int color[3]){
  int b=color[0];
  int g=color[1];
  int r=color[2];
  if(hasTexture){
    double tx = texcoords[0][0] * baryCoords[0] + texcoords[1][0] * baryCoords[1] + texcoords[2][0]*baryCoords[2];
    double ty = texcoords[0][1] * baryCoords[0] + texcoords[1][1] * baryCoords[1] + texcoords[2][1]*baryCoords[2];
    int* texColor = texture.getColor(tx,ty);
    b = b * (double(texColor[0]) / double(255));
    g = g * (double(texColor[1]) / double(255));
    r = r * (double(texColor[2]) / double(255));
    delete [] texColor;
  }
  double normal[3];
  normal[0] = normals[0][0]*baryCoords[0] + normals[1][0]*baryCoords[1] + normals[2][0] * baryCoords[2];
  normal[1] = normals[0][1]*baryCoords[0] + normals[1][1]*baryCoords[1] + normals[2][1] * baryCoords[2];
  normal[2] = normals[0][2]*baryCoords[0] + normals[1][2]*baryCoords[1] + normals[2][2] * baryCoords[2];
  double *nnormal = normalize(normal,3);
  double intensity = dot(nnormal, light , 3);
  if (intensity >=0 && intensity <0.2){
    intensity = 0;
  }else if(intensity >=0.2 && intensity < 0.4){
    intensity = 0.2;
  }else if(intensity >=0.4 && intensity < 0.6){
    intensity = 0.4;
  }else if(intensity >=0.6 && intensity < 0.8){
    intensity = 0.6;
  }else if(intensity >=0.8 && intensity < 1.0){
    intensity = 0.8;
  }else if(intensity = 1){
    intensity = 1;
  }else{
    intensity = 0;
  }
    b = b * intensity;
    g = g * intensity;
    r = r * intensity;
  delete[] nnormal;
  int *finalColor = new int[3];//{int(r), int(g), int(b)};
  finalColor[2] = r;  
  finalColor[1] = g;
  finalColor[0] = b;  
  if(intensity<=0){
    finalColor[0] = 0;
    finalColor[1] = 0;
    finalColor[2] = 0;
  }
  return finalColor;
}

// Introduce estática al modelo
int* Render::randomShader(
  double baryCoords[3],
  bool hasTexture,
  double **texcoords,
  double **normals,
  int color[3]
){
  int b=color[0];
  int g=color[1];
  int r=color[2];
  if(hasTexture){
    double tx = texcoords[0][0] * baryCoords[0] + texcoords[1][0] * baryCoords[1] + texcoords[2][0]*baryCoords[2];
    double ty = texcoords[0][1] * baryCoords[0] + texcoords[1][1] * baryCoords[1] + texcoords[2][1]*baryCoords[2];
    int* texColor = texture.getColor(tx,ty);
    b = b * (double(texColor[0]) / double(255));
    g = g * (double(texColor[1]) / double(255));
    r = r * (double(texColor[2]) / double(255));
    delete [] texColor;
  }
  double normal[3];
  normal[0] = normals[0][0]*baryCoords[0] + normals[1][0]*baryCoords[1] + normals[2][0] * baryCoords[2];
  normal[1] = normals[0][1]*baryCoords[0] + normals[1][1]*baryCoords[1] + normals[2][1] * baryCoords[2];
  normal[2] = normals[0][2]*baryCoords[0] + normals[1][2]*baryCoords[1] + normals[2][2] * baryCoords[2];
  double *nnormal = normalize(normal,3);
  double intensity = dot(nnormal, light , 3);
  int aleatorio = rand();
  b = b + (aleatorio%(255 - b));
  g = g + (aleatorio%(255 - g));
  r = r + (aleatorio%(255 - r));
  b = b * intensity;
  g = g * intensity;
  r = r * intensity;
  delete[] nnormal;
  int *finalColor = new int[3];//{int(r), int(g), int(b)};
  finalColor[2] = r;  
  finalColor[1] = g;
  finalColor[0] = b;  
  if(intensity<=0){
    finalColor[0] = 0;
    finalColor[1] = 0;
    finalColor[2] = 0;
  }
  return finalColor;
}

int* Render::unlitShader(
  double baryCoords[3],
  bool hasTexture,
  double **texcoords,
  double **normals,
  int color[3]
){
  int b=color[0];
  int g=color[1];
  int r=color[2];
  if(hasTexture){
    double tx = texcoords[0][0] * baryCoords[0] + texcoords[1][0] * baryCoords[1] + texcoords[2][0]*baryCoords[2];
    double ty = texcoords[0][1] * baryCoords[0] + texcoords[1][1] * baryCoords[1] + texcoords[2][1]*baryCoords[2];
    int* texColor = texture.getColor(tx,ty);
    b = b * (double(texColor[0]) / double(255));
    g = g * (double(texColor[1]) / double(255));
    r = r * (double(texColor[2]) / double(255));
    delete [] texColor;
  }
  double normal[3];
  normal[0] = normals[0][0]*baryCoords[0] + normals[1][0]*baryCoords[1] + normals[2][0] * baryCoords[2];
  normal[1] = normals[0][1]*baryCoords[0] + normals[1][1]*baryCoords[1] + normals[2][1] * baryCoords[2];
  normal[2] = normals[0][2]*baryCoords[0] + normals[1][2]*baryCoords[1] + normals[2][2] * baryCoords[2];
  int *finalColor = new int[3];//{int(r), int(g), int(b)};
  finalColor[2] = r;  
  finalColor[1] = g;
  finalColor[0] = b;  
  return finalColor;
}


int* Render::inverseShader(
  double baryCoords[3],
  bool hasTexture,
  double **texcoords,
  double **normals,
  int color[3]
){
  int b=color[0];
  int g=color[1];
  int r=color[2];
  if(hasTexture){
    double tx = texcoords[0][0] * baryCoords[0] + texcoords[1][0] * baryCoords[1] + texcoords[2][0]*baryCoords[2];
    double ty = texcoords[0][1] * baryCoords[0] + texcoords[1][1] * baryCoords[1] + texcoords[2][1]*baryCoords[2];
    int* texColor = texture.getColor(tx,ty);
    b = b * (double(texColor[0]) / double(255));
    g = g * (double(texColor[1]) / double(255));
    r = r * (double(texColor[2]) / double(255));
    delete [] texColor;
  }
  double normal[3];
  normal[0] = normals[0][0]*baryCoords[0] + normals[1][0]*baryCoords[1] + normals[2][0] * baryCoords[2];
  normal[1] = normals[0][1]*baryCoords[0] + normals[1][1]*baryCoords[1] + normals[2][1] * baryCoords[2];
  normal[2] = normals[0][2]*baryCoords[0] + normals[1][2]*baryCoords[1] + normals[2][2] * baryCoords[2];
  double *nnormal = normalize(normal,3);
  double intensity = dot(nnormal, light , 3);
  intensity = 1 - intensity;
  b = b * intensity;
  g = g * intensity;
  r = r * intensity;
  delete[] nnormal;
  int *finalColor = new int[3];//{int(r), int(g), int(b)};
  finalColor[2] = r;  
  finalColor[1] = g;
  finalColor[0] = b;  
  if(intensity<=0){
    finalColor[0] = 0;
    finalColor[1] = 0;
    finalColor[2] = 0;
  }
  return finalColor;

}

int *Render::randomChannelShader(
    double baryCoords[3],
    bool hasTexture,
    double **texcoords,
    double **normals,
    int color[3])
{
  int b = color[0];
  int g = color[1];
  int r = color[2];
  if (hasTexture)
  {
    double tx = texcoords[0][0] * baryCoords[0] + texcoords[1][0] * baryCoords[1] + texcoords[2][0] * baryCoords[2];
    double ty = texcoords[0][1] * baryCoords[0] + texcoords[1][1] * baryCoords[1] + texcoords[2][1] * baryCoords[2];
    int *texColor = texture.getColor(tx, ty);
    b = b * (double(texColor[0]) / double(255));
    g = g * (double(texColor[1]) / double(255));
    r = r * (double(texColor[2]) / double(255));
    delete[] texColor;
  }
  double normal[3];
  normal[0] = normals[0][0] * baryCoords[0] + normals[1][0] * baryCoords[1] + normals[2][0] * baryCoords[2];
  normal[1] = normals[0][1] * baryCoords[0] + normals[1][1] * baryCoords[1] + normals[2][1] * baryCoords[2];
  normal[2] = normals[0][2] * baryCoords[0] + normals[1][2] * baryCoords[1] + normals[2][2] * baryCoords[2];
  double *nnormal = normalize(normal, 3);
  double intensity = dot(nnormal, light, 3);
  int aleatorio = rand();
  int canal = rand()%3;
  canal == 0 ? b = b + (aleatorio % (255 - b)) : (canal == 1 ? g = g + (aleatorio % (255 - g)) : r = r + (aleatorio % (255 - r)));
  b = b * intensity;
  g = g * intensity;
  r = r * intensity;
  delete[] nnormal;
  int *finalColor = new int[3]; //{int(r), int(g), int(b)};
  finalColor[2] = r;
  finalColor[1] = g;
  finalColor[0] = b;
  if (intensity <= 0)
  {
    finalColor[0] = 0;
    finalColor[1] = 0;
    finalColor[2] = 0;
  }
  return finalColor;
}

int* Render::toonShaderGold(double baryCoords[3],
      bool hasTexture,
      double **texcoords,
      double **normals,
      int color[3]){
  int b=color[0];
  int g=color[1];
  int r=color[2];
  if(hasTexture){
    double tx = texcoords[0][0] * baryCoords[0] + texcoords[1][0] * baryCoords[1] + texcoords[2][0]*baryCoords[2];
    double ty = texcoords[0][1] * baryCoords[0] + texcoords[1][1] * baryCoords[1] + texcoords[2][1]*baryCoords[2];
    int* texColor = texture.getColor(tx,ty);
    b = b * (double(texColor[0]) / double(255));
    g = g * (double(texColor[1]) / double(255));
    r = r * (double(texColor[2]) / double(255));
    delete [] texColor;
  }
  double normal[3];
  normal[0] = normals[0][0]*baryCoords[0] + normals[1][0]*baryCoords[1] + normals[2][0] * baryCoords[2];
  normal[1] = normals[0][1]*baryCoords[0] + normals[1][1]*baryCoords[1] + normals[2][1] * baryCoords[2];
  normal[2] = normals[0][2]*baryCoords[0] + normals[1][2]*baryCoords[1] + normals[2][2] * baryCoords[2];
  double *nnormal = normalize(normal,3);
  double intensity = dot(nnormal, light , 3);
  double red = 1;
  if (intensity >=0 && intensity <0.2){
    intensity = 0;
    r = 0;
    g = 255 * intensity;
    // b = 0;
  }else if(intensity >=0.2 && intensity < 0.4){
    intensity = 0.2;
    r = 255 * intensity;
    g = 255 * intensity;
    // b = 0;
  }else if(intensity >=0.4 && intensity < 0.6){
    intensity = 0.4;
    r = 255 * intensity;
    g = 255 * intensity;
    // b = 0;
  }else if(intensity >=0.6 && intensity < 0.8){
    intensity = 0.6;
    r = 255 * intensity;
    g = 255 * intensity;
    // b = 0;
  }else if(intensity >=0.8 && intensity < 1.0){
    intensity = 0.8;
    r = 255 * intensity;
    g = 255 * intensity;
    // b = 0;
  }else if(intensity = 1){
    intensity = 1;
    r = 255;
    g = 255;
    // b = 0;
  }else{
    intensity = 0;
  }
    b = b * intensity;
    g = g * intensity;
    r = r * intensity;
  delete[] nnormal;
  int *finalColor = new int[3];//{int(r), int(g), int(b)};
  finalColor[2] = r;  
  finalColor[1] = g;
  finalColor[0] = b;  
  if(intensity<=0){
    finalColor[0] = 0;
    finalColor[1] = 0;
    finalColor[2] = 0;
  }
  return finalColor;
}

// Este es técnicamente un shader
void Render::PostProcessEffect(
    string pathFaces , 
    string pathBackground){
  Texture face;
  face.openFile(pathFaces);
  face.read();
  Texture background;
  background.openFile(pathBackground);
  background.read();
  glInit();
  glClearColor(0.0, 0.0, 0.0);
  glColor(1.0, 1.0, 1.0);
  glCreateWindow(face.getWidth(), face.getHeight());
  for (int i = 0; i < height; i++){
    for (int j = 0; j < width; j++){
      // Aqui tengo un pixel individual
      double tx = double(j)/width;
      double ty = double(i)/height;
      int *faceColor = face.getColor(tx,ty);
      if( faceColor[0] == COLOR_CLEAR[0] && 
        faceColor[1] == COLOR_CLEAR[1] && 
        faceColor[2] == COLOR_CLEAR[2] ){
          int *backColor = background.getColor(tx, ty);
          matrix[j][i][0] = backColor[0];
          matrix[j][i][1] = backColor[1];
          matrix[j][i][2] = backColor[2];
          delete[] backColor;
      }else{
        matrix[j][i][0] = faceColor[0];
        matrix[j][i][1] = faceColor[1];
        matrix[j][i][2] = faceColor[2];
      }
      delete[] faceColor;      
    }
  }
  glFinish("results/PostProcessFX.bmp");
}