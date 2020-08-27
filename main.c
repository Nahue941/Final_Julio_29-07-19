#include "main.h"



int main()
{
    crearOriginal(ORIGINAL);
    crearCodificado(CODIFIC, ORIGINAL);

    if(!leerYDecodificar(DECODIF, CODIFIC))
        puts("ERROR - decodificando el archivo.");

    if(!leerYReordenar(REORDEN, DECODIF))
        puts("ERROR - reordenando el archivo.");

    return 0;
}


