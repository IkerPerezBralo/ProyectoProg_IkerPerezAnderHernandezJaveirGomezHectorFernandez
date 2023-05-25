#ifndef PARTIDA_H_
#define PARTIDA_H_

class Partida{
    public:
        int comprobarLetra(char letra);
        int comprobarPalabra(char* palabra);
    private:
        int id;
        int siguiente;//1 indica que el jugador 1 es el que teine que actuar, 2 significa que el jugador 2
        int usuario1;
        int usuario2;

        char* palabraElegida;
        char* progresoPalabra;

        Partida();
        Partida(char* palabra);
        ~Partida();
};

#endif