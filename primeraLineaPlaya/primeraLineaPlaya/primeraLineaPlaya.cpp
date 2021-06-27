#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

struct Edificio {
    int W;
    int E;
};

bool operator<(Edificio const& a, Edificio const& b) {
    return a.E < b.E;
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    int N;
    cin >> N;
    if (N == 0)
        return false;

    vector<Edificio> edificios;
    for (int i = 0; i < N; ++i) {
        int w, e;
        cin >> w >> e;

        edificios.push_back({ w, e });
    }
    sort(edificios.begin(), edificios.end());

    int pasadizos = 1;
    int fEd = edificios[0].E;
    for (int i = 1; i < edificios.size(); ++i) {
        if (edificios[i].W > fEd - 1) {
            fEd = edificios[i].E;
            pasadizos++;
        }
    }
    cout << pasadizos << "\n";

    return true;
}

int main() {
    while (resuelveCaso());

    return 0;
}
