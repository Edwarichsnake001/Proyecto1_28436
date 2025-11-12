#include <iostream>
#include <string>
#include <vector>

using namespace std;

enum class Rol
{
    Usuario,
    Admin
};

<<<<<<< HEAD
// Estructura para registrar un préstamo
struct Prestamo
{
    string codigoLibro;
    string titulo;
    string fechaPrestamo;
    
    Prestamo(string cod, string tit, string fecha) 
        : codigoLibro(cod), titulo(tit), fechaPrestamo(fecha) {}
};

=======
template <typename T>
>>>>>>> ad259ca35ccf35c4d55bc784724025093398e5f3
class Usuario
{
private:
    string nombre;
    string cedula;
    string id;
    string contrasena;
    Rol rol;
    vector<Prestamo> librosPrestados;  // Nuevo: lista de libros prestados al usuario

public:
    Usuario(string nom, string ced, string i, string cont, Rol r) 
        : nombre(nom), cedula(ced), id(i), contrasena(cont), rol(r) {}

    // Getters originales
    Rol getRol() const
    {
        return rol;
    }

    string getNombre() const { return nombre; }
    string getCedula() const { return cedula; }
    string getId() const { return id; }
    string getContrasena() const { return contrasena; }

    bool esAdministrador() const
    {
        return rol == Rol::Admin;
    }

<<<<<<< HEAD
    // ==========================================
    // NUEVAS FUNCIONES: Gestión de Préstamos
    // ==========================================
    
    // Agregar un libro prestado al usuario - Complejidad: O(1)
    void agregarLibroPrestado(const string &codigo, const string &titulo, const string &fecha)
    {
        librosPrestados.push_back(Prestamo(codigo, titulo, fecha));
    }
    
    // Devolver un libro (eliminar de la lista) - Complejidad: O(n)
    bool devolverLibro(const string &codigo)
    {
        for (auto it = librosPrestados.begin(); it != librosPrestados.end(); ++it)
        {
            if (it->codigoLibro == codigo)
            {
                librosPrestados.erase(it);
                return true;
            }
        }
        return false;
    }
    
    // Obtener cantidad de libros prestados al usuario - Complejidad: O(1)
    int getCantidadLibrosPrestados() const
    {
        return librosPrestados.size();
    }
    
    // Verificar si usuario tiene un libro prestado - Complejidad: O(n)
    bool tienePrestado(const string &codigo) const
    {
        for (const auto &prestamo : librosPrestados)
        {
            if (prestamo.codigoLibro == codigo)
                return true;
        }
        return false;
    }
    
    // Mostrar libros prestados por este usuario - Complejidad: O(n)
    void mostrarLibrosPrestados() const
    {
        if (librosPrestados.empty())
        {
            cout << "No tiene libros prestados.\n";
            return;
        }
        
        cout << "\nLibros prestados por " << nombre << ":\n";
        cout << "=====================================\n";
        for (const auto &prestamo : librosPrestados)
        {
            cout << "- " << prestamo.titulo 
                 << " (Código: " << prestamo.codigoLibro << ")\n"
                 << "  Fecha de préstamo: " << prestamo.fechaPrestamo << "\n";
        }
        cout << "=====================================\n";
    }

    // Obtener referencia a los préstamos para guardado - O(1)
    const std::vector<Prestamo>& getLibrosPrestados() const {
        return librosPrestados;
    }
=======
>>>>>>> ad259ca35ccf35c4d55bc784724025093398e5f3
};