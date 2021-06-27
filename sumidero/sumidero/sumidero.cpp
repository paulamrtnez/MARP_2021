#include <iostream>
#include <fstream>
#include "Digrafo.h"
using namespace std;

class Sumidero {
public:
    Sumidero(Digrafo const& g) : visit(g.V(), false) {
        existeSumidero = buscaSumidero(g, 0);
    }

    bool haySumidero() const { return existeSumidero; }
    int sumidero() const { return idSumidero; }

private:
    bool existeSumidero = false;
    int idSumidero = -1;
    vector<bool> visit;

    bool buscaSumidero(Digrafo const& g, int v) {
        visit[v] = true;
        bool adyacentes = false;

        for (int w : g.ady(v)) {
            adyacentes = true;
            if (!visit[w]) {
                if (buscaSumidero(g, w))
                    return true;
            }
        }

        //Si no tiene adyacentes puede ser sumidero
        if (!adyacentes) {
            bool esS = true;
            for (int i = 0; i < g.V() && esS; ++i) {
                if (i != v && !g.hayArista(i, v))
                    esS = false;
            }
            if (esS) {
                idSumidero = v;
                return true;
            }
        }
        return false;
    }
};

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    int V;
    cin >> V;
    if (!std::cin)  // fin de la entrada
        return false;

    Digrafo grafo(V);
    int A;
    cin >> A;
    for (int i = 0; i < A; ++i) {
        int a, b;
        cin >> a >> b;
        grafo.ponArista(a, b);
    }

    Sumidero sumidero(grafo);

    if (sumidero.haySumidero())
        cout << "SI " << sumidero.sumidero() << "\n";
    else
        cout << "NO\n";

    return true;
}

int main() {
    while (resuelveCaso());

    return 0;
}