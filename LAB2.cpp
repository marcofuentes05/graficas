#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include "Render.hpp"
#include "OBJ.hpp"
#include "linearAlgebra.hpp"
#include "Texture.hpp"
using namespace std;

int main()
{  
  bool hasTexture = true;
  string modelPath = "models/model.obj";

  // Implementacion
  Render r;
  r.glInit();
  r.glClearColor(0.0, 0.0, 0.0);
  r.glColor(1.0, 1.0, 1.0);
  r.glCreateWindow(1000, 1000);
  r.glClear();
  // PARA EL PLANETA
  // r.setTexture("models/earthDay.bmp");
  // int transform[3] ={ 500, 500, 500 };
  // int scale[3] = {1, 1, 1};

  // PARA LA COCA
  // int transform[3] = {250, 30, 0};
  // int scale[3] = {2, 2,2};


  // PARA EL MODELO
  r.setTexture("models/model.bmp");
  int transform[3] = {500, 500,0};
  int scale[3] = {500, 500, 500};

  string shader = "randomChannel";
  cout << "Comenzando " << shader << " Shader..." << endl;
  r.loadModel(modelPath, transform, scale, false, hasTexture, shader);
  r.glFinish("results/"+shader+".bmp");
  cout << shader << " terminado!" << endl;

  shader = "gouradShader";
  cout << "Comenzando " << shader << " Shader..." << endl;
  r.loadModel(modelPath, transform, scale, false, hasTexture, shader);
  r.glFinish("results/"+shader+".bmp");
  cout << shader << " terminado!" << endl;

  shader = "toonShader";
  cout << "Comenzando " << shader << " Shader..." << endl;
  r.loadModel(modelPath, transform, scale, false, hasTexture, shader);
  r.glFinish("results/" + shader + ".bmp");
  cout << shader << " terminado!" << endl;

  shader = "unlit";
  cout << "Comenzando " << shader << " Shader..." << endl;
  r.loadModel(modelPath, transform, scale, false, hasTexture, shader);
  r.glFinish("results/" + shader + ".bmp");
  cout << shader << " terminado!" << endl;

  shader = "inverse";
  cout << "Comenzando " << shader << " Shader..." << endl;
  r.loadModel(modelPath, transform, scale, false, hasTexture, shader);
  r.glFinish("results/" + shader + ".bmp");
  cout << shader << " terminado!" << endl;

  shader = "toonGold";
  cout << "Comenzando " << shader << " Shader..." << endl;
  r.loadModel(modelPath, transform, scale, false, hasTexture, shader);
  r.glFinish("results/" + shader + ".bmp");
  cout << shader << " terminado!" << endl;

  cout << "Comenzando PostProcessEffect..." << endl;
  r.PostProcessEffect("results/gouradShader.bmp" , "models/fondo.bmp");
  cout << "PostProcessEffect terminado!" << endl;

  cout << "El fin." << endl;
}