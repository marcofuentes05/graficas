/* -------------------------------------------------------------------  
Render.cpp
Algoritmo que escribe un archivo BMP con el nombre de 'SR5.bmp',
representando un wireframde de un modelo OBJ.
Marco Fuentes - 18188
Gráficas por computadora - Segundo Semestre 2020 - UVG
------------------------------------------------------------------- */
#include "Render.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <algorithm>
#include <stdlib.h>
using namespace std;

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
void Render::glViewPort(int x, int y, int width, int height)
{
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
    for (int j = 0; j < width; j++)
    {

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
        if (zbuffer[j][i] != -1 * std::numeric_limits<double>::infinity()){
          valor = int((zbuffer[j][i]-minZ ) * 255 / (double)(maxZ - minZ) );
        }
        archivo.write((char *)&valor, 1);
      }
    }
  }
  archivo.close();
};

double * Render::transform(double vector[3] ,  int transform[3] , int scale[3]){ 
  double *result = new double[3];
  result[0] = (vector[0] * scale[0] + transform[0]);
  result[1] = (vector[1] * scale[1] + transform[1]);
  result[2] = (vector[2] * scale[2] + transform[2]);
  return result;
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

void Render::triangle_bc(double v1[3] , double v2[3] , double v3[3] , int color[3] , double**texcoords , bool hasTexture , double intensity){
  int _color[3];
  int minx = int(min(v1[0] , min(v2[0], v3[0])));
  int miny = int(min(v1[1], min(v2[1], v3[1])));

  int maxx = int(max(v1[0], max(v2[0], v3[0])));
  int maxy = int(max(v1[1], max(v2[1], v3[1])));

  double b , g , r;
  for (int i = minx; i <= maxx; i++){
    for (int j = miny; j <= maxy; j++){
      double p[2] = {(double)i, (double)j};
      double *bary = baryCoords(v1, v2, v3, p); // DELETE[] THIS
      if (bary[0] >= 0 && bary[1] >= 0 && bary[2] >= 0){
        double z = v1[2] * bary[0] + v2[2] * bary[1] + v3[2] * bary[2];
        if (z > zbuffer[i][j]){
          _color[0] = int(double(color[0]) * intensity);
          _color[1] = int(double(color[1]) * intensity);
          _color[2] = int(double(color[2]) * intensity);
          if(hasTexture){
            double tx = texcoords[0][0] * bary[0] + texcoords[1][0] * bary[1] + texcoords[2][0]*bary[2];
            double ty = texcoords[0][1] * bary[0] + texcoords[1][1] * bary[1] + texcoords[2][1]*bary[2];
            int* texColor = texture.getColor(tx,ty);
            _color[0] = int(_color[0] * double(texColor[0]) / 255);
            _color[1] = int(_color[1] * double(texColor[1]) / 255);
            _color[2] = int(_color[2] * double(texColor[2]) / 255);
            delete [] texColor;
          }
          zbuffer[i][j] = z;
          glVertexAbs(j, i, _color );
        }
      }
      delete[] bary;
    }
  }
}

void Render::loadModel(string name , int transform[3] , int scale[3] , bool isWireframe , bool hasTexture){
  OBJ obj(name);
  obj.read();
  int numFaces = obj.getNumFaces();
  int* facesLen = obj.getFacesLen();
  int *** faces = obj.getFaces();
  double** vertices = obj.getVertices();
  double ** texCoords = obj.getTexCoords();
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
      x0 = x0 < 0 ? x0 * (-1) : x0;
      y0 = y0 < 0 ? y0 * (-1) : y0;
      if (z0 < minZ){
        minZ = z0;
      }
      if(z0>maxZ){
        maxZ = z0;
      }
    }
  }
  for (int i = 0 ; i < numFaces ; i++){
    if (isWireframe) {
      for (int j = 0 ; j < facesLen[i] ; j++){
        v0[0] = vertices[ faces[i][ j ][ 0 ] - 1 ][0];
        v0[1] = vertices[ faces[i][ j ][ 0 ] - 1 ][1];

        v1[0] = vertices[ faces[i][ (j + 1) % facesLen[i] ][0] - 1 ][0];
        v1[1] = vertices[ faces[i][ (j + 1) % facesLen[i] ][0] - 1 ][1];

        int x0 = int(v0[0]*scale[0] + transform[0]) % width ;
        int y0 = int(v0[1]*scale[1] + transform[1]) % height ;
        int x1 = int(v1[0] * scale[0] + transform[0]) % width ;
        int y1 = int(v1[1] * scale[1] + transform[1]) % height ;

        x0 = x0<0 ? x0*(-1) : x0;
        y0 = y0<0 ? y0*(-1) : y0;
        x1 = x1<0 ? x1*(-1) : x1;
        y1 = y1<0 ? y1*(-1) : y1; 

        glLineAbs(x0,y0,x1,y1);
      }
    }else{
      double v0[3];
      double v1[3];
      double v2[3];
      double light[3] = {00,50, 100};
      v0[0] = vertices[ faces[i][0][0] - 1 ][0];
      v0[1] = vertices[ faces[i][0][0] - 1 ][1];
      v0[2] = vertices[ faces[i][0][0] - 1 ][2];

      v1[0] = vertices[ faces[i][1][0] - 1][0];
      v1[1] = vertices[ faces[i][1][0] - 1][1];
      v1[2] = vertices[ faces[i][1][0] - 1][2];

      v2[0] = vertices[ faces[i][2][0] - 1][0];
      v2[1] = vertices[ faces[i][2][0] - 1][1];
      v2[2] = vertices[ faces[i][2][0] - 1][2];

      v0[0] =  (v0[0]*scale[0] +transform[0]);
      v0[1] =  (v0[1]*scale[1] +transform[1]);
      v0[2] =  (v0[2]*scale[2] +transform[2]);
      
      v1[0] =  (v1[0]*scale[0] +transform[0]);
      v1[1] =  (v1[1]*scale[1] +transform[1]);
      v1[2] =  (v1[2]*scale[2] +transform[2]);
      
      v2[0] =  (v2[0]*scale[0] +transform[0]);
      v2[1] =  (v2[1]*scale[1] +transform[1]);
      v2[2] =  (v2[2]*scale[2] +transform[2]);
     
      double vt0[2];
      double vt1[2];
      double vt2[2];
      double vt3[2];
      double **tcoords = new double*[4];
      tcoords[0] = new double[2];
      tcoords[1] = new double[2];
      tcoords[2] = new double[2];
      tcoords[3] = new double[2];
      if(hasTexture){
        vt0[0] = texCoords[faces[i][0][1] - 1 ][0];
        vt0[1] = texCoords[faces[i][0][1] - 1 ][1];
        // vt0[2] = texCoords[faces[i][0][1] - 1 ][2];

        vt1[0] = texCoords[faces[i][1][1] - 1 ][0];
        vt1[1] = texCoords[faces[i][1][1] - 1 ][1];
        // vt1[2] = texCoords[faces[i][1][1] - 1 ][2];

        vt2[0] = texCoords[faces[i][2][1] - 1 ][0];
        vt2[1] = texCoords[faces[i][2][1] - 1 ][1];
        // vt2[2] = texCoords[faces[i][2][1] - 1 ][2];
        tcoords[0][0] = vt0[0];
        tcoords[0][1] = vt0[1];
        // tcoords[0][2] = vt0[2];
        tcoords[1][0] = vt1[0];
        tcoords[1][1] = vt1[1];
        tcoords[1][2] = vt1[2];

        tcoords[2][0] = vt2[0];
        tcoords[2][1] = vt2[1];
        tcoords[2][2] = vt2[2];

        if (facesLen[i]>3){
          vt3[0] = texCoords[faces[i][3][1] - 1 ][0];
          vt3[1] = texCoords[faces[i][3][1] - 1 ][1];
          // vt3[2] = texCoords[faces[i][3][1] - 1 ][2];
        }
      }

      double *d1 = substract(v1, v0, 3); // MUST DELETE[] THIS
      double *d2 = substract(v2, v0, 3); // MUST DELETE[] THIS
      double *normal = cross(d1, d2); // MUST DELETE[] THIS
      double *nnormal = normalize(normal , 3); // MUST DELETE[] THIS
      double *nlight = normalize(light, 3);    // MUST DELETE[] THIS
      double intensity = dot(nnormal , nlight , 3);
      int color[3] = {50,50,50};
      
      if (intensity >= 0){ 
        color[0] = int(COLOR_VERTEX[0] * intensity);
        color[1] = int(COLOR_VERTEX[1] * intensity);
        color[2] = int(COLOR_VERTEX[2] * intensity);
        triangle_bc(v0,v1,v2, COLOR_VERTEX , tcoords , hasTexture , intensity );
        if (facesLen[i] > 3){
          double v3[3];
          v3[0] = vertices[faces[i][3][0] - 1][0];
          v3[1] = vertices[faces[i][3][0] - 1][1];
          v3[2] = vertices[faces[i][3][0] - 1][2];
          double *v3Transformed = this->transform(v3, transform, scale);
          if(facesLen[i] > 3){
            tcoords[3] = vt3; 
          }
          triangle_bc(v0, v2,v3, color , tcoords , hasTexture , intensity) ;
          delete[] v3Transformed;
        }
      };

      // delete[] v0Transformed;
      // delete[] v1Transformed;
      // delete[] v2Transformed;
      delete[] d1;
      delete[] d2;
      delete[] normal;
      delete[] nnormal;
      delete[] nlight;
      delete[] tcoords[0];
      delete[] tcoords[1];
      delete[] tcoords[2];
      delete[] tcoords[3];
      delete[] tcoords;
    }
  }
  if(!isWireframe){
    glFinishZBuffer("zbuffer.bmp");
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
