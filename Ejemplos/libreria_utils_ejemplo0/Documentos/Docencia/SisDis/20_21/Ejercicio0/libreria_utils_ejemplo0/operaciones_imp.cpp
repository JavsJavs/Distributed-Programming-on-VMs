#include "operaciones_imp.h"
#include "operaciones_stub.h"
#include "utils.h"
#include <string.h>


operaciones_imp::operaciones_imp(int clientID)
{
    this->clientID=clientID;//waitForConnections(server_fd);
    op=new operaciones();
}


void operaciones_imp::recvOP()
{
    int op=-1;
    char* buff;
    int bufLen;
    recvMSG(clientID,(void**)&buff,&bufLen);
    op=((int*)buff)[0];
    delete[] buff;

    switch(op)
    {
    case OP_SUMA:
    {
        int op1=0;
        int op2=0;
        recvMSG(clientID,(void**)&buff,&bufLen);

        op1=((int*)buff)[0];
        delete[] buff;

        recvMSG(clientID,(void**)&buff,&bufLen);
        op2=((int*)buff)[0];
        delete[] buff;

        int res=this->op->suma(op1,op2);
        sendMSG(clientID,(void*)&res,sizeof(int));

        break;
    }
    case OP_LEEFICHERO:
    {        recvMSG(clientID,(void**)&buff,&bufLen);
        char* data=this->op->leeFichero(buff);
        sendMSG(clientID,data,strlen(data));
        delete[] data;
        delete[] buff;
        break;}

    case OP_FIN:
    {    salir=true;
        break;
    }
    default:
    {      printf("ERROR OP NO DEFINIDA: %d\n",op);
        break;
    }
    }
}

operaciones_imp::~operaciones_imp()
{

    closeConnection(clientID);

  delete op;
}
