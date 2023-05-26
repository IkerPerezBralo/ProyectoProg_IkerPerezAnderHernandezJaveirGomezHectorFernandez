#ifndef PARTIDA_H_
#define PARTIDA_H_

#ifndef USUARIO_H_
extern "C"{
    #include "baseDeDatos/usuario.h"
}
#endif

class Partida{
    private:
        int id;
    public:
        
        int turno;//1 indica que el jugador 1 es el que teine que actuar, 2 significa que el jugador 2
        Usuario* usuario1;
        Usuario* usuario2;

        char* palabraElegida;
        char* progresoPalabra;

        Partida(int user1id);
        ~Partida();

        int comprobarLetra(char letra);
        int comprobarPalabra(const char* palabra);
        void setUsuario2(int user2id);
};

#endif