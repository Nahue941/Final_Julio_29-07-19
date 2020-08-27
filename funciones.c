#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "funciones.h"


/** ------------------------------x----o----x------------------------------ **/
/** DEBE RESOLVER SU PROPIA VERSIÓN DE LAS SIGUIENTE FUNCIONES
 **     Y DE TODAS LAS FUNCIONES QUE UTILICE
 **/

int leerYDecodificar(const char *archSal, const char *archEnt)
{
    FILE* fpSal = fopen(archSal, "w");
    if (!fpSal)
        return 0;
    FILE* fpEnt = fopen(archEnt, "r");
    if (!fpEnt)
        return 0;

    char cadLectura[TAM_CAD];//Cadena para leer del archivo de entrada.

    while (fgets(cadLectura, TAM_CAD, fpEnt)){
        decodificarCadena(cadLectura);
        ordenarCadena(cadLectura);
        fputs(cadLectura, fpSal);
        fputc('\n',fpSal);
    }
    fclose(fpEnt);
    fclose(fpSal);

    return 1;
}


int leerYReordenar(const char *archSal, const char *archEnt)
{
    FILE* fpEnt = fopen(archEnt, "r");
    FILE* fpSal = fopen(archSal, "w");

    if(!fpEnt)
        return 0;//Mensaje de error
    if(!fpSal)
        return 0;//Mensaje de error

    tPila pila;
    crear_pila(&pila);
    tCola cola;
    crearCola(&cola);

    tInfo lectura;

    while(fgets(lectura.linea, TAM_CAD, fpEnt)){
        int bandera = -1;
        bandera = cargarLinea(lectura.linea, &pila, &cola);
        descargarLinea(lectura.linea, &pila, &cola, bandera);

        fputs(lectura.linea, fpSal);
        fputc('\n',fpSal);
        }

    fclose(fpEnt);
    fclose(fpSal);

    return 1;
}

void crear_pila(tPila * pp)
{
    *pp = NULL;
}

int poner_en_pila(tPila *pp, const tInfo *d)
{
    tNodo* nue = (tNodo*)malloc(sizeof(tNodo));

    if(!nue){
        free(nue);
        return 0;
    }
    memcpy(nue->info.linea, d->linea, sizeof(tInfo));
    nue->sig = *pp;
    *pp = nue;
    return 1;
}


int sacar_de_pila(tPila *pp , tInfo *d)
{
    tNodo* aux = *pp;
    if (!aux)
        return 0;
    *pp = aux->sig;
    memcpy(d->linea, aux->info.linea, sizeof(tInfo));
    free(aux);
    return 1;
}

int pila_vacia(tPila* pp)
{
    if (!*pp)
        return 1;
    return 0;
}
/////////////////////////////////////////////////////
void crearCola(tCola* pc)
{
    pc->frente = NULL;
    pc->fondo = NULL;
}

int ponerEnCola(tCola*pc, const tInfo* d)
{
    tNodo* nue=(tNodo*)malloc(sizeof(tNodo));
    if(!nue){
        free(nue);
        return 0;
    }
    memcpy(nue->info.linea, d->linea, sizeof(tInfo));
    nue->sig = NULL;
    if(!pc->fondo)
        pc->frente=nue;
    else
        pc->fondo->sig=nue;
    pc->fondo=nue;
    return 1;
}

int sacarDeCola_(tCola*pc, tInfo* d)
{
    tNodo* aux = pc->frente;
    if(!aux)
        return 0;
    memcpy(d->linea, aux->info.linea, sizeof(tInfo));
    pc->frente = aux->sig;
    free(aux);
    if(!pc->frente)
        pc->fondo=NULL;
    return 1;
}

int colaVacia (tCola* pc)
{
    return (pc->frente==NULL && pc->fondo==NULL);
}
////////////////////////////////////////////////////

void decodificarCadena (char* cad)
{
    while(*cad){
            if(isNum(*cad)){//se supone que nunca se encuentra un caracter sin numero.
                int num = *cad - '0', cont = 0;
                cad++;
                rotarCadena(cad, cad+num-1);
                while(cont < num){
                    *(cad) = decodificarCaracter(*cad, num);
                    cont++;
                    cad++;
                }
            }
            else
                cad++;
    }
}

void ordenarCadena (char* cad)
{
    int cant;
    char* cadOrd;//puntero a cad Ordenada
    char* mov;//puntero que uso para moverme por la cadena
    char* aux;//puntero auxiliar

    cadOrd = mov = aux = cad;

    while (*mov){
        if(isNum(*mov)){
            cant = *mov - '0';
            aux = mov+1;
            mov += cant + 1;
            for(int i=0; i<cant; i++){
                *cadOrd = *aux;
                cadOrd++;
                aux++;
            }
        }
        else{
            *cadOrd = *mov;
            cadOrd++;
            mov++;
        }
    }
    if(!*mov)
        *(cadOrd - 1)= '\0';
}

int isNum (int x)
{
    return x>= '0' && x<= '9';
}

int isMinus (int x)
{
    return x>='a' && x<='z';
}

int isMayus (int x)
{
    return x>='A' && x<='Z';
}

int isValid (int x)
{
    return (isMinus(x) || isNum(x) || isMayus(x));
}

char decodificarCaracter(char x, int numero)
{
    int sentido = numero%2 == 1? 1:-1;
    if(isNum(x))
        x= x -'0';
    else if(isMayus(x))
        x = x-'A'+10;
    else if(isMinus(x))
        x= x-'a'+36;

    x += numero*sentido;
    if(x>=62)
        x%=62;
    else if(x<0)
        x = 62 + x;

    if(x<=9)
        x+='0';
    else if(x>=10 && x<36)
        x = x+'A'-10;
    else
        x = x+'a'-36;

    return x;
}

void rotarCadena (char* desde, char* hasta)
{
    char aux;
    while (desde<hasta){
        aux = *desde;
        *desde = *hasta;
        *hasta = aux;
        desde++;
        hasta--;
    }
}

void copiarEnCadena (char* dest, const char* origen, int cantVeces)
{
    for(int i=0; i<cantVeces; i++){
        *dest = *origen;
        dest++;
        origen++;
    }
    *dest = '\0';
}

int cargarLinea (char* cad, tPila* pp, tCola* pc)
{
    tInfo aux;
    char* start;
    int cont;
    int f = -1; //Bandera que uso para saber si arranco con un caracter o con una palabra
                //(1) : La cadena arranca con una palabra
                //(0) : La cadena arranca con un caracteres especiales
    while(*cad){
        if(isValid(*cad)){//pongo en pila
            start = cad;
            cont = 0;
            while(isValid(*cad)){
                cont++;
                cad++;
            }
            copiarEnCadena(aux.linea, start, cont);
            poner_en_pila(pp, &aux);
            if(f == -1)
                f = 1;
        }
        else if (*cad){//*cad quiere decir que el caracter tiene que ser distinto al fin de cadena
            start = cad;
            cont = 0;
            while(!isValid(*cad) && *cad){
                cont++;
                cad++;
            }// si es fin de cadena TENER CUIDADO
//            if(!*cad)
//                cont--;
            copiarEnCadena(aux.linea, start, cont);
            ponerEnCola(pc, &aux);
            if(f == -1)
                f = 0;
        }
    }
    return f;
}

void descargarLinea(char* cad, tPila* pp, tCola* pc, int f)
{
    *cad = '\0';
    tInfo aux;
    if (!f && !colaVacia(pc)){
        sacarDeCola_(pc, &aux);
        pegarEnCadena(cad, aux.linea);
    }
    while (!pila_vacia(pp) || !colaVacia(pc)){
        if(!pila_vacia(pp)){
            sacar_de_pila(pp, &aux);
            pegarEnCadena(cad, aux.linea);
        }
        if(!colaVacia(pc)){
            sacarDeCola_(pc, &aux);
            pegarEnCadena(cad, aux.linea);
        }
    }
}

void pegarEnCadena (char* cad, char* aCopiar)
{
    while (*cad)
        cad++;
    while(*aCopiar){
        *cad = *aCopiar;
        cad++;
        aCopiar++;
    }
    *cad = *aCopiar;
}








