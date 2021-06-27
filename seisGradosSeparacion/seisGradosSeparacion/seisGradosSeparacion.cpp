#include <iostream>
#include <fstream>
#include <unordered_map>
#include "EnterosInf.h"
#include "Matriz.h"
using namespace std;

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    int P;
    cin >> P;
    if (!std::cin)  // fin de la entrada
        return false;

    Matriz<EntInf> G(P, P, Infinito);
    unordered_map<string, int> personas;
    int R, numPers = 0;
    cin >> R;
    for (int i = 0; i < R; ++i) {
        string nombre1, nombre2;
        cin >> nombre1 >> nombre2;

        if (!personas.count(nombre1)) {
            personas.insert({ nombre1, numPers });
            numPers++;
        }
        if (!personas.count(nombre2)) {
            personas.insert({ nombre2, numPers });
            numPers++;
        }

        G[personas[nombre1]][personas[nombre2]] = 1;
        G[personas[nombre2]][personas[nombre1]] = 1;
    }
    for (int i = 0; i < P; ++i)
        G[i][i] = 0;

    for (int k = 0; k < P; ++k) {
        for (int i = 0; i < P; ++i) {
            for (int j = 0; j < P; ++j) {
                auto temp = G[i][k] + G[k][j];
                if (temp < G[i][j]) {
                    G[i][j] = temp;
                }
            }
        }
    }

    EntInf gradoMax = -1;
    bool desconectada = false;
    for (int i = 0; i < P && !desconectada; ++i) {
        for (int j = 0; j < P && !desconectada; ++j) {
            if (G[i][j] == Infinito)
                desconectada = true;
            if (gradoMax < G[i][j])
                gradoMax = G[i][j];
        }
    }
    
    if (desconectada)
        cout << "DESCONECTADA\n";
    else
        cout << gradoMax << "\n";
    return true;
}

int main() {
    while (resuelveCaso());

    return 0;
}