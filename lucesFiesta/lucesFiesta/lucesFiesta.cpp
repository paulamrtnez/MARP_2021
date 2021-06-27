#include <iostream>
#include <fstream>
#include <algorithm>
#include "EnterosInf.h"
#include "Matriz.h"
using namespace std;

void lucesParaFiesta(vector<int> L, vector<int> C, int Pmax, int Pmin) {
    int n = L.size();
    int mejorCol = Pmin;
    Matriz<EntInf> tabla(n + 1, Pmax + 1, Infinito);
    tabla[0][0] = 0;
    for (int i = 1; i <= n; ++i) {
        tabla[i][0] = 0;
        for (int j = 1; j <= Pmax; ++j) {
            if (L[i - 1] > j)
                tabla[i][j] = tabla[i - 1][j];
            else
                tabla[i][j] = min(tabla[i - 1][j], tabla[i][j - L[i - 1]] + C[i - 1]);

            if (i == n && j >= Pmin) {
                if (tabla[i][mejorCol] > tabla[i][j])
                    mejorCol = j;
            }
        }
    }

    if (tabla[n][mejorCol] == Infinito)
        cout << "IMPOSIBLE\n";
    else
        cout << tabla[n][mejorCol] << " " << mejorCol << "\n";
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    int N;
    cin >> N;
    if (!std::cin)  // fin de la entrada
        return false;
    
    vector<int> potencias, costes;
    int Pmax, Pmin;
    cin >> Pmax >> Pmin;

    for (int i = 0; i < N; ++i) {
        int val;
        cin >> val;
        potencias.push_back(val);
    }
    for (int i = 0; i < N; ++i) {
        int val;
        cin >> val;
        costes.push_back(val);
    }
    lucesParaFiesta(potencias, costes, Pmax, Pmin);
    return true;
}

int main() {
    while (resuelveCaso());

    return 0;
}