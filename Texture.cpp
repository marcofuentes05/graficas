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
    pixels = new int**[height];
    for (int i = 0 ; i < height ; i++){
      pixels[i] = new int*[width];
      for (int j = 0 ; j < width ; j++){
        pixels[i][j] = new int[3];
        file.read((char *)&pixels[i][j][0] , 1);
        file.read((char *)&pixels[i][j][1] , 1);
        file.read((char *)&pixels[i][j][2] , 1);
      }
    }
    file.close();
    for (int i = 0 ; i < height ; i++){
      for (int j = 0 ; j < width ; j++){
        for(int k = 0 ; k < 3 ; k++){
          if (pixels[i][j][k] > 255){
            pixels[i][j][k] = 255;
          }else if(pixels[i][j][k] <0){
            pixels[i][j][k] = 0;
          }
        }
      }
    }
  }
}

int* Texture::getColor(double tx, double ty){
  int* result = new int[3];
  result[0] = 0;
  result[1] = 0;
  result[2] = 0;
  if (tx >= 0 && tx <=1 && ty >= 0 && ty <= 1){ 
    int x = int(tx*(width-1));
    int y = int(ty*(height-1));
    result[2] = pixels[y][x][2];//r
    result[1] = pixels[y][x][1];//g
    result[0] = pixels[y][x][0];//b
  }
  return result;
};

string Texture::getPath(){
  return path;
}

Texture::~Texture(){
  for (int i = 0 ; i < height ; i++){
    for (int j = 0 ; j < width ; j++){
      delete[] pixels[i][j];
    }
    delete[] pixels[i];
  }
  
  if(height > 0 && width > 0) {delete[] pixels;};
};

int Texture::getWidth(){
  return width;
}

int Texture::getHeight(){
  return height;
}