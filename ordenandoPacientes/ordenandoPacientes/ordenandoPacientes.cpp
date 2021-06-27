#include <iostream>
#include <fstream>
#include <queue>
using namespace std;

struct paciente {
    string nombre;
    int gravedad;
    int tiempo;
    paciente(string n, int g, int t) : nombre(n), gravedad(g), tiempo(t) {}
};

bool operator<(paciente const& a, paciente const& b) {
    return a.gravedad < b.gravedad || (a.gravedad == b.gravedad && a.tiempo > b.tiempo);
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    int N;
    cin >> N;
    if (N == 0)
        return false;

    priority_queue<paciente> cola;
    for (int i = 0; i < N; ++i) {
        char accion;
        cin >> accion;
        if (accion == 'I') {
            string nom;
            int grav;
            cin >> nom >> grav;
            cola.push(paciente(nom, grav, i));
        }
        else {  //accion == 'A'
            cout << cola.top().nombre << "\n";
            cola.pop();
        }
    }
    cout << "---\n";
    // escribir sol

    return true;
}

int main() {
    while (resuelveCaso());

    return 0;
}