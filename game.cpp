// importamos las librerias que vamos a utilizar para el juego
#include <iostream> // entrada y salita, tipo cout y cin
#include "generador.hpp"  
#include "solucionador.hpp"

using namespace std::chrono; // esto usamos para medir el tiempo en que se resuelve el laberinto


int main() {
    // pedimos medida de laberinto al usuario
    cout << "Ingresa el tamaño del laberinto por favor: ";
    cin >> alto_del_laberinto;
    ancho_del_laberinto = alto_del_laberinto;

    // generamos el laberinto usando la funcion que creamos
    vector<vector<string>> laberinto = generador_de_laberinto(alto_del_laberinto, ancho_del_laberinto, "🟫");

    // aca creamos la matriz de las visitadas
    vector<vector<bool>> visitadas(alto_del_laberinto, vector<bool>(ancho_del_laberinto, false));


    // llamamos a la funcion que crea nuestro camino para abrir camino des el inicio
    crear_camino(laberinto, 1, 1);

    // coordenadas para incio y final del laberinto
    int fila_inicio = 1; 
    int columna_inicio = 0;
    int fila_destino = alto_del_laberinto -2;
    int columna_destino = ancho_del_laberinto -1;


    // aca medimos el tiempo que tarda en resolver el laberinto
    // marcamos el tiempo antes de empezar a resolver el laberinto
    auto inicio = high_resolution_clock::now();
    // llamamos a la funcion para resolver el laberinto que devuelve true o false si encontro camino y la guardamos en una variable nueva
    bool se_resolvio = resolver_camino(laberinto, fila_inicio, columna_inicio, fila_destino, columna_destino);
    // marcamos el tiempo despues de terminar de resolver
    auto fin = high_resolution_clock::now();

    // calculamos el tiempo y lo mostramos en consola
    auto duracion = duration_cast<milliseconds>(fin - inicio);
    cout<< "El tiempo para solucionar el slaberinto es de: " << duracion.count() << "ms\n";


    // si se resolvio muestra este mensaje de que se encontro
    if (se_resolvio) {
        cout << "✅ El gato encontro la salida\n\n";
    }

    // aca mostramos el laberinto en la consola 
    for(int fila = 0; fila < alto_del_laberinto; fila++) {
        for(int columna = 0; columna < ancho_del_laberinto; columna ++) {
            cout << laberinto[fila][columna] << " ";
        }
        // y aca hacemos el salto de linea, imprime por fila entonces tira mucho mas prolijo
        cout << endl;
    }
    return 0;
}