#include <iostream>
#include <fstream>
#include <queue>
using namespace std;

struct Pelicula {
    int inicio;
    int fin;
    Pelicula(int i, int f) : inicio(i), fin(f) {}
};

bool operator<(Pelicula const& a, Pelicula const& b) {
    return b.fin < a.fin;
}

// función que resuelve el problema
// comentario sobre el coste, O(f(N)), donde N es ...
int resolver(priority_queue<Pelicula>& cartelera) {
    int sol = 0;
    if (!cartelera.empty()) {
        Pelicula primera = cartelera.top();
        cartelera.pop();
        sol++;
        while (!cartelera.empty()) {
            Pelicula sig = cartelera.top();
            cartelera.pop();

            if (sig.inicio >= primera.fin + 10) {
                sol++;
                primera = sig;
            }
        }
    }

    return sol;
}

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    int N;
    cin >> N;
    if (N == 0)
        return false;

    priority_queue<Pelicula> cartelera;
    for (int i = 0; i < N; ++i) {
        int H, M, inicio, duracion;
        cin >> H;
        cin.get();
        cin >> M >> duracion;
        inicio = H * 60 + M;

        cartelera.push(Pelicula(inicio, inicio + duracion));
    }

    int sol = resolver(cartelera);

    cout << sol << "\n";

    return true;
}

int main() {
    while (resuelveCaso());

    return 0;
}