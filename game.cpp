// importamos las librerias que vamos a utilizar para el juego
#include <iostream> // para leer datos en la consola
#include "generador.hpp" 
#include "solucionador.hpp"

using namespace std::chrono;

// aca en el main hacemos que corra el laberinto
int main() {
    cout << "Ingresa el tamaño del laberinto por favor: ";
    cin >> alto_del_laberinto;
    ancho_del_laberinto = alto_del_laberinto;

    vector<vector<string>> laberinto = generador_de_laberinto(alto_del_laberinto, ancho_del_laberinto, "🟫");
    vector<vector<bool>> visitadas(alto_del_laberinto, vector<bool>(ancho_del_laberinto, false));
    bool llego_a_la_salida = false;
    crear_camino(laberinto, 1, 1);

    // coordenadas
    int fila_inicio = 1;
    int columna_inicio = 0;
    int fila_destino = alto_del_laberinto -2;
    int columna_destino = ancho_del_laberinto -1;


    auto inicio = high_resolution_clock::now();
    bool se_resolvio = resolver_camino(laberinto, fila_inicio, columna_inicio, fila_destino, columna_destino);
    auto fin = high_resolution_clock::now();

    auto duracion = duration_cast<milliseconds>(fin - inicio);
    cout<< "El tiempo para solucionar el slaberinto es de: " << duracion.count() << "ms\n";


    if (se_resolvio) {
        cout << "✅ El gato encontro la salida\n\n";
    }

    for(int fila = 0; fila < alto_del_laberinto; fila++) {
        for(int columna = 0; columna < ancho_del_laberinto; columna ++) {
            cout << laberinto[fila][columna] << " ";
        }
        cout << endl;
    }
}