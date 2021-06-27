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

    priority_queue<long long int, vector<long long int>, greater<long long int>> partidos;
    for (int i = 0; i < N; ++i) {
        long long int val;
        cin >> val;
        partidos.push(val);
    }

    long long int gorras = 0;
    while (partidos.size() > 1) {
        long long int eq1 = partidos.top();
        partidos.pop();
        long long int aux = eq1 + partidos.top();
        partidos.pop();
        partidos.push(aux);
        gorras += aux;
    }
    cout << gorras << "\n";
    return true;
}

int main() {
    while (resuelveCaso());

    return 0;
}