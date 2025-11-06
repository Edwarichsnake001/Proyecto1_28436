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

public:
    Libros(string tit, string aut, string cod, bool disp) : titulo(tit), autor(aut), codigo(cod), disponible(disp){}

    string getTitulo()const {
        return titulo;
    }

    string getAutor()const {
        return autor;
    }

    friend std::ostream& operator<<(std::ostream& os, const Libros& libro) {
        os << "Título: " << libro.titulo
           << ", Autor: " << libro.autor
           << ", Código: " << libro.codigo
           << ", Estatus: " << (libro.disponible ? "Disponible" : "No disponible");
        return os;
    }




};