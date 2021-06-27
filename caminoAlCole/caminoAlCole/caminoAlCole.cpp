#include <iostream>
#include <fstream>
#include "IndexPQ.h"
#include "GrafoValorado.h"
using namespace std;

class CaminoAlCole {
public:
    CaminoAlCole(GrafoValorado<int> const& g, int origen, int destino) : origen_(origen), destino_(destino),
        dist(g.V(), INF), numCaminos(g.V(), 0), ulti(g.V()), pq(g.V()) {
        dist[origen_] = 0;
        numCaminos[origen_] = 1;
        pq.push(origen_, 0);

        while (!pq.empty() && pq.top().elem != destino) {
            int v = pq.top().elem;
            pq.pop();

            for (auto a : g.ady(v)) {
                relajar(a, v);
            }
        }
    }

    int numCaminosColegio() {
        return numCaminos[destino_];
    }

private:
    const int INF = 2147483647;
    int origen_;
    int destino_;
    vector<int> dist;
    vector<int> numCaminos;
    vector<Arista<int>> ulti;   //Solo guarda un camino minimo
    IndexPQ<int> pq;

    void relajar(Arista<int> a, int v) {
        int w = a.otro(v);

        if (dist[w] > dist[v] + a.valor()) {    //Tenemos un nuevo camino minimo
            dist[w] = dist[v] + a.valor();
            numCaminos[w] = numCaminos[v];
            ulti[w] = a;
            pq.update(w, dist[w]);
        }
        else if (dist[w] == dist[v] + a.valor()) {  //Tenemos otro camino con el mismo coste minimo CONOCIDO
            numCaminos[w] += numCaminos[v];
        }
    }
};

bool resuelveCaso() {
    int N;
    cin >> N;
    if (!std::cin)  // fin de la entrada
        return false;

    GrafoValorado<int> pueblo(N);
    int C;
    cin >> C;
    for (int i = 0; i < C; ++i) {
        int v, w, valor;
        cin >> v >> w >> valor;
        pueblo.ponArista(Arista<int>(v - 1, w - 1, valor));
    }

    CaminoAlCole camino(pueblo, 0, N - 1);
    cout << camino.numCaminosColegio() << "\n";

    return true;
}

int main() {
    while (resuelveCaso());

    return 0;
}