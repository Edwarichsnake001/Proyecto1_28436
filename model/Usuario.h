#include <iostream>
#include <string>

using namespace std;

enum class Rol
{
    Usuario,
    Admin
};

class Usuario
{
private:
    string nombre;
    string cedula;
    string id;
    Rol rol;

public:
    Usuario(string nom, string ced, string i, Rol r) : nombre(nom), cedula(ced), id(i), rol(r) {}

    Rol getRol() const
    {
        return rol;
    }

    bool esAdministrador() const
    {
        return rol == Rol::Admin;
    }
};