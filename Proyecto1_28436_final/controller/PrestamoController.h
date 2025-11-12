#ifndef PRESTAMO_CONTROLLER_H
#define PRESTAMO_CONTROLLER_H

#include "../model/Cola.h"
#include "../model/SolicitudPrestamo.h"
#include <string>
#include <iostream>

using namespace std;

class PrestamoControlador
{
private:
    Cola<SolicitudPrestamo> colaPrestamosPendientes;  // Cola FIFO de solicitudes
    int prestamosTotales;
    
public:
    PrestamoControlador() : prestamosTotales(0) {}
    
    // ==========================================
    // MÓDULO DE PRÉSTAMOS (Cola - FIFO)
    // ==========================================
    
    // Solicitar préstamo - Complejidad: O(1)
    // Agrega la solicitud al final de la cola
    void solicitarPrestamo(const string &idUsuario, 
                          const string &nombreUsuario,
                          const string &codigoLibro,
                          const string &tituloLibro,
                          const string &fecha)
    {
        SolicitudPrestamo solicitud(idUsuario, nombreUsuario, codigoLibro, tituloLibro, fecha);
        colaPrestamosPendientes.encolar(solicitud);
        cout << "✓ Solicitud de préstamo registrada para " << nombreUsuario << "\n";
        cout << "  Libro: " << tituloLibro << "\n";
        cout << "  Posición en cola: " << colaPrestamosPendientes.tamaño() << "\n";
    }
    
    // Atender solicitud - Complejidad: O(1)
    // Procesa la primera solicitud de la cola (FIFO)
    bool atenderSolicitud()
    {
        if (colaPrestamosPendientes.estaVacia())
        {
            cout << "No hay solicitudes de préstamo pendientes.\n";
            return false;
        }
        
        // Obtener la primera solicitud (FIFO)
        SolicitudPrestamo solicitud = colaPrestamosPendientes.desencolar();
        
        cout << "\n===== ATENDIENDO SOLICITUD =====\n";
        cout << "Usuario: " << solicitud.nombreUsuario << "\n";
        cout << "Libro: " << solicitud.tituloLibro << "\n";
        cout << "Código: " << solicitud.codigoLibro << "\n";
        cout << "Fecha de solicitud: " << solicitud.fechaSolicitud << "\n";
        cout << "================================\n";
        cout << "✓ Préstamo aprobado y procesado.\n";
        
        prestamosTotales++;
        return true;
    }
    
    // Mostrar cola de solicitudes - Complejidad: O(n)
    void mostrarColaPendientes() const
    {
        if (colaPrestamosPendientes.estaVacia())
        {
            cout << "No hay solicitudes pendientes.\n";
            return;
        }
        
        cout << "\n===== SOLICITUDES PENDIENTES =====\n";
        cout << "Total pendientes: " << colaPrestamosPendientes.tamaño() << "\n";
        cout << "==================================\n";
        
        // Mostrar cada solicitud
        NodoCola<SolicitudPrestamo> *actual = colaPrestamosPendientes.getFrente();
        int contador = 1;
        while (actual)
        {
            cout << contador << ". ";
            actual->getDato().mostrar();
            cout << "\n";
            actual = actual->getSiguiente();
            contador++;
        }
    }
    
    // Obtener cantidad de solicitudes pendientes - Complejidad: O(1)
    int getCantidadSolicitudesPendientes() const
    {
        return colaPrestamosPendientes.tamaño();
    }
    
    // Obtener total de préstamos atendidos - Complejidad: O(1)
    int getTotalPrestamosAtendidos() const
    {
        return prestamosTotales;
    }
    
    // Verificar si hay solicitudes pendientes - Complejidad: O(1)
    bool hayPendientes() const
    {
        return !colaPrestamosPendientes.estaVacia();
    }
};

#endif
