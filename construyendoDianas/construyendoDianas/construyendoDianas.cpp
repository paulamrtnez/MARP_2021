#include <iostream>
#include <fstream>
#include <algorithm>
#include "EnterosInf.h"
#include "Matriz.h"
using namespace std;

vector<int> puntuaciones_necesarias(vector<int> const& P, int T) {
    int n = P.size();
    vector<EntInf> puntuaciones(T + 1, Infinito);
    puntuaciones[0] = 0;

    for (int i = 1; i <= n; ++i) {
        for (int j = P[i - 1]; j <= T; ++j)
            puntuaciones[j] = min(puntuaciones[j], puntuaciones[j - P[i - 1]] + 1);
    }

    vector<int> sol;
    if (puntuaciones[T] != Infinito) {
        int i = n, j = T;
        while (j > 0) {
            if (P[i - 1] <= j && puntuaciones[j] == puntuaciones[j - P[i - 1]] + 1) {
                sol.push_back(P[i - 1]);
                j = j - P[i - 1];
            }
            else --i;
        }
    }
    return sol;
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    int V;
    cin >> V;
    if (!std::cin)  // fin de la entrada
        return false;

    vector<int> puntuaciones;
    int S;
    cin >> S;
    for (int i = 0; i < S; ++i) {
        int p;
        cin >> p;
        puntuaciones.push_back(p);
    }

    vector<int> sol = puntuaciones_necesarias(puntuaciones, V);

    if (sol.empty())
        cout << "Imposible\n";
    else {
        cout << sol.size() << ": ";
        for (int s = 0; s < sol.size(); ++s)
            cout << sol[s] << " ";
        cout << "\n";
    }

    return true;
}

int main() {
    while (resuelveCaso());

    return 0;
}