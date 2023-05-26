#ifndef PARTIDA_USU_H_
#define PARTIDA_USU_H_

class PartidaUsuario{
    private:
        
    public:
        int vidas;
        char* palabra;

        PartidaUsuario(int palabraSize);
        ~PartidaUsuario();
        
        void actualizar(const char* progreso);
        void imprimir_ahorcado();
};

#endif