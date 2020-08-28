#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include "Render.hpp"
#include "OBJ.hpp"
#include "linearAlgebra.hpp"
#include "Texture.hpp"
#include "Matrix.hpp"
using namespace std;
Matrix multi(Matrix  &m0 , Matrix &m1){
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

int main(){  
  bool hasTexture = false;
  string modelPath = "models/helmet.obj";


  double matriz[4][4] = {
    {1,1,0,0},
    {0,-1,-2,0},
    {0,0,1,-1},
    {0,0,0,1}
  };
  cout << "Determinante: " << det(matriz) << endl;
  Matrix m0(matriz);
  cout << "Matriz 1:" << endl;
  m0.toString();
  double **matrizI = inversa(matriz);
  double matrizInversa[4][4] = {
    {matrizI[0][0] , matrizI[0][1] , matrizI[0][2] , matrizI[0][3]},
    {matrizI[1][0] , matrizI[1][1] , matrizI[1][2] , matrizI[1][3]},
    {matrizI[2][0] , matrizI[2][1] , matrizI[2][2] , matrizI[2][3]},
    {matrizI[3][0] , matrizI[3][1] , matrizI[3][2] , matrizI[3][3]}
  };
  cout << "Matriz 2:" << endl;
  Matrix m1(matrizInversa);
  m1.toString();
  Matrix m2 = multi(m0,m1);

  cout << "Resultado de multiplicacion: " << endl;
  m2.toString();

  // Implementacion
  // string shader = "gouradShader";
  // Render r;
  // r.glInit();
  // r.glClearColor(0.0, 0.0, 0.0);
  // r.glColor(1.0, 1.0, 1.0);
  // r.glCreateWindow(2000, 2004);
  // r.glClear();
  
  // cout << "Comenzando renderizado..." << endl;
  // double transform[3] = {500, 650,1};
  // double scale[3] = {2000, 2000, 2000}; //Para el casco
  // double rotate[3] = {25,25,0};
  // r.loadModel(modelPath, transform, scale, rotate , false, false, shader);
  // cout << "renderizado terminado!" << endl;


  // // PARA EL PLANETA
  // modelPath = "models/earth.obj";
  // r.setTexture("models/textures/moon.bmp");
  //   cout << "Comenzando renderizado..." << endl;
  // double transform0[3] ={ 1500, 500, 500 };
  // double scale0[3] = {1, 1, 1};
  // double rotate0[3] = {0, 30, 0};
  // r.loadModel(modelPath, transform0, scale0, rotate0, false, true, shader);
  //   cout << "renderizado terminado!" << endl;

  // // PARA LA COCA
  // modelPath = "models/coca.obj";
  // r.setTexture("models/textures/earthDay.bmp");
  // double transform1[3] = {250, 900, 0};
  // double scale1[3] = {3, 3,3};
  // double rotate1[3] = {60,0,0};
  // r.loadModel(modelPath, transform1, scale1, rotate1, false, false, shader);

  // // shader = "gouradShader";
  // // r.loadModel(modelPath, transform, scale, rotate, false, hasTexture, shader);
  // r.glFinish("results/test.bmp");
}