#ifndef LIBROS_H
#define LIBROS_H

#include "Lista.h"
#include <iostream>
#include <ostream>
#include <string>

using namespace std;

class Libros
{
private:
    string titulo;
    string autor;
    string codigo;
    bool disponible;
    int cantidad;

public:
    Libros(string tit, string aut, string cod, bool disp, int cant)
        : titulo(tit), autor(aut), codigo(cod), disponible(disp), cantidad(cant) {}

    string getTitulo() const;
    string getAutor() const;
    string getCodigo() const;
    int getCantidad() const;

    void setDisponible(bool estado);
    bool disponibilidad() const;

    bool coincideTitulo(const std::string &t) const;
    bool coincideAutor(const std::string &a) const;

    // Operadores de comparación - Complejidad: O(1)
    bool operator==(const Libros &otro) const;  // Compara por código
    bool operator!=(const Libros &otro) const;  // Compara por código
    bool operator<(const Libros &otro) const;   // Compara cantidad de ejemplares
    bool operator>(const Libros &otro) const;   // Compara cantidad de ejemplares
    bool operator<=(const Libros &otro) const;  // Compara cantidad de ejemplares
    bool operator>=(const Libros &otro) const;  // Compara cantidad de ejemplares

    // Operadores aritméticos - Complejidad: O(1)
    Libros operator+(const Libros &otro) const; // Combina libros del mismo código
    Libros operator-(int restar) const;         // Resta cantidad de ejemplares
    
    // Operadores de incremento y decremento - Complejidad: O(1)
    Libros& operator++();      // Prefijo ++libro (incrementa cantidad)
    Libros operator++(int);    // Postfijo libro++ (incrementa cantidad)
    Libros& operator--();      // Prefijo --libro (decrementa cantidad)
    Libros operator--(int);    // Postfijo libro-- (decrementa cantidad)

    // Operador de salida - Complejidad: O(1)
    friend std::ostream &operator<<(std::ostream &os, const Libros &libro);
};

// Función global para combinar dos colecciones de libros - Complejidad: O(n + m)
// donde n y m son el tamaño de ambas listas
Lista<Libros> operator+(const Lista<Libros> &lista1, const Lista<Libros> &lista2);

#endif