#include <iostream>
#include <fstream>
#include "IndexPQ.h"
#include "DigrafoValorado.h"
using namespace std;

class Navegando {
public:
    Navegando(DigrafoValorado<int> const& g, vector<int>& costes, int origen, int destino) : origen_(origen),
        dist(g.V(), INF), costes(costes), ulti(g.V()), pq(g.V()) {   
        dist[origen_] = costes[origen_];
        pq.push(origen_, costes[origen_]);

        while (!pq.empty() && pq.top().elem != destino) {
            int v = pq.top().elem;
            pq.pop();

            for (auto a : g.ady(v))
                relajar(a);
        }

        if (!pq.empty()) {  //Significa que el top es el destino
            costeSolucion_ = dist[destino];
        }
    }

    int coste() {
        return costeSolucion_;
    }

private:
    const int INF = 2147483647;
    int origen_;
    int costeSolucion_ = -1;
    vector<int> dist;
    vector<int> costes;
    vector<AristaDirigida<int>> ulti;
    IndexPQ<int> pq;

    void relajar(AristaDirigida<int> a) {
        int v = a.desde();
        int w = a.hasta();

        if (dist[w] > dist[v] + a.valor() + costes[w]) {
            dist[w] = dist[v] + a.valor() + costes[w];
            ulti[w] = a;
            pq.update(w, dist[w]);
        }
    }
};

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    int N;
    cin >> N;
    if (N == 0)
        return false;

    int tiemCarga;
    vector<int> costes;
    for (int i = 0; i < N; ++i) {
        cin >> tiemCarga;
        costes.push_back(tiemCarga);
    }

    DigrafoValorado<int> enlaces(N);
    int M;
    cin >> M;
    for (int j = 0; j < M; ++j) {
        int v, w, valor;
        cin >> v >> w >> valor;
        enlaces.ponArista(AristaDirigida<int>(v - 1, w - 1, valor));
    }

    Navegando navegando(enlaces, costes, 0, N - 1);
    if (navegando.coste() == -1) cout << "IMPOSIBLE\n";
    else cout << navegando.coste() << "\n";

    return true;
}

int main() {
    while (resuelveCaso());

    return 0;
}