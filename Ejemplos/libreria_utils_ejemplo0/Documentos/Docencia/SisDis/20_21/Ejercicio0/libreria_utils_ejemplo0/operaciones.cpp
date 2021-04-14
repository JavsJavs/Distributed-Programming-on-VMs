#include "operaciones.h"
#include <stdio.h>
#include <stdlib.h>


operaciones::operaciones()
{

}

int operaciones::suma(int a, int b)
{
    return a+b;
}

char* operaciones::leeFichero(char* nombre)
{

    char* datos=0x00;
    FILE* f=0x00;
    int dataLen=0;

    f=fopen(nombre,"r");
    if(f!=NULL)
    {
        //averiguar el tamaño de fichero
        fseek(f,0,SEEK_END);
        dataLen=ftell(f);
        fseek(f,0,SEEK_SET);

        datos=new char[dataLen+1];

        fread(datos,1,dataLen,f);
        fclose(f);

        datos[dataLen]='\0';

    }

    return datos;
}
