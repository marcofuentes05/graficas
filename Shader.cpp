/* -------------------------------------------------------------------
Shaders.cpp
Clase con métodos necesarios para la implementación de distintos 
shaders para el renderizado de modelos OBJ.
Marco Fuentes - 18188
Gráficas por Computadora - Segundo Semestre 2020 - UVG
-------------------------------------------------------------------  */
#include "Render.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <algorithm>
#include <stdlib.h>
using namespace std;

Shader::Shader(){
  cout << "CONSTRUCTOR VACIO" << endl;  
};

Shader::Shader(Render *r){
  Render*(&render) = r;
};

void Shader::setRenderer(Render r){

};

void Shader::gourad(double baryCoords[3], 
    double texCoords[][3] , 
    double normals[][3], 
    double color[3] ,
    Texture t ){
  double b = color[0]/255;
  double g = color[1]/255;
  double r = color[2]/255;

  if (t.getPath()!= ""){
    double tx = texCoords[0][0]*baryCoords[0] +texCoords[1][0]*baryCoords[1] + texCoords[2][0]*baryCoords[2];
    double ty = texCoords[0][1]*baryCoords[0] +texCoords[1][1]*baryCoords[1] + texCoords[2][1]*baryCoords[2];
    int *texColor = t.getColor(tx,ty);
  }
}