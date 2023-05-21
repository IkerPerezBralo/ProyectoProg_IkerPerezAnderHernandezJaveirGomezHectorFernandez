#include <iostream>
#include "consultaUsuario.h"

using namespace std;

void consultaUsuario::iniciar() {
    char respuesta;
    bool respuestaValida = false;

    while (!respuestaValida) {
        cout << "Confirme si es un usuario existente o no (s/n): ";
        cin >> respuesta;

        if (respuesta == 's' || respuesta == 'S') {
            cout << "Interfaz de iniciar usuario" << endl;
            respuestaValida = true;
        } else if (respuesta == 'n' || respuesta == 'N') {
            cout << "Interfaz de registrar usuario" << endl;
            respuestaValida = true;
        } else {
            cout << "Respuesta inválida. Por favor, introduce 's' o 'n'." << endl;
        }
    }
    menuUsuario();
}

void consultaUsuario::menuUsuario()
{
    int victorias = 5;
    int derrotas = 3;

    cout << "-----------------------------" << endl;
    cout << "   Ahorcado The Game" << endl;
    cout << "-----------------------------" << endl;
    cout << "Victorias: " << victorias << endl;
    cout << "Derrotas: " << derrotas << endl;
    cout << "-----------------------------" << endl;
    cout << "Opciones:" << endl;
    cout << "1. Crear una partida" << endl;
    cout << "2. Buscar partidas" << endl;
    cout << "3. Ver historial de partidas" << endl;
    cout << "4. Cerrar sesion" << endl;
    cout << "-----------------------------" << endl;

    int opcion;
    cout << "Ingrese el numero de opcion deseada: ";
    cin >> opcion;

    switch (opcion) {
        case 1:
            cout << "Creando una partida..." << endl;
            break;
        case 2:
            cout << "Buscando partidas..." << endl;
            break;
        case 3:
            cout << "Viendo historial de partidas..." << endl;
            break;
        case 4:
            cout << "Cerrando sesion..." << endl;
            cout << "..." << endl;
            cout << "..." << endl;
            cout << "..." << endl;
            cout << "Sesion cerrada" << endl;
            iniciar();
            break;
        default:
            cout << "Opción inválida." << endl;
            break;
    }
}
