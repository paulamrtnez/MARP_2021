
#include <iostream>
#include <fstream>
#include "IndexPQ.h"
using namespace std;

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    int N;
    cin >> N;
    if (!std::cin)  // fin de la entrada
        return false;
    
    int cant;
    IndexPQ<int> enemigos(N);
    IndexPQ<int> tropas(N);
    for (int i = 0; i < N; ++i) {
        cin >> cant;
        enemigos.push(i, cant);
    }
    for (int i = 0; i < N; ++i) {
        cin >> cant;
        tropas.push(i, cant);
    }
    
    int numGarantizadas = 0;

    for (int i = 0; i < N; ++i) {
        if (enemigos.top().prioridad <= tropas.top().prioridad) {
            numGarantizadas++;
            enemigos.pop();
        }
        tropas.pop();
    }

    cout << numGarantizadas << "\n";

    return true;
}

int main() {
    while (resuelveCaso());

    return 0;
}