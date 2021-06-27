#include <iostream>
#include <fstream>
#include <climits>
#include "Matriz.h"
using namespace std;

int cortaTableros(vector<int> const& C) {
    int n = C.size();
    Matriz<int> matrices(n + 1, n + 1, 0);
    for (int d = 2; d < n; ++d) {   //Las diagonales van de 1 a n - 1
        for (int i = 1; i <= n - d; ++i) {  //Nº total de elems en la diagonal d es n - d
            int j = i + d;  //La columna a la que pertenece el elem i de la diagonal d es i + d
            matrices[i][j] = INT_MAX;
            for (int k = i + 1; k < j; ++k) {
                int temp = matrices[i][k] + matrices[k][j] + 2 * (C[j - 1] - C[i - 1]);
                if (temp < matrices[i][j]) {
                    matrices[i][j] = temp;
                }
            }
        }
    }
    return matrices[1][n];
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    int L, N;
    cin >> L >> N;
    if (L == 0 && N == 0)
        return false;

    vector<int> cortes;
    cortes.push_back(0);
    for (int i = 0; i < N; ++i) {
        int c;
        cin >> c;
        cortes.push_back(c);
    }
    cortes.push_back(L);

    cout << cortaTableros(cortes) << "\n";
    return true;
}

int main() {
    while (resuelveCaso());

    return 0;
}