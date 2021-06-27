#include <iostream>
#include <queue>
using namespace std;

//
//  Grafo.h
//
//  ImplementaciÃ³n de grafos no dirigidos
//
//  Facultad de InformÃ¡tica
//  Universidad Complutense de Madrid
//
//  Copyright (c) 2020  Alberto Verdejo
//

#ifndef GRAFO_H_
#define GRAFO_H_

#include <iostream>
#include <vector>
#include <iostream>
#include <stdexcept>

using Adys = std::vector<int>;  // lista de adyacentes a un vÃ©rtice

class Grafo {
private:
    int _V;  // nÃºmero de vÃ©rtices
    int _A;  // nÃºmero de aristas
    std::vector<Adys> _ady;  // vector de listas de adyacentes
public:

    /**
     * Crea un grafo con V vÃ©rtices.
     */
    Grafo(int V) : _V(V), _A(0), _ady(_V) {}

    /**
     * Crea un grafo a partir de los datos en el flujo de entrada (si puede).
     * primer es el Ã­ndice del primer vÃ©rtice del grafo en el entrada.
     */
    Grafo(std::istream& flujo, int primer = 0) : _A(0) {
        flujo >> _V;
        if (!flujo) return;
        _ady.resize(_V);
        int E, v, w;
        flujo >> E;
        while (E--) {
            flujo >> v >> w;
            ponArista(v - primer, w - primer);
        }
    }

    /**
     * Devuelve el nÃºmero de vÃ©rtices del grafo.
     */
    int V() const { return _V; }

    /**
     * Devuelve el nÃºmero de aristas del grafo.
     */
    int A() const { return _A; }

    /**
     * AÃ±ade la arista v-w al grafo.
     * @throws domain_error si algÃºn vÃ©rtice no existe
     */
    void ponArista(int v, int w) {
        if (v < 0 || v >= _V || w < 0 || w >= _V)
            throw std::domain_error("Vertice inexistente");
        ++_A;
        _ady[v].push_back(w);
        _ady[w].push_back(v);
    }

    /**
     * Devuelve la lista de adyacencia de v.
     * @throws domain_error si v no existe
     */
    Adys const& ady(int v) const {
        if (v < 0 || v >= _V)
            throw std::domain_error("Vertice inexistente");
        return _ady[v];
    }

    /**
     * Muestra el grafo en el stream de salida o (para depurar)
     */
    void print(std::ostream& o = std::cout) const {
        o << _V << " vÃ©rtices, " << _A << " aristas\n";
        for (int v = 0; v < _V; ++v) {
            o << v << ": ";
            for (int w : _ady[v]) {
                o << w << " ";
            }
            o << "\n";
        }
    }
};

/**
 * Para mostrar grafos por la salida estÃ¡ndar
 */
inline std::ostream& operator<<(std::ostream& o, Grafo const& g) {
    g.print(o);
    return o;
}

#endif /* GRAFO_H_ */

class NodoLejano {
public:
    NodoLejano() {}

    int dfs(Grafo const& g, int origen, int TTL) {
        int nodos = 1;
        if (TTL > 0) {
            queue<int> cola;
            vector<int> distancia(g.V(), -1);
            distancia[origen] = 0;
            cola.push(origen);

            while (!cola.empty()) {
                int v = cola.front();
                cola.pop();

                for (int w : g.ady(v)) {
                    if (distancia[w] == -1) {
                        distancia[w] = distancia[v] + 1;
                        nodos++;
                        if (distancia[w] < TTL) {
                            cola.push(w);
                        }
                    }
                }
            }
        }
        return nodos;
    }
};

bool resuelveCaso() {
    vector<int> sols;
    int N, C;
    cin >> N; cin >> C;

    if (!cin) return false;

    int x, y;
    Grafo grafito(N);
    NodoLejano redes;

    for (int i = 0; i < C; ++i) {
        cin >> x; cin >> y;
        grafito.ponArista(x - 1, y - 1);
    }

    int K;
    cin >> K;
    for (int j = 0; j < K; ++j) {
        cin >> x; cin >> y;
        sols.push_back(N - redes.dfs(grafito, x - 1, y));
    }

    for (int l = 0; l < K; ++l)
        cout << sols[l] << "\n";
    cout << "---\n";

    return true;
}

int main()
{
    while (resuelveCaso());

    return 0;
}