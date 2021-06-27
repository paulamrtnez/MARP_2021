#include <iostream>
#include <fstream>
#include <algorithm>
#include "Grafo.h"
using namespace std;

class ColocaGuardias {
public:
    ColocaGuardias(Grafo const& g) : visit(g.V(), false), guardia(g.V(), 0) {
        for (int i = 0; i < g.V(); ++i) {
            if (!visit[i]) {
                int aux = coloca(g, i);

                if (aux == -1) {
                    minimo = -1;
                    break;
                }
                else minimo += aux;
            }
        }
    }

    int minimoGuardias() const { return minimo; }

private:
    int minimo = 0;
    vector<bool> visit;
    vector<int> guardia;

    int coloca(Grafo const& g, int v) {
        //Probamos poniendo guardia en v
        int nGuardiasCon = poneGuardia(g, v);

        //Reseteamos el vector para el segundo caso
        for (int i = 0; i < g.V(); ++i)
            guardia[i] = 0;

        //Ahora probamos sin poner guardia en v
        int nGuardiasSin = noPoneGuardia(g, v);

        if (nGuardiasCon > -1 && nGuardiasSin == -1)
            return nGuardiasCon;
        else if (nGuardiasCon == -1 && nGuardiasSin > -1)
            return nGuardiasSin;
        else return min(nGuardiasCon, nGuardiasSin);
    }

    int poneGuardia(Grafo const& g, int v) {
        guardia[v] = 1;
        visit[v] = true;
        int nG = 1;
        for (int w : g.ady(v)) {
            if (guardia[w] == 1)
                return -1;
            else if (guardia[w] == 0) {
                int aux = noPoneGuardia(g, w);
                if (aux == -1) return -1;
                nG += aux;
            }
        }
        return nG;
    }

    int noPoneGuardia(Grafo const& g, int v) {
        guardia[v] = -1;
        visit[v] = true;
        int nG = 0;
        for (int w : g.ady(v)) {
            if (guardia[w] == -1)
                return -1;
            else if (guardia[w] == 0) {
                int aux = poneGuardia(g, w);
                if (aux == -1) return -1;
                nG += aux;
            }
        }
        return nG;
    }
};

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    int N;
    cin >> N;
    if (!std::cin)  // fin de la entrada
        return false;

    Grafo ciudad(N);
    int C;
    cin >> C;
    for (int i = 0; i < C; ++i) {
        int v, w;
        cin >> v >> w;
        ciudad.ponArista(v - 1, w - 1);
    }

    ColocaGuardias guardias(ciudad);

    int sol = guardias.minimoGuardias();

    if (sol == -1)
        cout << "IMPOSIBLE\n";
    else
        cout << sol << "\n";

    return true;
}

int main() {
    while (resuelveCaso());

    return 0;
}