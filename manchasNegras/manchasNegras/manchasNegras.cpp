#include <iostream>
#include <fstream>
#include <algorithm>
#include "Grafo.h"
using namespace std;

class ManchasNegras {
public:
    ManchasNegras(Grafo const& g, vector<vector<bool>> const& matriz, int F, int C) : visit(g.V(), false) {
        for (int i = 0; i < F; ++i) {
            for (int j = 0; j < C; ++j) {
                int tam = 0;
                if (!visit[i * C + j] && matriz[i][j]) {
                    nManchas++;
                    tam = dfs(g, i * C + j);
                }
                maximo = max(tam, maximo);
            }
        }
    }

    int numManchas() { return nManchas; }
    int maxMancha() { return maximo; }

private:
    int nManchas = 0;
    int maximo = 0;
    vector<bool> visit;

    int dfs(Grafo const& g, int v) {
        visit[v] = true;
        int tam = 1;
        for (int w : g.ady(v)) {
            if (!visit[w])
                tam += dfs(g, w);
        }
        return tam;
    }
};

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    int F;
    cin >> F;
    if (!std::cin)  // fin de la entrada
        return false;

    int C;
    cin >> C;
    vector<vector<bool>> matriz(F, vector<bool> (C, false));
    Grafo manchas(F * C);

    for (int i = 0; i < F; i++) {
        for (int j = 0; j < C; j++) {
            char caract;
            cin >> caract;
            if (caract == '#') {
                matriz[i][j] = true;
                if (i - 1 >= 0 && matriz[i - 1][j])
                    manchas.ponArista(i * C + j, (i - 1) * C + j);
                if (j - 1 >= 0 && matriz[i][j - 1])
                    manchas.ponArista(i * C + j, i * C + (j - 1));
            }
        }
    }

    ManchasNegras mNegras(manchas, matriz, F, C);
    cout << mNegras.numManchas() << " " << mNegras.maxMancha() << "\n";

    return true;
}

int main() {
    while (resuelveCaso());

    return 0;
}