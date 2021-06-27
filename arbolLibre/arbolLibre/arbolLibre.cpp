#include <iostream>
#include <fstream>
#include "Grafo.h"
using namespace std;

class ArbolLibre {
public:
    ArbolLibre(Grafo const& g) : visit(g.V(), false) {
        int tam = dfs(g, 0);

        if (tam == g.V()) conexo = true;
    }

    bool esConexo() const { return conexo; }
    bool esCiclico() { return ciclico; }

private:
    bool conexo = false;
    bool ciclico = false;
    vector<bool> visit;

    int dfs(Grafo const& g, int v) {
        visit[v] = true;
        int tam = 1;
        int visitados = 0;
        for (int w : g.ady(v)) {
            if (!visit[w])
                tam += dfs(g, w);
            else {
                visitados++;
                if (visitados > 1) ciclico = true;
            }
        }
        return tam;
    }
};

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    int V;
    cin >> V;
    if (!std::cin)  // fin de la entrada
        return false;

    Grafo grafo(V);
    int A;
    cin >> A;
    for (int i = 0; i < A; ++i) {
        int v, w;
        cin >> v >> w;
        grafo.ponArista(v, w);
    }

    ArbolLibre arbol(grafo);

    if (!arbol.esCiclico() && arbol.esConexo()) cout << "SI\n";
    else cout << "NO\n";

    return true;
}

int main() {
    while (resuelveCaso());

    return 0;
}