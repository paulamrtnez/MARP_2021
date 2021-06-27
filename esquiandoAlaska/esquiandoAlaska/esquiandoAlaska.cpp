#include <iostream>
#include <fstream>
#include <queue>
using namespace std;

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    int N;
    cin >> N;
    if (N == 0)
        return false;

    priority_queue<int> alturas;
    priority_queue<int> longitudes;

    for (int i = 0; i < N; ++i) {
        int elem;
        cin >> elem;
        alturas.push(elem);
    }
    for (int i = 0; i < N; ++i) {
        int elem;
        cin >> elem;
        longitudes.push(elem);
    }

    int sumaDiferencias = 0;
    for (int i = 0; i < N; ++i) {
        sumaDiferencias += abs(alturas.top() - longitudes.top());
        alturas.pop();  longitudes.pop();
    }

    cout << sumaDiferencias << "\n";

    return true;
}

int main() {
    while (resuelveCaso());

    return 0;
}