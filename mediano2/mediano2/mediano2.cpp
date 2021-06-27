#include <iostream>
#include <fstream>
#include <queue>
using namespace std;

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    int N;
    cin >> N;
    if (!std::cin)  // fin de la entrada
        return false;

    priority_queue<int> peque;
    priority_queue<int, vector<int>, greater<int>> grande;
    int numClientes = 0;

    for (int i = 0; i < N; ++i) {
        int evento;
        cin >> evento;

        if (evento == 0) {  //El carnicero llama al siguiente cliente
            if (peque.size() == 0) cout << "ECSA";
            else { //Si se atiende a un cliente
                numClientes--;
                cout << peque.top();
                peque.pop();

                if (numClientes % 2 == 1) { //numClientes es impar
                    peque.push(grande.top());
                    grande.pop();
                }   //Si numClientes es par no se hace nada
            }
            cout << " ";
        }
        else {  //Entra un nuevo cliente
            numClientes++;
            if (numClientes % 2 == 0) { //numClientes es par
                if (evento > peque.top()) grande.push(evento);
                else {
                    grande.push(peque.top());
                    peque.pop();
                    peque.push(evento);
                }
            }
            else {  //numClientes es impar
                if (numClientes == 1 || evento < grande.top()) peque.push(evento);
                else {
                    peque.push(grande.top());
                    grande.pop();
                    grande.push(evento);
                }
            }
        }
    }
    cout << "\n";
    return true;
}

int main() {
    while (resuelveCaso());

    return 0;
}