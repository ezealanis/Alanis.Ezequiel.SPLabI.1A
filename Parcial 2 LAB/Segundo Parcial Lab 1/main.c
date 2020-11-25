#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include <time.h>
#include "bicicleta.h"
#include "controller.h"


int main()
{
    srand (time(NULL));
    int guardarOrdenado = 0;
    int tiempoAsignado = 0;
    char seguir = 'n';
    char archivo[51];
    LinkedList* listaBicicletas = ll_newLinkedList();

    do
    {
        switch(menu())
        {
        case 1:
            printf("\nIngrese el nombre del archivo a cargar: ");
            scanf("%s", archivo);
            controller_loadFromText(archivo, listaBicicletas);
            system("pause");
            break;

        case 2:
            if( !ll_isEmpty(listaBicicletas))
            {
                controller_ListarBicicletas(listaBicicletas);
            }
            else
            {
                printf("Primero debe cargar el archivo..\n");
            }
            system("pause");
            break;

        case 3:

            if( !ll_isEmpty(listaBicicletas))
            {
                listaBicicletas = ll_map(listaBicicletas, cambiarTiempo);
                printf("Se asignaron los tiempos.\n");
                tiempoAsignado = 1;
            }
            else
            {
                printf("Primero debe cargar el archivo.\n");
            }
            system("pause");
            break;

        case 4:
            if(!ll_isEmpty(listaBicicletas))
            {
                filtrarPorTipos(listaBicicletas);
            }
            else
            {
                printf("Primero debe cargar el archivo.\n");
            }
            system("pause");
            break;

        case 5:
            if(!ll_isEmpty(listaBicicletas) && tiempoAsignado == 1)
            {
                controller_sortBicicletas(listaBicicletas);
                guardarOrdenado = 1;
            }
            else
            {
                printf("Primero debe cargar el archivo y debe asignar los tiempos.\n");
            }
            system("pause");
            break;

        case 6:
            if(!ll_isEmpty(listaBicicletas) && guardarOrdenado == 1)
            {
                controller_guardarComoTexto("bicisOrdenadas.csv", listaBicicletas);
                printf("Se genero el archivo bicisOrdenadas.csv\n");
            }
            else
            {
                printf("Primero debe cargar el archivo y ordenarlo.\n");
            }
            system("pause");
            break;

        case 7:
            printf("Presione 's' para confirmar la salida: ");
            fflush(stdin);
            scanf("%c", &seguir);
            break;

        default:
            printf("\nOpcion invalida.\n\n");
            system("pause");
            break;
        }

    }
    while(seguir != 's');

    ll_deleteLinkedList(listaBicicletas);

    return 0;
}
