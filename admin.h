#ifndef ADMIN_H_
#define ADMIN_H_
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

void imprimir_ahorcado(int num_intento);
void anadirPalabra(FILE *archivo);
char* cargarPalabrasFichero(FILE* archivo, char* palabras);
void cargarPalabrasBases(); // BASES DE DATOS -- Por implementar

void establecerMaxIntentos(int *numEstablecido, int nuevoNumero);
char* palabraAleatoria(FILE* archivo,  int numPalabras);
int conseguirNumeroPalabras(FILE* archivoNumPalabras);
void aumentarNumPalabras(FILE* archivoNumpalabras,int cantAaumentar);

int menu();
int menuGestionUsuarios();

void borrarPalabra2(FILE* archivo);

void anadirUsuarioConsola();
void borrarUsuarioConsola();
void listarUsuarioConsola();
void editarUsuarioConsola();

void imprimirPagina(int pagina);
void listadoDePalabras();

#endif 