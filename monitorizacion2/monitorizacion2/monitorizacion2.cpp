#include <iostream>
#include <fstream>
#include <queue>
using namespace std;

struct registro {
    int id;
    int periodo;
    int momento;
    registro(int i, int p, int m) : id(i), periodo(p), momento(m) {}
};

bool operator<(registro const& a, registro const& b) {
    return b.momento < a.momento || (b.momento == a.momento && b.id < a.id);
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    int N;
    cin >> N;
    if (N == 0)
        return false;

    priority_queue<registro> cola;
    for (int i = 0; i < N; ++i) {
        int id, p;
        cin >> id >> p;
        cola.push(registro(id, p, p));
    }

    int K;
    cin >> K;
    for (int i = 0; i < K; ++i) {
        registro prior = cola.top();
        cola.pop();
        cout << prior.id << "\n";
        prior.momento += prior.periodo;
        cola.push(prior);
    }
    cout << "---\n";

    return true;
}

int main() {
    while (resuelveCaso());

    return 0;
}