/* -------------------------------------------------------------------  
Render.cpp
Clase que renderiza modelos OBJ a formato BMP.
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
int abs(int m){
  return (m < 0) ? -m : m;
}

void swap(int *a, int *b){
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
  fov = 60;
};

void Render::glCreateWindow(int width, int height){
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
  if (modw == 0){
    this->width = width;
    this->view_width = width;
  }else{
    this->width = width + (4 - modw);
    this->view_width = width + (4 - modw);
  }
  if (modh == 0){
    this->height = height;
    this->view_height = height;
  }else{
    this->height = height + (4 - modh);
    this->view_height = height + (4 - modh);
  }
  //Crear nueva matriz dinamica
  matrix = new int **[this->width];
  zbuffer = new double*[this->width];
  for (int i = 0; i < this->width; i++){
    matrix[i] = new int *[this->height];
    zbuffer[i] = new double [this->height];
    for (int j = 0; j < this->height; j++){
      matrix[i][j] = new int[3];
    };
  };
  glViewPort(0,0,width, height);
};

void Render::glViewPort(int x, int y, int width, int height){
  try{
    if ((x + width <= this->width) && (y + height <= this->height)){
      x_view = x;
      y_view = y;
      view_height = height;
      view_width = width;
      double vMatrix[4][4] = {
        {double(width)/2 , 0,0,x+double(width)/2},
        {0, double(height)/2, 0, y + double(height)/2},
        {0,0,0.5,0.5},
        {0,0,0,1}
      };
      viewPortMatrix = Matrix(vMatrix);
    }else{
      throw 1;
    }
  }
  catch (int error){
    if (error == 1){
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

void Render::glClear(){
  for (int i = 0; i < height; i++){
    for (int j = 0; j < width; j++){
      zbuffer[j][i] = /*-1 **/ std::numeric_limits<double>::infinity();
      for (int k = 0; k < 3; k++){
        matrix[j][i][k] = COLOR_CLEAR[k];
      };
    };
  };
}

int Render::GDCtoPixels(double x, bool isX){
  return isX ? (int)(x_view + ((x + 1) * view_width / 2)) : (int)(y_view + ((x + 1) * view_height / 2));
}

void Render::glVertex(double x, double y){
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
      if (y_0 < y_1){
        y = y + 1;
      }else{
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
  for (int i = 0; i < height; i++){
    for (int j = 0; j < width; j++){
      for (int k = 0; k < 3; k++){
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
  for (int i = 0; i < this->height; i++){
    for (int j = 0; j < this->width; j++){
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

void Render::lookAt(double eye[3], double camPosition[3]){
  double* forward = substract(camPosition, eye , 3);
  double *forwardN = normalize(forward,3);
  double *randomVector = new double[3];
  randomVector[0] = 0;
  randomVector[1] = 1;
  randomVector[2] = 0;
  double *right = cross(randomVector, forwardN );
  double *rightN = normalize(right , 3);
  double *up = cross(forwardN , rightN);
  double *upN = normalize(up , 3);
  
  double matriz[4][4] = {
    {rightN[0], upN[0], forwardN[0], camPosition[0]},
    {rightN[1], upN[1], forwardN[1], camPosition[1]},
    {rightN[2], upN[2], forwardN[2], camPosition[2]},
    {0,0,0,1}
  };

  camMatrix = Matrix(matriz);
  // camMatrix.toString();
  // exit(1);

  delete upN;
  delete up;
  delete randomVector;
  delete forwardN;
  delete rightN;
}

double toRad(double deg){
  return deg * PI / 180;
}

void Render::rtRender(){
  for (int j = 0 ; j < height ; j++){
    for (int i = 0 ; i < width ; i++){
      // Convertir a NDC
      double px = 2*((double(i)+0.5)/width)-1;
      double py = 2 * ((double(j) + 0.5) / height) - 1;

      // Calcular FOV suponiendo que el nearPlane esta a 1m de la camara
      double t = tan((fov*PI/180)/2);
      double r = t * width /height;

      px = px * r;
      py = py * t;

      double direction[3] = {px,py,-1}; //Camara siempre apunta a -z
      double *normalDirection = normalize(direction,3); // DELETE THIS
      Material material;
      bool hasM = false;
      for (auto item : scene){
        Intersect intersect = item.ray_intersect(camPosition , normalDirection);
        if (!intersect.getIsNone()){ 
          if ( intersect.getDistance() < zbuffer[i][j] ){
            zbuffer[i][j] = intersect.getDistance();
            material = item.getMaterial();
            double *diffuse = material.getDiffuse();
            int iDiffuse[3] = {
              int(diffuse[0]*255),
              int(diffuse[1]*255),
              int(diffuse[2]*255)
            };
            glVertexAbs( j , i , iDiffuse);
          }
        }
      } 
      delete normalDirection;
    }
  }
}
//DESTRUCTOR
Render::~Render(){
  for (int i = 0; i < width; i++){
    for (int j = 0; j < height; j++){
      delete[] matrix[i][j];
    }
    delete[] matrix[i];
    // delete[] zbuffer[i];
  }
  delete[] matrix;
  // delete[] zbuffer;
};
