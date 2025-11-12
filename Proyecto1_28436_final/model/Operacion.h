#ifndef OPERACION_H
#define OPERACION_H

#include <string>
#include <iostream>

using namespace std;

enum class TipoOperacion
{
    PRESTAMO,
    DEVOLUCION,
    INSERCION_LIBRO,
    ELIMINACION_LIBRO,
    ASIGNACION_USUARIO
};

struct Operacion
{
    TipoOperacion tipo;
    string descripcion;
    string timestamp;
    string usuarioResponsable;
    bool deshecha;
    
    Operacion(TipoOperacion t, const string &desc, const string &ts, const string &usuario)
        : tipo(t), descripcion(desc), timestamp(ts), 
          usuarioResponsable(usuario), deshecha(false) {}
    
    Operacion()
        : tipo(TipoOperacion::PRESTAMO), descripcion(""), timestamp(""), usuarioResponsable(""), deshecha(false) {}
    
    string getTipoStr() const
    {
        switch (tipo)
        {
            case TipoOperacion::PRESTAMO:
                return "PRÉSTAMO";
            case TipoOperacion::DEVOLUCION:
                return "DEVOLUCIÓN";
            case TipoOperacion::INSERCION_LIBRO:
                return "INSERCIÓN DE LIBRO";
            case TipoOperacion::ELIMINACION_LIBRO:
                return "ELIMINACIÓN DE LIBRO";
            case TipoOperacion::ASIGNACION_USUARIO:
                return "ASIGNACIÓN A USUARIO";
            default:
                return "DESCONOCIDA";
        }
    }
    
    void mostrar() const
    {
        cout << "[" << timestamp << "] "
             << getTipoStr() << "\n"
             << "  Descripción: " << descripcion << "\n"
             << "  Usuario: " << usuarioResponsable << "\n"
             << "  Estado: " << (deshecha ? "DESHECHA" : "ACTIVA") << "\n";
    }
};

#endif
