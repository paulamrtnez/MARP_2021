#include <iostream>
#include <queue>
using namespace std;

//Metodo recursivo para calcular el coste de las operaciones
long long int Calculin(priority_queue<long long int, vector<long long int>, greater<long long int>>& calculin, long long int coste) {
    if (calculin.size() == 1) return coste;
    else {
        long long int a, b;
        a = calculin.top();
        calculin.pop();
        b = calculin.top();
        calculin.pop();
        calculin.push(a + b);

        return Calculin(calculin, coste + a + b);
    }
}

long long int Resuelve(int N) {
    long long int coste = 0, elem;
    priority_queue<long long int, vector<long long int>, greater<long long int>> calculin;
    cin >> elem;
    if (N > 1) {
        calculin.push(elem);
        for (int i = 1; i < N; ++i) {
            cin >> elem;
            calculin.push(elem);
        }
        coste = Calculin(calculin, coste);
    }
    return coste;
}

int main()
{
    int N;
    cin >> N;
    while (N > 0) {
        cout << Resuelve(N) << endl;
        cin >> N;
    }
    return 0;
}