#include "multmatrix_imp.h"

multMatrix_imp::multMatrix_imp(int clientID)
{
    char *buffer;
    this->clientID=clientID;
    multMatrix = new multMatrix();
}

void multMatrix_imp::recvOP(){
    int op = -1, bufLen;
    char* buffer;
    recvMSG(clientID, (void**)&buffer, &bufLen);
    op=((int*)buffer)[0];
    delete[] buffer;

    switch(op){
       case OP_READMATRIX:{
            char *nombre, *data;
            int len;
            unsigned long int datalen;
            matrix_t *result;
            recvMSG(clientID, (void**)&nombre, &len);
            result = multMatrix->readMatrix(nombre);
            sendMatrix(clientID, result);
        break;
        }
        case OP_WRITEMATRIX:{
            matrix_t *m1, *m2, *result;
            m1 = recvMatrix(clientID);
            m2 = recvMatrix(clientID);
            result = multMatrix->multMatrices(m1, m2);
            sendMatrix(clientID, result);
        break;
        }
        case OP_MULTMATRICES:{
            char *nombre, *data;
            int len;
            unsigned long int datalen;
            matrix_t *result;
            recvMSG(clientID, (void**)&nombre, &len);
            result = recvMatrix(clientID);
            multMatrix->writeMatrix(result, nombre);
        break;
        }
        case OP_IDENTITY:{
            matrix_t *result;
            int rows, cols, bufLen;
            char* buffer;
            recvMSG(clientID, (void**)&buffer, &bufLen);
            rows = ((int*)buffer)[0];
            recvMSG(clientID, (void**)&buffer, &bufLen);
            cols = ((int*)buffer)[0];
            result = multMatrix->createIdentity(rows, cols);
            sendMatrix(clientID, result);
        break;
        }
        case OP_RANDOM:{
            matrix_t *result;
            int rows, cols;
            char* buffer;
            int bufLen;
            recvMSG(clientID, (void**)&buffer, &bufLen);
            rows = ((int*)buffer)[0];
            recvMSG(clientID, (void**)&buffer, &bufLen);
            cols = ((int*)buffer)[0];
            result = multMatrix->createRandMatrix(rows, cols);
            sendMatrix(clientID, result); 
        break;
        }
        case OP_EXIT:{    
            exit = true;
        break;
        }
        default:{      
            std::cout<<"ERROR SWITCH DEFAULT"<<std::endl;
            break;
        }
    }
}
    
multMatrix_imp::~multMatrix_imp(){
    delete multMatrix; 
    closeConnection(clientID);
}


