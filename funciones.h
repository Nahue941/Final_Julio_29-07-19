#ifndef FUNCIONES_H_
#define FUNCIONES_H_

#include <stdio.h>

#define SIN_MEM 0
#define TODO_OK 1

/**-----------------------------------------------------*/
#define TAM_CAD 500
#define ES_NUM(x) ((x) >= '0' && (x) <= '9' ? 1:0)

int crearOriginal(const char *nomArch);
int crearCodificado(const char *archSal, const char *archEnt);
/** ------------------------------x----o----x------------------------------ **/



/** ------------------------------x----o----x------------------------------ **/

typedef struct
{
    char    linea[101];
} tInfo;


typedef struct sNodo
{
    tInfo           info;
    struct  sNodo  *sig;
} tNodo;

typedef tNodo  *tPila;

typedef struct{
    tNodo* frente;
    tNodo* fondo;
}tCola;

/** FUNCIONES A RESOLVER
 **/

int leerYDecodificar(const char *archSal, const char *archEnt);

int leerYReordenar(const char *archSal, const char *archEnt);

void crear_pila(tPila *);
int poner_en_pila(tPila *,const tInfo *);
int sacar_de_pila(tPila *,tInfo*);
int pila_vacia(tPila*);
////////////////////////////////////////////////
void crearCola(tCola* pc);
int ponerEnCola(tCola* pc, const tInfo* d);
int sacarDeCola_(tCola* pc, tInfo* d);
int colaVacia(tCola* pc);
////////////////////////////////////////////////
void decodificarCadena (char* cad);
void ordenarCadena (char* cad);
int isNum (int x);
char decodificarCaracter(char x, int numero);
void rotarCadena (char* desde, char* hasta);
void copiarEnCadena (char* dest, const char* origen, int cantVeces);
int isMayus (int x);
int isMinus(int x);
int isValid(int x);
int cargarLinea(char* cad, tPila* pp, tCola* pc);
void descargarLinea(char* cad, tPila* pp, tCola* pc, int f);
void pegarEnCadena (char* cad, char* aCopiar);


#endif
