#ifndef PARTIDA_USU_H_
#define PARTIDA_USU_H_

class PartidaUsuario{
    public:
        
        char* palabra;

        char* palabraElegida;
        char* progresoPalabra;

        PartidaUsuario();

        void inicializar(char* palabra);
        void actualizar(const char* progreso);
};

#endif