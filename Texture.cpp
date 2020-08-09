/* ----------------------------------------------------
Tecture.cpp
Clase que interpreta texturas en formato BMP para 
aplicarlas a un modelo OBJ.
Marco Fuentes - 18188
Gráficas por computadora - Segundo Semestre 2020 - UVG
---------------------------------------------------- */

#include "Texture.hpp"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <stdlib.h>   
using namespace std;

Texture::Texture(){
  path = "";
}

void Texture::openFile(string path){
  this->path = path;
  file.open(this->path ,ios::in | ios::binary);
}

void Texture::read(){
  string line;
  if (file.is_open()){
    int headerSize;
    file.seekg(10);
    file.read((char *)&headerSize,  4);
    file.seekg(14+4);
    file.read((char *)&width , 4);
    file.read((char *)&height, 4);
    file.seekg(headerSize);
    pixels = new int**[width];
    for (int i = 0 ; i < width ; i++){
      pixels[i] = new int*[height];
      for (int j = 0 ; j < height ; j++){
        pixels[i][j] = new int[3];
        file.read((char *)&pixels[i][j][0] , 1);
        file.read((char *)&pixels[i][j][1] , 1);
        file.read((char *)&pixels[i][j][2] , 1);
      }
    }
    file.close();
  }
}

int* Texture::getColor(double tx, double ty){
  int* result = new int[3];
  result[0] = 0;
  result[1] = 0;
  result[2] = 0;
  if (tx >= 0 && tx <=1 && ty >= 0 and ty <= 1){      
    int x = int(tx*width);
    int y = int(ty*height);
    result[0] = pixels[y][x][0];//b
    result[1] = pixels[y][x][1];//g
    result[2] = pixels[y][x][2];//r
  }
  return result;
};

string Texture::getPath(){
  return path;
}

Texture::~Texture(){
  for (int i = 0 ; i < width ; i++){
    for (int j = 0 ; j < height ; j++){
      delete[] pixels[i][j];
    }
    delete[] pixels[i];
  }
  delete[] pixels;
};
