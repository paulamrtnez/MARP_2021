#include <iostream>
#include <fstream>
#include <vector>
#include "ConjuntosDisjuntos.h"
using namespace std;

class Ardilla {
public:

};

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    int N;
    cin >> N;
    if (!std::cin)  // fin de la entrada
        return false;
    int M, K, n;
    cin >> M >> K >> n;

    ConjuntosDisjuntos bosque((N + 1) * (M + 1));
    vector<vector<bool>> matriz(N + 1, vector<bool>(M + 1, false));
    vector<pair<int, int>> arboles;
    matriz[0][0] = true;
    matriz[N][M] = true;

    for (int i = 0; i < n; ++i) {
        int x, y;
        cin >> x >> y;
        arboles.push_back(make_pair(x, y));
    }

    bool encontrado = false;
    pair<int, int> nuevoArb;
    while (!arboles.empty() && !encontrado) {
        nuevoArb = arboles.back();
        arboles.pop_back();
        matriz[nuevoArb.first][nuevoArb.second] = true;

        //Unimos el ultimo arbol con los que hay
        int idNuevoArb = ((N + 1) * nuevoArb.first) + nuevoArb.second;
        for (int i = 0; i <= K; ++i) {
            for (int j = 0; j <= K; ++j) {
                if (nuevoArb.first - i >= 0 && nuevoArb.first - j >= 0 && matriz[nuevoArb.first - i][nuevoArb.second - j]) bosque.unir(idNuevoArb, ((N + 1) * nuevoArb.first - i) + nuevoArb.second - j);
                if (nuevoArb.first + i <= N && nuevoArb.first - j >= 0 && matriz[nuevoArb.first + i][nuevoArb.second - j]) bosque.unir(idNuevoArb, ((N + 1) * nuevoArb.first + i) + nuevoArb.second - j);
                if (nuevoArb.first - i >= 0 && nuevoArb.first + j <= M && matriz[nuevoArb.first - i][nuevoArb.second + j]) bosque.unir(idNuevoArb, ((N + 1) * nuevoArb.first - i) + nuevoArb.second + j);
                if (nuevoArb.first + i <= N && nuevoArb.first + j <= M && matriz[nuevoArb.first + i][nuevoArb.second + j]) bosque.unir(idNuevoArb, ((N + 1) * nuevoArb.first + i) + nuevoArb.second + j);
            }
        }

        //¿El origen y el destino estan conectados?
        encontrado = bosque.unidos(0, ((N + 1) * (M + 1)) - 1);
    }

    if (!encontrado) cout << "NUNCA SE PUDO\n";
    else {
        //El ultimo arbol que permitia realizar el viaje es nuevoArb
        cout << nuevoArb.first << " " << nuevoArb.second << "\n";
    }

    return true;
}

int main() {
    while (resuelveCaso());

    return 0;
}