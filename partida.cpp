#include "partida.h"
#include<string.h>

extern "C"{
    #include "gestorBD.h"
}

Partida::Partida(){
    palabraElegida = palabraRandom();
    int longitud = strlen(palabraElegida);
    progresoPalabra = new char[longitud+1];
    for(int i =0;i<=longitud;i++){
        if(i<longitud){
            progresoPalabra[i]='_';
        } else if (i==longitud){
            progresoPalabra[i] = '\0';
        }
    }
    siguiente=1;
    //TODO Crear partida en BD y conseguir id
}

Partida::~Partida(){
    delete palabraElegida;
    delete progresoPalabra;
}