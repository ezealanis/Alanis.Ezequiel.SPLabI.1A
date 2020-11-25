#include <stdio.h>
#include <stdlib.h>
#include "bicicleta.h"
#include <string.h>
#include "Controller.h"


int menu()
{
    int opcion;

    system("cls");

    printf("**** Menu de bicicletas **** \n\n");
    printf("1. Cargar archivo. \n");
    printf("2. Imprimir lista. \n");
    printf("3. Asignar tiempos.\n");
    printf("4. Filtrar por tipo.\n");
    printf("5. Mostrar posiciones. (ordenadas por tipo y tiempo)\n");
    printf("6. Guardar posiciones. (ordenado)\n");
    printf("7. Salir.\n\n");

    printf("Ingrese opcion: ");
    fflush(stdin);
    scanf("%d", &opcion);

    return opcion;
}

eBicicleta* nuevaBicicleta()
{
    return (eBicicleta*) malloc(sizeof(eBicicleta));
}

eBicicleta* nuevaBicicletaParam(char* id_bikeStr, char* nombre, char* tipo, char* tiempoStr)
{
    eBicicleta*  biciNueva;

    biciNueva = nuevaBicicleta();

    if(biciNueva != NULL)
    {
        bicicleta_setId_bike(biciNueva, atoi(id_bikeStr));
        bicicleta_setNombre(biciNueva, nombre);
        bicicleta_setTipo(biciNueva, tipo);
        bicicleta_setTiempo(biciNueva, atoi(tiempoStr));
    }

    return biciNueva;
}

int bicicleta_setId_bike(eBicicleta* this, int id_bike)
{
    int todoOk = -1;

    if ( this != NULL && id_bike > 1 && id_bike <= 1000)
    {
        this-> id_bike = id_bike;
        todoOk = 1;
    }
    return todoOk;
}

int bicicleta_setNombre(eBicicleta* this, char* nombre)
{
    int todoOk = -1;

    if (this != NULL  && strlen(nombre) >= 3  && strlen(nombre) < 30)
    {
        strcpy(this -> nombre, nombre);
        todoOk = 1;
    }
    return todoOk;
}

int bicicleta_setTipo(eBicicleta* this, char* tipo)
{
    int todoOk = -1;

    if (this != NULL  && strlen(tipo) >= 3  && strlen(tipo) < 20)
    {
        strcpy(this -> tipo, tipo);
        todoOk = 1;
    }
    return todoOk;
}

int bicicleta_setTiempo(eBicicleta* this, int tiempo)
{
    int todoOk = -1;

    if ( this != NULL && tiempo >= 0 && tiempo <= 1000)
    {
        this-> tiempo = tiempo;
        todoOk = 1;
    }
    return todoOk;
}

int bicicleta_getTipo(eBicicleta* this, char* tipo)
{
    int todoOk = -1;
    if (this != NULL && tipo != NULL)
    {
        strcpy(tipo, this -> tipo);
        todoOk = 1;
    }
    return todoOk;

}

int bicicleta_getTiempo(eBicicleta* this, int* tiempo)
{
    int todoOk = -1;
    if (this!= NULL && tiempo != NULL)
    {
        *tiempo = this-> tiempo;
        todoOk =1;
    }
    return todoOk;

}

int mostrarBicicleta(eBicicleta* this)
{
    int todoOk =-1;
    if(this != NULL)
    {
        todoOk = 1;
        printf("%4d  %30s  %20s                     %4d \n", this->id_bike, this->nombre, this-> tipo, this-> tiempo);
    }
    return todoOk;
}

void* cambiarTiempo(void* this)
{
    eBicicleta* auxBicicleta;
    void * retorno = NULL;
    int aleatorio;
    if( this != NULL)
    {
        auxBicicleta= (eBicicleta*) this;
        aleatorio = rand()%(71)+50;
        bicicleta_setTiempo(auxBicicleta, aleatorio);
        retorno = (void*) auxBicicleta;
    }
    return retorno;
}

int elegirTipo()
{
    int opcion;

    system("cls");
    printf("***** Filtrar bicicletas  ***** \n" );
    printf("1. BMX.\n");
    printf("2. Playera.\n");
    printf("3. MTB.\n");
    printf("4. Paseo.\n");

    printf("Ingrese opcion: ");
    fflush(stdin);
    scanf("%d", &opcion);

    return opcion;
}

void filtrarPorTipos(LinkedList* this)
{
    LinkedList* listaFiltrada = NULL;

    switch(elegirTipo())
    {
    case 1:

        listaFiltrada = ll_filter(this, esTipoBMX);
        if( !ll_isEmpty(listaFiltrada))
        {
            controller_guardarComoTexto("bicisBMX.csv", listaFiltrada);
            printf("Se genero el archivo bicisBMX.\n");
        }
        else
        {
            printf("No se genero un archivo ya que no hay bicicletas del tipo BMX.\n");
        }
        system("pause");
        break;

    case 2:
         listaFiltrada = ll_filter(this, esTipoPlayera);
        if( !ll_isEmpty(listaFiltrada))
        {
            controller_guardarComoTexto("bicisPlayeras.csv", listaFiltrada);
            printf("Se genero el archivo bicisPlayeras.\n");
        }
        else
        {
            printf("No se genero un archivo ya que no hay bicicletas del tipo playeras.\n");
        }
        system("pause");
        break;

    case 3:
        listaFiltrada = ll_filter(this, esTipoMtb);
        if( !ll_isEmpty(listaFiltrada))
        {
            controller_guardarComoTexto("bicisMtb.csv", listaFiltrada);
            printf("Se genero el archivo bicisMtb.\n");
        }
        else
        {
            printf("No se genero un archivo ya que no hay bicicletas del tipo MTB.\n");
        }
        system("pause");
        break;

    case 4:
       listaFiltrada = ll_filter(this, esTipoPaseo);
        if( !ll_isEmpty(listaFiltrada))
        {
            controller_guardarComoTexto("bicisPaseo.csv", listaFiltrada);
            printf("Se genero el archivo bicisPaseo.\n");
        }
        else
        {
            printf("No se genero un archivo ya que no hay bicicletas del tipo Paseo.\n");
        }
        system("pause");
      break;

    default:
        printf("Opcion invalida.\n");
        break;
    }
}

int esTipoBMX(void* this)
{
    eBicicleta* auxBicicleta;
    int retorno = 0;
    char tipoBici[20];

    if( this != NULL)
    {
        auxBicicleta= (eBicicleta*) this;

        if (bicicleta_getTipo(auxBicicleta, tipoBici) != -1)
        {
            strlwr(tipoBici);
            if(strcmp(tipoBici, "bmx") == 0)
            {
                retorno =1;
            }
        }

    }
    return retorno;
}

int esTipoPlayera(void* this)
{
    eBicicleta* auxBicicleta;
    int retorno = 0;
    char tipoBici[20];

    if( this != NULL)
    {
        auxBicicleta= (eBicicleta*) this;

        if (bicicleta_getTipo(auxBicicleta, tipoBici) != -1)
        {
            strlwr(tipoBici);
            if(strcmp(tipoBici, "playera")== 0)
            {
                retorno =1;
            }
        }

    }
    return retorno;
}

int esTipoPaseo(void* this)
{
    eBicicleta* auxBicicleta;
    int retorno = 0;
    char tipoBici[20];

    if( this != NULL)
    {
        auxBicicleta= (eBicicleta*) this;

        if (bicicleta_getTipo(auxBicicleta, tipoBici) != -1)
        {
            strlwr(tipoBici);
            if(strcmp(tipoBici, "paseo")== 0)
            {
                retorno =1;
            }
        }

    }
    return retorno;
}

int esTipoMtb(void* this)
{
    eBicicleta* auxBicicleta;
    int retorno = 0;
    char tipoBici[20];

    if( this != NULL)
    {
        auxBicicleta= (eBicicleta*) this;

        if (bicicleta_getTipo(auxBicicleta, tipoBici) != -1)
        {
            strlwr(tipoBici);
            if(strcmp(tipoBici, "mtb")== 0)
            {
                retorno =1;
            }
        }

    }
    return retorno;
}

int compararBicicletasPorTipoyTiempo(void* biciA,void* biciB)
{
    int orden = 0;

    if( biciA != NULL && biciB != NULL )
    {
        eBicicleta* pBiciA = (eBicicleta*) biciA;
        eBicicleta* pBiciB = (eBicicleta*) biciB;
        char tipoBiciA[20];
        char tipoBiciB[20];
        int tiempoBiciA;
        int tiempoBiciB;

        bicicleta_getTipo(pBiciA,tipoBiciA);
        bicicleta_getTipo(pBiciB,tipoBiciB);
        bicicleta_getTiempo(pBiciA, &tiempoBiciA);
        bicicleta_getTiempo(pBiciB, &tiempoBiciB);

        if (strcmp(tipoBiciA, tipoBiciB) > 0 )
        {
            orden = 1;
        }
        else if ( strcmp(tipoBiciA, tipoBiciB) ==0 )
        {
            if(tiempoBiciA > tiempoBiciB)
            {
                orden = 1;
            }
            else
            {
                orden = -1;
            }
        }

    }
    return orden;
}
