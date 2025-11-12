#include "UsuariosController.h"
#include "../model/FileUtils.h"
#include <fstream>
#include <sstream>

UsuariosControlador::UsuariosControlador()
{
    usuarios.push_back(Usuario("Mat", "0102030405", "admin01", "clave123", Rol::Admin));
    usuarios.push_back(Usuario("Ana", "1122334455", "user01", "libros456", Rol::Usuario));
}

Usuario *UsuariosControlador::login(const string id, const string &contrasena)
{
    for (auto &usuario : usuarios)
    {
        if (usuario.getId() == id && usuario.getContrasena() == contrasena)
        {
            return &usuario;
        }
    }
    return nullptr;
}

void UsuariosControlador::agregarUsuario(const Usuario &nuevoUser)
{
    usuarios.push_back(nuevoUser);
}

Usuario *UsuariosControlador::busquedaID(const string &id)
{
    for (auto &usuario : usuarios)
    {
        if (usuario.getId() == id)
        {
            return &usuario;
        }
    }
    return nullptr;
}

// ============================
// Persistencia de Usuarios
// ============================
// Formato por línea: id|nombre|rol|cedula|contrasena|prestamo1;prestamo2;...
// Cada prestamo: codigo~titulo~fecha
bool UsuariosControlador::saveToFile(const std::string &path) const
{
    std::ofstream ofs(path);
    if (!ofs.is_open()) return false;
    for (const auto &usuario : usuarios)
    {
        std::string rolStr = (usuario.getRol() == Rol::Admin) ? "Admin" : "Usuario";
        ofs << escapeField(usuario.getId()) << "|"
            << escapeField(usuario.getNombre()) << "|"
            << rolStr << "|"
            << escapeField(usuario.getCedula()) << "|"
            << escapeField(usuario.getContrasena()) << "|";

        // prestamos
        const auto &prest = usuario.getLibrosPrestados();
        bool first = true;
        for (const auto &p : prest)
        {
            if (!first) ofs << ";";
            first = false;
            ofs << escapeField(p.codigoLibro) << "~"
                << escapeField(p.titulo) << "~"
                << escapeField(p.fechaPrestamo);
        }
        ofs << "\n";
    }
    ofs.close();
    return true;
}

bool UsuariosControlador::loadFromFile(const std::string &path)
{
    std::ifstream ifs(path);
    if (!ifs.is_open()) return true; // treat as empty if not present

    usuarios.clear();
    std::string line;
    while (std::getline(ifs, line))
    {
        if (line.empty()) continue;
        if (line[0] == '#') continue;
        auto parts = splitEscaped(line, '|');
        if (parts.size() < 6) continue;
        std::string id = unescapeField(parts[0]);
        std::string nombre = unescapeField(parts[1]);
        std::string rolS = parts[2];
        std::string cedula = unescapeField(parts[3]);
        std::string contrasena = unescapeField(parts[4]);
        std::string prestamosField = parts[5];

        Rol rol = Rol::Usuario;
        if (rolS == "Admin" || rolS == "ADMIN" ) rol = Rol::Admin;

        Usuario u(nombre, cedula, id, contrasena, rol);

        // parse prestamos
        auto items = splitEscaped(prestamosField, ';');
        for (const auto &it : items)
        {
            if (it.empty()) continue;
            auto pparts = splitEscaped(it, '~');
            if (pparts.size() < 3) continue;
            std::string codigo = unescapeField(pparts[0]);
            std::string titulo = unescapeField(pparts[1]);
            std::string fecha = unescapeField(pparts[2]);
            u.agregarLibroPrestado(codigo, titulo, fecha);
        }

        usuarios.push_back(u);
    }

    ifs.close();
    return true;
}

// ==========================================
// IMPLEMENTACIÓN: Gestión de Préstamos
// ==========================================

// Asignar libro a usuario - Complejidad: O(n)
bool UsuariosControlador::asignarLibroAUsuario(const string &idUsuario, 
                                               const string &codigoLibro, 
                                               const string &tituloLibro,
                                               const string &fecha)
{
    // Buscar usuario - O(n)
    Usuario *usuario = busquedaID(idUsuario);
    
    if (!usuario)
    {
        cout << "Error: Usuario con ID '" << idUsuario << "' no encontrado.\n";
        return false;
    }
    
    // Verificar que no tenga el mismo libro ya prestado
    if (usuario->tienePrestado(codigoLibro))
    {
        cout << "Error: El usuario ya tiene este libro prestado.\n";
        return false;
    }
    
    // Agregar el libro al usuario - O(1)
    usuario->agregarLibroPrestado(codigoLibro, tituloLibro, fecha);
    cout << "✓ Libro '" << tituloLibro << "' asignado a " << usuario->getNombre() 
         << " exitosamente.\n";
    return true;
}

// Devolver libro prestado - Complejidad: O(n)
bool UsuariosControlador::devolverLibroPrestado(const string &idUsuario, const string &codigoLibro)
{
    // Buscar usuario - O(n)
    Usuario *usuario = busquedaID(idUsuario);
    
    if (!usuario)
    {
        cout << "Error: Usuario no encontrado.\n";
        return false;
    }
    
    // Devolver libro - O(n)
    if (usuario->devolverLibro(codigoLibro))
    {
        cout << "✓ Libro devuelto exitosamente.\n";
        return true;
    }
    
    cout << "Error: El usuario no tiene este libro prestado.\n";
    return false;
}

// Mostrar libros prestados por usuario - Complejidad: O(n)
void UsuariosControlador::mostrarPrestamosUsuario(const string &idUsuario)
{
    Usuario *usuario = busquedaID(idUsuario);
    
    if (!usuario)
    {
        cout << "Error: Usuario no encontrado.\n";
        return;
    }
    
    usuario->mostrarLibrosPrestados();
}

// Obtener cantidad de libros prestados por usuario - Complejidad: O(n)
int UsuariosControlador::getCantidadPrestamosUsuario(const string &idUsuario)
{
    Usuario *usuario = busquedaID(idUsuario);
    
    if (!usuario)
    {
        return -1;  // Error
    }
    
    return usuario->getCantidadLibrosPrestados();
}
