#include <iostream>
#include <fstream>
#include <queue>
#include "Digrafo.h"
using namespace std;

class SerpientesEscaleras {
public:
    SerpientesEscaleras(Digrafo const& g) : destino(g.V() - 1), dist(g.V(), -1) {
        bst(g);
    }

    int minimo() const { return dist[destino]; }

private:
    int origen = 0;
    int destino;
    vector<int> dist;
    queue<int> cola;

    void bst(Digrafo const& g) {
        dist[origen] = 0;
        cola.push(origen);
        while (!cola.empty()) {
            int v = cola.front();
            cola.pop();
            for (int w : g.ady(v)) {
                if (dist[w] == -1) {
                    dist[w] = dist[v] + 1;
                    if (w == destino)
                        return;
                    cola.push(w);
                }
            }
        }
    }
};

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    int N, K, S, E;
    cin >> N >> K >> S >> E;
    if (N == 0 && K == 0 && S == 0 && E == 0)
        return false;

    Digrafo tablero(N * N);

    //Generamos las conexiones por serpientes y escaleras
    for (int se = 0; se < S + E; ++se) {
        int o, d;
        cin >> o >> d;
        tablero.ponArista(o - 1, d - 1);
    }

    //Generamos las conexiones para cada tirada de dado
    for (int i = 0; i < (N * N) - 1; ++i) {
        for (int j = 1; j <= K; ++j) {
            if (i + j < N * N) {
                bool se = false;
                int ad;
                for (int w : tablero.ady(i + j)) {  //Si ya tiene adyacentes es porque tiene una serpiente o una escalera
                    se = true;
                    ad = w;
                }

                if (se)
                    tablero.ponArista(i, ad);
                else
                    tablero.ponArista(i, i + j);
            }
        }
    }

    SerpientesEscaleras serpEsc(tablero);

    cout << serpEsc.minimo() << "\n";

    return true;
}

int main() {
    while (resuelveCaso());

    return 0;
}