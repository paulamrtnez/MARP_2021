#include <iostream>
#include <fstream>
#include "GrafoValorado.h"
using namespace std;

void camino(GrafoValorado<int> const& g, int origen, int const destino, int const ancho, vector<bool>& visitado, bool& hayCamino) {
    for (auto a : g.ady(origen)) {
        if (hayCamino) return;

        if (a.valor() >= ancho && !visitado[a.otro(origen)]) {
            visitado[a.otro(origen)] = true;
            if (a.otro(origen) == destino) hayCamino = true;
            else camino(g, a.otro(origen), destino, ancho, visitado, hayCamino);
        }
    }
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    int V;
    cin >> V;
    if (!std::cin)  // fin de la entrada
        return false;
    int E;
    cin >> E;

    GrafoValorado<int> ciudad(V);

    for (int i = 0; i < E; ++i) {
        int x, y, ancho;
        cin >> x >> y >> ancho;
        ciudad.ponArista(Arista<int>(x - 1, y - 1, ancho));
    }

    int K;
    cin >> K;
    for (int j = 0; j < K; ++j) {
        int O, D, A;
        cin >> O >> D >> A;

        if (O == D) cout << "SI\n";
        else {
            vector<bool> visitado(V);
            bool hayCamino = false;

            camino(ciudad, O - 1, D - 1, A, visitado, hayCamino);

            if (hayCamino) cout << "SI\n";
            else  cout << "NO\n";
        }
    }

    return true;
}

int main() {
    while (resuelveCaso());
    return 0;
}