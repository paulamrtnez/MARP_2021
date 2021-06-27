#include <iostream>
#include <fstream>
#include <algorithm>
#include "Matriz.h"
using namespace std;

int subsecuencia_rec(string const& s1, string const& s2, int i, int j, Matriz<int>& tabla) {
    if (i >= s1.size() || j >= s2.size())
        return 0;
    
    if (tabla[i][j] == -1) {
        if (s1[i] == s2[j])
            tabla[i][j] = subsecuencia_rec(s1, s2, i + 1, j + 1, tabla) + 1;
        else
            tabla[i][j] = max(subsecuencia_rec(s1, s2, i + 1, j, tabla),
                              subsecuencia_rec(s1, s2, i, j + 1, tabla));
    }
    return tabla[i][j];
}

void reconstruir(string const& s1, string const& s2, Matriz<int> const& tabla, int i, int j, string& sol) {
    if (i >= s1.size() || j >= s2.size())
        return;
    if (s1[i] == s2[j]) {
        sol.push_back(s1[i]);
        reconstruir(s1, s2, tabla, i + 1, j + 1, sol);
    }
    else if (i + 1 < s1.size() && tabla[i][j] == tabla[i + 1][j])
        reconstruir(s1, s2, tabla, i + 1, j, sol);
    else if (j + 1 < s2.size())
        reconstruir(s1, s2, tabla, i, j + 1, sol);
    else
        return;
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    string secuencia1;
    cin >> secuencia1;
    if (!std::cin)  // fin de la entrada
        return false;

    string secuencia2;
    cin >> secuencia2;

    Matriz<int> tabla(secuencia1.size(), secuencia2.size(), -1);
    subsecuencia_rec(secuencia1, secuencia2, 0, 0, tabla);

    string sol;
    reconstruir(secuencia1, secuencia2, tabla, 0, 0, sol);
    cout << sol << "\n";
    return true;
}

int main() {
    while (resuelveCaso());

    return 0;
}