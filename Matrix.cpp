/* -------------------------------------------------------------------  
Matrix.cpp
Clase que modela una matriz de 4x4, y permite definir operaciones como
la multiplicacion de matrices a través de sobrecarga de operadores.
Marco Fuentes - 18188
Gráficas por computadora - Segundo Semestre 2020 - UVG
------------------------------------------------------------------- */
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include "Matrix.hpp"
using namespace std;

Matrix::Matrix(){
  //Inicializar todo con 0
  for (int i = 0 ; i < 4 ; i++){
    for (int j = 0 ; j < 4 ; j++){
      this->matriz[i][j] = 0.0;
    }
  }
}

Matrix::Matrix(double **matriz){
  for (int i = 0 ; i < 4 ; i++){
    for (int j = 0 ; j < 4 ; j++){
      this->matriz[i][j] = matriz[i][j];
    }
  }
}

Matrix::Matrix(double matriz[4][4]){
  for (int i = 0 ; i < 4 ; i++){
    for (int j = 0 ; j < 4 ; j++){
      this->matriz[i][j] = matriz[i][j];
    }
  }
}

double Matrix::getItem(int i , int j){
  return this->matriz[i][j];
}

void Matrix::setValue(int i, int j , double value){
  if (i<4 && j <4){
    this->matriz[i][j] = value;
  }else{
    cout << "Indices invalidos" << endl;
  }
}
void Matrix::toString(){
  for (int i  = 0; i < 4 ; i++){
    for (int j = 0 ; j < 4 ; j ++){
      cout << getItem(i,j) << "\t";
    }
    cout << endl;
  }
}