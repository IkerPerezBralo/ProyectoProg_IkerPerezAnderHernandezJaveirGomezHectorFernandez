#ifndef USUARIO_H_
#include "usuario.h"
#endif

#ifndef GESTORBD_H_
#define GESTORBD_H_



int insertarUsuario(char *usuario, char *pass);
int logIn(char *usuario, char *pass);
int deleteUser(int userID);
int listarUsuariosBD(Usuario* outUsers);
int listarUsuariosPagina(Usuario** outUsers,int pagina);
int editarUsuario(int usID,char *usuario);
Usuario* informacionUsuario(int userID);
int clearTablaPalabra();
int insertarPalabra(char* palabra);
int borrarPalabraBD(char* palabra);
char* palabraRandom();
int totalPalabras();

#endif