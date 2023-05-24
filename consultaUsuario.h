#ifndef CONSULTA_USUARIO_H
#define CONSULTA_USUARIO_H

#include <vector>
#include <string>

using namespace std;
class consultaUsuario {
public:
    void iniciar();
    void registrar();
    void logIn();
    void menuUsuario();
    void historial();
    void crearPartida();
    void unirtePartida();
    vector<string> cargarPalabras();
    string obtenerPalabraAleatoria(const vector<string>& palabras);
    void imprimirPalabra(const string& palabra, const vector<bool>& letrasAdivinadas);
    void procesarLetra(char letra, const string& palabra, vector<bool>& letrasAdivinadas, int& intentosRestantes);
    bool todasLetrasAdivinadas(const vector<bool>& letrasAdivinadas);
    void jugarAhorcado();
};

#endif