#include <iostream>
#include <fstream>
#include <queue>
using namespace std;

struct instrumento {
    int musicos;
    int partituras;
    instrumento(int m, int p) : musicos(m), partituras(p) {}
};

bool operator<(instrumento const& a, instrumento const& b) {
    return (a.musicos / a.partituras) < (b.musicos / b.partituras) ||
        ((a.musicos / a.partituras) == (b.musicos / b.partituras) && (a.musicos % a.partituras) < (b.musicos % b.partituras));
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    int p;
    cin >> p;
    if (!std::cin)  // fin de la entrada
        return false;

    int n;
    cin >> n;
    if (n > 0) {
        priority_queue<instrumento> concierto;
        for (int i = 0; i < n; ++i) {
            int num;
            cin >> num;
            concierto.push(instrumento(num, 1));
        }

        for (int j = n; j < p; ++j) {
            instrumento prior = concierto.top();
            if (prior.musicos > prior.partituras) {
                concierto.pop();
                concierto.push(instrumento(prior.musicos, prior.partituras + 1));
            }
        }

        if (concierto.top().musicos % concierto.top().partituras == 0) cout << concierto.top().musicos / concierto.top().partituras << "\n";
        else cout << (concierto.top().musicos / concierto.top().partituras) + 1 << "\n";
    }
    else cout << 0 << "\n";
    return true;
}

int main() {
    while (resuelveCaso());

    return 0;
}