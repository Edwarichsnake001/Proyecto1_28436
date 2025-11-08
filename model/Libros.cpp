#include "Libros.h"
#include <iostream>
#include <string>

using namespace std;

string Libros::getTitulo() const
{
    return string();
}

string Libros::getAutor() const
{
    return string();
}

string Libros::getCodigo() const
{
    return string();
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

bool Libros::operator<(const Libros &otro) const
{
    return cantidad < otro.cantidad;
}

bool Libros::operator>(const Libros &otro) const
{
    return cantidad > otro.cantidad;
}

std::ostream &operator<<(std::ostream &os, const Libros &libro)
{
    os << "Título: " << libro.titulo << endl
       << "Autor: " << libro.autor << endl
       << "Código: " << libro.codigo << endl
       << "Estado: " << (libro.disponible ? "Disponible" : "Prestado") << endl
       << "Cantidad: " << libro.cantidad << endl;
    return os;
}
