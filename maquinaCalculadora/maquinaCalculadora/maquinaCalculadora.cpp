#include <iostream>
#include <queue>
using namespace std;

int MAX = 10000;

int maquinaCalculadora(int origen, int solucion) {
    if (origen == solucion) return 0;
    vector<int> distancia(MAX, -1);
    queue<int> cola;
    distancia[origen] = 0;
    cola.push(origen);
    
    while (!cola.empty()) {
        int v;
        int w = cola.front();
        cola.pop();
        for (int i = 0; i < 3; ++i) {
            if (i == 0) v = (w + 1) % MAX;
            else if (i == 1) v = (w * 2) % MAX;
            else v = w / 3;

            if (distancia[v] == -1) {
                distancia[v] = distancia[w] + 1;
                if (solucion == v) return distancia[v];
                cola.push(v);
            }
        }
    }
}

bool resuelveCaso() {
    int origen, solucion;
    cin >> origen; cin >> solucion;

    if (!cin) return false;

    cout << maquinaCalculadora(origen, solucion) << "\n";
    return true;
}

int main()
{
    bool casos = true;
    while (casos) {
        casos = resuelveCaso();
    }
    return 0;
}