/* -------------------------------------------------------------------  
linearAlgebra.cpp
Conjunto de funciones que realizan operaciones de álgebra lineal usadas
para renderizado de modelos.
Marco Fuentes - 18188
Gráficas por Computadora - Segundo Semestre 2020 - UVG
-------------------------------------------------------------------   */

#include "linearAlgebra.hpp"
#include <math.h>

double dot(double *v1, double *v2, int size){
  double result = 0 ;
  for (int i = 0 ; i < size ; i ++){
    result = result+v1[i]*v2[i];
  }
  return result;
};
int dot(int *v1, int *v2, int size){
  int result = 0;
  for (int i = 0; i < size; i++){
    result = result + v1[i] * v2[i];
  }
  return result;
};

double *cross(double *v1, double *v2){
  // Temporal, pensado únicamente cuando size = 3
  double *result = new double[3];
  result[0] = v1[1]*v2[2] - v1[2]*v2[1] ;
  result[1] = v1[2]*v2[0] - v1[0]*v2[2] ;
  result[2] = v1[0]*v2[1] - v1[1]*v2[0] ;
  return result;
  // IMPORTANTE llamar delete[] result en MAIN para prevenir memory leaks
};
int *cross(int *v1, int *v2){
  // Temporal, pensado únicamente cuando size = 3
  int *result = new int[3];
  result[0] = v1[1] * v2[2] - v1[2] * v2[1];
  result[1] = v1[2] * v2[0] - v1[0] * v2[2];
  result[2] = v1[0] * v2[1] - v1[1] * v2[0];
  return result;
  // IMPORTANTE llamar delete[] result en MAIN para prevenir memory leaks
};

double norm(double *vector, int size){
  double result = 0;
  for(int i = 0 ; i < size ; i ++){
    result += vector[i] * vector[i];
  }
  return sqrt(result);
};
double norm(int *vector, int size){
  int result = 0;
  for (int i = 0; i < size; i++)
  {
    result += vector[i] * vector[i];
  }
  return sqrt(result);
};

double *substract(double*v1 , double*v2, int size){
  double* result = new double[size];
  for(int i = 0 ; i < size ; i++){
    result[i] = v1[i] - v2[i];
  }
  return result;
  // IMPORTANTE llamar delete[] result en MAIN para prevenir memory leaks
};

int *substract(int*v1 , int*v2, int size){
  int* result = new int[size];
  for(int i = 0 ; i < size ; i++){
    result[i] = v1[i] - v2[i];
  }
  return result;
  // IMPORTANTE llamar delete[] result en MAIN para prevenir memory leaks
};

double* normalize(double*vector, int size){
  double norma = norm(vector, size);
  double *result = new double[size];
  for (int i = 0 ; i < size ; i ++){
    result[i] = vector[i]/norma;
  }
  return result;
};
