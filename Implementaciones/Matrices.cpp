#include <iostream>
#include <vector>
#include <algorithm>
#include "Matriz.h"


using namespace std;

struct tCofre{
	int profundidad, oro;
	bool cogido;
};

bool resuelveCaso() {
	int T;
	cin >> T;
		if (!std::cin) // fin de la entrada
			return false;
	int n;
	cin >> n;
	int p, o;
	vector <tCofre> cofres;
	for (int i = 0; i < n; ++i) {
		cin >> p >> o;
		cofres.push_back({ p,o, false });
	}
	Matriz<int> M(n+1, T+1);
	for (int i = 0; i < n+1; ++i) M[i][0] = 0;
	for (int j = 1; j < T+1; ++j) M[0][j] = 0;

	for (int i = 1; i < n+1; ++i) {
		for (int j = 1; j < T+1; ++j) {
			if (3 * cofres[i - 1].profundidad > j) M[i][j] = M[i - 1][j];
			else M[i][j] = max( M[i - 1][j],  M[i - 1][j - 3 * cofres[i - 1].profundidad] + cofres[i - 1].oro );
		}
	}
	int j = T;
	int cont = 0;
	for (int i = n; i > 0; --i) {
		if (M[i][j] != M[i - 1][j]) {
			cofres[i-1].cogido = true;
			j -= 3 * cofres[i - 1].profundidad;
			cont++;
		}
	}
	cout << M[n][T] << '\n';
	cout << cont << '\n';
	for (int i = 0; i < n; ++i)
		if (cofres[i].cogido) cout << cofres[i].profundidad << " " << cofres[i].oro << '\n';
	cout << "----"<< '\n';
		return true;
}
int main() {
	while (resuelveCaso());
	return 0;
}



#include <iostream>
#include <vector>
#include <algorithm>
#include "Matriz.h"
using namespace std;

bool resuelveCaso() {
	int N;
	cin >> N;
	if (!std::cin) // fin de la entrada
		return false;
	Matriz<int> M(N+1, N+1);

	//Inicializo la matriz
	for (int j = 0; j < N + 1; ++j)
		M[0][j] = 0;
	for (int i = 1; i < N + 1; ++i)
		M[i][0] = 0;

	for (int i = 1; i < N+1; ++i)
		for (int j = 1; j < N+1; ++j) {
			cin >> M[i][j];
		}
	int mejor;
	vector <int> mejorSol = M[1];
	int anterior;
	for (int i = 2; i < N + 1; ++i) {
		anterior = 0;
		for (int j = 1; j < N + 1; ++j) {
			if (j < N) mejor = max(anterior, max(mejorSol[j], mejorSol[j + 1]));
			else mejor = max(anterior, mejorSol[j]);
			anterior = mejorSol[j];
			mejorSol[j] = mejor + M[i][j];
		}
	}

	int maximo = mejorSol[1];
	int posMaximo = 1;
	for (int j = 2; j < N + 1; ++j) {
		if (mejorSol[j] > maximo) {
			maximo = mejorSol[j];
			posMaximo = j;
		}
	}
	cout << mejorSol[posMaximo] << " " << posMaximo << '\n';
	return true;
}
int main() {
	while (resuelveCaso());
	return 0;
}



#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool resuelveCaso() {
	int n;
	cin >> n;
	if (n == 0)
		return false;
	vector <int> rivales, locales;
	int valor;
	for (int i = 0; i < n; ++i) {
		cin >> valor;
		rivales.push_back(valor);
	}
	for (int i = 0; i < n; ++i) {
		cin >> valor;
		locales.push_back(valor);
	}
	sort(rivales.begin(), rivales.end());
	sort(locales.begin(), locales.end(), greater<int>());
	int suma = 0;
	bool mayor = true;
	int i = 0;
	while (i < n && mayor) {
		if (locales[i] > rivales[i]) suma += locales[i] - rivales[i];
		else mayor = false;
		++i;
	}
	cout << suma << '\n';
	return true;
}
int main() {
	while (resuelveCaso());
	return 0;
}