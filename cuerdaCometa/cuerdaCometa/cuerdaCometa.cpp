#include <iostream>
#include <fstream>
#include <algorithm>
#include "Matriz.h"
#include "EnterosInf.h"
using namespace std;

EntInf matematico(vector<int> const& C, int L) {
    int n = C.size();
    Matriz<EntInf> cuerdas(n + 1, L + 1, Infinito);
    cuerdas[0][0] = 1;
    for (int i = 1; i <= n; ++i) {
        cuerdas[i][0] = 1;
        for (int j = 1; j <= L; ++j) {
            if (C[i - 1] > j) {
                cuerdas[i][j] = cuerdas[i - 1][j];
            }
            else {
                if (cuerdas[i - 1][j] == Infinito)
                    cuerdas[i][j] = cuerdas[i - 1][j - C[i - 1]];
                else if (cuerdas[i - 1][j - C[i - 1]] == Infinito)
                    cuerdas[i][j] = cuerdas[i - 1][j];
                else 
                    cuerdas[i][j] = cuerdas[i - 1][j] + cuerdas[i - 1][j - C[i - 1]];
            }
        }
    }
    return cuerdas[n][L];
}

EntInf ingeniero(vector<int> const& C, int L) {
    int n = C.size();
    Matriz<EntInf> cuerdas(n + 1, L + 1, Infinito);
    cuerdas[0][0] = 0;
    for (int i = 1; i <= n; ++i) {
        cuerdas[i][0] = 0;
        for (int j = 1; j <= L; ++j) {
            if (C[i - 1] > j) {
                cuerdas[i][j] = cuerdas[i - 1][j];
            }
            else {
                cuerdas[i][j] = min(cuerdas[i - 1][j], cuerdas[i - 1][j - C[i - 1]] + 1);
            }
        }
    }
    return cuerdas[n][L];
}

EntInf economista(vector<int> const& C, vector<int> const& P, int L) {
    int n = C.size();
    Matriz<EntInf> cuerdas(n + 1, L + 1, Infinito);
    cuerdas[0][0] = 0;
    for (int i = 1; i <= n; ++i) {
        cuerdas[i][0] = 0;
        for (int j = 1; j <= L; ++j) {
            if (C[i - 1] > j) {
                cuerdas[i][j] = cuerdas[i - 1][j];
            }
            else {
                cuerdas[i][j] = min(cuerdas[i - 1][j], cuerdas[i - 1][j - C[i - 1]] + P[i - 1]);
            }
        }
    }
    return cuerdas[n][L];
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    int N;
    cin >> N;
    if (!std::cin)  // fin de la entrada
        return false;

    vector<int> longitudes;
    vector<int> precios;
    int L;
    cin >> L;
    for (int i = 0; i < N; ++i) {
        int l, p;
        cin >> l >> p;
        longitudes.push_back(l);
        precios.push_back(p);
    }

    EntInf mat = matematico(longitudes, L);
    if (mat == Infinito)
        cout << "NO\n";
    else
        cout << "SI " << mat << " " << ingeniero(longitudes, L) << " " << economista(longitudes, precios, L) << "\n";

    return true;
}

int main() {
    while (resuelveCaso());

    return 0;
}