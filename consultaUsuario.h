#ifndef CONSULTA_USUARIO_H
#define CONSULTA_USUARIO_H

#include <vector>
#include <string>
#include "clientConnectionManager/clientConnectionManager.h"
extern "C"{
    #include "baseDeDatos/gestorBD.h"
}
#define SERVER_PORT_1 6000
#define SERVER_PORT_2 6001
#define SERVER_INFOPORT 6002
using namespace std;
class consultaUsuario {
private:
    clientConnectionManager CCM;
    Usuario* usuario;
public:
    void iniciar();
    bool registrar();
    bool logInUsuario();
    void menuUsuario();
    void historial();
    void crearPartida();
    vector<string> cargarPalabras();
    string obtenerPalabraAleatoria(const vector<string>& palabras);
    void imprimirPalabra(const string& palabra, const vector<bool>& letrasAdivinadas);
    void procesarLetra(char letra, const string& palabra, vector<bool>& letrasAdivinadas, int& intentosRestantes);
    bool todasLetrasAdivinadas(const vector<bool>& letrasAdivinadas);
    void jugarAhorcado();
};

#endif