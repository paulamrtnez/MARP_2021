#include <iostream>
#include <fstream>
#include <queue>
#include "ConjuntosDisjuntos.h"
using namespace std;

bool resuelveCaso() {
    int f, c;
    cin >> f;
    if (!std::cin)  // fin de la entrada
        return false;
    cin >> c;
    getchar();  //Para no leer luego el salto de linea

    ConjuntosDisjuntos manchas(f * c);
    vector<vector<bool>> matriz(f, vector<bool>(c, false));
    char elem;
    int tamMax = 0;

    for (int i = 0; i < f; ++i) {
        for (int j = 0; j < c; ++j) {
            elem = getchar();   //Leemos el caracter de entrada
            if (elem == '#') {
                matriz[i][j] = true;

                //Añadimos la mancha a un conjunto, si tiene alguna mancha adyacente
                //Como vamos metiendo las manchas en orden, solo necesitamos buscar manchas en 4 direcciones
                //Arriba-izquierda
                if (i > 0 && j > 0 && matriz[i - 1][j - 1]) manchas.unir((c * (i - 1)) + (j - 1), (c * i) + j);
                //Arriba
                if (i > 0 && matriz[i - 1][j]) manchas.unir((c * (i - 1)) + j, (c * i) + j);
                //Izquierda
                if (j > 0 && matriz[i][j - 1]) manchas.unir((c * i) + (j - 1), (c * i) + j);
                //Arriba-derecha
                if (i > 0 && j < c - 1 && matriz[i - 1][j + 1]) manchas.unir((c * (i - 1)) + (j + 1), (c * i) + j);

                int nuevoTam = manchas.cardinal((c * i) + j);
                if (tamMax < nuevoTam) tamMax = nuevoTam;
            }
            //else matriz[i][j] = false; -> No hace falta porque ya se inicializa a false
        }
        getchar();  //Saltamos el nuevo salto de linea
    }

    //Soluciones (añadimos nuevos casos de manchas)
    queue<int> soluciones;
    soluciones.push(tamMax);
    int N;
    cin >> N;
    for (int n = 0; n < N; ++n) {
        int i, j;
        cin >> i >> j;
        i--;
        j--;

        matriz[i][j] = true;

        //Ahora necesitamos comprobar la union de manchas en las 8 direcciones
        //Arriba-izquierda
        if (i > 0 && j > 0 && matriz[i - 1][j - 1]) manchas.unir((c * (i - 1)) + (j - 1), (c * i) + j);
        //Arriba
        if (i > 0 && matriz[i - 1][j]) manchas.unir((c * (i - 1)) + j, (c * i) + j);
        //Izquierda
        if (j > 0 && matriz[i][j - 1]) manchas.unir((c * i) + (j - 1), (c * i) + j);
        //Arriba-derecha
        if (i > 0 && j < c - 1 && matriz[i - 1][j + 1]) manchas.unir((c * (i - 1)) + (j + 1), (c * i) + j);

        //Abajo-derecha
        if (i < f - 1 && j < c - 1 && matriz[i + 1][j + 1]) manchas.unir((c * (i + 1)) + (j + 1), (c * i) + j);
        //Abajo
        if (i < f - 1 && matriz[i + 1][j]) manchas.unir((c * (i + 1)) + j, (c * i) + j);
        //Derecha
        if (j < c - 1 && matriz[i][j + 1]) manchas.unir((c * i) + (j + 1), (c * i) + j);
        //Abajo-izquierda
        if (i < f - 1 && j > 0 && matriz[i + 1][j - 1]) manchas.unir((c * (i + 1)) + (j - 1), (c * i) + j);

        int nuevoTam = manchas.cardinal((c * i) + j);
        if (tamMax < nuevoTam) tamMax = nuevoTam;
        soluciones.push(tamMax);
    }

    //Escribir sol
    for (int s = 0; s < N; ++s) {
        cout << soluciones.front() << " ";
        soluciones.pop();
    }
    cout << soluciones.front() << "\n";
    soluciones.pop();

    return true;
}

int main() {
    while (resuelveCaso());

    return 0;
}