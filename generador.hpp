#ifndef GENERADOR_HPP
#define GENERADOR_HPP

#include <vector>
#include <string>
using namespace std;

extern int ancho_del_laberinto;
extern int alto_del_laberinto;

vector<vector<string>> generador_de_laberinto(int alto, int ancho, string simbolo);
void crear_camino(vector<vector<string>> &laberinto, int fila, int columna);

#endif