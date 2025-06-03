// importamos las librerias que vamos a utilizar para el juego
#include <iostream>
#include "generador.hpp"
#include "solucionador.hpp"
using namespace std;


// aca en el main hacemos que corra el laberinto
int main() {
    cout << "Ingresa el tamaño del laberinto por favor: ";
    cin >> alto_del_laberinto;
    ancho_del_laberinto = alto_del_laberinto;

    vector<vector<string>> laberinto = generador_de_laberinto(alto_del_laberinto, ancho_del_laberinto, "🟫");
    crear_camino(laberinto, 1, 1, 0, 70);

    int fila_inicio = 1;
    int columna_inicio = 1;
    int fila_fin = alto_del_laberinto -2;
    int columna_fin = ancho_del_laberinto -1;

    bool se_resolvio = resolver_camino(laberinto, fila_inicio, columna_inicio, fila_fin, columna_fin);

    if (se_resolvio) {
        cout << "✅ El gato encontró la salida!\n\n";
    }

    for(int fila = 0; fila < alto_del_laberinto; fila++) {
        for(int columna = 0; columna < ancho_del_laberinto; columna ++) {
            cout << laberinto[fila][columna] << " ";
        }
        cout << endl;
    }
}