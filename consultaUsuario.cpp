#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include "consultaUsuario.h"
#include "partidaUsuario.h"
extern "C"
{
#include "baseDeDatos/gestorBD.h"
}

using namespace std;

void consultaUsuario::iniciar()
{
    char respuesta;
    bool respuestaValida = false;
    CCM = clientConnectionManager();

    while (!respuestaValida)
    {
        cout << "Confirme si es un usuario existente o no (s/n): ";
        cin >> respuesta;

        if (respuesta == 's' || respuesta == 'S')
        {
            cout << "Interfaz de iniciar usuario" << endl;

            respuestaValida = logInUsuario();
            // respuestaValida = true;
        }
        else if (respuesta == 'n' || respuesta == 'N')
        {
            cout << "Interfaz de registrar usuario" << endl;

            respuestaValida = registrar();
            // respuestaValida = true;
        }
        else
        {
            cout << "Respuesta invalida. Por favor, introduce 's' o 'n'." << endl;
        }
    }
    menuUsuario();
}

bool consultaUsuario::registrar()
{
    char usuarioNombre[50];
    char contrasenya[50];
    int usuarioID;

    cout << "Ingrese el nombre de usuario que desee: ";
    cin >> usuarioNombre;

    cout << "Ingrese su contrasenya: ";
    cin >> contrasenya;

    insertarUsuario(usuarioNombre, contrasenya);

    usuarioID = logIn(usuarioNombre, contrasenya);

    if (usuarioID >= 0)
    {

        usuario = informacionUsuario(usuarioID);

        return true;
    }
    cout << "Fallo al identificar usuario" << endl;
    return false;
}

void consultaUsuario::menuUsuario()
{
    bool open = true;
    do
    {
        int victorias= partidasGanadas(usuario->id);
        int derrotas = partidasPerdidas(usuario->id);

        cout << "-----------------------------" << endl;
        cout << "   Ahorcado The Game" << endl;
        cout << "-----------------------------" << endl;
        cout << "Victorias: " << victorias << endl;
        cout << "Derrotas: " << derrotas << endl;
        cout << "-----------------------------" << endl;
        cout << "Opciones:" << endl;
        cout << "1. Crear una partida" << endl;
        
        cout << "2. Ver historial de ultima partida" << endl;
        cout << "3. Cerrar sesion" << endl;
        cout << "-----------------------------" << endl;

        int opcion;
        cout << "Ingrese el numero de opcion deseada: ";
        cin >> opcion;

        switch (opcion)
        {
        case 1:
            cout << "Creando una partida..." << endl;
            crearPartida();
            break;
        
        case 2:
            cout << "Viendo historial de ultima partida..." << endl;
            imprimirUltimaPArtida(usuario->id);
            break;
        case 3:
            cout << "Cerrando sesion..." << endl;
            open = false;
            break;
        default:
            cout << "Opcion invalida." << endl;
            break;
        }
    } while (open);
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

    if (respuesta == 's' || respuesta == 'S')
    {
        cout << "Iniciando partida..." << endl;
        CCM.initializeConnection();
        CCM.initializeSocket(SERVER_PORT_1);
        CCM.connectToServer();

        /*Pruebas para ver si enviaría un userID*/

        int userID = usuario->id;
        char userIDchar[20];
        string str = to_string(userID);
        strcpy(userIDchar, str.c_str());
        CCM.sendData(0, userIDchar);
        /*Final de prueba*/
        int bytes = recv(CCM.s, CCM.recvBuff, sizeof(CCM.recvBuff), 0);
        if (bytes > 0)
        {
            
            printf("Longitud de la palabra: %s \n", CCM.recvBuff);
            int numLetrasPalabra = stoi(CCM.recvBuff);
            CCM.partidaUsuario = new PartidaUsuario(numLetrasPalabra);
            
        }

        jugarAhorcado();
    }
    else
    {
        cout << "Esperando a que alguien inicie la partida..." << endl;
    }
}


vector<string> consultaUsuario::cargarPalabras()
{
    vector<string> palabras;
    ifstream archivo("palabras.txt");
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

string consultaUsuario::obtenerPalabraAleatoria(const vector<string> &palabras)
{
    int indice = rand() % palabras.size();
    return palabras[indice];
}

void consultaUsuario::imprimirPalabra(const string &palabra, const vector<bool> &letrasAdivinadas)
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

void consultaUsuario::procesarLetra(char letra, const string &palabra, vector<bool> &letrasAdivinadas, int &intentosRestantes)
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

bool consultaUsuario::todasLetrasAdivinadas(const vector<bool> &letrasAdivinadas)
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

    string palabra = obtenerPalabraAleatoria(palabras);
    int longitudPalabra = palabra.length();

    vector<bool> letrasAdivinadas(longitudPalabra, false);
    int intentosRestantes = 6;

    cout << "Adivina la palabra!" << endl;

    bool jugando = true;
    while (CCM.partidaUsuario->vidas > 0 && jugando)
    {
        cout << "Intentos restantes: " << CCM.partidaUsuario->vidas << endl;

        //  imprimirPalabra(palabra, letrasAdivinadas);
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
            char *puntero_cadena = cadena;
            CCM.sendData(1, puntero_cadena);

            // int bytes = recv(CCM.s, CCM.recvBuff, sizeof(CCM.recvBuff), 0);
            // cout<<CCM.recvBuff<<endl;

            do
            {

                int bytes = recv(CCM.s, CCM.recvBuff, sizeof(CCM.recvBuff), 0);

                if (bytes > 0)
                {

                    printf("Esperando respuesta... \n");
                    

                    if (CCM.recvBuff[0] == 'N' || CCM.recvBuff[0] == 'Y')
                    {

                        if (CCM.recvBuff[0] == 'Y')
                        {
                            const char *delimiter = "-";
                            const char *datos = strchr(CCM.recvBuff, *delimiter);

                            CCM.partidaUsuario->actualizar(datos + 1);
                        }
                        else
                        {
                            CCM.partidaUsuario->vidas--;
                        }
                        CCM.partidaUsuario->imprimir_ahorcado();
                        cout << (CCM.recvBuff + 2) << endl;
                        break;
                    }
                }

            } while (1);

            // QUITARprocesarLetra(letra, palabra, letrasAdivinadas, intentosRestantes);
        }
        else if (opcion == 'P' || opcion == 'p')
        {
            string palabraAdivinada;
            cout << "Ingresa la palabra completa: ";
            cin >> palabraAdivinada;
            char *palabraAdivinadaChar = new char[palabraAdivinada.length() + 1];
            strcpy(palabraAdivinadaChar, palabraAdivinada.c_str());
            CCM.sendData(2, palabraAdivinadaChar + '\0');

            do
            {

                int bytes = recv(CCM.s, CCM.recvBuff, sizeof(CCM.recvBuff), 0);

                if (bytes > 0)
                {

                    printf("Esperando respuesta... \n");
                   

                    if (CCM.recvBuff[0] == 'N' || CCM.recvBuff[0] == 'Y')
                    {
                        if (CCM.recvBuff[0] == 'Y')
                        {
                            cout << usuario->nombre << " ha ganado la partida.";
                            jugando = false;
                            sprintf(CCM.sendBuff, "x");
                            send(CCM.s, CCM.sendBuff, sizeof(CCM.sendBuff), 0);
                            
                        }
                        else
                        {
                            CCM.partidaUsuario->vidas--;
                            CCM.partidaUsuario->imprimir_ahorcado();
                            cout << (CCM.recvBuff + 2) << endl;
                        }

                        break;
                    }
                }
            } while (1);
        }
        else
        {
            cout << "Opcion invalida. Por favor, elige 'L' para adivinar una letra o 'P' para adivinar la palabra completa." << endl;
        }
    }
    if(CCM.partidaUsuario->vidas == 0)
    {
        sprintf(CCM.sendBuff, "X");
        send(CCM.s, CCM.sendBuff, sizeof(CCM.sendBuff), 0);
    }
    CCM.closeSocket();

    cout << "Gracias por jugar!" << endl;
}

bool consultaUsuario::logInUsuario()
{
    char usuarioNombre[50];
    char contrasenya[50];
    int usuarioID;
    cout << "Ingrese su nombre de usuario: ";
    cin >> usuarioNombre;
    cout << "Ingrese su contrasenya: ";
    cin >> contrasenya;
    usuarioID = logIn(usuarioNombre, contrasenya);
    if (usuarioID >= 0)
    {
        usuario = informacionUsuario(usuarioID);
        return true;
    }
    cout << "Fallo en el login" << endl;
    return false;
}
