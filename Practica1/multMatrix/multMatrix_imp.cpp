#include "multMatrix_imp.h"
#include "matrix_func.h"

multMatrix_imp::multMatrix_imp(int clientID)
{
    char *buffer;
    this->clientID=clientID;
    mMatrix = new multMatrix();
}

void multMatrix_imp::recvOP(){
    int op = -1, bufLen;
    char* buffer;
    recvMSG(clientID, (void**)&buffer, &bufLen);
    op=((int*)buffer)[0];
    delete[] buffer;

    switch(op){
        case OP_WRITE:{

            char *nombre, *data;
            int len;
            unsigned long int datalen;
            matrix_t *result;

            recvMSG(clientID, (void**)&nombre, &len);
            result = receiveMatrix(clientID);
            mMatrix->writeMatrix(result, nombre);
        break;

        }
       case OP_READ:{

            char *nombre, *data;
            int len;
            unsigned long int datalen;
            matrix_t *result;

            recvMSG(clientID, (void**)&nombre, &len);
            result = mMatrix->readMatrix(nombre);
            sendMatrix(clientID, result);

        break;
        }
        case OP_MULT:{

            matrix_t *matrix1, *matrix2, *result;

            matrix1 = receiveMatrix(clientID);
            matrix2 = receiveMatrix(clientID);
            result = mMatrix->multMatrices(matrix1, matrix2);
            sendMatrix(clientID, result);
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
            result = mMatrix->createIdentity(rows, cols);
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
            result = mMatrix->createRandMatrix(rows, cols);
            sendMatrix(clientID, result); 
            break;

        }
        case OP_EXIT:{    

            salir = true;
            break;
            
        }
        default:{      
            std::cout<<"ERROR SWITCH DEFAULT"<<std::endl;
            break;
        }
    }
}
    
multMatrix_imp::~multMatrix_imp(){
    delete mMatrix; 
    closeConnection(clientID);
}