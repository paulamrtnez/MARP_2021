#include <iostream>
#include <fstream>
#include <deque>
#include <algorithm>
using namespace std;

void resuelveCaso() {
    int N, V;
    cin >> N >> V;
    
    deque<int> pilas;
    for (int i = 0; i < N; ++i) {
        int voltaje;
        cin >> voltaje;
        pilas.push_back(voltaje);
    }
    sort(pilas.begin(), pilas.end());   //Ordenamos la lista de pilas de menor a mayor

    int coches = 0;
    if (N % 2 != 0) pilas.pop_front();

    while (!pilas.empty()) {
        if (pilas.front() + pilas.back() >= V) {    //Las dos pilas sirven para un coche
            coches++;
            pilas.pop_back();
        }
        else {
            pilas.pop_front();
        }
        pilas.pop_front();
    }

    cout << coches << "\n";
}

int main() {
    int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();

    return 0;
}