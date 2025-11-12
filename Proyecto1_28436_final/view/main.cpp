#include "../controller/LibroController.h"
#include "../controller/UsuariosController.h"
#include "../controller/PrestamoController.h"
#include "../controller/HistorialController.h"
#include "../model/Libros.h"
#include "../model/FileUtils.h"
#include <iostream>
#include <locale.h>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

void mostrarMenuAdmin() {
    cout << "\n===== MENÚ ADMINISTRADOR =====\n";
    cout << "1. Insertar libro\n";
    cout << "2. Eliminar libro\n";
    cout << "3. Mostrar todos los libros\n";
    cout << "4. Mostrar libros por cantidad\n";
    cout << "5. Mostrar libros por autor\n";
    cout << "6. Contar libros prestados\n";
    cout << "7. Mostrar libros ordenados\n";
    cout << "0. Salir\n";
    cout << "==============================\n";
    cout << "Seleccione una opción: ";
}

void mostrarMenuOrdenamiento() {
    cout << "\n===== ORDENAR LIBROS POR =====\n";
    cout << "1. Título (A-Z)\n";
    cout << "2. Autor (A-Z)\n";
    cout << "3. Código\n";
    cout << "0. Volver\n";
    cout << "==============================\n";
    cout << "Seleccione una opción: ";
}

void mostrarMenuUsuario() {
    cout << "\n===== MENÚ USUARIO =====\n";
    cout << "1. Mostrar libros disponibles\n";
    cout << "2. Buscar libro por título\n";
    cout << "3. Mostrar libros por autor\n";
    cout << "4. Contar libros prestados\n";
    cout << "5. Mostrar todos los libros\n";
    cout << "0. Salir\n";
    cout << "=========================\n";
    cout << "Seleccione una opción: ";
}

void ejecutarMenuAdmin(Lista<Libros>& lista) {
    int opcion;
    do {
        mostrarMenuAdmin();
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1: {
                string titulo, autor, codigo;
                bool disponible;
                int cantidad;

                cout << "Título: ";
                getline(cin, titulo);
                cout << "Autor: ";
                getline(cin, autor);
                cout << "Código: ";
                getline(cin, codigo);
                cout << "¿Disponible? (1 = sí, 0 = no): ";
                cin >> disponible;
                cout << "Cantidad: ";
                cin >> cantidad;
                cin.ignore();

                insertarLibro(lista, Libros(titulo, autor, codigo, disponible, cantidad));
                break;
            }
            case 2: {
                string codigo;
                cout << "Código del libro a eliminar: ";
                getline(cin, codigo);
                eliminarLibro(lista, codigo);
                break;
            }
            case 3:
                mostrarTodosLosLibros(lista);
                break;
            case 4:
                mostrarPorCantidad(lista);
                break;
            case 5: {
                string autor;
                cout << "Autor a mostrar: ";
                getline(cin, autor);
                mostrarPorAutor(lista, autor);
                break;
            }
            case 6:
                cout << "Cantidad de libros prestados: " << contarPrestados(lista) << "\n";
                break;
            case 7: {
                int opcionOrden;
                do {
                    mostrarMenuOrdenamiento();
                    cin >> opcionOrden;
                    cin.ignore();
                    
                    switch (opcionOrden) {
                        case 1:
                            mostrarLibrosAlfabeticamente(lista);
                            break;
                        case 2: {
                            string autor;
                            cout << "Autor a mostrar ordenado: ";
                            getline(cin, autor);
                            mostrarPorAutor(lista, autor);
                            break;
                        }
                        case 3: {
                            cout << "\n===== LIBROS ORDENADOS POR CÓDIGO =====\n";
                            vector<Libros> libros;
                            NodoLista<Libros> *actual = lista.getCabeza();
                            while (actual) {
                                libros.push_back(actual->getDato());
                                actual = actual->getSiguiente();
                            }
                            sort(libros.begin(), libros.end(), [](const Libros &a, const Libros &b) {
                                return a.getCodigo() < b.getCodigo();
                            });
                            for (const auto &libro : libros) {
                                cout << libro << endl;
                            }
                            cout << "========================================\n";
                            break;
                        }
                        case 0:
                            cout << "Volviendo al menú principal...\n";
                            break;
                        default:
                            cout << "Opción inválida.\n";
                    }
                } while (opcionOrden != 0);
                break;
            }
            case 0:
                cout << "Saliendo del menú administrador...\n";
                break;
            default:
                cout << "Opción inválida.\n";
        }
    } while (opcion != 0);
}

void ejecutarMenuUsuario(Lista<Libros>& lista) {
    int opcion;
    do {
        mostrarMenuUsuario();
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1:
                mostrarLibrosDisponibles(lista);
                break;
            case 2: {
                string titulo;
                cout << "Título a buscar: ";
                getline(cin, titulo);
                cout << (buscarPorTitulo(lista, titulo) ? "Encontrado\n" : "No encontrado\n");
                break;
            }
            case 3: {
                string autor;
                cout << "Autor a mostrar: ";
                getline(cin, autor);
                mostrarPorAutor(lista, autor);
                break;
            }
            case 4:
                cout << "Cantidad de libros prestados: " << contarPrestados(lista) << "\n";
                break;
            case 5:
                mostrarLibros(lista);
                break;
            case 0:
                cout << "Saliendo del menú usuario...\n";
                break;
            default:
                cout << "Opción inválida.\n";
        }
    } while (opcion != 0);
}

int main() {
    setlocale(LC_ALL, "es_ES.UTF-8");

    Lista<Libros> lista;
    UsuariosControlador usuariosControlador;

    cout << "\n[Sistema] Cargando datos desde archivos...\n";
    
    if (!loadLibrosFromFile(lista, "data/books.txt")) {
        cerr << "Advertencia: no se pudo cargar books.txt\n";
    } else {
        cout << "Libros cargados\n";
    }
    
    if (!usuariosControlador.loadFromFile("data/users.txt")) {
        cerr << "Advertencia: no se pudo cargar users.txt\n";
    } else {
        cout << "Usuarios cargados\n";
    }
    cout << "\n";
    // Presiona 0 en el menú de login para salir sin loguear
    
    cout << "\n===== SISTEMA DE GESTIÓN DE BIBLIOTECA =====\n";

    // Login
    string id, contrasena;
    cout << "\n=== LOGIN ===\n";
    cout << "Usuarios disponibles: admin01, user01, user02, user03, user04\n";
    cout << "ID: ";
    getline(cin, id);
    cout << "Contraseña: ";
    getline(cin, contrasena);
    
    Usuario* usuarioActual = usuariosControlador.login(id, contrasena);

    if (!usuarioActual) {
        cout << "Credenciales inválidas. Los IDs disponibles son: admin01, user01, user02, user03, user04\n";
        cout << "Por favor, reinicia el programa e intenta nuevamente.\n";
        return 1;
    }

    cout << "Bienvenido, " << usuarioActual->getNombre() << "\n";

    if (usuarioActual->esAdministrador()) {
        ejecutarMenuAdmin(lista);
    } else {
        ejecutarMenuUsuario(lista);
    }

    cout << "\n[Sistema] Guardando datos en archivos...\n";
    if (saveLibrosToFile(lista, "data/books.txt")) {
        cout << "[✓] Libros guardados en data/books.txt\n";
    } else {
        cerr << "Error al guardar books.txt\n";
    }
    
    if (usuariosControlador.saveToFile("data/users.txt")) {
        cout << "[✓] Usuarios guardados en data/users.txt\n";
    } else {
        cerr << "Error al guardar users.txt\n";
    }
    cout << "\n";

    return 0;
}
