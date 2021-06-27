#include <iostream>
#include <fstream>
#include <queue>
#include "IndexPQ.h"
using namespace std;

struct Baterias {
    int id;
    int carga;
    int tiempoVida;
    Baterias(int i, int t) : id(i), carga(t), tiempoVida(t) {}
    Baterias(int i, int c, int t) : id(i), carga(c), tiempoVida(t) {}
};

bool operator<(Baterias const& a, Baterias const& b) {
    return b.tiempoVida < a.tiempoVida || 
        (a.tiempoVida == b.tiempoVida && b.id < a.id);
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    int B;
    cin >> B;
    if (!std::cin)  // fin de la entrada
        return false;

    priority_queue<Baterias> baterias;
    queue<Baterias> repuestos;

    for (int i = 1; i <= B; ++i) {
        int t;
        cin >> t;
        baterias.push(Baterias(i, t));
    }

    int R;
    cin >> R;

    for (int i = B + 1; i <= B + R; ++i) {
        int t;
        cin >> t;
        repuestos.push(Baterias(i, t));
    }

    int Z, T, tiempo = 0;
    cin >> Z >> T;

    if (!baterias.empty()) {
        tiempo = baterias.top().tiempoVida;
        while (tiempo <= T && !baterias.empty()) {
            if (baterias.top().carga - Z <= 0) {
                baterias.pop();
                if (!repuestos.empty()) {
                    baterias.push(Baterias(repuestos.front().id,
                        repuestos.front().carga,
                        repuestos.front().tiempoVida + tiempo));
                    repuestos.pop();
                }
            }
            else {
                Baterias nueva = baterias.top();
                baterias.pop();
                baterias.push(Baterias(nueva.id, nueva.carga - Z, nueva.carga - Z + tiempo));
            }
            if (!baterias.empty()) tiempo = baterias.top().tiempoVida;
        }
    }

    if (baterias.empty()) {
        cout << "ABANDONEN INMEDIATAMENTE LA BASE\n";
    }
    else {
        if (baterias.size() == B)
            cout << "CORRECTO\n";
        else
            cout << "FALLO EN EL SISTEMA\n";

        while (!baterias.empty()) {
            cout << baterias.top().id << " " << baterias.top().tiempoVida << "\n";
            baterias.pop();
        }
    }
    cout << "---\n";
    return true;
}

int main() {
    while (resuelveCaso());

    return 0;
}