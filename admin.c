#include "admin.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sqlite3.h"
#include <unistd.h>
#include "gestorBD.h"
#define PALABRA_MAS_LARGA 15
#define NOMBRE_ARCHIVO_PALABRAS "palabras.txt"
#define ARCHIVO_NUM_PALABRAS "numPalabras.txt"
#define LONG_MAX_NUM_PALABRAS 4 //Longitud maxima del numero que representa el numero de palabras en el fichero

int menu(){
    int opcion;
    FILE* archivoPalabras;
    FILE* archivoNumeroPalabras;
    printf("\nBienvenido al sistema de administracion de Ahorcado - The Game.\n");
    do {
        printf("\nSeleccione una opcion:\n");
        printf("1. Iniciar partida (mantenimiento)\n");
        printf("2. Insertar palabra\n");
        printf("3. Borrar palabra\n");
        printf("4. Navegar por la lista de palabras\n");
        printf("5. Gestion de usuarios\n");
        printf("0. Salir\n");
        scanf("%d", &opcion);
        switch(opcion) {
            case 1:
                
                break;
            case 2:
                anadirPalabra(archivoPalabras);
                
                break;
            case 3:
                borrarPalabra2(archivoPalabras);
                
                break;
            case 4:
                listadoDePalabras();
                
                break;
            case 5:
                menuGestionUsuarios();
                
                break;
            case 0:
                printf("Saliendo del sistema de administracion...\n");
                break;
            default:
                printf("Opcion invalida, por favor seleccione de nuevo.\n");
        }
    } while(opcion != 0);
}

int menuGestionUsuarios(){
      int opcion;
    printf("\nSistema de Gestion de Usuarios de Ahorcado - The Game.\n");
    do {
        printf("\nSeleccione una opcion:\n");
        printf("1. Crear Usuario\n");
        printf("2. Borrar Usuario\n");
        printf("3. Cambiar Nombre de Usuario\n");
        printf("4. Cambiar Contrasenya\n");
        printf("0. Salir\n");
        scanf("%d", &opcion);
        switch(opcion) {
            case 1:
                anadirUsuarioConsola();
                break;
            case 2:
                borrarUsuarioConsola();
                break;
            case 3:
                
                break;
            case 4:
                
                break;
            case 5:
               
                break;
            case 0:
                printf("Volviendo al menu anterior\n");
                break;
            default:
                printf("Opcion invalida, por favor seleccione de nuevo.\n");
        }
        
    } while(opcion != 0);
}

void borrarUsuarioConsola(){
    int userID;
    printf("ID del usuario a borrar: ");
    scanf("%d", &userID);
    switch (deleteUser(userID))
    {
        case 1:
            printf("Usuario borrado correctamente");
            break;
        case -1:
            printf("Error en el prepared statement");
            break;
        case -2:
            printf("No existe el usuario");
            break;
    }
        
}

void anadirUsuarioConsola(){
    char usuario[PALABRA_MAS_LARGA];
    char contrasenya[PALABRA_MAS_LARGA];
    printf("Nombre de usuario: ");
    scanf("%s", usuario);
    printf("Password: ");
    scanf("%s", contrasenya);
    switch (insertarUsuario(usuario, contrasenya))
    {
    case -1:
        printf("Error en la BBDD");
        break;
    case -2:
        printf("Error al insertar en la BBDD");
        break;
    default:
        printf("Usuario insertado correctamente");
        break;
    }
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



void anadirPalabra(FILE *archivo)
{
    char palabraAnadir[PALABRA_MAS_LARGA];
    printf("Ingrese la palabra a anadir: ");
    scanf("%s", palabraAnadir);
    archivo = fopen("Palabras.txt","a"); /* Abrir archivo en modo lectura */
    char pal[strlen(palabraAnadir)];
    strcpy(pal, palabraAnadir);
    fprintf(archivo, "%s\n", pal);
    fclose(archivo); /* Cerrar el archivo */
    aumentarNumPalabras(archivo, 1);
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
    //printf("El numero de palabras es: %d\n", num);

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
    scanf("%s", palabraABuscar);
    
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
                printf("Eliminada con exito.\n");
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
    }



    void imprimirPagina(int pagina)
{
    FILE* f;
    f = fopen(NOMBRE_ARCHIVO_PALABRAS, "r");
    int contadorPalabras = conseguirNumeroPalabras(f);
    double numPags = contadorPalabras / 10;

    if(contadorPalabras % 10 != 0 )
    {
        numPags++;
    }

    int primeraPalabra = pagina*10;
    int ultimaPalabra = primeraPalabra + 10;

    char palabra[PALABRA_MAS_LARGA];
    char c;
    int i = 0;
    while ((c = fgetc(f)) != EOF && i <= ultimaPalabra && i<= contadorPalabras)
    {
        if (c == ' ' || c == '\n')
        {
            i++;
        }
        if(i>=primeraPalabra && i <= ultimaPalabra)
        {
            printf("%c", c);
        }

    }
        printf("\n");
    fclose(f);    
    
}






    void listadoDePalabras()
    {
        FILE* archivo;
         int opcion;
         int numPagina = 0;
         int pagMax = (conseguirNumeroPalabras(archivo) / 10); 
    
    do {
        printf("\nLISTA DE PALABRAS - PAG%i\n", numPagina);
        imprimirPagina(numPagina);
        if(numPagina <= 0)
        {
            printf("\n -------------------------  x. Atras / 2. Siguiente\n");
         } 
         else if(numPagina >= pagMax)
         {
            printf("\n -------------------------  1. Atras / x. Siguiente\n");
         }
        else
        {
            printf("\n -------------------------  1. Atras / 2. Siguiente\n");
        }
         
        printf("0. Volver al menu\n");
        scanf("%d", &opcion);
        switch(opcion) {
            case 1:
                if(numPagina > 0){
                    numPagina--;
                }
                break;
            case 2:
            if(numPagina <  pagMax)
                numPagina++;
                
                break;
            
            case 0:
                
                break;
            default:
                printf("Opcion invalida, por favor seleccione de nuevo.\n");
        }
    } while(opcion != 0);

    }
    
   
