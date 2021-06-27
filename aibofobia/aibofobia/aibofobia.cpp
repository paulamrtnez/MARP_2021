#include <iostream>
#include <fstream>
#include <algorithm>
#include "EnterosInf.h"
#include "Matriz.h"
using namespace std;

//Rellenamos la matriz con el minimo num de letras que hay que añadir
//para generar un palindromo en frase[i...j]
EntInf aibofobia_rec(string const& frase, int i, int j, Matriz<EntInf>& tabla) {
    if (tabla[i][j] == Infinito) {
        //i debe ser estrictamente menor que j
        if (i >= j) tabla[i][j] = 0;
        //else if (i == j) tabla[i][j] = 1;
        else if (frase[i] == frase[j])
            tabla[i][j] = aibofobia_rec(frase, i + 1, j - 1, tabla);
        else
            tabla[i][j] = min(aibofobia_rec(frase, i, j - 1, tabla) + 1,
                              aibofobia_rec(frase, i + 1, j, tabla) + 1);
    }
    return tabla[i][j];
}

void reconstruir(string const& frase, Matriz<EntInf> const& tabla, int i, int j, string& sol) {
    if (i > j) return;
    else if (i == j) sol.push_back(frase[i]);
    else if (frase[i] == frase[j]) {
        sol.push_back(frase[i]);
        reconstruir(frase, tabla, i + 1, j - 1, sol);
        sol.push_back(frase[j]);
    }
    else if (tabla[i][j] == tabla[i][j - 1] + 1) {
        sol.push_back(frase[j]);
        reconstruir(frase, tabla, i, j - 1, sol);
        sol.push_back(frase[j]);
    }
    else {
        sol.push_back(frase[i]);
        reconstruir(frase, tabla, i + 1, j, sol);
        sol.push_back(frase[i]);
    }
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    string frase;
    cin >> frase;
    if (!std::cin)  // fin de la entrada
        return false;

    int n = frase.length();
    Matriz<EntInf> tabla(n, n, Infinito);
    cout << aibofobia_rec(frase, 0, n - 1, tabla) << " ";

    string sol;
    reconstruir(frase, tabla, 0, n - 1, sol);
    cout << sol << "\n";

    return true;
}

int main() {
    while (resuelveCaso());

    return 0;
}