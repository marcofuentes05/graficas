# Gráficas
Repositorio para entregas del curso Gráficas por Computadora - UVG2020

## Laboratorio 1: SR1

El laboratorio consiste en desarrollar un render de imágenes en formato BMP a través del desarrollo de diversas funciones (listadas a continuación). Para esta entrega se decidió desarrollar una clase Render que cuenta con los siguientes métodos públicos:
```
void glInit();
void glCreateWindow(int width, int height);
void glViewPort(int x, int y, int width , int height);
void glClear();
void glClearColor(double r,double g,double b);
void glVertex(double x, double y);
void glColor(double r, double g, double b);
void glFinish();
string toString(); //Retorna el estado de la instancia de la clase.
string getMatrix(); //Retorna la matriz de valores RBG como un string.
```

Estos métodos están todos implementados en la función ```main``` de ```SR1.cpp```.