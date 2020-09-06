#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include <chrono>
#include "Render.hpp"
#include "OBJ.hpp"
#include "linearAlgebra.hpp"
#include "Texture.hpp"
#include "Matrix.hpp"
#include "Sphere.hpp"
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
  chrono::steady_clock sc; // create an object of `steady_clock` class
  auto start = sc.now();   // start timer

  // do stuff....

  Material WHITE;
  WHITE.setDiffuse(1,1,1);
  Material BLACK;
  BLACK.setDiffuse(0,0,0);
  Material GREY;
  GREY.setDiffuse(0.4, 0.4, 0.4 );
  Material ORANGE;
  ORANGE.setDiffuse(1,0.49,0.31);

  Material brick;
  brick.setDiffuse(0.8, 0.25, 0.25 );
  Material grass;
  grass.setDiffuse(0.5, 1, 0);

  double pos0 [3] = { 0, -1.9 , -7 };
  double pos1[3] =  { 0, 0    , -7 };
  double pos2[3] =  { 0, 1.9  , -7 };
  double posEyel[3] = {-0.35 , 1.7 , -5};
  double posEyer[3] = {0.35  , 1.7 , -5};
  double posNose[3] = {0, 1.3, -5};
  double posButton1[3] = {0 , 0.2 , -5};
  double posButton2[3] = {0 , -0.6 , -5};
  double posButton3[3] = {0 , -1.4 , -5};
  double posSmile0[3] = { -0.3 , 1 , -5};
  double posSmile1[3] = { -0.15 , 0.9 , -5};
  double posSmile2[3] = { 0 , 0.85 , -5};
  double posSmile3[3] = { 0.15 , 0.9 , -5};
  double posSmile4[3] = { 0.3 , 1 , -5};

  Sphere s0(pos0, 1.5 ,  WHITE);
  Sphere s1(pos1, 1.2, WHITE);
  Sphere s2(pos2, 1, WHITE);

  Sphere eyel(posEyel, 0.1 , BLACK);
  Sphere eyer(posEyer, 0.1 , BLACK);

  Sphere nose(posNose, 0.15 , ORANGE);

  Sphere button1(posButton1 , 0.08 , BLACK);
  Sphere button2(posButton2 , 0.08 , BLACK);
  Sphere button3(posButton3 , 0.08 , BLACK);

  Sphere smile0 (posSmile0 , 0.04 , BLACK);
  Sphere smile1 (posSmile1 , 0.04 , BLACK);
  Sphere smile2 (posSmile2 , 0.04 , BLACK);
  Sphere smile3 (posSmile3 , 0.04 , BLACK);
  Sphere smile4 (posSmile4 , 0.04 , BLACK);
  

  Render r;
  r.glInit();
  r.glClearColor( 0.5, 0.5 , 1);
  r.glColor(1.0, 1.0, 1.0);
  r.glCreateWindow(768, 1024);
  r.glClear();
  r.scene.push_back(s0);
  r.scene.push_back(s1);
  r.scene.push_back(s2);
  r.scene.push_back(eyel);
  r.scene.push_back(eyer);
  r.scene.push_back(nose);
  r.scene.push_back(button1);
  r.scene.push_back(button2);
  r.scene.push_back(button3);
  r.scene.push_back(smile0);
  r.scene.push_back(smile1);
  r.scene.push_back(smile2);
  r.scene.push_back(smile3);
  r.scene.push_back(smile4);

  r.rtRender();
  r.glFinish("results/DR1.bmp");
  auto end = sc.now();                                                 // end timer (starting & ending is done by measuring the time at the moment the process started & ended respectively)
  auto time_span = static_cast<chrono::duration<double>>(end - start); // measure time span between start & end
  cout << "Renderizado terminado! Operación duró " << time_span.count() << " segundos" << endl;
  return 0;
}