/* -------------------------------------------------------------------  
OBJ.cpp
Algoritmo que lee un archivo OBJ y lo traduce a wireframe
Marco Fuentes - 18188
Gráficas por computadora - Segundo Semestre 2020 - UVG
------------------------------------------------------------------- */
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <vector>
#include "OBJ.hpp"
using namespace std; 
/*
Funcion explode (string ,  char) inspirada en PHP, copiada de
http://www.cplusplus.com/articles/2wA0RXSz/ 
*/
const vector<string> explode(const string &s, const char &c){
  string buff{""};
  vector<string> v;
  for (auto n : s){
    if (n != c)
      buff += n;
    else if (n == c && buff != ""){
      v.push_back(buff);
      buff = "";
    }
  }
  if (buff != "")
    v.push_back(buff);
  return v;
}
 
OBJ::OBJ(){
  numVertices = 0;
  numNormals = 0;
  numTexCoord = 0;
  numFaces = 0;
  name = "";
  cout << "CONSTRUCTOR POR DEFECTO" <<endl;
}
OBJ::OBJ(string name){
  numVertices = 0;
  numNormals = 0;
  numTexCoord = 0;
  numFaces = 0;
  // Abrir archivo
  this->name = name;
  archivo.open(name , ios::in);
};
void OBJ::read(){
  string line;
  if (archivo.is_open())
  {
    
    string temp;
    while (getline(archivo, line)){
      temp = line.substr(0, 2);
      if (temp == "v "){
        numVertices++;
      }else if (temp=="vt"){
        numTexCoord ++;
      }else if (temp == "vn"){
        numNormals++;
      }else if (temp == "f "){
        numFaces ++;
      }
    };

    // Inicialización de listas dinámicas
    facesLen = new int[numFaces];
    vertices = new double *[numVertices];
    for (int i = 0 ; i < numVertices ; i++){
      vertices[i] = new double[4];
    }
    texcoords = new double *[numTexCoord];
    for (int i = 0; i<numTexCoord ; i++){
      texcoords[i] = new double[3];
    }
    normals = new double*[numNormals];
    for ( int i = 0 ; i<numNormals ; i++){
      normals[i] = new double[3];
    }
    faces = new int** [ numFaces ] ;

    int contVertices = 0;
    int contNormals = 0;
    int contTexCoord = 0;
    int contFaces = 0;

    ifstream archivo0;
    archivo0.open(this->name , ios::in);
    while(getline(archivo0, line)){
      string temp = line.substr(0,2);
      if (temp == "v "){
        int contador = 0;
        vector<string> l = explode(line, ' ');
        for (auto n:l){
          if (contador != 0){
            vertices[contVertices][contador-1] = atof(n.c_str());
          }
          contador++;
        }
        contVertices++;
      }else if (temp=="vt"){
        int contador = 0;
        vector<string> l = explode(line, ' ');
        for (auto n:l){
          if (contador != 0){
            texcoords[contTexCoord][contador-1] = atof(n.c_str());
          }
          contador++;
        }
        contTexCoord++;        
      }else if (temp == "vn"){
        int contador = 0;
        vector<string> l = explode(line, ' ');
        for (auto n:l){
          if (contador != 0){
            normals[contNormals][contador-1] = atof(n.c_str());
          }
          contador++;
        }
        contNormals++;  
      }else if (temp == "f "){
        vector<string> components = explode ( line , ' ');
        faces[contFaces] = new int*[ components.size() - 1 ];
        facesLen[contFaces] = components.size() - 1;
        int contadorItem = 0;
        for (auto item : components ){
          if(item != "f"){
            faces[contFaces][contadorItem] = new int[3];
            int facesContador = 0;
            vector<string> coords = explode( item , '/' );
            for(auto coord : coords){
              int i = 5;
              string str = coord;
              try{
                int value = stoi(str);
                if (value < 0){
                  value = value * (-1);
                }
                faces[contFaces][contadorItem][facesContador] = value;
                facesContador++;
              }
              catch (std::invalid_argument d){
                cout << "Archivo corrupto. Revisar indentaciones." << endl;
                exit(1);
              }
            }
            contadorItem++;
          }
        }
        facesLen[contFaces] = contadorItem;
        contFaces ++;
      }
    }
  }else{
    cout << "Could not open file" << endl;
  }
};
int*** OBJ::getFaces(){
  return this->faces;
}  
int OBJ::getNumFaces(){
  return numFaces;
}
int *OBJ::getFacesLen(){
  return facesLen;
}
double** OBJ::getVertices(){
  return vertices;
}
int OBJ::getNumVertices(){
  return numVertices;
}
double** OBJ::getTexCoords(){
  return texcoords;
}
double **OBJ::getNormals(){
  return normals;
}
int OBJ::getNumNormals(){
  return numNormals;
}
OBJ::~OBJ(){
  // DESTROY **vertices
  for  (int i = 0 ; i < numVertices ; i++ ){
    delete[] vertices[i];
  }
  delete [] vertices;

  // DESTOY **normals
  for (int i  =0 ; i<numNormals ; i++){
    delete[] normals[i];
  }
  delete[] normals;

  // DESTROY texcoords
  for ( int i = 0 ; i < numTexCoord ; i++ ){
    delete[] texcoords[i];
  }
  delete[] texcoords;

  // DESTROY faces
  for ( int i = 0 ; i < numFaces; i++ ){
    for (int  j = 0 ; j < facesLen[i] ; j++){
      delete[] faces[i][j];
    }
    delete[] faces[i];
  }
  delete[] faces;

  // DESTROY facesLen
  delete[] facesLen;
}
