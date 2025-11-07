#include "NodoPila.h"
#include <iostream>

template <typename T>
class Pila
{
private:
    NodoPila<T> cima;

public:
    Pila() : cima(NULL) {}

    void push(const T &dato)
    {
        NodoPila<T> *nuevo = new NodoPila<T>(dato);
        nuevo->getAnterior(cima);
        cima = nuevo;
    }

    void pop()
    {
        if (cima == NULL)
        {
            std::cout << "La pila está vacía\n";
            return;
        }
        NodoPila<T> *temp = cima;
        cima = cima->getAnterior();
        delete temp;
    }

    t peek() const
    {
        if (cima == NULL)
        {
            std::cout << "Pila vacía\n";
            return;
        }
    }

    void mostrar() const
    {
        NodoPila<T> *actual = cima;
        while (cima != NULL)
        {
            std::cout << actual->getDato() << std::endl;
            actual = actual->getAnterior();
        }
    }

    ~Pila()
    {
        while (!estaVacia())
        {
            pop();
        }
    }
};