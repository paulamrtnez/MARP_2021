#include <iostream>
#include <fstream>
#include <queue>
using namespace std;

struct datos {
    int id;
    int periodo;
    int prioridad;
    datos(int id_, int periodo_, int prioridad_) {
        id = id_;
        periodo = periodo_;
        prioridad = prioridad_;
    }
};

class CompareSecond
{
public:
    bool operator()(datos n1, datos n2) {
        if (n1.prioridad == n2.prioridad)
            return n1.id > n2.id;
        else
            return n1.prioridad > n2.prioridad;
    }
};

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    int N;
    cin >> N;
    if (N == 0)
        return false;

    priority_queue<datos, vector<datos>, CompareSecond> pq;
    for (int i = 0; i < N; ++i) {
        int id, periodo;
        cin >> id >> periodo;
        pq.push(datos(id, periodo, periodo));
    }

    int K;
    cin >> K;

    //Salida
    if (!pq.empty()) {
        for (int i = 0; i < K; ++i) {
            auto usuario = pq.top();
            pq.pop();
            cout << usuario.id << "\n";
            pq.push(datos(usuario.id, usuario.periodo, usuario.prioridad + usuario.periodo));
        }
    }
    cout << "---\n";

    return true;
}

int main() {
    while (resuelveCaso());
    return 0;
}