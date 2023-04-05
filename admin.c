#include "admin.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sqlite3.h"
#include <unistd.h>
#define PALABRA_MAS_LARGA 15
#define NOMBRE_ARCHIVO_PALABRAS "palabras.txt"
#define ARCHIVO_NUM_PALABRAS "numPalabras.txt"
#define LONG_MAX_NUM_PALABRAS 4 //Longitud maxima del numero que representa el numero de palabras en el fichero

int menu(){
    int opcion;
    printf("Bienvenido al sistema de administracion de Ahorcado - The Game.\n");
    do {
        printf("\nSeleccione una opción:\n");
        printf("1. Iniciar partida (mantenimiento)\n");
        printf("2. Insertar palabra\n");
        printf("3. Borrar palabra\n");
        printf("4. Navegar lista de palabras\n");
        printf("0. Salir\n");
        scanf("%d", &opcion);
        switch(opcion) {
            case 1:
                return 1;
                break;
            case 2:
                return 2;
                break;
            case 3:
                return 3;
                break;
            case 4:
                return 4;
                break;
            case 0:
                printf("Saliendo del sistema de administracion...\n");
                break;
            default:
                printf("Opcion invalida, por favor seleccione de nuevo.\n");
        }
    } while(opcion != 0);
}

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
void anadirPalabra(FILE *archivo)
{
    archivo = fopen("Palabras.txt","a"); /* Abrir archivo en modo escritura */
    char pal[100];
    char buffer[1024];
    printf("Ingrese la palabra a añadir al archivo: ");
    fgets(buffer, 1024, stdin);
    sscanf(buffer, "%s", pal);
    fprintf(archivo, "%s\n", pal);
    
    fclose(archivo); /* Cerrar el archivo */
    aumentarNumPalabras(archivo, 1);
}


void cargarPalabrasBases() // BASES DE DATOS -- Por implementar
{

}


void establecerMaxIntentos(int *numEstablecido, int nuevoNumero)
{
    *numEstablecido = nuevoNumero;
}

char* palabraAleatoria(FILE* archivo, int numPalabras)
{
    archivo = fopen(NOMBRE_ARCHIVO_PALABRAS,"r"); 
    
    char palabra[PALABRA_MAS_LARGA];
    int numAleatorio = 0;

    if (archivo == NULL) {
        printf("No se pudieron obtener las palabras.\n");
        return NULL;
    }
    srand(time(NULL));
    numAleatorio = rand() % numPalabras + 1;
    printf("%i\n", numAleatorio);

    // Mover el puntero de archivo al comienzo del archivo
    rewind(archivo);

    for (int i = 1; i <= numPalabras; i++)
    {
        if(i == numAleatorio)
        {
            fgets(palabra,PALABRA_MAS_LARGA, archivo);
            char* palabraTemp = malloc(PALABRA_MAS_LARGA * sizeof(char));
            sscanf(palabra, "%s", palabraTemp);
            fclose(archivo);
            return strdup(palabraTemp);
        } 
        fgets(palabra, PALABRA_MAS_LARGA, archivo);
    }

    fclose(archivo);
    return NULL;
}

int conseguirNumeroPalabras(FILE* archivoNumPalabras)
{
    char c[LONG_MAX_NUM_PALABRAS];
    int num;
    archivoNumPalabras = fopen(ARCHIVO_NUM_PALABRAS, "r");

    fgets(c,LONG_MAX_NUM_PALABRAS, archivoNumPalabras);
    sscanf(c, "%d", &num);
    printf("El numero de palabras es: %d\n", num);

    fclose(archivoNumPalabras);
    return num;
    
}
void aumentarNumPalabras(FILE* archivoNumpalabras,int cantAaumentar)
{   
    //FILE* archivoAux;
    int numPalabras = conseguirNumeroPalabras( archivoNumpalabras);
    numPalabras+= cantAaumentar;

    archivoNumpalabras = fopen(ARCHIVO_NUM_PALABRAS,"w"); 
    fprintf(archivoNumpalabras, "%i\n", numPalabras);

    fclose(archivoNumpalabras);
     
}

void borrarPalabra(FILE *archivo)
{
    
}