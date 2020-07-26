/* -------------------------------------------------------------------  
LAB1.cpp
Algoritmo que escribe un archivo BMP con el nombre de 'LAB1.bmp',
implementando glPoligonFill.
glPolygonFill usa como apoyo a  pointInPoligon.
Marco Fuentes - 18188
Gráficas por computadora - Segundo Semestre 2020 - UVG
------------------------------------------------------------------- */
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

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
  void glLine_abs(int x0, int y0, int x1, int y1);
  void glDrawSquare(double *ld, double *lu, double *rd, double *ru);
  void glFinish();
  string toString();
  string getMatrix();
  int GDCtoPixels(double x, bool isX);
  void drawPoligon(int[][2], int);
  bool pointOnPoligon(float poligon[][2], int nVertices, float point[2]);
  void glPoligonFill(int poligon[][2] , int nVertices );
  ~Render();
};
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
  if (this->width > 0)
  {
    for (int i = 0; i < w; i++)
    {
      for (int j = 0; j < h; j++)
      {
        delete[] matrix[i][j];
      }
      delete[] matrix[i];
    }
    delete[] matrix;
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
  for (int i = 0; i < this->width; i++)
  {
    matrix[i] = new int *[this->height];
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
void Render::glLine_abs(int x_0, int y_0, int x_1, int y_1)
{
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
void Render::glDrawSquare(double *ld, double *lu, double *rd, double *ru)
{
  glLine(ld[0], ld[1], lu[0], lu[1]);
  glLine(lu[0], lu[1], ru[0], ru[1]);
  glLine(ru[0], ru[1], rd[0], rd[1]);
  glLine(rd[0], rd[1], ld[0], ld[1]);
}
void Render::drawPoligon(int arr[][2], int size)
{
  for (int i = 0; i < size; i++)
  {
    glLine_abs(arr[i][0], arr[i][1], arr[(i + 1) % size][0], arr[(i + 1) % size][1]);
  }
}
bool Render::pointOnPoligon(float poligon[][2], int nVertices, float point[2]){
  // Codigo inspirado en http://alienryderflex.com/polygon/, por Nathan Mercer
  bool isIn = false;
  int j = nVertices -1;
  for ( int i = 0 ; i < nVertices ; i++){
    if ((poligon[i][0] <= point[0] || poligon[j][0] <= point[0]) 
      && (poligon[i][1] < point[1] 
        && poligon[j][1] >= point[1] || poligon[j][1] < point[1] 
          && poligon[i][1] >= point[1] ) ) { //Reviso que tenga aristas arriba, abajo y a la izquierda del punto
      if (poligon[i][0] + (point[1] - poligon[i][1]) / (poligon[j][1] - poligon[i][1]) * (poligon[j][0] - poligon[i][0]) < point[0]){
        isIn = !isIn;
      }
    }
    j = i;
  }
  return isIn;
}
void Render::glPoligonFill( int poligon[][2] , int nVertices ){
  int xmin = poligon[0][1] , xmax = poligon[0][1] , ymin = poligon[0][1] , ymax = poligon[0][1];
  //Encierro la figura en un cuadrado adecuado a su tamaño, por motivos de performance
  float fPoli[nVertices][2];
  for (int i = 0 ; i < nVertices ; i++){
    if (xmin > poligon[i][0]){
      xmin = poligon[i][0];
    }
    if (xmax < poligon[i][0]){
      xmax = poligon[i][0];
    }
    if (ymin > poligon[i][1]){
      ymin = poligon[i][1];
    }
    if (ymax < poligon[i][1]){
      ymax = poligon[i][1];
    }
    fPoli[i][0] = (float)poligon[i][0];
    fPoli[i][1] = (float)poligon[i][1];
  }
  for (int x = xmin ; x <= xmax ; x++){
    for (int y = ymin ; y <= ymax ; y++){
      float arr[2] = {(float)x, (float)y};
      if (pointOnPoligon(fPoli , nVertices ,  arr )){
        matrix[x][y][0] = COLOR_VERTEX[0];
        matrix[x][y][1] = COLOR_VERTEX[1];
        matrix[x][y][2] = COLOR_VERTEX[2];
      }
    }
  }
}
//Todos son arrays de dos elementos indicando las coordenadas del vertice
void Render::glFinish()
{
  // Crear archivo
  ofstream archivo;
  archivo.open("LAB1.bmp", ios::binary);
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
Render::~Render()
{
  for (int i = 0; i < width; i++)
  {
    for (int j = 0; j < height; j++)
    {
      delete[] matrix[i][j];
    }
    delete[] matrix[i];
  }
  delete[] matrix;
};

// Main function
int main()
{
  //Implementacion
  Render r;
  r.glInit();
  r.glColor(0.0, 0.0, 1.0); //Azul
  r.glClearColor(0.0, 1.0, 0.0);
  r.glCreateWindow(800, 800);
  r.glClear();
  r.glViewPort(100, 100, 600, 600);

  // for (double i = 0.0; i < 1; i = i + 0.01)
  // {
  //   double ld[2] = {-1, -1 + 2 * i};
  //   double lu[2] = {-1 + 2 * i, 1};
  //   double ru[2] = {1, 1 - 2 * i};
  //   double rd[2] = {1 - 2 * i, -1};
  //   r.glDrawSquare(ld, lu, rd, ru);
  // }

  int lista[][2] = {{165, 380}, {185, 360}, {180, 330}, {207, 345}, {233, 330}, {230, 360}, {250, 380}, {220, 385}, {205, 410}, {193, 383}};
  r.drawPoligon(lista, 10);
  r.glPoligonFill(lista, 10);

  r.glColor(0.0, 1.0, 1.0); //Azul
  int lista0[][2] = {{321, 335} ,{288, 286} ,{339, 251} ,{374, 302} };
  r.drawPoligon(lista0, 4);
  r.glPoligonFill(lista0, 4);

  r.glColor(1.0, 0.0, 1.0); //Azul
  int lista1[][2]  = {{377, 249} , {411, 197} , {436, 249}};
  r.drawPoligon(lista1, 3);
  r.glPoligonFill(lista1, 3);

  r.glColor(1.0, 1.0, 1.0); //Azul
  int lista2[][2] = {{413, 177} , {448, 159} , {502, 88} , {553, 53} , {535, 36} , {676, 37} , {660, 52} , {750, 145} , {761, 179} , {672, 192} , {659, 214} , {615, 214} , {632, 230} , {580, 230} , {597, 215} , {552, 214} , {517, 144} , {466, 180} };
  r.drawPoligon(lista2, 18);
  r.glPoligonFill(lista2, 18);

  r.glColor(0.0, 1.0, 0.0); //Azul
  int lista3[][2] = {{682, 175} ,{708, 120} ,{735, 148} ,{739, 170}};
  r.drawPoligon(lista3, 4);
  r.glPoligonFill(lista3, 4);
  // //Guardo el archivo
  r.glFinish();
}
