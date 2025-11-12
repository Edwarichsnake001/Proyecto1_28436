    #ifndef LIBROCONTROLLER_H
    #define LIBROCONTROLLER_H

    #include "../model/Lista.h"
    #include "../model/Libros.h"

    #include <string>

// ==========================================
// FUNCIONES DE GESTIÓN DE LIBROS
// ==========================================

// Inserción de libros - Complejidad: O(1) en promedio
void insertarLibro(Lista<Libros>& lista, const Libros& libro);

// Eliminación de libros - Complejidad: O(n)
bool eliminarLibro(Lista<Libros>& lista, const std::string& codigo);

// Búsqueda y Mostrado
void mostrarPorAutor(const Lista<Libros>& lista, const std::string& autor);      // Complejidad: O(n)
void mostrarPorCantidad(const Lista<Libros>& lista);                             // Complejidad: O(n log n)
void mostrarLibros(const Lista<Libros> &lista);                                  // Complejidad: O(n) - Muestra solo no disponibles
void mostrarTodosLosLibros(const Lista<Libros> &lista);                          // Complejidad: O(n) - Muestra TODOS los libros
void mostrarLibrosDisponibles(const Lista<Libros> &lista);                       // Complejidad: O(n)

// ==========================================
// FUNCIONES RECURSIVAS
// ==========================================

// Búsqueda recursiva por título - Complejidad: O(n)
bool buscarPorTitulo(const Lista<Libros> &lista, const std::string &titulo);

// Contar libros prestados de forma RECURSIVA - Complejidad: O(n)
// Recorre la lista de forma recursiva sumando los libros no disponibles
int contarPrestados(const Lista<Libros> &lista);

// Mostrar libros ordenados ALFABÉTICAMENTE de forma RECURSIVA - Complejidad: O(n log n)
// Utiliza merge sort recursivo para ordenar por título
void mostrarLibrosAlfabeticamente(const Lista<Libros> &lista);

// Persistencia - guardar y cargar catálogo de libros
bool saveLibrosToFile(const Lista<Libros> &lista, const std::string &path);
bool loadLibrosFromFile(Lista<Libros> &lista, const std::string &path);

#endif // LIBROCONTROLLER_H