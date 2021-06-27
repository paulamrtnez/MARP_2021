#include <iostream>
#include <fstream>
#include <queue>
using namespace std;

struct Investigacion {  //[c, f)
    int comienzo;
    int final;
    Investigacion(int c = 0, int f = 0) : comienzo(c), final(f) {}
};

bool operator<(Investigacion const& a, Investigacion const& b) {
    return b.comienzo < a.comienzo || (b.comienzo == a.comienzo && a.final < b.comienzo);
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {   //[C, F)
    int C, F, N;
    cin >> C >> F >> N;
    if (C == 0 && F == 0 && N == 0)
        return false;

    priority_queue<Investigacion> investigaciones;

    for (int i = 0; i < N; ++i) {
        int c, f;
        cin >> c >> f;
        investigaciones.push(Investigacion(c, f));
    }

    int ultComienzo = C, cont = 0;
    while (!investigaciones.empty()) {
        Investigacion inv = investigaciones.top();
        investigaciones.pop();

        if (inv.comienzo > ultComienzo) {
            cout << "Imposible\n";
            return true;
        }

        while (!investigaciones.empty() && investigaciones.top().comienzo <= ultComienzo) {
            if (investigaciones.top().final > inv.final)
                inv = investigaciones.top();
            investigaciones.pop();
        }

        cont++;
        ultComienzo = inv.final;

        if (inv.final >= F) {
            cout << cont << "\n";
            return true;
        }
    }
    cout << "Imposible\n";
    return true;
}

int main() {
    while (resuelveCaso());

    return 0;
}