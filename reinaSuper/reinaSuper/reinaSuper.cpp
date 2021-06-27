#include <iostream>
#include <fstream>
#include <queue>
using namespace std;

struct caja {
    int numCaja;
    int momento;
    caja(int n, int m) : numCaja(n), momento(m) {}
};

bool operator<(caja const& a, caja const& b) {
    return b.momento < a.momento || (b.momento == a.momento && b.numCaja < a.numCaja);
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    int N, C;
    cin >> N >> C;
    if (N == 0 && C == 0)
        return false;

    priority_queue<caja> cola;
    for (int i = 0; i < C; ++i) {
        int cliente;
        cin >> cliente;
        if (i < N) cola.push(caja(i + 1, cliente));
        else {
            caja vacia = cola.top();
            cola.pop();
            vacia.momento += cliente;
            cola.push(vacia);
        }
    }

    if (C < N) cout << C + 1 << "\n";
    else cout << cola.top().numCaja << "\n";

    return true;
}

int main() {
    while (resuelveCaso());

    return 0;
}