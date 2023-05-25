#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include "consultaUsuario.h"

extern "C"{
    #include "baseDeDatos/gestorBD.h"
}

using namespace std;

void consultaUsuario::iniciar() {
    char respuesta;
    bool respuestaValida = false;
    CCM = clientConnectionManager();

    while (!respuestaValida) {
        cout << "Confirme si es un usuario existente o no (s/n): ";
        cin >> respuesta;

        if (respuesta == 's' || respuesta == 'S') {
            cout << "Interfaz de iniciar usuario" << endl;

            respuestaValida = true;
        } else if (respuesta == 'n' || respuesta == 'N') {
            cout << "Interfaz de registrar usuario" << endl;
            registrar();
            respuestaValida = true;
        } else {
            cout << "Respuesta invalida. Por favor, introduce 's' o 'n'." << endl;
        }
    }
    menuUsuario();
}

void consultaUsuario::registrar()
{
    char usuario[50];
    char contrasenya[50];

    cout << "Ingrese el nombre de usuario que desee: ";
    cin >> usuario;

    cout << "Ingrese su contrasenya: ";
    cin >> contrasenya;

    insertarUsuario(usuario, contrasenya);
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
            crearPartida();
            break;
        case 2:
            cout << "Buscando partidas..." << endl;
            unirtePartida();
            break;
        case 3:
            cout << "Viendo historial de partidas..." << endl;
            historial();
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
            cout << "Opcion invalida." << endl;
            break;
    }
}

void consultaUsuario::historial()
{
    cout << "ACCEDE A LA BD Y PONE EL HISTORIAL DE PARTIDAS CONTRA QUIEN Y QUIEN GANO" << endl;
    cout << "EJEMPLO(podria ser otro depende de la BD): usuario1 1 vs 0 usuario2" << endl;
}

void consultaUsuario::crearPartida()
{
    cout << "Partida creada. Esperando a que alguien se una..." << endl;
    // CONSEGUIR HACER QUE ESPERA A QUE SE UNA ALGUIEN
    cout << "ESPERANDO..." << endl;
    char respuesta;
    cout << "Desea empezar la partida? (s/n): ";
    cin >> respuesta;

    if (respuesta == 's' || respuesta == 'S') {
        cout << "Iniciando partida..." << endl;
        CCM.initializeConnection();
        CCM.initializeSocket();
        CCM.connectToServer();
        jugarAhorcado();
    } else {
        cout << "Esperando a que alguien inicie la partida..." << endl;
    }
}
void consultaUsuario::unirtePartida()
{

}

vector<string> consultaUsuario::cargarPalabras()
{
    vector<string> palabras;
    ifstream archivo("baseDeDatos/palabras.txt");
    string palabra;

    if (archivo.is_open())
    {
        while (getline(archivo, palabra))
        {
            palabras.push_back(palabra);
        }
        archivo.close();
    }

    return palabras;
}

string consultaUsuario::obtenerPalabraAleatoria(const vector<string>& palabras)
{
    int indice = rand() % palabras.size();
    return palabras[indice];
}

void consultaUsuario::imprimirPalabra(const string& palabra, const vector<bool>& letrasAdivinadas)
{
    for (int i = 0; i < palabra.length(); i++)
    {
        if (letrasAdivinadas[i])
            cout << palabra[i] << " ";
        else
            cout << "_ ";
    }
    cout << endl;
}

void consultaUsuario::procesarLetra(char letra, const string& palabra, vector<bool>& letrasAdivinadas, int& intentosRestantes)
{
    bool letraAdivinada = false;

    for (int i = 0; i < palabra.length(); i++)
    {
        if (palabra[i] == letra)
        {
            letrasAdivinadas[i] = true;
            letraAdivinada = true;
        }
    }

    if (!letraAdivinada)
        intentosRestantes--;
}

bool consultaUsuario::todasLetrasAdivinadas(const vector<bool>& letrasAdivinadas)
{
    for (bool letraAdivinada : letrasAdivinadas)
    {
        if (!letraAdivinada)
            return false;
    }
    return true;
}

void consultaUsuario::jugarAhorcado()
{
    srand(static_cast<unsigned>(time(0)));

    vector<string> palabras = cargarPalabras();
    int numPalabras = palabras.size();

    ifstream archivoNumPalabras("numPalabras.txt");
    if (archivoNumPalabras.is_open())
    {
        archivoNumPalabras >> numPalabras;
        archivoNumPalabras.close();
    }

    if (numPalabras == 0 || palabras.empty())
    {
        cout << "No hay palabras disponibles. Asegúrate de que el archivo palabras.txt contenga palabras." << endl;
        return;
    }

    cout << "Bienvenido al juego del ahorcado!" << endl;

    char jugarNuevamente = 's';
    while (jugarNuevamente == 's' || jugarNuevamente == 'S')
    {
        string palabra = obtenerPalabraAleatoria(palabras);
        int longitudPalabra = palabra.length();

        vector<bool> letrasAdivinadas(longitudPalabra, false);
        int intentosRestantes = 6;

        cout << "Adivina la palabra!" << endl;

        while (intentosRestantes > 0 && !todasLetrasAdivinadas(letrasAdivinadas))
        {
            cout << "Intentos restantes: " << intentosRestantes << endl;
            cout << "Palabra: ";
            imprimirPalabra(palabra, letrasAdivinadas);
            cout << endl;

            char opcion;
            cout << "Deseas adivinar una letra (L) o la palabra completa (P)? ";
            cin >> opcion;

            if (opcion == 'L' || opcion == 'l')
            {
                
                char letra;
                cout << "Ingresa una letra: ";
                cin >> letra;
                char cadena[4];
                cadena[0] = letra;
                cadena[1] = '\0';
                char* puntero_cadena = cadena;
                CCM.sendData(1, puntero_cadena);

                procesarLetra(letra, palabra, letrasAdivinadas, intentosRestantes);
            }
            else if (opcion == 'P' || opcion == 'p')
            {
                string palabraAdivinada;
                cout << "Ingresa la palabra completa: ";
                cin >> palabraAdivinada;
                char* palabraAdivinadaChar = new char[palabraAdivinada.length() + 1];
                strcpy(palabraAdivinadaChar, palabraAdivinada.c_str());
                CCM.sendData(2, palabraAdivinadaChar);

                if (palabraAdivinada == palabra)
                {
                    for (size_t i = 0; i < letrasAdivinadas.size(); i++)
                    {
                        letrasAdivinadas[i] = true;
                    }
                    break;
                }
                else
                {
                    cout << "Palabra incorrecta. Pierdes un intento." << endl;
                    intentosRestantes--;
                }
            }
            else
            {
                cout << "Opcion invalida. Por favor, elige 'L' para adivinar una letra o 'P' para adivinar la palabra completa." << endl;
            }
        }

        if (todasLetrasAdivinadas(letrasAdivinadas))
            cout << "Felicidades! Adivinaste la palabra: " << palabra << endl;
        else
            cout << "Oh no, has perdido. La palabra era: " << palabra << endl;

        CCM.closeSocket();

        cout << "Quieres jugar nuevamente? (s/n): ";
        cin >> jugarNuevamente;
        cout << endl;
    }

    cout << "Gracias por jugar!" << endl;
}
