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

//
// Matrix operator*(Matrix  &m0 , Matrix &m1){
//   Matrix result;
//   for (int i = 0; i < 4 ; i ++){
//     for (int j = 0 ; j < 4 ; j++){
//       double contador = 0 ;
//       for (int x  = 0 ; x < 4 ; x++){
//         contador = contador + (m1.getItem(x, j) * m0.getItem(i, x));
//       }
//       result.setValue(i,j,contador); 
//     }
//   }
//   return result;
// }

// double* operator*(Matrix &m, double* &v ){
//   double *result = new double[4];
//   for (int i = 0 ; i < 4 ; i ++){
//     double contador = 0 ;
//     for (int j = 0 ; j <4 ; j++){
//       contador = contador + m.getItem(i,j) * v[i];
//     }
//     result[i] = contador;
//   }
//   return result;
// }

int main()
{  
  bool hasTexture = false;
  string modelPath = "models/coca.obj";

  // Implementacion
  string shader = "gouradShader";
  Render r;
  r.glInit();
  r.glClearColor(0.0, 0.0, 0.0);
  r.glColor(1.0, 1.0, 1.0);
  r.glCreateWindow(1000, 1000);
  r.glClear();


  // PARA EL PLANETA
  // r.setTexture("models/earthDay.bmp");
  // double transform[3] ={ 500, 500, 500 };
  // double scale[3] = {1, 1, 1};

  // PARA LA COCA
  // double transform[3] = {250, 400, 0};
  // double scale[3] = {3, 3,3};
  // double rotate[3] = {60,60,0};

  // shader = "gouradShader";
  // r.loadModel(modelPath, transform, scale, rotate, false, hasTexture, shader);

  // PARA EL MODELO
  cout << "Comenzando medium shot..." << endl;
  r.setTexture("models/model.bmp");
  modelPath = "models/model.obj";
  double transform0[3] = {500, 500,700};
  double scale0[3] = {400, 400, 400};
  double rotate0[3] = {0,-30,0};
  r.loadModel(modelPath, transform0, scale0, rotate0 , false, true, shader);
  r.glFinish("results/mediumShot.bmp");
  r.glClear();
  cout << "Medium shot terminado!" << endl;

  cout << "Comenzando dutch angle..." << endl;
  double transform1[3] = {500, 500, 500};
  double scale1[3] = {400, 400, 400};
  double rotate1[3] = {0, -30, -15};
  r.loadModel(modelPath, transform1, scale1, rotate1, false, true, shader);
  r.glFinish("results/dutchAngle.bmp");
  r.glClear();
  cout << "Dutch angle terminado!" << endl;

  cout << "Comenzando high angle..." << endl;
  double transform2[3] = {500, 500, 500};
  double scale2[3] = {400, 400, 400};
  double rotate2[3] = {45, -30, 0};
  r.loadModel(modelPath, transform2, scale2, rotate2, false, true, shader);
  r.glFinish("results/highAngle.bmp");
  r.glClear();
  cout << "high angle terminado!" << endl;

  cout << "Comenzando low angle..." << endl;
  double transform3[3] = {500, 500, 500};
  double scale3[3] = {400, 400, 400};
  double rotate3[3] = {-45, -30, 0};
  r.loadModel(modelPath, transform3, scale3, rotate3, false, true, shader);
  r.glFinish("results/lowAngle.bmp");
  cout << "low angle terminado!" << endl;

  cout << "El fin." << endl << "Los resultados se encuentran en el directorio results" << endl;
}