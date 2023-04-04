#include "admin.h"
int main(void)
{
    FILE* archivoPalabras;
    FILE* archivoCantidad;
    //anadirPalabra(archivo, "AMOGUS");
    //printf("%d", conseguirNumeroPalabras(archivo));
    //aumentarNumPalabras(archivo,3);
    //printf("%d", conseguirNumeroPalabras(archivo, 4));
    printf("%s", palabraAleatoria(archivoPalabras, conseguirNumeroPalabras(archivoCantidad)));
    menu();
    return 0;
}