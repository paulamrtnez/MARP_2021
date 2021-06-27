#include <iostream>
#include <fstream>
#include <climits>
#include "IndexPQ.h"
#include "DigrafoValorado.h"
using namespace std;

class AventuraAmazonas {
public:
    AventuraAmazonas(DigrafoValorado<int> const& g, int orig) : origen(orig),
        dist(g.V(), INF), ulti(g.V()), pq(g.V()) {
        dist[origen] = 0;
        pq.push(origen, 0);
        while (!pq.empty()) {
            int v = pq.top().elem; pq.pop();
            for (auto a : g.ady(v))
                relajar(a);
        }
    }

    bool hayCamino(int v) const { return dist[v] != INF; }
    int distancia(int v) const { return dist[v]; }

private:
    const int INF = INT_MAX;
    int origen;
    std::vector<int> dist;
    std::vector<AristaDirigida<int>> ulti;
    IndexPQ<int> pq;

    void relajar(AristaDirigida<int> a) {
        int v = a.desde(), w = a.hasta();
        if (dist[w] > dist[v] + a.valor()) {
            dist[w] = dist[v] + a.valor(); ulti[w] = a;
            pq.update(w, dist[w]);
        }
    }
};

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    int N;
    cin >> N;
    if (!std::cin)  // fin de la entrada
        return false;

    DigrafoValorado<int> Amazonas(N);

    for (int s = 0; s < N - 1; ++s) {
        for (int i = N - 1; i > s; --i) {
            int coste;
            cin >> coste;
            Amazonas.ponArista(AristaDirigida<int>(s, N - i + s, coste));
        }
    }

    for (int s = 0; s < N - 1; ++s) {
        AventuraAmazonas aventura(Amazonas, s);
        for (int i = N - 1; i > s; --i) {
            cout << aventura.distancia(N - i + s) << " ";
        }
        cout << "\n";
    }
    return true;
}

int main() {
    while (resuelveCaso());

    return 0;
}