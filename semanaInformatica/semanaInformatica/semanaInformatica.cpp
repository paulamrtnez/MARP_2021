#include <iostream>
#include <fstream>
#include <queue>
using namespace std;

bool resuelveCaso() {
    int N;
    cin >> N;
    if (N == 0)
        return false;

    priority_queue<int, vector<int>, greater<int>> comienzos;
    priority_queue<int, vector<int>, greater<int>> finales;

    for (int i = 0; i < N; ++i) {
        int c, f;
        cin >> c >> f;
        comienzos.push(c);
        finales.push(f);
    }

    int gente = -1;      //Cuenta la gente necesaria para las actividades que comienzan antes que el primer final
    int maxGente = -1;   //Numero maximo de gente que ha tenido la variable gente
    //Buscamos todas las entradas que empiecen antes del primer final (ordenados de menor
    //a mayor) que significaran necesitar un amigo
    while (!comienzos.empty()) {
        if (comienzos.top() < finales.top()) {
            gente++;
            //Hemos acabado de procesar el primer comienzo
            comienzos.pop();
        }
        else {
            gente--;
            //Hemos acabado de procesar el primer final
            finales.pop();
        }
        if (gente > maxGente) maxGente = gente;
    }

    cout << maxGente << "\n";
    return true;
}

int main() {
    while (resuelveCaso());

    return 0;
}