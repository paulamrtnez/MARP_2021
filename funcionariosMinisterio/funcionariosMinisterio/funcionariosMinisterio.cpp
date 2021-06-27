#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include "Matriz.h"
using namespace std;

struct Nodo {
	vector<int> sol;
	int k;
	int tiempo;
	int tiempoOpt;
	vector <bool> asignados;
};

bool operator < (Nodo const& n1, Nodo const& n2) {
	return n1.tiempoOpt < n2.tiempoOpt;
}

bool resuelveCaso() {
	int n;
	cin >> n;
	if (n == 0)
		return false;

	Matriz <int> M(n + 1, n + 1);
	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			cin >> M[i][j];

	vector<int> lento(n + 1), rapido(n + 1);
	for (int i = 1; i <= n; ++i) {
		lento[i] = M[i][1];
		rapido[i] = M[i][1];
		for (int j = 2; j <= n; ++j) {
			lento[i] = max(lento[i], M[i][j]);
			rapido[i] = min(rapido[i], M[i][j]);
		}
	}
	vector<int> opt(n + 1), pes(n + 1);
	opt[n] = 0;
	pes[n] = 0;
	for (int i = n - 1; i >= 0; --i) {
		opt[i] = opt[i + 1] + rapido[i + 1];
		pes[i] = pes[i + 1] + lento[i + 1];
	}

	Nodo X, Y;
	priority_queue<Nodo> PQ;
	Y = { vector<int>(n + 1), 0, 0, opt[0], vector<bool>(n + 1, false) };
	PQ.push(Y);
	int tiempoMejor = pes[0];
	while (!PQ.empty() && PQ.top().tiempoOpt <= tiempoMejor) {
		Y = PQ.top(); PQ.pop();
		X.k = Y.k + 1; X.sol = Y.sol; X.asignados = Y.asignados;
		for (int i = 1; i <= n; ++i) {
			if (!X.asignados[i]) {
				X.asignados[i] = true;
				X.tiempo = Y.tiempo + M[X.k][i];
				X.tiempoOpt = X.tiempo + opt[X.k];
				if (X.tiempoOpt <= tiempoMejor) {
					if (X.k == n) tiempoMejor = X.tiempo;
					else {
						PQ.push(X);
						tiempoMejor = min(tiempoMejor, X.tiempo + pes[X.k]);
					}
				}
				X.asignados[i] = false;
			}
		}
	}
	cout << tiempoMejor << '\n';

	return true;
}
int main() {
	while (resuelveCaso());
	return 0;
}