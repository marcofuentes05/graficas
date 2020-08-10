/* -------------------------------------------------------------------
Shaders.cpp
Métodos necesarios para la implementación de distintos 
shaders para el renderizado de modelos OBJ.
Marco Fuentes - 18188
Gráficas por Computadora - Segundo Semestre 2020 - UVG
-------------------------------------------------------------------  */

#include "Shaders.hpp"
// #include "Render.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <algorithm>
#include <stdlib.h>
using namespace std;

// Shaders::Shaders(){
//   cout << "CONSTRUCTOR VACIO" << endl;  
// };

// Shaders::Shaders(Render *r){
//   Render* (render) =  r;
//   cout << "Ya cargamos el render" << endl;
//   string algo = render->getSom();
//   cout <<  algo<<endl;
//   cout << "Y ya salimos :)" << endl;
// }

// void Shaders::setRenderer(Render*r){
//   Render* (render) = r;
// };

int * gourad(Render *render,
    double baryCoords[3], 
    bool hasTexture ,
    double **texcoords, 
    double **normals,   
    int color[3]){
  double b=color[0] / 255;
  double g=color[1] / 255;
  double r=color[2] / 255;
  if(hasTexture){
    double tx = texcoords[0][0] * baryCoords[0] + texcoords[1][0] * baryCoords[1] + texcoords[2][0]*baryCoords[2];
    double ty = texcoords[0][1] * baryCoords[0] + texcoords[1][1] * baryCoords[1] + texcoords[2][1]*baryCoords[2];
    int* texColor = render->texture.getColor(tx,ty);
    b = b * (double(texColor[0]) / double(255));
    g = g * (double(texColor[1]) / double(255));
    r = r * (double(texColor[2]) / double(255));
    delete [] texColor;
  }
  double normal[3];
  normal[0] = normals[0][0]*baryCoords[0] + normals[1][0]*baryCoords[1] + normals[2][0] * baryCoords[2];
  normal[1] = normals[0][1]*baryCoords[0] + normals[1][1]*baryCoords[1] + normals[2][1] * baryCoords[2];
  normal[2] = normals[0][2]*baryCoords[0] + normals[1][2]*baryCoords[1] + normals[2][2] * baryCoords[2];

  double intensity = dot(normal, render->light , 3);
    b = b * intensity;
    g = g * intensity;
    r = r * intensity;

  int *finalColor = new int[3];//{int(r), int(g), int(b)};
  finalColor[0] = int(r);  
  finalColor[1] = int(g);
  finalColor[2] = int(b);  
  if(intensity<=0){
    finalColor[0] = 0;
    finalColor[1] = 0;
    finalColor[2] = 0;
  }
  return finalColor;
}

// Shaders::~Shaders(){
//   cout << "DESTRUYENDO SHADERS" << endl;
// }