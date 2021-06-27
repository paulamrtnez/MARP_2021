#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    int N;
    cin >> N;
    if (!std::cin)  // fin de la entrada
        return false;

    //Guardamos los valores iniciales de la tabla
    vector<vector<int>> matriz(N, vector<int>(N, 0));
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            int valor;
            cin >> valor;
            matriz[i][j] = valor;
        }
    }

    int mejorCol = 0;
    //Vamos generando en mejor camino para cada casilla
    for (int i = 1; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (j > 0)
                if (j < N - 1)
                    matriz[i][j] += max(max(matriz[i - 1][j], matriz[i - 1][j - 1]), matriz[i - 1][j + 1]);
                else
                    matriz[i][j] += max(matriz[i - 1][j], matriz[i - 1][j - 1]);
            else
                if (j < N - 1)
                    matriz[i][j] += max(matriz[i - 1][j], matriz[i - 1][j + 1]);
                else
                    matriz[i][j] += matriz[i - 1][j];
            
            if (i == N - 1) {  //Ultima fila del tablero
                if (matriz[i][mejorCol] < matriz[i][j])
                    mejorCol = j;
            }
        }
    }
    cout << matriz[N - 1][mejorCol] << " " << mejorCol + 1 << "\n";
    return true;
}

int main() {
    while (resuelveCaso());

    return 0;
}