#include <iostream>
#include <fstream>
#include "DigrafoValorado.h"
#include "IndexPQ.h"
using namespace std;

class Reparto {
public:
    Reparto(DigrafoValorado<int> const& g, int origen) : origen_(origen),
        dist(g.V(), INF), numCaminos(g.V(), 0), ulti(g.V()), pq(g.V()) {
        dist[origen_] = 0;
        numCaminos[origen_] = 1;
        pq.push(origen_, 0);

        while (!pq.empty()) {
            int v = pq.top().elem;
            pq.pop();

            for (auto a : g.ady(v)) {
                relajar(a);
            }
        }
    }

    bool hayCamino(int destino) {
        if (dist[destino] == INF) return false;
        else return true;
    }

    int costeHacia(int destino) {   //Esfuerzo de ir desde el origen al destino
        return dist[destino];
    }

    //int costeVuelta(DigrafoValorado<int> const& g, int casa) {     //Casa representa el punto de partida para volver a la oficina
    //    vector<int> distVuelta(g.V(), INF);
    //}

private:
    const int INF = 2147483647;
    int origen_;
    vector<int> dist;
    vector<int> numCaminos;
    vector<AristaDirigida<int>> ulti;
    IndexPQ<int> pq;

    void relajar(AristaDirigida<int> a) {
        int v = a.desde();
        int w = a.hasta();

        if (dist[w] > dist[v] + a.valor()) {    //Tenemos un nuevo camino minimo
            dist[w] = dist[v] + a.valor();
            numCaminos[w] = numCaminos[v];
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

    bool posible = true;
    int O, P;
    cin >> O >> P;
    O--;
    Reparto repartoIda(comarca, O);
    int esfuerzoMinimo = 0;
    int j = 0;
    while (posible && j < P) {
        int destinatario;
        cin >> destinatario;
        destinatario--;

        if (!repartoIda.hayCamino(destinatario))
            posible = false;
        else {
            esfuerzoMinimo += repartoIda.costeHacia(destinatario);  //Esfuerzo para ir
            
            Reparto repartoVuelta(comarca, destinatario);
            if (!repartoVuelta.hayCamino(O))
                posible = false;
            else {
                esfuerzoMinimo += repartoVuelta.costeHacia(O);      //Esfuerzo para volver
            }
        }
        ++j;
    }

    if (posible) cout << esfuerzoMinimo << "\n";
    else cout << "Imposible\n";

    return true;
}

int main() {
    while (resuelveCaso());

    return 0;
}
