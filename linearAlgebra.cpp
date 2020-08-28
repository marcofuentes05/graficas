/* -------------------------------------------------------------------  
linearAlgebra.cpp
Conjunto de funciones que realizan operaciones de álgebra lineal usadas
para renderizado de modelos.
Marco Fuentes - 18188
Gráficas por Computadora - Segundo Semestre 2020 - UVG
-------------------------------------------------------------------   */

#include "linearAlgebra.hpp"
#include <math.h>
#include <iostream>
using namespace std;
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
  // if (norma = 0 ){
  //   return vector;
  // }
    result[i] = vector[i]/norma;
    
  }
  return result;
};

double det(double matriz[4][4] ){
  double m0[3][3] = {
    {matriz[1][1] ,matriz[1][2], matriz[1][3]},
    {matriz[2][1] , matriz[2][2] , matriz[2][3]},
    {matriz[3][1] , matriz[3][2] , matriz[3][3]}
  };
  double m1[3][3] = {
    {matriz[1][0], matriz[1][2], matriz[1][3]},
    {matriz[2][0], matriz[2][2], matriz[2][3]},
    {matriz[3][0], matriz[3][2], matriz[3][3]}
  };
  double m2[3][3] ={
    {matriz[1][0],  matriz[1][1] , matriz[1][3]},
    {matriz[2][0] , matriz[2][1] , matriz[2][3]},
    {matriz[3][0] , matriz[3][1] , matriz[3][3]}
  };
  double m3[3][3] ={
    {matriz[1][0] , matriz[1][1] , matriz[1][2] },
    {matriz[2][0] , matriz[2][1] , matriz[2][2] },
    {matriz[3][0] , matriz[3][1] , matriz[3][2] }
  };
  double result = 0;
  result = result + matriz[0][0]*det3(m0);
  result = result - matriz[0][1]*det3(m1);
  result = result + matriz[0][2]*det3(m2);
  result = result - matriz[0][3]*det3(m3);
  return result;
}

double det3(double matriz[3][3]){
  double result = 0;
  result = result 
    + matriz[0][0] * (matriz[1][1] * matriz[2][2] - matriz[1][2] * matriz[2][1]) 
    - matriz[0][1] * (matriz[1][0] * matriz[2][2] - matriz[2][0] * matriz[1][2]) 
    + matriz[0][2] * (matriz[1][0] * matriz[2][1] - matriz[2][0] * matriz[1][1]);
  return result;
}

double** transpuesta(double **matriz){
  double **result = new double *[4];
  for (int i = 0 ;  i< 4 ; i ++){
    result[i] = new double[4];
    for (int j = 0 ; j< 4 ; j++ ){
      result[i][j] = matriz[j][i];
    }
  }
  return result;
}

double **cof(double matriz[4][4]){
  double **result = new double*[4];
  for (int i = 0 ; i < 4 ; i ++){
    result[i] = new double[4];
    for (int j = 0 ; j <4 ; j++){
      double cofT[3][3];
      int x = 0;
      int y = 0;
      for ( int w =0;w<4;w++){
        for (int h = 0 ; h <4; h++){
          if ((w!= i) && (h!=j)){
            cofT[x][y] = matriz[w][h];
            y++;
          }
        }
        if (y>=3){
          y=0;
          x++;
        }
      }
      result[i][j] = pow(-1,i+j)*det3(cofT);
    }
  }
  return result; //DELETE THIS
}

double **inversa(double **matriz){
  double **result = new double*[4];
  double determinante = det(matriz);
  double ** cofactores = cof(matriz); //DELETE THIS
  double** adjunta = transpuesta(cofactores); //DELETE 
  cout << "Cofactores: " << endl;
  for (int i  = 0; i < 4 ; i++){
    for (int j = 0 ; j < 4 ; j ++){
      cout << cofactores[i][j] << "\t";
    }
    cout << endl;
  }
  cout << to_string(determinante) << endl;
  for (int i = 0 ; i < 4 ; i++){
    result[i] = new double[4];
    for (int j = 0 ; j <4 ; j++){
      result[i][j] = adjunta[i][j] / determinante;
      cout << adjunta[i][j] << "\t";
    }
    cout << endl;
  }
  //delete round
  for (int i = 0 ; i<4;i++){
      delete[] cofactores[i];
      delete[] adjunta[i];
  }
  delete cofactores;
  delete adjunta;

  return result;
}