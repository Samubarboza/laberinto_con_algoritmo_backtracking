#include "solucionador.hpp"

// aca creamos la funcion que va a resolver el camino hacia la salida
bool resolver_camino(vector<vector<string>> &laberinto, int fila, int columna, int fila_destino, int columna_destino) {
    if (fila == fila_destino && columna == columna_destino) {
        return true;
    }
    if (laberinto[fila][columna] != "⬜" && !(fila == fila_destino && columna == columna_destino)) {
        return false;
    }
    
    laberinto[fila][columna] = "🐱";

    vector<pair<int, int>> direcciones = {
        {1, 0},
        {-1, 0},
        {0, 1},
        {0, -1}
    };
    
    for(auto movimiento : direcciones) {
        int nueva_fila = fila + movimiento.first;
        int nueva_columna = columna + movimiento.second;
        
        if (nueva_fila >= 0 && nueva_fila < laberinto.size() && nueva_columna >= 0 && nueva_columna < laberinto[0].size()) {
            if (resolver_camino(laberinto, nueva_fila, nueva_columna, fila_destino, columna_destino)) {
                laberinto[fila][columna] = "🐱";
                return true;
            }
        }
    }
    laberinto[fila][columna] = "⬜";
    return false;
}
