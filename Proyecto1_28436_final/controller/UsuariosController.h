#pragma once

#include "../model/Usuario.h"
#include "../model/Libros.h"
#include <vector>
#include <string>

using namespace std;

class UsuariosControlador
{
private:
    vector<Usuario> usuarios;

public:
    UsuariosControlador();
    
    // Autenticación - Complejidad: O(n)
    Usuario *login(const string id, const string &contrasena);
    
    // Gestión de usuarios - Complejidad: O(1)
    void agregarUsuario(const Usuario &nuevoUser);
    
    // Búsqueda - Complejidad: O(n)
    Usuario *busquedaID(const string &id);
    
    // ==========================================
    // NUEVAS FUNCIONES: Gestión de Préstamos
    // ==========================================
    
    // Asignar libro a usuario - Complejidad: O(n)
    // Valida que el usuario exista y agregue el préstamo
    bool asignarLibroAUsuario(const string &idUsuario, 
                             const string &codigoLibro, 
                             const string &tituloLibro,
                             const string &fecha);
    
    // Devolver libro prestado - Complejidad: O(n)
    bool devolverLibroPrestado(const string &idUsuario, const string &codigoLibro);
    
    // Mostrar libros prestados por usuario - Complejidad: O(n)
    void mostrarPrestamosUsuario(const string &idUsuario);
    
    // Obtener cantidad de libros prestados por usuario - Complejidad: O(n)
    int getCantidadPrestamosUsuario(const string &idUsuario);

    // Persistencia de usuarios
    bool saveToFile(const std::string &path) const;
    bool loadFromFile(const std::string &path);
};