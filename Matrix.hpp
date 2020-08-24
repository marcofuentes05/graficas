#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
using namespace std;

class Matrix{
  double matriz[4][4];
  public:
    Matrix();
    Matrix(double ** matriz);
    Matrix(double matriz[4][4]);
    double getItem(int i , int j);
    void setValue(int i , int j , double value);
    void toString();
};