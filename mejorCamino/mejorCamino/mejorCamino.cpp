#include <iostream>
#include <fstream>
#include <queue>
#include "IndexPQ.h"
#include "GrafoValorado.h"
using namespace std;

class menosAristas {
public:
    menosAristas(GrafoValorado<int> const& g, int origen) : origen_(origen),
    visit(g.V(), false), ant(g.V()), dist(g.V()) {
        bfs(g);
    }

    bool hayCamino(int destino) {
        return visit[destino];
    }

    int numAristas(int destino) {
        return dist[destino];
    }

private:
    int origen_;
    vector<int> dist;
    vector<bool> visit;
    vector<int> ant;

    void bfs(GrafoValorado<int> const& g) {
        queue<int> q;
        dist[origen_] = 0; visit[origen_] = true;
        q.push(origen_);

        while (!q.empty()) {
            int v = q.front(); q.pop();
            for (auto w : g.ady(v)) {
                if (!visit[w.otro(v)]) {
                    ant[w.otro(v)] = v;
                    dist[w.otro(v)] = dist[v] + 1;
                    visit[w.otro(v)] = true;
                    q.push(w.otro(v));
                }
            }
        }
    }
};

class mejorCamino {
public:
    mejorCamino(GrafoValorado<int> const& g, int origen, int destino) : origen_(origen), destino_(destino),
        dist(g.V(), INF), numAristas(g.V(), 0), ulti(g.V()), pq(g.V()) {
        dist[origen_] = 0;
        pq.push(origen_, 0);

        while (!pq.empty() && pq.top().elem != destino) {
            int v = pq.top().elem;
            pq.pop();

            for (auto a : g.ady(v)) {
                relajar(a, v);
            }
        }
    }

    int costeCamino() {
        return dist[destino_];
    }

    int numAristasDijkstra() {
        return numAristas[destino_];
    }

private:
    const int INF = 2147483647;
    int origen_;
    int destino_;
    vector<int> dist;
    vector<int> numAristas;
    vector<Arista<int>> ulti;   //Solo guarda un camino minimo
    IndexPQ<int> pq;

    void relajar(Arista<int> a, int v) {
        int w = a.otro(v);

        if (dist[w] > dist[v] + a.valor()) {    //Tenemos un nuevo camino minimo
            dist[w] = dist[v] + a.valor();
            numAristas[w] = numAristas[v] + 1;
            ulti[w] = a;
            pq.update(w, dist[w]);
        }
        else if (dist[w] == dist[v] + a.valor() && numAristas[w] > numAristas[v] + 1) {  //Tenemos otro camino con el mismo coste minimo CONOCIDO
            numAristas[w] = numAristas[v] + 1;
            ulti[w] = a;
        }
    }
};

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int N;
    cin >> N;
    if (!std::cin)  // fin de la entrada
        return false;

    GrafoValorado<int> ciudad(N);
    int C;
    cin >> C;
    for (int i = 0; i < C; ++i) {
        int v, w, valor;
        cin >> v >> w >> valor;
        ciudad.ponArista(Arista<int>(v - 1, w - 1, valor));
    }

    int K;
    cin >> K;
    for (int j = 0; j < K; ++j) {
        int o, d;
        cin >> o >> d;
        menosAristas menosA(ciudad, o - 1);
        if (menosA.hayCamino(d - 1)) {
            mejorCamino mejorC(ciudad, o - 1, d - 1);
            cout << mejorC.costeCamino() << " ";
            if (mejorC.numAristasDijkstra() == menosA.numAristas(d - 1))
                cout << "SI\n";
            else cout << "NO\n";
        }
        else cout << "SIN CAMINO\n";
    }
    cout << "---\n";

    return true;
}

int main() {
    while (resuelveCaso());

    return 0;
}
