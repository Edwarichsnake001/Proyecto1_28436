#pragma once
#include "NodoLista.h"

using namespace std;

template <typename T>
class Lista
{
private:
    NodoLista<T> *cabeza;

public:
    Lista() : cabeza(NULL) {}

    void insertar(const T &dato)
    {
        NodoLista<T> *nuevo = new NodoLista<T>(dato);
        nuevo->setSiguiente(cabeza);
        cabeza = nuevo;
    }

    void mostrar() const
    {
        NodoLista<T> *actual = cabeza;
        while (actual != NULL)
        {
            cout << actual->getDato() << endl;
            actual = actual->getSiguiente();
        }
    }
};