#ifndef ADMIN_H_
#define ADMIN_H_
#include <stdlib.h>
#include <stdio.h>

void imprimir_ahorcado(int num_intento);
void anadirPalabra(FILE *archivo, char *palabra);
char* cargarPalabrasFichero(FILE* archivo, char* palabras);
void cargarPalabrasBases(); // BASES DE DATOS -- Por implementar

void establecerMaxIntentos(int *numEstablecido, int nuevoNumero);

#endif 