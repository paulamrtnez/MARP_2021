#include <queue>

template <typename Valor>
class ARM_Kruskal {
public:
	ARM_Kruskal(GrafoValorado<Valor> const& g, priority_queue<Arista<int>>& pq) : coste(0) {
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
	}

	Valor costeARM() const { return coste; }
	std::vector<Arista<Valor>> const& ARM() const { return _ARM; }

private:
	std::vector<Arista<Valor>> _ARM;
	Valor coste;
};