#include "NodoPila.h"
#include <iostream>

template <typename T>
class Pila
{
private:
    NodoPila<T> *cima;

public:
    Pila() : cima(nullptr) {}

    void push(const T &dato)
    {
        NodoPila<T> *nuevo = new NodoPila<T>(dato);
        nuevo->setAnterior(cima);
        cima = nuevo;
    }

    void pop()
    {
        if (cima == nullptr)
        {
            std::cout << "La pila está vacía\n";
            return;
        }
        NodoPila<T> *temp = cima;
        cima = cima->getAnterior();
        delete temp;
    }

    T peek() const
    {
        if (cima == nullptr)
        {
            std::cout << "Pila vacía\n";
            return T();
        }
        return cima->getDato();
    }

    void mostrar() const
    {
        NodoPila<T> *actual = cima;
        while (actual != nullptr)
        {
            std::cout << actual->getDato() << std::endl;
            actual = actual->getAnterior();
        }
    }

    bool estaVacia() const { return cima == nullptr; }

    void apilar(const T &dato) { push(dato); }

    T desapilar()
    {
        if (cima == nullptr)
        {
            std::cout << "La pila está vacía\n";
            return T();
        }
        T valor = cima->getDato();
        pop();
        return valor;
    }

    int tamaño() const
    {
        int contador = 0;
        NodoPila<T>* actual = cima;
        while (actual)
        {
            ++contador;
            actual = actual->getAnterior();
        }
        return contador;
    }

    int tamano() const { return tamaño(); }
    int size() const { return tamaño(); }

    NodoPila<T>* getTope() const { return cima; }

    ~Pila()
    {
        while (!estaVacia())
        {
            pop();
        }
    }
};