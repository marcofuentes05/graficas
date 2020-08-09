#ifndef TEXTURE_H
#define TEXTURE_H

#include <iostream>
#include <fstream>
#include <string>
using namespace std;
class Texture{
  int width;
  int height;
  string path;
  ifstream file;
  int ***pixels;
  public:
    Texture();
    void openFile(string path);
    void read();
    int *getColor(double tx, double ty);
    string getPath();
    ~Texture();
};

#endif
