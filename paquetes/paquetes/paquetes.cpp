#include <iostream>
#include <fstream>
#include "DigrafoValorado.h"
#include "IndexPQ.h"
using namespace std;

class Paquetes {
public:
    //Realizamos Dijsktra al grafo de la comarca para encontrar el esfuerzo minimo desde un punto a todos los demas
    Paquetes(DigrafoValorado<int> const& g, int origen) : origen_(origen),
        dist(g.V(), INF), ulti(g.V()), pq(g.V()) {
        dist[origen_] = 0;
        pq.push(origen_, 0);

        while (!pq.empty()) {
            int v = pq.top().elem;
            pq.pop();

            for (auto a : g.ady(v)) {
                relajar(a);
            }
        }
    }

    //Devuelve si es posible alcanzar el destino desde el origen
    bool hayCamino(int destino) {
        if (dist[destino] == INF) return false;
        else return true;
    }

    //Devuelve el esfuerzo de alcanzar el destino desde el origen
    int esfuerzoCamino(int destino) {
        return dist[destino];
    }

private:
    const int INF = 2147483647;
    int origen_;
    vector<int> dist;
    vector<AristaDirigida<int>> ulti;   //Solo guarda un camino minimo
    IndexPQ<int> pq;

    void relajar(AristaDirigida<int> a) {
        int v = a.desde();
        int w = a.hasta();

        if (dist[w] > dist[v] + a.valor()) {    //Tenemos un nuevo camino minimo
            dist[w] = dist[v] + a.valor();
            ulti[w] = a;
            pq.update(w, dist[w]);
        }
    }
};

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    int N;
    cin >> N;
    if (!std::cin)  // fin de la entrada
        return false;

    //Descripcion de la comarca
    DigrafoValorado<int> comarca(N);
    int C;
    cin >> C;
    for (int i = 0; i < C; ++i) {
        int origen, destino, esfuerzo;
        cin >> origen >> destino >> esfuerzo;
        origen--;
        destino--;
        comarca.ponArista(AristaDirigida<int>(origen, destino, esfuerzo));
    }
    
    DigrafoValorado<int> comarcaInv(N);
    comarcaInv = comarca.inverso();
    int O, P;
    cin >> O >> P;
    O--;
    Paquetes rutaIda(comarca, O);
    Paquetes rutaVuelta(comarcaInv, O);

    bool posible = true;
    int esfuerzoMinTotal = 0;
    int j = 0;
    while (j < P) {
        int destinatario;
        cin >> destinatario;
        destinatario--;

        if (!rutaIda.hayCamino(destinatario))  //Comprobamos si hay camino desde O hasta el destino
            posible = false;
        else {
            esfuerzoMinTotal += rutaIda.esfuerzoCamino(destinatario);

            if (!rutaVuelta.hayCamino(destinatario))   //Comprobamos si hay camino desde el destino hasta O
                posible = false;
            else esfuerzoMinTotal += rutaVuelta.esfuerzoCamino(destinatario);
        }

        ++j;
    }

    //Procesamos la salida
    if (!posible) cout << "Imposible\n";
    else cout << esfuerzoMinTotal << "\n";

    return true;
}

int main() {
    while (resuelveCaso());

    return 0;
}
