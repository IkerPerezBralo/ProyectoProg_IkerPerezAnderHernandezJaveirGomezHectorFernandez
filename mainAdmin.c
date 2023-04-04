#include "admin.h"
int main(void)
{
    FILE* archivoPalabras;
    FILE* archivoCantidad;
    int opcion;
    //anadirPalabra(archivo, "AMOGUS");
    //printf("%d", conseguirNumeroPalabras(archivo));
    //aumentarNumPalabras(archivo,3);
    //printf("%d", conseguirNumeroPalabras(archivo, 4));
    printf("%s", palabraAleatoria(archivoPalabras, conseguirNumeroPalabras(archivoCantidad)));
    opcion = menu();
    return 0;
}