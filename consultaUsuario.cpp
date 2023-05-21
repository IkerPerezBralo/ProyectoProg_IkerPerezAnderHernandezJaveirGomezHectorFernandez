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
}