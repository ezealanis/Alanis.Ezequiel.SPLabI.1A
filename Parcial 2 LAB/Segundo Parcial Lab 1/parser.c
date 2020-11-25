#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"
#include "bicicleta.h"

int parser_EmployeeFromText(FILE* pFile, LinkedList* pListaBicicletas)
{
    int cantParametros;
    eBicicleta* auxBicicleta;
    int todoOk = -1;
    char buffer[4][100];

    if (pFile != NULL  && pListaBicicletas != NULL)
    {
        fscanf(pFile, "%*[^\n]\n");
        while(!feof(pFile))
        {
            auxBicicleta = nuevaBicicleta();
            cantParametros = fscanf(pFile,"%[^,] , %[^,], %[^,], %[^\n]\n", buffer[0], buffer[1], buffer[2], buffer[3]);
            if(cantParametros == 4)
            {
                auxBicicleta = nuevaBicicletaParam(buffer[0], buffer[1], buffer[2],  buffer[3]);
                ll_add(pListaBicicletas, auxBicicleta);
                todoOk = 1;
            }
        }
    }

    return todoOk;
}

