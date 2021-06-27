#include <iostream>
#include <fstream>
#include "Grafo.h"
using namespace std;

class NoticiasVuelan {
public:
    NoticiasVuelan(Grafo const& g) : visit(g.V(), false), grupos(g.V(), 0), idGrupo(g.V(), -1) {
        int id = 0;
        for (int v = 0; v < g.V(); ++v) {
            if (!visit[v]) {
                dfs(g, v, id);
                id++;
            }
        }
    }

    int tamGrupo(int id) const { return grupos[idGrupo[id]]; }

private:
    vector<bool> visit;
    vector<int> grupos;
    vector<int> idGrupo;

    void dfs(Grafo const& g, int v, int id) {
        visit[v] = true;
        idGrupo[v] = id;
        grupos[id]++;
        for (int w : g.ady(v)) {
            if (!visit[w])
                dfs(g, w, id);
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

    Grafo usuarios(N);
    int M;
    cin >> M;
    for (int i = 0; i < M; ++i) {
        int tam;
        cin >> tam;
        if (tam > 0) {
            int id, id2;
            cin >> id;
            tam--;
            while (tam > 0) {
                cin >> id2;
                tam--;
                usuarios.ponArista(id - 1, id2 - 1);
            }
        }
    }

    NoticiasVuelan noticia(usuarios);

    for (int id = 0; id < N; ++id)
        cout << noticia.tamGrupo(id) << " ";
    cout << "\n";

    return true;
}

int main() {
    while (resuelveCaso());

    return 0;
}