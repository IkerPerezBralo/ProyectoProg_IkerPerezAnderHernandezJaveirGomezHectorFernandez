#include "usuario.h"
#include <stdio.h>

void imprimirUsuario(Usuario* user){
    
    printf("%d - %s\n",user->id,user->nombre);
    
}