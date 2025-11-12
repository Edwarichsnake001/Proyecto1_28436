#ifndef HISTORIAL_CONTROLLER_H
#define HISTORIAL_CONTROLLER_H

#include "../model/Pila.h"
#include "../model/Operacion.h"
#include <string>
#include <iostream>

using namespace std;

class HistorialControlador
{
private:
    Pila<Operacion> pilaOperaciones;  // Pila LIFO para deshacer últimas operaciones
    int operacionesTotales;
    int operacionesDeshechadas;
    
public:
    HistorialControlador() 
        : operacionesTotales(0), operacionesDeshechadas(0) {}
    
    // ==========================================
    // MÓDULO DE HISTORIAL (Pila - LIFO)
    // ==========================================
    
    // Registrar operación - Complejidad: O(1)
    // Agrega la operación al tope de la pila
    void registrarOperacion(TipoOperacion tipo,
                           const string &descripcion,
                           const string &timestamp,
                           const string &usuario)
    {
        Operacion op(tipo, descripcion, timestamp, usuario);
        pilaOperaciones.apilar(op);
        operacionesTotales++;
        cout << "✓ Operación registrada: " << op.getTipoStr() << "\n";
    }
    
    // Deshacer última operación - Complejidad: O(1)
    // Desapila la operación del tope (LIFO)
    bool deshacerUltima()
    {
        if (pilaOperaciones.estaVacia())
        {
            cout << "No hay operaciones que deshacer.\n";
            return false;
        }
        
        // Obtener la última operación (tope de pila)
        Operacion operacion = pilaOperaciones.desapilar();
        
        cout << "\n===== DESHACIENDO OPERACIÓN =====\n";
        cout << "Tipo: " << operacion.getTipoStr() << "\n";
        cout << "Descripción: " << operacion.descripcion << "\n";
        cout << "Realizada por: " << operacion.usuarioResponsable << "\n";
        cout << "Marca temporal: " << operacion.timestamp << "\n";
        cout << "==================================\n";
        cout << "✓ Operación deshecha exitosamente.\n";
        
        operacionesDeshechadas++;
        return true;
    }
    
    // Mostrar historial completo - Complejidad: O(n)
    void mostrarHistorial() const
    {
        if (pilaOperaciones.estaVacia())
        {
            cout << "El historial está vacío.\n";
            return;
        }
        
        cout << "\n===== HISTORIAL DE OPERACIONES =====\n";
        cout << "Total de operaciones: " << operacionesTotales << "\n";
        cout << "Operaciones activas: " << pilaOperaciones.tamaño() << "\n";
        cout << "Operaciones deshechas: " << operacionesDeshechadas << "\n";
        cout << "====================================\n";
        
        // Mostrar cada operación
        NodoPila<Operacion> *actual = pilaOperaciones.getTope();
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
    
    // Mostrar últimas N operaciones - Complejidad: O(n)
    void mostrarUltimas(int cantidad) const
    {
        if (pilaOperaciones.estaVacia())
        {
            cout << "No hay operaciones en el historial.\n";
            return;
        }
        
        cout << "\n===== ÚLTIMAS " << cantidad << " OPERACIONES =====\n";
        
        NodoPila<Operacion> *actual = pilaOperaciones.getTope();
        int contador = 1;
        
        while (actual && contador <= cantidad)
        {
            cout << contador << ". ";
            actual->getDato().mostrar();
            cout << "\n";
            actual = actual->getSiguiente();
            contador++;
        }
    }
    
    // Obtener cantidad de operaciones activas - Complejidad: O(1)
    int getCantidadOperacionesActivas() const
    {
        return pilaOperaciones.tamaño();
    }
    
    // Obtener total de operaciones realizadas - Complejidad: O(1)
    int getTotalOperacionesRealizadas() const
    {
        return operacionesTotales;
    }
    
    // Obtener total de operaciones deshechas - Complejidad: O(1)
    int getTotalOperacionesDeshechas() const
    {
        return operacionesDeshechadas;
    }
    
    // Verificar si hay operaciones - Complejidad: O(1)
    bool hayOperaciones() const
    {
        return !pilaOperaciones.estaVacia();
    }
    
    // Limpiar historial - Complejidad: O(n)
    void limpiarHistorial()
    {
        while (!pilaOperaciones.estaVacia())
        {
            pilaOperaciones.desapilar();
        }
        cout << "✓ Historial limpiado.\n";
    }
};

#endif
