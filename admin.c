#include "admin.h"
#include <stdio.h>
#include <string.h>
#include "sqlite3.h"
#define PALABRA_MAS_LARGA 10
#define NOMBRE_ARCHIVO_PALABRAS "palabras.txt"
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
}

/*char* cargarPalabrasFichero(FILE* archivo, char* palabras) // TO DO ==> HAY QUE HACER MALLOC PARA RESERVAR ESPACIO DE MEMORIA
{
    char *palabra;
    char c;
    char numPalabras = 0;
    archivo = fopen(NOMBRE_ARCHIVO_PALABRAS,"r"); 

   if (archivo == NULL) {
      printf("No se pudieron obtener las palabras.\n");
      return;
   }

    while ((c = fgetc(archivo)) != EOF)
	{
		if (c == '\n')
			numPalabras++;  
		putchar(c);
	}


   fclose(archivo); // Cerrar el archivo 

   return palabras;
}
*/
void anadirPalabra(FILE *archivo, char *palabra)
{
    archivo = fopen("Palabras.txt","a"); /* Abrir archivo en modo lectura */
    char pal[strlen(palabra)];
    strcpy(pal, palabra);
    fprintf(archivo, "%s\n", pal);

    fclose(archivo); /* Cerrar el archivo */
}
void cargarPalabrasBases() // BASES DE DATOS -- Por implementar
{

}


void establecerMaxIntentos(int *numEstablecido, int nuevoNumero)
{
    *numEstablecido = nuevoNumero;
}

