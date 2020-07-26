#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
using namespace std;

class OBJ{
  string name;
  int numVertices = 0;
  int numNormals = 0;
  int numTexCoord = 0;
  int numFaces = 0;
  double **vertices ;
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
    ~OBJ();
};

const vector<string> explode(const string &s, const char &c);
