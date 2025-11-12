#include <iostream>
#include <vector>
#include <algorithm>

#include "../controller/LibroController.h"
#include "../model/FileUtils.h"
#include <fstream>
#include <sstream>

using namespace std;

// ==========================================
// FUNCIONES DE INSERCIÓN Y ELIMINACIÓN
// ==========================================

// Insertar libro en la lista - Complejidad: O(1) en promedio
void insertarLibro(Lista<Libros> &lista, const Libros &libro)
{
    lista.insertar(libro);
}

bool eliminarLibro(Lista<Libros> &lista, const std::string &codigo)
{
    NodoLista<Libros> *actual = lista.getCabeza();
    while (actual)
    {
        if (actual->getDato().getCodigo() == codigo)
        {
            lista.eliminar(actual->getDato());
            return true;
        }
        actual = actual->getSiguiente();
    }
    return false;
}

void mostrarPorAutor(const Lista<Libros> &lista, const std::string &autor)
{
    NodoLista<Libros> *actual = lista.getCabeza();
    while (actual)
    {
        if (actual->getDato().coincideAutor(autor))
        {
            cout << actual->getDato() << endl;
        }
        actual = actual->getSiguiente();
    }
}

void mostrarPorCantidad(const Lista<Libros> &lista)
{
    vector<Libros> libros;
    NodoLista<Libros> *actual = lista.getCabeza();
    while (actual)
    {
        libros.push_back(actual->getDato());
        actual = actual->getSiguiente();
    }

    sort(libros.begin(), libros.end(), [](const Libros &a, const Libros &b)
         { return a.getCantidad() > b.getCantidad(); });

    for (const auto &libro : libros)
    {
        cout << libro << endl;
    }
}

void mostrarLibros(const Lista<Libros> &lista)
{
    NodoLista<Libros> *actual = lista.getCabeza();
    while (actual)
    {
        if (!actual->getDato().disponibilidad())
        {
            cout << actual->getDato() << endl;
        }
        actual = actual->getSiguiente();
    }
}

void mostrarTodosLosLibros(const Lista<Libros> &lista)
{
    NodoLista<Libros> *actual = lista.getCabeza();
    cout << "\n===== CATÁLOGO COMPLETO DE LIBROS =====\n";
    if (!actual) {
        cout << "No hay libros registrados.\n";
        cout << "========================================\n";
        return;
    }
    while (actual)
    {
        cout << actual->getDato() << endl;
        actual = actual->getSiguiente();
    }
    cout << "========================================\n";
}

bool buscarPorTituloRecursivo(NodoLista<Libros> *nodo, const std::string &titulo)
{
    if (!nodo)
        return false;
    if (nodo->getDato().coincideTitulo(titulo))
        return true;
    return buscarPorTituloRecursivo(nodo->getSiguiente(), titulo);
}

bool buscarPorTitulo(const Lista<Libros> &lista, const std::string &titulo)
{
    return buscarPorTituloRecursivo(lista.getCabeza(), titulo);
}

int contarPrestadosRec(NodoLista<Libros> *nodo)
{
    if (!nodo)
        return 0;
    int suma = nodo->getDato().disponibilidad() ? 0 : 1;
    return suma + contarPrestadosRec(nodo->getSiguiente());
}

int contarPrestados(const Lista<Libros> &lista)
{
    return contarPrestadosRec(lista.getCabeza());
}

void mostrarLibrosDisponibles(const Lista<Libros> &lista)
{
    NodoLista<Libros> *actual = lista.getCabeza();
    while (actual)
    {
        if (actual->getDato().disponibilidad())
        {
            cout << actual->getDato() << endl;
        }
        actual = actual->getSiguiente();
    }
}

// ==========================================
// FUNCIÓN RECURSIVA: ORDENAMIENTO ALFABÉTICO
// ==========================================
// Complejidad: O(n log n) - Merge Sort Recursivo
// Esta función recolecta los libros en un vector y luego los ordena
// recursivamente utilizando merge sort

// Función auxiliar recursiva para merge sort - Complejidad: O(n log n)
void mergeSortRecursivo(std::vector<Libros> &libros, int izq, int der)
{
    if (izq < der)
    {
        int mid = (izq + der) / 2;
        
        // Divide: ordena la mitad izquierda - O(n/2 log n/2)
        mergeSortRecursivo(libros, izq, mid);
        
        // Divide: ordena la mitad derecha - O(n/2 log n/2)
        mergeSortRecursivo(libros, mid + 1, der);
        
        // Conquista: mezcla las dos mitades ordenadas - O(n)
        std::vector<Libros> temp;
        int i = izq, j = mid + 1;
        
        while (i <= mid && j <= der)
        {
            if (libros[i].getTitulo() <= libros[j].getTitulo())
            {
                temp.push_back(libros[i++]);
            }
            else
            {
                temp.push_back(libros[j++]);
            }
        }
        
        while (i <= mid)
            temp.push_back(libros[i++]);
        
        while (j <= der)
            temp.push_back(libros[j++]);
        
        // Copia los elementos ordenados de vuelta al vector original
        for (int k = 0; k < temp.size(); k++)
        {
            libros[izq + k] = temp[k];
        }
    }
}

// Función pública para mostrar libros ordenados alfabéticamente - Complejidad: O(n log n)
void mostrarLibrosAlfabeticamente(const Lista<Libros> &lista)
{
    // Recolectar todos los libros en un vector - O(n)
    std::vector<Libros> libros;
    NodoLista<Libros> *actual = lista.getCabeza();
    
    while (actual)
    {
        libros.push_back(actual->getDato());
        actual = actual->getSiguiente();
    }
    
    // Ordenar recursivamente usando merge sort - O(n log n)
    if (!libros.empty())
    {
        mergeSortRecursivo(libros, 0, libros.size() - 1);
    }
    
    // Mostrar los libros ordenados alfabéticamente - O(n)
    cout << "\n===== LIBROS ORDENADOS ALFABÉTICAMENTE =====\n";
    for (const auto &libro : libros)
    {
        cout << libro << endl;
    }
}

// ============================
// Persistencia de Libros
// ============================
// Formato por línea: codigo|titulo|autor|cantidad|disponible(0/1)
bool saveLibrosToFile(const Lista<Libros> &lista, const std::string &path)
{
    std::ofstream ofs(path);
    if (!ofs.is_open()) return false;
    NodoLista<Libros> *actual = lista.getCabeza();
    while (actual)
    {
        const Libros &lib = actual->getDato();
        ofs << escapeField(lib.getCodigo()) << "|"
            << escapeField(lib.getTitulo()) << "|"
            << escapeField(lib.getAutor()) << "|"
            << lib.getCantidad() << "|"
            << (lib.disponibilidad() ? 1 : 0) << "\n";
        actual = actual->getSiguiente();
    }
    ofs.close();
    return true;
}

bool loadLibrosFromFile(Lista<Libros> &lista, const std::string &path)
{
    std::ifstream ifs(path);
    if (!ifs.is_open()) {
        return true;
    }
    
    std::string line;
    int lineNum = 0;
    while (std::getline(ifs, line))
    {
        lineNum++;
        if (line.empty()) continue;
        if (line[0] == '#') continue;
        
        std::vector<std::string> parts;
        std::stringstream ss(line);
        std::string part;
        while (std::getline(ss, part, '|')) {
            parts.push_back(part);
        }
        
        if (parts.size() < 5) {
            continue;
        }
        
        std::string codigo = parts[0];
        std::string titulo = parts[1];
        std::string autor = parts[2];
        int cantidad = 0;
        int disp = 1;
        
        try { 
            cantidad = std::stoi(parts[3]); 
        } catch (...) { 
            cantidad = 0; 
        }
        
        try { 
            disp = std::stoi(parts[4]); 
        } catch (...) { 
            disp = (cantidad > 0 ? 1 : 0); 
        }
        
        bool disponible = (disp != 0);

        Libros libro(titulo, autor, codigo, disponible, cantidad);
        insertarLibro(lista, libro);
    }
    ifs.close();
    return true;
}
