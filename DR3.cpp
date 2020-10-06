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
#include "Plane.hpp"
#include "AABB.hpp"
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
  chrono::steady_clock sc;
  auto start = sc.now();

  Material WHITE;
  WHITE.setDiffuse(1,1,1);
  WHITE.setSpec(64);
  Material BLACK;
  BLACK.setDiffuse(0,0,0);
  BLACK.setSpec(16);
  Material GREY;
  GREY.setDiffuse(0.4, 0.4, 0.4 );
  GREY.setSpec(16);
  Material ORANGE;
  ORANGE.setDiffuse(1,0.49,0.31);
  ORANGE.setSpec(16);

  Material brick;
  brick.setDiffuse(0.8, 0.25, 0.25 );
  brick.setSpec(16);
  Material grass;
  grass.setDiffuse(0.5, 1, 0);
  grass.setSpec(32);

  double centerc0[3] = { -1 , -1 , -7 };
  double sizec0 = 1;
  AABB c0( centerc0 , sizec0 , brick );

  double centerc1[3] = {1, 1, -7};
  double sizec1 = 1;
  AABB c1(centerc1, sizec1, brick);

  double centerp0[3] = {0, -2, -7};
  double n0[3] = {0,1,0} ;
  Plane p0(centerp0 , n0 , brick);

  double centerp1[3] = {-2, 0 , -7};
  double n1[3] = {1, 0, 0};
  Plane p1(centerp1, n1, brick);

  double centerp2[3] = {2, 0, -7};
  double n2[3] = {-1, 0, 0};
  Plane p2(centerp2, n2, brick);

  double centerp3[3] = {0, 2, -7};
  double n3[3] = {0, -1, 0};
  Plane p3(centerp3, n3, brick);

  double centerp4[3] = {0, 0, -7};
  double n4[3] = {0, 0, 1};
  Plane p4(centerp4, n4, brick);

  double pos0 [3] = { 0, -1.9 , -7 };
  double pos1[3] =  { 0, 0 , -7 };
  double pos2[3] =  { 0, 1.9  , -7 };
  double pos3[3] = {0, -0.5, -3};
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
  Sphere s1(pos1, 1.25, brick);
  Sphere s2(pos2, 1, WHITE);
  Sphere s3(pos3, 0.25, ORANGE);

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
  
  double colorA[3] = {0.8,0.2,0.23};
  AmbientLight ambient(0.1 , colorA);

  double colorP[3] = {1 , 1 , 1};
  double colorP1[3] = {1, 1, 1};
  double colorP2[3] = {1, 1, 1};
  double positionP[3] = {0,0,0};
  double positionP1[3] = {2, 2, 0};
  double positionP2[3] = {0, -2, 0};
  PointLight point(1.0 , positionP , colorP);
  PointLight point1(0.5, positionP1, colorP1);
  PointLight point2(0.25, positionP2, colorP2);

  Render r;
  r.glInit();
  r.glClearColor( 0.0, 0.0 , 0.0);
  r.glColor(1.0, 1.0, 1.0);
  r.glCreateWindow(500, 500);
  r.glClear();
  r.setPointLight(point);
  // r.setPointLight(point1);
  // r.setPointLight(point2);
  // r.setAmbientLight(ambient);


  // r.scene.push_back(s0);
  // r.scene.push_back(s1);
  // r.scene.push_back(s2);
  r.scenePlanes.push_back(p1);
  r.scenePlanes.push_back(p2);
  r.scenePlanes.push_back(p3);
  r.scenePlanes.push_back(p4);
  r.scenePlanes.push_back(p0);
  r.sceneAABBs.push_back(c0);
  r.sceneAABBs.push_back(c1);
  // r.scene.push_back(s3);
  // r.scene.push_back(eyel);
  // r.scene.push_back(eyer);
  // r.scene.push_back(nose);
  // r.scene.push_back(button1);
  // r.scene.push_back(button2);
  // r.scene.push_back(button3);
  // r.scene.push_back(smile0);
  // r.scene.push_back(smile1);
  // r.scene.push_back(smile2);
  // r.scene.push_back(smile3);
  // r.scene.push_back(smile4);


  r.rtRender();
  r.glFinish("results/DR3.bmp");
  auto end = sc.now();
  auto time_span = static_cast<chrono::duration<double>>(end - start);
  cout << "Renderizado terminado! Operación duró " << time_span.count() << " segundos" << endl;
  return 0;
}
