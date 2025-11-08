#include "Libros.h"
#include "Lista.h"

using namespace std;

void mostrarLibros(const Lista<Libros> &lista){
    NodoLista<Libros> *actual = lista.getCabeza();
    while (actual)
    {
        if(!actual->getDato().disponibilidad()){
            cout << actual -> getDato() << endl;
        }
        actual = actual ->getSiguiente();
    }   
}

bool buscarPorTituloRecursivo(NodoLista<Libros>* nodo, const std::string& titulo) {
    if (!nodo) return false;
    if (nodo->getDato().coincideTitulo(titulo)) return true;
    return buscarPorTituloRecursivo(nodo->getSiguiente(), titulo);
}

bool buscarPorTitulo(const Lista<Libros>& lista, const std::string& titulo) {
    return buscarPorTituloRecursivo(lista.getCabeza(), titulo);
}

int contarPrestadosRec(NodoLista<Libros>* nodo) {
    if (!nodo) return 0;
    int suma = nodo->getDato().disponibilidad() ? 0 : 1;
    return suma + contarPrestadosRec(nodo->getSiguiente());
}

int contarPrestados(const Lista<Libros>& lista) {
    return contarPrestadosRec(lista.getCabeza());
}

void mostrarLibrosDisponibles(const Lista<Libros>& lista) {
    NodoLista<Libros>* actual = lista.getCabeza();
    while (actual) {
        if (actual->getDato().disponibilidad()) {
            std::cout << actual->getDato() << std::endl;
        }
        actual = actual->getSiguiente();
    }
}


