#ifndef ADMIN_H_
#define ADMIN_H_
#include <stdlib.h>
#include <stdio.h>

void imprimir_ahorcado(int num_intento);
void cargarPalabras(FILE *archivo);
void anadirPalabra(FILE *archivo, char *palabra);
void cargarPalabras(); // BASES DE DATOS
void establecerMaxIntentos(int num);

#endif 