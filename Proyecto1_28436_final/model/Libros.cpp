#include "Libros.h"
#include <iostream>
#include <string>

using namespace std;

string Libros::getTitulo() const
{
    return titulo;
}

string Libros::getAutor() const
{
    return autor;
}

string Libros::getCodigo() const
{
    return codigo;
}

int Libros::getCantidad() const
{
    return cantidad;
}

bool Libros::operator==(const Libros &otro) const
{
   return codigo == otro.codigo;
}

void Libros::setDisponible(bool estado)
{
    disponible = estado;
}

bool Libros::disponibilidad() const
{
    return disponible;
}

bool Libros::coincideTitulo(const std::string &t) const
{
    return titulo == t;
}

bool Libros::coincideAutor(const std::string &a) const
{
    return autor == a;
}

/*Todavía no sé donde puedo implementar estos operadores ni como debería
usarlo dentro del programa como una funcionalidad necesaria
por lo que ahora solo están de """Adorno"""""*/

// Operadores de comparación - Complejidad: O(1)
bool Libros::operator<(const Libros &otro) const
{
    return cantidad < otro.cantidad;
}

bool Libros::operator>(const Libros &otro) const
{
    return cantidad > otro.cantidad;
}

bool Libros::operator<=(const Libros &otro) const
{
    return cantidad <= otro.cantidad;
}

bool Libros::operator>=(const Libros &otro) const
{
    return cantidad >= otro.cantidad;
}

bool Libros::operator!=(const Libros &otro) const
{
    return codigo != otro.codigo;
}

// Operador suma: combina las cantidades de dos libros (mismo código) - Complejidad: O(1)
Libros Libros::operator+(const Libros &otro) const
{
    if (codigo == otro.codigo)
    {
        return Libros(titulo, autor, codigo, disponible, cantidad + otro.cantidad);
    }
    // Si los códigos no coinciden, retorna una copia del libro actual
    return Libros(titulo, autor, codigo, disponible, cantidad);
}

// Operador resta: disminuye la cantidad - Complejidad: O(1)
Libros Libros::operator-(int restar) const
{
    int nuevaCantidad = cantidad - restar;
    if (nuevaCantidad < 0) nuevaCantidad = 0;
    return Libros(titulo, autor, codigo, disponible, nuevaCantidad);
}

// Prefijo ++: incrementa la cantidad y retorna la referencia - Complejidad: O(1)
Libros& Libros::operator++()
{
    cantidad++;
    return *this;
}

// Postfijo ++: incrementa la cantidad pero retorna una copia del valor anterior - Complejidad: O(1)
Libros Libros::operator++(int)
{
    Libros temp(*this);
    cantidad++;
    return temp;
}

// Prefijo --: decrementa la cantidad y retorna la referencia - Complejidad: O(1)
Libros& Libros::operator--()
{
    if (cantidad > 0) cantidad--;
    return *this;
}

// Postfijo --: decrementa la cantidad pero retorna una copia del valor anterior - Complejidad: O(1)
Libros Libros::operator--(int)
{
    Libros temp(*this);
    if (cantidad > 0) cantidad--;
    return temp;
}

// Operador de salida - Complejidad: O(1)
std::ostream &operator<<(std::ostream &os, const Libros &libro)
{
    os << "Título: " << libro.titulo << endl
       << "Autor: " << libro.autor << endl
       << "Código: " << libro.codigo << endl
       << "Estado: " << (libro.disponible ? "Disponible" : "Prestado") << endl
       << "Cantidad: " << libro.cantidad << endl;
    return os;
}

// ============================================
// FUNCIÓN GLOBAL PARA COMBINAR COLECCIONES
// ============================================
// Operador + para combinar dos listas de libros - Complejidad: O(n + m)
// donde n = tamaño de lista1 y m = tamaño de lista2
// Recorre ambas listas e inserta todos los elementos en una nueva lista
Lista<Libros> operator+(const Lista<Libros> &lista1, const Lista<Libros> &lista2)
{
    Lista<Libros> resultado;
    
    // Insertar todos los libros de la primera lista - O(n)
    NodoLista<Libros> *actual = lista1.getCabeza();
    while (actual)
    {
        resultado.insertar(actual->getDato());
        actual = actual->getSiguiente();
    }
    
    // Insertar todos los libros de la segunda lista - O(m)
    actual = lista2.getCabeza();
    while (actual)
    {
        resultado.insertar(actual->getDato());
        actual = actual->getSiguiente();
    }
    
    return resultado;
}
