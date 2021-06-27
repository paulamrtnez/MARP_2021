#include <iostream>
#include <fstream>
#include <algorithm>
#include "Grafo.h"
using namespace std;

class AmigosDeMisAmigos {
public:
    AmigosDeMisAmigos(Grafo const& g) : visit(g.V(), false) {
        for (int i = 0; i < g.V(); ++i) {
            if (!visit[i]) {
                int tam = dfs(g, i);
                maximo = max(maximo, tam);
            }
        }
    }

    int maxAmigos() const { return maximo; }

private:
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
void resuelveCaso() {
    int N, M;
    cin >> N >> M;

    Grafo personas(N);

    for (int i = 0; i < M; ++i) {
        int a, b;
        cin >> a >> b;
        personas.ponArista(a - 1, b - 1);
    }

    AmigosDeMisAmigos amigos (personas);

    cout << amigos.maxAmigos() << "\n";
}

int main() {
    int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();

    return 0;
}