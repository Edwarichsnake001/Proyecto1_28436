#ifndef SOLICITUD_PRESTAMO_H
#define SOLICITUD_PRESTAMO_H

#include <string>
#include <iostream>

using namespace std;

struct SolicitudPrestamo
{
    string idUsuario;
    string nombreUsuario;
    string codigoLibro;
    string tituloLibro;
    string fechaSolicitud;
    bool atendida;
    
    SolicitudPrestamo(const string &id, const string &nombre, 
                     const string &codLibro, const string &titLibro,
                     const string &fecha)
        : idUsuario(id), nombreUsuario(nombre), 
          codigoLibro(codLibro), tituloLibro(titLibro),
          fechaSolicitud(fecha), atendida(false) {}

    SolicitudPrestamo()
        : idUsuario(""), nombreUsuario(""), codigoLibro(""), tituloLibro(""), fechaSolicitud(""), atendida(false) {}
    
    void mostrar() const
    {
        cout << "Solicitud: " << nombreUsuario 
             << " - Libro: " << tituloLibro 
             << " (Código: " << codigoLibro << ")\n"
             << "  Fecha: " << fechaSolicitud
             << " | Estado: " << (atendida ? "ATENDIDA" : "PENDIENTE") << "\n";
    }
};

#endif
