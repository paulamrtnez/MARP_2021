#include <iostream>
#include <fstream>
#include <queue>
#include "Digrafo.h"
using namespace std;

class OrdenandoTareas {
public:
    OrdenandoTareas(Digrafo const& g) : visit(g.V(), false), apilado(g.V(), false) {
        for (int v = 0; v < g.V() && !ciclo; ++v) {
            if (!visit[v])
                dfs(g, v);
        }
    }

    bool hayCiclo() const { return ciclo; }
    deque<int> const& ordenacionTopologica() const { return orden; }

private:
    bool ciclo = false;
    vector<bool> visit;
    vector<bool> apilado;
    deque<int> orden;

    void dfs(Digrafo const& g, int v) {
        visit[v] = true;
        apilado[v] = true;

        for (int w : g.ady(v)) {
            if (ciclo)
                break;
            if (!visit[w])
                dfs(g, w);
            else if (apilado[w])
                ciclo = true;
        }

        apilado[v] = false;
        orden.push_front(v);
    }
};

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    int N;
    cin >> N;
    if (!std::cin)  // fin de la entrada
        return false;

    Digrafo tareas(N);
    int M;
    cin >> M;
    for (int i = 0; i < M; ++i) {
        int a, b;
        cin >> a >> b;
        tareas.ponArista(a - 1, b - 1);
    }

    OrdenandoTareas ordenacion(tareas);

    if (ordenacion.hayCiclo())
        cout << "Imposible\n";
    else {
        deque<int> orden = ordenacion.ordenacionTopologica();
        for (int i = 0; i < N; ++i)
            cout << orden[i] + 1 << " ";
        cout << "\n";
    }

    return true;
}

int main() {
    while (resuelveCaso());

    return 0;
}