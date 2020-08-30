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
  // Implementacion
  string modelPath="models/helmet.obj";
  string shader = "";
  Render r;
  r.glInit();
  r.glClearColor(0.0, 0.0, 0.0);
  r.glColor(1.0, 1.0, 1.0);
  r.glCreateWindow(768, 432);
  r.glClear();
  r.createProjectionMatrix();
  // double vector[3] = {0,0,0};
  // double vector1[3] = {500, 500, 1000};
  // r.createViewMatrix(vector1, vector);
  
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
  // double transform0[3] ={ 1500, 500, 0 };
  // double scale0[3] = {1, 1, 1};
  // double rotate0[3] = {0, 30, 0};
  // double camPosition[3] = {2,2,0};
  // // r.lookAt(transform0 , camPosition);
  // r.loadModel(modelPath, transform0, scale0, rotate0, false, true, shader);
  // cout << "renderizado terminado!" << endl;

  // // PARA EL MODELO
  modelPath = "models/model.obj";
  r.setTexture("models/textures/model.bmp");
    cout << "Comenzando renderizado..." << endl;
  double transform0[3] ={ 1, 0, -5 };
  double scale0[3] = {1, 1, 1};
  double rotate0[3] = {0, 0, 0};
  double camPosition[3] = {0,0,1};
  r.lookAt(transform0 , camPosition);
  r.loadModel(modelPath, transform0, scale0, rotate0, false, true, shader);
  cout << "renderizado terminado!" << endl;

  cout << "Comenzando renderizado..." << endl;
  double transform1[3] = {-1, 0, -5};
  // double scale0[3] = {1, 1, 1};
  // double rotate0[3] = {0, 0, 0};
  // double camPosition[3] = {0, 0, 0};
  // r.lookAt(transform0, camPosition);
  r.loadModel(modelPath, transform1, scale0, rotate0, false, true, shader);
  cout << "renderizado terminado!" << endl;

  double transform2[3] = {-1, 0, -2};
  r.loadModel(modelPath, transform2, scale0, rotate0, false, true, shader);
  // // PARA LA COCA
  // modelPath = "models/coca.obj";
  // r.setTexture("models/textures/earthDay.bmp");
  // double transform1[3] = {250, 900, 0};
  // double scale1[3] = {3, 3,3};
  // double rotate1[3] = {60,0,0};
  // r.loadModel(modelPath, transform1, scale1, rotate1, false, false, shader);

  // // shader = "gouradShader";
  // // r.loadModel(modelPath, transform, scale, rotate, false, hasTexture, shader);
  r.glFinish("results/tst.bmp");
}