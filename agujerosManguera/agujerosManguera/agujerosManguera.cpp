#include <iostream>
#include <fstream>
using namespace std;

//Usar el algoritmo voraz es optimo, al darse las posiciones de los agujeros en orden creciente siempre se colocaran
//los parches con el extremo en el primer agujero sin tapar y de ahi hasta su alcance maximo. Es optimo porque es necesario
//tapar todos los agujeros, por tanto, si entre cualquier grupo de agujeros la distancia entre los mas lejanos es K, el numero
//maximo de parches minimos será M siendo M >= K / L, que se daría si todas las posiciones entre los dos agujeros mas distantes
//estuviesen agujereados

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    int N;
    cin >> N;
    if (!std::cin)  // fin de la entrada
        return false;
    int L;
    cin >> L;

    int numParches = 1;
    int agujero;
    cin >> agujero;

    //Como los agujeros estan en orden creciente siempre el origen
    //mas optimo del primer parche es el primer agujero que nos dan
    int origenParche = agujero;

    for (int i = 0; i < N - 1; ++i) {
        cin >> agujero;

        if (agujero - origenParche > L) { //No nos sirve el mismo parche -> usamos uno nuevo
            numParches++;
            origenParche = agujero;
        }
        //else : nos sirve el mismo parche -> no se hace nada
    }
    
    cout << numParches << "\n";

    return true;
}

int main() {
    while (resuelveCaso());

    return 0;
}