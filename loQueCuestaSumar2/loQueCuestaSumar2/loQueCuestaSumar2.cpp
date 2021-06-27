#include <iostream>
#include <fstream>
#include <queue>
using namespace std;

// función que resuelve el problema
// comentario sobre el coste, O(f(N)), donde N es ...
long long int resolver(int N) {
    priority_queue<long long int, vector<long long int>, greater<long long int>> cuentas;
    long long int elem;
    for (int i = 0; i < N; ++i) {
        cin >> elem;
        cuentas.push(elem);
    }
    if (N == 1) return 0;

    long long int x, sol = 0, coste = 0;
    while (cuentas.size() > 1) {
        x = cuentas.top();
        cuentas.pop();
        sol = x + cuentas.top();
        cuentas.pop();
        coste += sol;
        cuentas.push(sol);
    }
    return coste;
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    int N;
    cin >> N;
    if (N == 0)
        return false;

    cout << resolver(N) << "\n";

    return true;
}

int main() {
    while (resuelveCaso());

    return 0;
}