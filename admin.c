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
    printf("\nBienvenido al sistema de administracion de Ahorcado - The Game.\n");
    do {
        printf("\nSeleccione una opcion:\n");
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

void borrarPalabra(FILE* archivo) {
    archivo = fopen(NOMBRE_ARCHIVO_PALABRAS, "r+");
    FILE* archivoDeNumPalabras;
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return;
    }
    
    char palabra[PALABRA_MAS_LARGA];
    char palabraABuscar[PALABRA_MAS_LARGA];
    printf("Ingrese la palabra a borrar: ");
    fgets(palabraABuscar, PALABRA_MAS_LARGA, stdin);
    sscanf(palabraABuscar, "%s", palabraABuscar);
    printf(palabraABuscar);
    
    // Buscar la palabra en el archivo y eliminarla
    char linea[PALABRA_MAS_LARGA];
    int contador = 1;
    while (fgets(linea, PALABRA_MAS_LARGA, archivo) != NULL) {
        char palabraTemp[PALABRA_MAS_LARGA];
        sscanf(linea, "%s", palabraTemp);
        printf(palabraTemp);
        if (strcmp(palabraTemp, palabraABuscar) == 0) {
            fseek(archivo, -(strlen(linea)+1), SEEK_CUR);
            for (int i = 0; i < strlen(linea); i++) {
                fputc(' ', archivo);
            }
            fclose(archivo);
            aumentarNumPalabras(archivoDeNumPalabras, -1);
            printf("La palabra ha sido borrada del archivo.\n");
            return;
        }
        contador++;
    }
    
    // Si la palabra no se encontró en el archivo, mostrar un mensaje de error
    fclose(archivo);
    printf("La palabra ingresada no fue encontrada en el archivo.\n");
}

void borrarPalabra2(FILE* archivo) {
    
    FILE* archivoDeNumPalabras;
    FILE* archivoAuxiliar;
    archivo = fopen(NOMBRE_ARCHIVO_PALABRAS, "r+");
    archivoAuxiliar = fopen("temp.txt", "w");

    if (archivo == NULL || archivoAuxiliar == NULL) 
    {
        printf("No se pudo abrir el archivo.\n");
        return;
    }
    
    char palabra[PALABRA_MAS_LARGA + 3];//El más 3 es para evitar problemas de que haya algun caracter extra 
    char palabraABuscar[PALABRA_MAS_LARGA];
    char c;
    printf("Ingrese la palabra a borrar: ");
    fgets(palabraABuscar, PALABRA_MAS_LARGA, stdin);
    sscanf(palabraABuscar, "%s", palabraABuscar);
    
    int i = 0;
    while((c = fgetc(archivo)) != EOF)
    {
        if(c == ' ' || c == '\n'){
            palabra[i] = '\0'; //Señala el final de la palabra cuando encuentra el final de la linea
            if(strcmp(palabra, palabraABuscar) != 0)
            {
                fprintf(archivoAuxiliar, "%s\n", palabra);
            }else
            {
                aumentarNumPalabras(archivoDeNumPalabras, -1);
            }
            i = 0;
        }else
        {   

            palabra[i] = c;
            i++;
        }
    }
    

    
    fclose(archivo);
    fclose(archivoAuxiliar);
    remove(NOMBRE_ARCHIVO_PALABRAS);
    rename("temp.txt",NOMBRE_ARCHIVO_PALABRAS);


    printf("Eliminada con exito.\n");


    }
    
   
