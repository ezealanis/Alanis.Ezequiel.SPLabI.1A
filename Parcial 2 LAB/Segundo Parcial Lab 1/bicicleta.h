#include "LinkedList.h"
#ifndef BICICLETA_H_INCLUDED
#define BICICLETA_H_INCLUDED

typedef struct
{
    int id_bike;
    char nombre[30];
    char tipo[20];
    int tiempo;
}eBicicleta;

#endif // BICICLETA_H_INCLUDED

int menu();
eBicicleta* nuevaBicicleta();
eBicicleta* nuevaBicicletaParam(char* id_bikeStr, char* nombre, char* tipo, char* tiempoStr);
int bicicleta_setId_bike(eBicicleta* this, int id_bike);
int bicicleta_setNombre(eBicicleta* this, char* nombre);
int bicicleta_setTipo(eBicicleta* this, char* tipo);
int bicicleta_setTiempo(eBicicleta* this, int tiempo);
int bicicleta_getTiempo(eBicicleta* this, int* tiempo);
int bicicleta_getTipo(eBicicleta* this, char* tipo);
void borrarBici(eBicicleta* this );
int mostrarBicicleta(eBicicleta* this);
void* cambiarTiempo(void* this);
int elegirTipo();
void filtrarPorTipos(LinkedList* this);
int esTipoBMX(void* this);
int esTipoPlayera(void* this);
int esTipoPaseo(void* this);
int esTipoMtb(void* this);
int compararBicicletasPorTipoyTiempo(void* biciA,void* biciB);

