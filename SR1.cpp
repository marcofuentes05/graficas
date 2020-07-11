#include <iostream>
#include <fstream>
#include <string>
using namespace std;
/*----------------------------------------------------------------
Idea de ***matrix obtenida de Stack Overflow:
https://stackoverflow.com/questions/32675730/matrix-pointer-c
----------------------------------------------------------------*/
class Render{
  int width, height, x_view , y_view, view_width, view_height;
  int ***matrix;
  int COLOR_CLEAR[3];
  int COLOR_VERTEX[3];
  public:
    void glInit();
    void glCreateWindow(int width, int height);
    void glViewPort(int x, int y, int width , int height);
    void glClear();
    void glClearColor(double r,double g,double b);
    void glVertex(double x, double y);
    void glColor(double r, double g, double b);
    void glFinish();
    string toString(); 
    string getMatrix();
    void test(){
      matrix[0][0][0] = 1; //superior izquierda
      matrix[0][0][1] = 1;
      matrix[0][0][2] = 1;
      matrix[width-1][height -1][0] = 1;//inferior derecha
      matrix[width-1][height -1][1] = 1;
      matrix[width-1][height -1][2] = 1;
      matrix[width - 1][0][0] = 1;//superior derecha
      matrix[width - 1][0][1] = 1;
      matrix[width - 1][0][2] = 1;
      matrix[0][height - 1][0] = 1;//inferior izquierda
      matrix[0][height - 1][1] = 1;
      matrix[0][height - 1][2] = 1;
    };
    ~Render();
};
void Render::glInit(){
  width = 0;
  height = 0;
  x_view = 0;
  y_view = 0;
  view_width = 0;
  view_height = 0;
  glClearColor(0.0,0.0,0.0);
  glColor(0.0, 0.0, 0.0);
};
void Render::glCreateWindow(int width, int height){
  this->width = width;
  this->height = height;
  this ->view_height = height;
  this->view_width = width;
  matrix = new int**[width];
  for (int i = 0 ; i<width;i++){
    matrix[i] = new int*[height];
    for(int j =0;j<height;j++){
      matrix[i][j] = new int[3];
    };
  };
};
void Render::glViewPort(int x , int y ,int width , int height){
  x_view = x;
  y_view = y;
  view_height=height;
  view_width = width;
}
void Render::glClearColor(double r, double g, double b){
  this->COLOR_CLEAR[0] = int(r*255);
  this->COLOR_CLEAR[1] = int(g * 255);
  this->COLOR_CLEAR[2] = int(b * 255);
};
void Render::glColor(double r, double g, double b){
  this->COLOR_VERTEX[0] = (r * 255);
  this->COLOR_VERTEX[1] = (g * 255);
  this->COLOR_VERTEX[2] = (b * 255);
};
string Render::toString(){
  return "Width: "+to_string(width)+"\nHeight: "+to_string(height);
}
string Render::getMatrix(){
  string r = "MATRIZ: \n";
  for (int i = 0 ; i< height;i++){
    for (int j = 0;j<width ; j++){
      r+="(";
      for (int k = 0; k<3 ; k++){
        r+= to_string(matrix[j][i][k]) + " , ";
      };
      r += ")  " ;
    };
    r+="\n";
  };
  return r;
}
void Render::glClear(){
  for (int i = 0 ; i< height;i++){
    for (int j = 0;j<width ; j++){
      for (int k = 0; k<3 ; k++){
        matrix[j][i][k] = COLOR_CLEAR[k];
      };
    };
  };
}
void Render::glVertex(double x , double y){
    //x,y son decimales pertenecientes a [-1,1]
    int x_coor,y_coor = 0;
    x_coor = x_view + (int)((x+1)*view_width/2);
    y_coor = y_view + (int)((-y + 1) * view_height / 2);
    matrix[x_coor][y_coor] = COLOR_VERTEX;
    cout << to_string(COLOR_VERTEX[0]) <<endl;
};
void Render::glFinish(){
  // Crear archivo
  ofstream archivo("miImagen.bmp");
  // File type data
  unsigned char B = 'B';
  unsigned char M = 'M';
  unsigned int size = 14 + 40 + width * height * 3;
  unsigned int reserved = 0;
  unsigned int pixelDataOffset = 14 + 40;
  archivo << B;
  archivo << M;
  archivo << size;
  archivo << reserved;
  archivo << pixelDataOffset;

  //Image information data
  unsigned int headerSize = 40;
  unsigned short planes =1; 
  unsigned short bitsPerPixel= 24;
  unsigned int compression = 0;
  unsigned int varios = 0;
  unsigned int imageSize = this->width * this->height * 3 ;
  archivo << headerSize ;
  archivo << width;
  archivo << height;
  archivo << planes ;
  archivo << bitsPerPixel;
  archivo << compression;
  archivo << imageSize;
  
  archivo << varios;
  archivo << varios;
  archivo << varios;
  archivo << varios;

  //Color pallete

  //Raw pixel data
  cout << "Tamaño de  un pixel "<<sizeof(matrix[1][2][0]) <<endl;
  for (int i = 0 ;i < height ; i++){
    for (int j = 0 ; j < width ; j++){
      unsigned char r = matrix[i][j][0];
      unsigned char g = matrix[i][j][1];
      unsigned char b = matrix[i][j][2];
      archivo << b;
      archivo << g;
      archivo << r;
    }
  }
  archivo.close();
};
Render::~Render(){
  delete matrix;
};

// Main function
int main(){
  Render r;
  r.glInit();
  r.glCreateWindow(10,10);
  r.glClear();
  r.glColor(1.0,1.0,1.0);
  r.glViewPort(1,2,5,5);
  r.glVertex(-1.0,1.0);
  r.glFinish();
  // cout << sizeof(unsigned int) << endl; -- 4
  // cout << sizeof(unsigned short) << endl; -- 2
  // cout << sizeof(unsigned char) << endl; -- 1
}

