#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
using namespace std;

class OBJ{
  string name;
  int numVertices;
  int numNormals;
  int numTexCoord;
  int numFaces;
  double **vertices;
  double **normals ;
  double **texcoords;
  int ***faces ;
  int * facesLen;
  ifstream archivo;
  public:
    OBJ();
    OBJ(string name);
    void read();
    int*** getFaces();
    int getNumFaces();
    int* getFacesLen();
    double** getVertices();
    int getNumVertices();
    double **getTexCoords();
    ~OBJ();
};

const vector<string> explode(const string &s, const char &c);