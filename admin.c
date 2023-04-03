#include "admin.h"
#include <stdio.h>
#include <string.h>
#include "sqlite3.h"
#define PALABRA_MAS_LARGA 10
// Función para imprimir la figura del ahorcado
void imprimir_ahorcado(int intentos) // No se si esto puede ir en administrador o solo en cliente
{
    switch (intentos)
    {
    case 0:
        printf("  +---+\n");
        printf("  |   |\n");
        printf("      |\n");
        printf("      |\n");
        printf("      |\n");
        printf("      |\n");
        printf("=========\n");
        break;

    case 1:
        printf("  +---+\n");
        printf("  |   |\n");
        printf("  O   |\n");
        printf("      |\n");
        printf("      |\n");
        printf("      |\n");
        printf("=========\n");
        break;
    
    case 2:
        printf("  +---+\n");
        printf("  |   |\n");
        printf("  O   |\n");
        printf("  |   |\n");
        printf("      |\n");
        printf("      |\n");
        printf("=========\n");
        break;

    case 3:
        printf("  +---+\n");
        printf("  |   |\n");
        printf("  O   |\n");
        printf(" /|   |\n");
        printf("      |\n");
        printf("      |\n");
        printf("=========\n");
        break;

    case 4:
        printf("  +---+\n");
        printf("  |   |\n");
        printf("  O   |\n");
        printf(" /|\\  |\n");
        printf("      |\n");
        printf("      |\n");
        printf("=========\n");
        break;

    case 5:
        printf("  +---+\n");
        printf("  |   |\n");
        printf("  O   |\n");
        printf(" /|\\  |\n");
        printf(" /    |\n");
        printf("      |\n");
        printf("=========\n");
        break;
    default:
        printf("  +---+\n");
        printf("  |   |\n");
        printf("  O   |\n");
        printf(" /|\\  |\n");
        printf(" / \\  |\n");
        printf("      |\n");
        printf("=========\n");
        break;
    }


    /*
    if (intentos == 0)
    {
        printf("  +---+\n");
        printf("  |   |\n");
        printf("      |\n");
        printf("      |\n");
        printf("      |\n");
        printf("      |\n");
        printf("=========\n");
    }
    else if (intentos == 1)
    {
        printf("  +---+\n");
        printf("  |   |\n");
        printf("  O   |\n");
        printf("      |\n");
        printf("      |\n");
        printf("      |\n");
        printf("=========\n");
    }
    else if (intentos == 2)
    {
        printf("  +---+\n");
        printf("  |   |\n");
        printf("  O   |\n");
        printf("  |   |\n");
        printf("      |\n");
        printf("      |\n");
        printf("=========\n");
    }
    else if (intentos == 3)
    {
        printf("  +---+\n");
        printf("  |   |\n");
        printf("  O   |\n");
        printf(" /|   |\n");
        printf("      |\n");
        printf("      |\n");
        printf("=========\n");
    }
    else if (intentos == 4)
    {
        printf("  +---+\n");
        printf("  |   |\n");
        printf("  O   |\n");
        printf(" /|\\  |\n");
        printf("      |\n");
        printf("      |\n");
        printf("=========\n");
    }
    else if (intentos == 5)
    {
        printf("  +---+\n");
        printf("  |   |\n");
        printf("  O   |\n");
        printf(" /|\\  |\n");
        printf(" /    |\n");
        printf("      |\n");
        printf("=========\n");
    }
    else
    {
        printf("  +---+\n");
        printf("  |   |\n");
        printf("  O   |\n");
        printf(" /|\\  |\n");
        printf(" / \\  |\n");
        printf("      |\n");
        printf("=========\n");
    }
    */
}

char* cargarPalabrasFichero(FILE *archivo, char* palabras) // TO DO ==> HAY QUE HACER MALLOC PARA RESERVAR ESPACIO DE MEMORIA
{
    char *palabra;

   archivo = fopen("Palabras.txt","r"); /* Abrir archivo en modo lectura */

   if (archivo == NULL) {
      printf("No se pudieron obtener las palabras.\n");
      return 1;
   }

   /* Leer el archivo y guardar las palabras en un array*/
   int contador_plb = 0;
   while(fscanf(archivo, "%s", palabra) == 1)
   {
        palabras[contador_plb] = palabra;
        contador_plb++;
   }
   fclose(archivo); /* Cerrar el archivo */

   return *palabras;
}
void anadirPalabra(FILE *archivo, char *palabra)
{
    archivo = fopen("Palabras.txt","r"); /* Abrir archivo en modo lectura */

   if (archivo == NULL) {
      printf("No se pudieron obtener las palabras.\n");
      return 1;
   }
   /* Leer el archivo entero hasta que se le acaben las palabras ya escritas*/
   while(fscanf(archivo, "%s", palabra) == 1)
   {
   }
   /* Una vez leido todas, insertar despues del último la palabra que se desea introducir*/
   fprintf(archivo, "%s\n", palabra);

   fclose(archivo); /* Cerrar el archivo */
}
void cargarPalabrasBases() // BASES DE DATOS -- Por implementar
{

}


void establecerMaxIntentos(int *numEstablecido, int nuevoNumero)
{
    *numEstablecido = nuevoNumero;
}

