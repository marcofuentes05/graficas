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
  string shader = "toonGold";
  Render r;
  r.glInit();
  r.glClearColor(0.0, 0.0, 0.0);
  r.glColor(1.0, 1.0, 1.0);
  r.glCreateWindow(1280, 720);
  r.glClear();
  r.createProjectionMatrix();

  // // PARA EL MODELO
  shader = "randomChannel";
  modelPath = "models/aircraft.obj";
  r.setTexture("models/textures/aircraft.bmp");
  double transform0[3] ={ 30, 35, -100 };
  double scale0[3] = {7, 7, 7};
  double rotate0[3] = {90,-30, 0};
  double camPosition[3] = {0,0,4};
  double camTransform[3] = {0,0,-100};
  r.lookAt(camTransform , camPosition);
  
  cout << "Comenzando renderizado..." << endl;
  r.loadModel(modelPath, transform0, scale0, rotate0, false, true, shader);
  cout << "renderizado terminado!" << endl;

  shader = "toonGold";
  modelPath = "models/model.obj";
  r.setTexture("models/textures/model.bmp");
  double transform1[3] ={ 5, -20, -60 };
  double scale1[3] = {10, 10, 10};
  double rotate1[3] = {0,30, 0};

  cout << "Comenzando renderizado..." << endl;
  r.loadModel(modelPath, transform1, scale1, rotate1, false, true, shader);
  cout << "renderizado terminado!" << endl;

  shader = "toonShader";
  modelPath = "models/coca.obj";
  r.glColor(1,0,0);
  double transform2[3] = {-160, -130, -600};
  double scale2[3] = {1, 1, 1};
  double rotate2[3] = {0, 0, 0};

  cout << "Comenzando renderizado..." << endl;
  r.loadModel(modelPath, transform2, scale2, rotate2, false, false, shader);
  cout << "renderizado terminado!" << endl;

  shader = "inverse";
  modelPath = "models/helmet.obj";
  r.glColor(0,0.1,1);
  r.glColor(0.3, 0.3, 0.3);
  double transform3[3] = {7, -5, -20};
  double scale3[3] = {10, 10, 10};
  double rotate3[3] = {30, 0, 0};

  cout << "Comenzando renderizado..." << endl;
  r.loadModel(modelPath, transform3, scale3, rotate3, false, false, shader);
  cout << "renderizado terminado!" << endl;

  shader = "random";
  modelPath = "models/torre.obj";
  r.setTexture("models/textures/torre.bmp");
  r.glColor(0.5, 0.5, 0.5);
  double transform4[3] = {-70, -70, -150};
  double scale4[3] = {6, 6, 6};
  double rotate4[3] = {0, 0, 0};

  cout << "Comenzando renderizado..." << endl;
  r.loadModel(modelPath, transform4, scale4, rotate4, false, true, shader);
  cout << "renderizado terminado!" << endl;


  shader = "toonShader";
  modelPath = "models/andromeda.obj";
  r.setTexture("models/textures/aircraft.bmp");
  double transform5[3] = {-300, 300, -800};
  double scale5[3] = {10, 10, 10};
  double rotate5[3] = {0, 0, 0};

  cout << "Comenzando renderizado..." << endl;
  r.loadModel(modelPath, transform5, scale5, rotate5, false, false, shader);
  cout << "renderizado terminado!" << endl;
  r.glFinish("results/sinFondo.bmp");

  r.PostProcessEffect("results/sinFondo.bmp", "models/textures/wxp.bmp");
}