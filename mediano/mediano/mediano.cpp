#include <iostream>
#include <queue>
using namespace std;

class ColaMedianas {
private:
    priority_queue<int> colaMenores;
    priority_queue<int, vector<int>, greater<int>> colaMayores;

public:
    void insertar(int x) {
        if (colaMenores.size() == colaMayores.size()) {
            if (colaMenores.empty() || x < colaMenores.top())
                colaMenores.push(x);
            else {
                colaMayores.push(x);
                colaMenores.push(colaMayores.top());
                colaMayores.pop();
            }
        }
        else {  //Siempre colaMenores será mayor que colaMayores
            if (x < colaMenores.top()) {
                colaMenores.push(x);
                colaMayores.push(colaMenores.top());
                colaMenores.pop();
            }
            else colaMayores.push(x);
        }
    };

    bool vacia() const {
        return colaMenores.empty();
    };

    int mediana() const {
        //La mediana siempre estará en la raíz de colaMenores
        if (colaMenores.empty())
            throw domain_error("No se puede acceder a la mediana si la cola es vacía");
        else return colaMenores.top();
    };

    void quitarMediana() {
        if (colaMenores.empty())
            throw domain_error("No se puede quitar la mediana si la cola es vacía");
        else {
            colaMenores.pop();
            //Si colaMayores queda mayor que colaMenores la nueva
            //mediana será el top de colasMayores
            if (colaMenores.size() < colaMayores.size()) {
                colaMenores.push(colaMayores.top());
                colaMayores.pop();
            }
        }
    };
};

bool resuelveCaso() {
    ColaMedianas cola;
    int N, elem;
    cin >> N;
    if (!cin) return false; //Fin de la entrada

    for (int i = 0; i < N; ++i) {
        cin >> elem;
        if (elem == 0) {    //El carnicero llama al siguiente cliente
            if (cola.vacia()) cout << "ECSA ";
            else {
                cout << cola.mediana() << " ";
                cola.quitarMediana();
            }
        }
        else {
            cola.insertar(elem);
        }
    }
    cout << "\n";

    return true;
}

int main()
{
    bool casos = true;
    while (casos) casos = resuelveCaso();
    return 0;
}