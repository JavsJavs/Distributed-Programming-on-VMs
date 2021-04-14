#include "operaciones_stub.h"
#include "utils.h"
operaciones_stub::operaciones_stub()
{
     conn=initClient("127.0.0.1",60000);
}

int operaciones_stub::suma(int a, int b)
{
    int result=0;
    int bufferSize=0;
    char* buffer=0x00;

    int op=OP_SUMA;


    sendMSG(0,(void*)&op,sizeof(int));

    sendMSG(0,(void*)&a,sizeof(int));
    sendMSG(0,(void*)&b,sizeof(int));
    recvMSG(0,(void**)&buffer,&bufferSize);

    result=((int*)buffer)[0];

    delete[] buffer;
    return result;
}


char* operaciones_stub::leeFichero(char* nombre)
{

    int bufferSize=0;
    char* buffer=0x00;

    int op=OP_LEEFICHERO;

    sendMSG(0,(void*)&op,sizeof(int));

    sendMSG(0, nombre,strlen(nombre));
    recvMSG(0, (void**)&buffer,&bufferSize);

    return buffer;
}

operaciones_stub::~operaciones_stub()
{
    int op=OP_FIN;
    sendMSG(0,&op,sizeof(int));

    closeConnection(0);
}
