#pragma once

#include "../model/Usuario.h"
#include <vector>
#include <string>

using namespace std;

class UsuariosControlador{
    private:
        vector<Usuario> usuarios;
    public:
        Usuario *login(const string id, const string &contrasena);
        void agregarUsuario(const Usuario& nuevoUser);
        Usuario *busquedaID(const string &id);
};