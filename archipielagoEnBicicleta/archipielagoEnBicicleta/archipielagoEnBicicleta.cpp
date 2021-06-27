#include <iostream>
#include <fstream>
#include <queue>
#include "GrafoValorado.h"
#include "ConjuntosDisjuntos.h"
using namespace std;

template <typename Valor>
class ARM_Kruskal {
public:
	ARM_Kruskal(GrafoValorado<Valor> const& g, priority_queue<Arista<int>, vector<Arista<int>>, greater<Arista<int>>>& pq) : coste(0) {
		ConjuntosDisjuntos cjtos(g.V());
		while (!pq.empty()) {
			auto a = pq.top(); pq.pop();
			int v = a.uno(), w = a.otro(v);
			if (!cjtos.unidos(v, w)) {
				cjtos.unir(v, w);
				_ARM.push_back(a);
				coste += a.valor();
				if (_ARM.size() == g.V() - 1) break;
			}
		}
		numCjtos = cjtos.num_cjtos();
	}

	int conjuntos() const { return numCjtos; }
	Valor costeARM() const { return coste; }
	vector<Arista<Valor>> const& ARM() const { return _ARM; }

private:
	vector<Arista<Valor>> _ARM;
	Valor coste;
	int numCjtos;
};

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
	int I;
	cin >> I;
    if (!std::cin)  // fin de la entrada
        return false;
	int P;
	cin >> P;

	//IndexPQ<Arista<int>> pq(P);
	priority_queue<Arista<int>, vector<Arista<int>>, greater<Arista<int>>> pq;
	GrafoValorado<int> milislotes(I);
	for (int i = 0; i < P; ++i) {
		int x, y, coste;
		cin >> x >> y >> coste;
		x--; y--;

		pq.push(Arista<int>(x, y, coste));
		milislotes.ponArista(Arista<int>(x, y, coste));
	}

	ARM_Kruskal<int> kruskal(milislotes, pq);
	
	if (kruskal.conjuntos() > 1) cout << "No hay puentes suficientes\n";
	else cout << kruskal.costeARM() << "\n";

    return true;
}

int main() {
    while (resuelveCaso());
    return 0;
}