#include <iostream>
#include <fstream>
#include <queue>
using namespace std;

struct tarea {
    int c;
    int f;
    int p;
    tarea(int c_, int f_, int p_) : c(c_), f(f_), p(p_) {}
};

bool operator<(tarea const& a, tarea const& b) {
    return b.c < a.c || (b.c == a.c && b.f < a.f);
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    int N;
    cin >> N;
    if (!std::cin)  // fin de la entrada
        return false;

    int M, T;
    cin >> M >> T;

    priority_queue<tarea> listaTareas;
    for (int i = 0; i < N; ++i) {
        int c, f, p;
        cin >> c >> f;
        p = 0;
        if (c < T) listaTareas.push(tarea(c, f, p));
    }
    for (int i = 0; i < M; ++i) {
        int c, f, p;
        cin >> c >> f >> p;
        if (c < T) listaTareas.push(tarea(c, f, p));
    }

    bool conflicto = false;
    if (!listaTareas.empty()) {
        tarea prim = listaTareas.top();
        listaTareas.pop();
        while (!listaTareas.empty() && !conflicto) {
            if (prim.f > listaTareas.top().c)
                conflicto = true;

            if (prim.p > 0) {
                prim.c += prim.p;
                prim.f += prim.p;
                if (prim.c < T) listaTareas.push(prim);
            }

            prim = listaTareas.top();
            listaTareas.pop();
        }
    }
    if (conflicto) cout << "SI\n";
    else cout << "NO\n";
    return true;
}

int main() {
    while (resuelveCaso());

    return 0;
}