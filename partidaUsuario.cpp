#include<iostream>
#include "partidaUsuario.h"

PartidaUsuario::PartidaUsuario(int palabraSize){
    vidas=6;
    palabra = new char[palabraSize+1];
}

PartidaUsuario::~PartidaUsuario(){
    delete palabra;
}

void PartidaUsuario::actualizar(const char* progreso){
    for(int i=0;palabra[i]!='\0';i++){
        palabra[i]=progreso[i];
    }
}

void PartidaUsuario::imprimir_ahorcado() {
    switch (vidas) {
        case 6:
            std::cout << "  +---+" << std::endl;
            std::cout << "  |   |" << std::endl;
            std::cout << "      |" << std::endl;
            std::cout << "      |" << std::endl;
            std::cout << "      |" << std::endl;
            std::cout << "      |" << std::endl;
            std::cout << "=========" << std::endl;
            break;

        case 5:
            std::cout << "  +---+" << std::endl;
            std::cout << "  |   |" << std::endl;
            std::cout << "  O   |" << std::endl;
            std::cout << "      |" << std::endl;
            std::cout << "      |" << std::endl;
            std::cout << "      |" << std::endl;
            std::cout << "=========" << std::endl;
            break;

        case 4:
            std::cout << "  +---+" << std::endl;
            std::cout << "  |   |" << std::endl;
            std::cout << "  O   |" << std::endl;
            std::cout << "  |   |" << std::endl;
            std::cout << "      |" << std::endl;
            std::cout << "      |" << std::endl;
            std::cout << "=========" << std::endl;
            break;

        case 3:
            std::cout << "  +---+" << std::endl;
            std::cout << "  |   |" << std::endl;
            std::cout << "  O   |" << std::endl;
            std::cout << " /|   |" << std::endl;
            std::cout << "      |" << std::endl;
            std::cout << "      |" << std::endl;
            std::cout << "=========" << std::endl;
            break;

        case 2:
            std::cout << "  +---+" << std::endl;
            std::cout << "  |   |" << std::endl;
            std::cout << "  O   |" << std::endl;
            std::cout << " /|\\  |" << std::endl;
            std::cout << "      |" << std::endl;
            std::cout << "      |" << std::endl;
            std::cout << "=========" << std::endl;
            break;

        case 1:
            std::cout << "  +---+" << std::endl;
            std::cout << "  |   |" << std::endl;
            std::cout << "  O   |" << std::endl;
            std::cout << " /|\\  |" << std::endl;
            std::cout << " /    |" << std::endl;
            std::cout << "      |" << std::endl;
            std::cout << "=========" << std::endl;
            break;

        case 0:
            std::cout << "  +---+" << std::endl;
            std::cout << "  |   |" << std::endl;
            std::cout << "  O   |" << std::endl;
            std::cout << " /|\\  |" << std::endl;
            std::cout << " / \\  |" << std::endl;
            std::cout << "      |" << std::endl;
            std::cout << "=========" << std::endl;
            break;
    }
}