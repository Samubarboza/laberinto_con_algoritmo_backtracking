#include "solucionador.hpp"
#include <queue> // esto importamos para usar la estructura de datos cola 
#include <map> // para almacenar las relaciones entre celdas
#include <chrono> // esto usamos para medir el tiempo de pausa cada vez que imprimimos
#include <thread> // este usamos para las pausas en ejecucion y simular animacion del camino
#include <iostream> // para imprimir en pantalla 
#include <cstdlib> // esto usamos para limpiar la pantalla mientras imprimimos

using namespace std;

// aca creamos la funcion principal que resulve el laberinto con el algoritmo bfs


// aca vamos a crear la funcion que resulve el camino con bfs  Breadth-First Search (Búsqueda en Anchura)
bool resolver_camino(vector<vector<string>> &laberinto, int fila_inicio, int columna_inicio, int fila_destino, int columna_destino) {
    // aca obtenemos las dimensiones del laberinto
    int cantidad_filas = laberinto.size();
    int cantidad_columnas = laberinto[0].size();

    // aca creamos una matriz para saber que celdas ya fueron visitadas
    vector<vector<bool>> celda_visitada(cantidad_filas, vector<bool>(cantidad_columnas, false));

    // mapa que guarda la celda desde la cual llego, y la celda en la que se encuentra para dps reconstruir el camino
    map<pair<int, int>, pair<int, int>> celda_anterior;

    // cola para procesar las celdas en orden (bfs usa cola) guardamos la celda inicial
    queue<pair<int, int>> cola_de_celdas;
    cola_de_celdas.push({fila_inicio, columna_inicio});
    // marcamos la columna de inicio como true para que no se vuelva a procesar mas adelante
    celda_visitada[fila_inicio][columna_inicio] = true; 

    // aca vamos a crear las posibles direcciones
    vector<pair<int, int>> direcciones_movimiento = {
        {1, 0},
        {-1, 0},
        {0, 1},
        {0, -1}
    };

            // aca creamos el ciclo que procesa cada celda del laberinto por orden de llegada, es decir, procesa la cola hasta varciar
    while (!cola_de_celdas.empty()) {
        pair<int, int> celda_actual = cola_de_celdas.front();// tomamos la primera celda
        cola_de_celdas.pop(); // la funcion procesa y luego elimina

        int fila_actual = celda_actual.first; 
        int columna_actual = celda_actual.second;

        // aca comparamos que, si llegamos a la celda de destino reconstruimos el camino
        if (fila_actual == fila_destino && columna_actual == columna_destino) {
            // Creamos un vector para guardar el camino
            vector<pair<int, int>> camino;

            // Reconstruimos el camino desde la meta hasta el inicio
            pair<int, int> celda = {fila_actual, columna_actual};
            while (celda != make_pair(fila_inicio, columna_inicio)) {
            camino.push_back(celda);
            celda = celda_anterior[celda];
            }
            // Agregamos la celda inicio también (opcional, para marcar todo)
            camino.push_back(make_pair(fila_inicio, columna_inicio));

            // Ahora invertimos el camino para que quede del inicio al destino
            reverse(camino.begin(), camino.end());

            // Pintamos el camino en orden
            for (const auto& c : camino) {
                int fila_celda = c.first;
                int columna_celda = c.second;

                if (laberinto[fila_celda][columna_celda] != "🟩") {
                laberinto[fila_celda][columna_celda] = "🐱";

                    system("clear");
                    
                    for (const auto& fila : laberinto) {
                        for (const auto& celda : fila) {
                            cout << celda << " ";
                    }
                    cout << endl;
                }
                this_thread::sleep_for(chrono::milliseconds(100));
            }
        }

        return true;
    }


        // aca creamos un for para que recorra todas las direcciones 
        for (pair<int, int> direccion : direcciones_movimiento) {
            int fila_siguiente = fila_actual + direccion.first;
            int columna_siguiente = columna_actual + direccion.second;

            // aca chequeamos si esta dentro de los limites del laberinto
            bool esta_dentro_de_limites = fila_siguiente >= 0 && fila_siguiente < cantidad_filas && columna_siguiente >= 0 && columna_siguiente < cantidad_columnas;

            // si esta dentro de los limites, y no fue visitada, si es un espacio libre o un objetivo, entonces pasamos a lo siguiente
            if (esta_dentro_de_limites && !celda_visitada[fila_siguiente][columna_siguiente] && (laberinto[fila_siguiente][columna_siguiente] == "⬜" || laberinto[fila_siguiente][columna_siguiente] == "🟩")) {
                
                // le agregamos a la cola 
                cola_de_celdas.push({fila_siguiente, columna_siguiente});
                celda_visitada[fila_siguiente][columna_siguiente] = true; // aca le decimos que ya visitamos para no volver a intentar
                celda_anterior[{fila_siguiente, columna_siguiente}] = {fila_actual, columna_actual}; // 
            }
        }
    }
    // aca lo que hacemos es, si ya probo todo le dice que ya no encontro camino. el while frena solo cuando termina el recorrido
    // usamos para saber si fallo o no la busqueda, el programa usa para avisar que no encontro mas nada. si no avisamos puede seguir buscando como si estuviera todo bien. 
    return false;
}