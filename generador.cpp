// importamos las librerias que vamos a utilizar para el juego
#include "generador.hpp"
#include <algorithm> // libreria y usamos shuffle de esta libreria para mezclar
#include <random>
using namespace std;

// aca se va a almacenar el tamaño del laberinto definido por el usuario
int ancho_del_laberinto;
int alto_del_laberinto;

// aca creamos la funcion para crear laberinto
vector<vector<string>> generador_de_laberinto(int alto, int ancho, string simbolo) {
    return vector<vector<string>>(alto, vector<string>(ancho, simbolo));
}

// aca creamos una funcion recursiva para generar el camino con el algoritmo backtraking
void crear_camino(vector<vector<string>> &laberinto, int fila, int columna) {
    

    // marcamos la celda actual como camino 
    laberinto[fila][columna] = "⬜";
    // definimos el punto de partida
    laberinto[1][0] = "🟥";
    //definimos la meta final
    laberinto[alto_del_laberinto -2][ancho_del_laberinto -1] = "🟩";

    // utilizamos una lista de pares enteros para las direcciones
    vector<pair<int, int>> direcciones = {
        {-2, 0},
        {2, 0},
        {0, -2},
        {0, 2}
    };

    // aca vamos a mezclar las direcciones aleatoriamente
    shuffle(direcciones.begin(), direcciones.end(), mt19937(random_device()()));

    //aca vamos a usar un for para recorrer las direcciones mezcladas
    for (auto movimiento : direcciones) {
        int nueva_fila = fila + movimiento.first;
        int nueva_columna = columna + movimiento.second;

        
        // aca verificamos si la nueva posicion esta dentro del laberinto y que sea una pared
        if (nueva_fila >= 0 && nueva_fila < laberinto.size() -1 && nueva_columna >= 0 && nueva_columna < laberinto[0].size() -1 && laberinto[nueva_fila][nueva_columna] == "🟫") {
            
            // rompemos la pared entre la celda actual y la nueva
            laberinto[fila + movimiento.first / 2][columna + movimiento.second / 2] = "⬜";


            // aca hacemos la recursion, repetimos el proceso desde la nueva celda
            crear_camino(laberinto, nueva_fila, nueva_columna);
        }
    }
}