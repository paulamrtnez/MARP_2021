#include <iostream>
#include <fstream>
#include <climits>
#include <queue>
#include <algorithm>
#include "Matriz.h"
using namespace std;

struct Pelicula {
    int comienzo;
    int fin;
    int duracion;
    Pelicula(int c, int d) : comienzo(c), fin(c + d), duracion(d) {}
};

bool operator<(Pelicula const& a, Pelicula const& b) {
    return b.comienzo < a.comienzo;
}

int verPeli(vector<Pelicula> const& P, int i, int j, Matriz<int>& tabla) {
    int n = P.size();
    if (tabla[i][j] == -1) {
        if (i == n + 1)
            tabla[i][j] = 0;
        else if (j != 0 && P[i - 1].comienzo < P[j - 1].fin + 10)
            tabla[i][j] = verPeli(P, i + 1, j, tabla);
        else
            tabla[i][j] = max(verPeli(P, i + 1, j, tabla), verPeli(P, i + 1, i, tabla) + P[i - 1].duracion);
    }
    return tabla[i][j];
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    int N;
    cin >> N;
    if (N == 0)
        return false;

    Matriz<int> tabla(N + 2, N + 1, -1);
    priority_queue<Pelicula> cola;
    vector<Pelicula> peliculas;
    for (int i = 0; i < N; ++i) {
        int H, M, D;
        cin >> H;
        cin.get();
        cin >> M >> D;
        cola.push(Pelicula((H * 60) + M, D));
    }

    while (!cola.empty()) {
        peliculas.push_back(cola.top());
        cola.pop();
    }

    cout << verPeli(peliculas, 1, 0, tabla) << "\n";
    return true;
}

int main() {
    while (resuelveCaso());

    return 0;
}