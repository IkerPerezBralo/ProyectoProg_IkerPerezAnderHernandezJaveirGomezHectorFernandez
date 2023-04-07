#ifndef USUARIO_H_
#define USUARIO_H_

typedef struct Usuario{
    int id;
    char* nombre; 
}Usuario;

void imprimirUsuario(Usuario* user);

#endif