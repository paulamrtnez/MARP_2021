#include <iostream>
#include <fstream>
using namespace std;

//
//  TreeSet_AVL.h
//
//  ImplementaciÃ³n de conjuntos mediante Ã¡rboles de bÃºsqueda AVL
//
//  Facultad de InformÃ¡tica
//  Universidad Complutense de Madrid
//
//  Copyright (c) 2020 Alberto Verdejo
//

#ifndef TREESET_AVL_H_
#define TREESET_AVL_H_

#include <algorithm>
#include <functional>
#include <stack>
#include <stdexcept>
#include <utility>

template <class T, class Comparator = std::less<T>>
class Set {
protected:

    /*
     Nodo que almacena internamente el elemento (de tipo T),
     punteros al hijo izquierdo y derecho, que pueden ser
     nullptr si el hijo es vacÃ­o, y la altura.
     */
    struct TreeNode;
    using Link = TreeNode*;
    struct TreeNode {
        T elem;
        Link iz, dr;
        int altura;
        int tam_i;
        TreeNode(T const& e, Link i = nullptr, Link d = nullptr,
            int alt = 1, int tam = 1) : elem(e), iz(i), dr(d), altura(alt), tam_i(tam) {}
    };

    // puntero a la raÃ­z de la estructura jerÃ¡rquica de nodos
    Link raiz;

    // nÃºmero de elementos (cardinal del conjunto)
    int nelems;

    // objeto funciÃ³n que compara elementos (orden total estricto)
    Comparator menor;

public:

    // constructor (conjunto vacÃ­o)
    Set(Comparator c = Comparator()) : raiz(nullptr), nelems(0), menor(c) {}

    // constructor por copia
    Set(Set const& other) {
        copia(other);
    }

    // operador de asignaciÃ³n
    Set& operator=(Set const& that) {
        if (this != &that) {
            libera(raiz);
            copia(that);
        }
        return *this;
    }

    ~Set() {
        libera(raiz);
    };

    bool insert(T const& e) {
        return inserta(e, raiz);
    }

    bool empty() const {
        return raiz == nullptr;
    }

    int size() const {
        return nelems;
    }

    bool contains(T const& e) const {
        return pertenece(e, raiz);
    }

    bool erase(T const& e) {
        return borra(e, raiz);
    }

    T const& kesimo(int k) const {
        if (k < 1 || k > nelems) throw std::domain_error("No existe el elemento k-esimo");
        return kesimo_rec(k, raiz);
    }

protected:

    void copia(Set const& other) {
        raiz = copia(other.raiz);
        nelems = other.nelems;
        menor = other.menor;
    }

    static Link copia(Link a) {
        if (a == nullptr) return nullptr;
        else return new TreeNode(a->elem, copia(a->iz), copia(a->dr), a->altura);
    }

    static void libera(Link a) {
        if (a != nullptr) {
            libera(a->iz);
            libera(a->dr);
            delete a;
        }
    }

    bool pertenece(T const& e, Link a) const {
        if (a == nullptr) {
            return false;
        }
        else if (menor(e, a->elem)) {
            return pertenece(e, a->iz);
        }
        else if (menor(a->elem, e)) {
            return pertenece(e, a->dr);
        }
        else { // e == a->elem
            return true;
        }
    }

    bool inserta(T const& e, Link& a) {
        bool crece;
        if (a == nullptr) { // se inserta el nuevo elemento e
            a = new TreeNode(e);
            ++nelems;
            crece = true;
        }
        else if (menor(e, a->elem)) {
            crece = inserta(e, a->iz);
            if (crece) {
                a->tam_i++;
                reequilibraDer(a);
            }
        }
        else if (menor(a->elem, e)) {
            crece = inserta(e, a->dr);
            if (crece) reequilibraIzq(a);
        }
        else // el elemento e ya estÃ¡ en el Ã¡rbol
            crece = false;
        return crece;
    }

    int altura(Link a) {
        if (a == nullptr) return 0;
        else return a->altura;
    }

    void rotaDer(Link& r2) {
        Link r1 = r2->iz;
        r2->iz = r1->dr;
        r1->dr = r2;
        r2->altura = std::max(altura(r2->iz), altura(r2->dr)) + 1;
        r1->altura = std::max(altura(r1->iz), altura(r1->dr)) + 1;
        r2->tam_i = r2->tam_i - r1->tam_i;
        r2 = r1;
    }

    void rotaIzq(Link& r1) {
        Link r2 = r1->dr;
        r1->dr = r2->iz;
        r2->iz = r1;
        r1->altura = std::max(altura(r1->iz), altura(r1->dr)) + 1;
        r2->altura = std::max(altura(r2->iz), altura(r2->dr)) + 1;
        r2->tam_i = r2->tam_i + r1->tam_i;
        r1 = r2;
    }

    void rotaIzqDer(Link& r3) {
        rotaIzq(r3->iz);
        rotaDer(r3);
    }

    void rotaDerIzq(Link& r1) {
        rotaDer(r1->dr);
        rotaIzq(r1);
    }

    void reequilibraIzq(Link& a) {
        if (altura(a->dr) - altura(a->iz) > 1) {
            if (altura(a->dr->iz) > altura(a->dr->dr))
                rotaDerIzq(a);
            else rotaIzq(a);
        }
        else a->altura = std::max(altura(a->iz), altura(a->dr)) + 1;
    }

    void reequilibraDer(Link& a) {
        if (altura(a->iz) - altura(a->dr) > 1) {
            if (altura(a->iz->dr) > altura(a->iz->iz))
                rotaIzqDer(a);
            else rotaDer(a);
        }
        else {
            a->altura = std::max(altura(a->iz), altura(a->dr)) + 1;
        }
    }

    // devuelve y borra el mÃ­nimo del Ã¡rbol con raÃ­z en a
    T borraMin(Link& a) {
        if (a->iz == nullptr) {
            T min = a->elem;
            a = a->dr;
            --nelems;
            return min;
        }
        else {
            T min = borraMin(a->iz);
            reequilibraIzq(a);
            return min;
        }
    }

    bool borra(T const& e, Link& a) {
        bool decrece = false;
        if (a != nullptr) {
            if (menor(e, a->elem)) {
                decrece = borra(e, a->iz);
                if (decrece) reequilibraIzq(a);
            }
            else if (menor(a->elem, e)) {
                decrece = borra(e, a->dr);
                if (decrece) reequilibraDer(a);
            }
            else { // e == a->elem
                if (a->iz == nullptr || a->dr == nullptr) {
                    Link aux = a;
                    a = (a->iz == nullptr) ? a->dr : a->iz;
                    --nelems;
                    delete aux;
                }
                else { // tiene dos hijos
                    T min = borraMin(a->dr);
                    a->elem = min;
                    reequilibraDer(a);
                }
                decrece = true;
            }
        }
        return decrece;
    }

    T const& kesimo_rec(int k, Link raiz) const {
        if (k == raiz->tam_i) return raiz->elem;
        else if (k < raiz->tam_i)  return kesimo_rec(k, raiz->iz);
        else return kesimo_rec(k - raiz->tam_i, raiz->dr);
    }

public:
    // iteradores que recorren los elementos del conjunto de menor a mayor
    class const_iterator {
    public:
        T const& operator*() const {
            if (act == nullptr)
                throw std::out_of_range("No hay elemento a consultar");
            return act->elem;
        }

        T const* operator->() const {
            return &operator*();
        }

        const_iterator& operator++() {  // ++ prefijo
            next();
            return *this;
        }

        bool operator==(const_iterator const& that) const {
            return act == that.act;
        }

        bool operator!=(const_iterator const& that) const {
            return !(this->operator==(that));
        }

    protected:
        friend class Set;
        Link act;
        std::stack<Link> ancestros;  // antecesores no visitados

        // construye el iterador al primero
        const_iterator(Link raiz) { act = first(raiz); }

        // construye el iterador al Ãºltimo
        const_iterator() : act(nullptr) {}

        Link first(Link ptr) {
            if (ptr == nullptr) {
                return nullptr;
            }
            else { // buscamos el nodo mÃ¡s a la izquierda
                while (ptr->iz != nullptr) {
                    ancestros.push(ptr);
                    ptr = ptr->iz;
                }
                return ptr;
            }
        }

        void next() {
            if (act == nullptr) {
                throw std::out_of_range("El iterador no puede avanzar");
            }
            else if (act->dr != nullptr) { // primero del hijo derecho
                act = first(act->dr);
            }
            else if (ancestros.empty()) { // hemos llegado al final
                act = nullptr;
            }
            else { // podemos retroceder
                act = ancestros.top();
                ancestros.pop();
            }
        }
    };

    const_iterator begin() const {
        return const_iterator(raiz);
    }

    const_iterator end() const {
        return const_iterator();
    }
};
#endif

// resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    int N;
    cin >> N;
    if (N == 0)
        return false;

    int elem;
    Set<int> arbol;
    for (int i = 0; i < N; ++i) {
        cin >> elem;
        arbol.insert(elem);
    }

    int M;
    cin >> M;
    int i;
    for (int j = 0; j < M; ++j) {
        cin >> i;

        if (i < 1 || i > arbol.size()) cout << "??\n";
        else cout << arbol.kesimo(i) << "\n";
    }
    cout << "---\n";

    return true;
}

int main() {
    while (resuelveCaso());

    return 0;
}