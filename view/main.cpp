#include "../controller/LibroController.h"

#include <iostream>
#include <locale.h>

using namespace std;

int main(){
    setlocale(LC_ALL, "es_ES.UTF-8");
    Lista<Libros> lista;

    // Insertar libros
    insertarLibro(lista, Libros("1984", "George Orwell", "L001", true, 5));
    insertarLibro(lista, Libros("Cien años de soledad", "Gabriel García Márquez", "L002", false, 3));
    insertarLibro(lista, Libros("El Principito", "Antoine de Saint-Exupéry", "L003", true, 7));
    insertarLibro(lista, Libros("Ficciones", "Jorge Luis Borges", "L004", false, 2));

    cout << "\nLibros disponibles:\n";
    mostrarLibrosDisponibles(lista);

    cout << "\nBuscar libro por título '1984': ";
    cout << (buscarPorTitulo(lista, "1984") ? "Encontrado\n" : "No encontrado\n");

    cout << "\nEliminar libro con código 'L002'\n";
    eliminarLibro(lista, "L002");

    cout << "\nLibros ordenados por cantidad:\n";
    mostrarPorCantidad(lista);

    cout << "\nLibros del autor 'Jorge Luis Borges':\n";
    mostrarPorAutor(lista, "Jorge Luis Borges");

    cout << "\nCantidad de libros prestados: " << contarPrestados(lista) << "\n";

    cout << "\nLibros prestados:\n";
    mostrarLibros(lista);

    return 0;


}