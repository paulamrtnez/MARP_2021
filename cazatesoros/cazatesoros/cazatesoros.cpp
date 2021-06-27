#include <iostream>
#include <fstream>
#include <queue>
#include <algorithm>
#include "Matriz.h"
using namespace std;

// función que resuelve el problema
// comentario sobre el coste, O(f(N)), donde N es ...
void cazatesoros(vector<int> O, vector<int> P, int T) {   //P = p + 2p
    int n = O.size();
    Matriz<int> tabla(n + 1, T + 1, -1);
    int mejorCol = 1;
    tabla[0][0] = 0;
    for (int i = 1; i <= n; ++i) {
        tabla[i][0] = 0;
        for (int j = 1; j <= T; ++j) {
            if (P[i - 1] > j)
                tabla[i][j] = tabla[i - 1][j];
            else {
                tabla[i][j] = max(tabla[i - 1][j], tabla[i - 1][j - P[i - 1]] + O[i - 1]);
            }

            if (i == n && tabla[i][mejorCol] < tabla[i][j])
                mejorCol = j;
        }
    }

    if (tabla[n][mejorCol] == -1)
        cout << 0 << "\n" << 0 << "\n";
    else {
        cout << tabla[n][mejorCol] << "\n";

        deque<int> profundidades, oros;
        int i = n, j = mejorCol;
        while (j > 0) {
            if (P[i - 1] <= j && tabla[i][j] != tabla[i - 1][j]) {
                profundidades.push_front(P[i - 1]);
                oros.push_front(O[i - 1]);
                j = j - P[i - 1];
            }
            --i;
        }

        cout << profundidades.size() << "\n";

        for (int i = 0; i < profundidades.size(); ++i)
            cout << profundidades[i] / 3 << " " << oros[i] << "\n";
    }
    cout << "---\n";
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    int T;
    cin >> T;
    if (!std::cin)  // fin de la entrada
        return false;

    vector<int> profundidad, oro;
    int N;
    cin >> N;
    for (int i = 0; i < N; ++i) {
        int p, o;
        cin >> p >> o;
        profundidad.push_back(p * 3);
        oro.push_back(o);
    }
    cazatesoros(oro, profundidad, T);
    return true;
}

int main() {
    while (resuelveCaso());

    return 0;
}