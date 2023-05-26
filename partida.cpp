#include "partida.h"
#include <string>
#include <string.h>
#include <ctype.h>
#include <iostream>
using namespace std;
extern "C"
{
#include "baseDeDatos/gestorBD.h"
}

Partida::Partida(int user1id)
{

    palabraElegida = palabraRandom();
    cout << "PALABRA: " << palabraElegida << endl;

    int longitud = strlen(palabraElegida);
    progresoPalabra = new char[longitud + 1];
    for (int i = 0; i <= longitud; i++)
    {
        if (i < longitud)
        {
            progresoPalabra[i] = '_';
        }
        else if (i == longitud)
        {
            progresoPalabra[i] = '\0';
        }
    }

    turno = 1;
    usuario1 = informacionUsuario(user1id);

    cout << "patata: " << user1id << endl;

    id = crearPartida(user1id, palabraElegida);

    string mensaje = usuario1->nombre;
    mensaje += " ha creado una partida.";
    escribirHistorial(id, mensaje.c_str());
}

Partida::~Partida()
{
    delete[] palabraElegida;
    delete[] progresoPalabra;
    delete usuario1;
    delete usuario2;
}

int Partida::comprobarLetra(char letra)
{
    letra = toupper(letra);
    int encontradas = 0;
    for (int i = 0; palabraElegida[i] != '\0'; i++)
    {
        if (palabraElegida[i] == letra)
        {
            progresoPalabra[i] = letra;
            encontradas++;
        }
    }
    std::string mensaje = "";
    if (turno == 1)
    {
        mensaje += usuario1->nombre;
    }
    else
    {
        mensaje += usuario2->nombre;
    }
    mensaje += " ha intentado adivinar la letra " + letra;
    mensaje += " y se han encontrado " + std::to_string(encontradas);
    escribirHistorial(id, mensaje.c_str());
    return encontradas;
};

void Partida::setUsuario2(int user2id)
{
    usuario2 = informacionUsuario(user2id);
    std::string mensaje = usuario2->nombre;
    mensaje += " se ha unido a la partida.";
    escribirHistorial(id, mensaje.c_str());
}

int Partida::comprobarPalabra(const char *inPalabra)
{
    strcpy(palabraElegida, palabraElegida);
    for (int i = 0; palabraElegida[i] != '\0'; i++)
    {
        char charCom = toupper(inPalabra[i]);
        if (palabraElegida[i] != charCom)
        {
            std::string mensaje = usuario1->nombre;
            mensaje += " ha intentado resolver con ";
            mensaje += inPalabra;
            mensaje += " pero no era la solucion.";
            escribirHistorial(id, mensaje.c_str());
            return 0;
        }
    }
    std::string mensaje = usuario1->nombre;
    mensaje += " ha intentado resolver con ";
    mensaje += inPalabra;
    mensaje += " y era la solcion.";
    escribirHistorial(id, mensaje.c_str());
    return 1;
}