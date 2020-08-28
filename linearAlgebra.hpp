#ifndef LINEARALGEBRA_H
#define LINEARALGEBRA_H

double dot(double* v1 , double *v2, int size);
int dot(int* v1 , int*v2 , int size);

double *cross(double*v1, double *v2);
int *cross(int *v1, int *v2);

double norm(double* vector, int size);
double norm(int* vector, int size);

double *substract(double* v1 , double*v2, int size);
int *substract(int *v1, int *v2, int size);
double* normalize(double* vector, int size);
double det(double matriz[4][4] );
double det3(double matriz[3][3]);
double** transpuesta(double **matriz);
double **cof(double matriz[4][4]);
double **inversa(double **matriz);
#endif