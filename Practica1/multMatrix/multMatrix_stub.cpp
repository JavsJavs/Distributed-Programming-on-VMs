#include "multmatrix_stub.h"
#include "multmatrix.h"


multMatrix_stub::multMatrix_stub(const char *ip){
    if(ip == nullptr)
        ip = "127.0.0.1";
    conn=initClient((char*)ip,65321);
    mm = new multMatrix();
}


matrix_t* multMatrix_stub::readMatrix(const char* fileName){

    /*  CÓDIGO ANTIGUO PARA LEER EN REMOTO

    int op = OP_READMATRIX;
    matrix_t *result;

    sendMSG(0, (void*)&op, sizeof(int));

    sendMSG(0, fileName, strlen(fileName));

    result = recvMatrix(0);
    */

    matrix_t *result = mm->readMatrix(fileName);

    return result;
}

matrix_t *multMatrix_stub::multMatrices(matrix_t* m1, matrix_t *m2){
    int op = OP_MULTMATRICES;

    sendMSG(0, (void*)&op, sizeof(int));

    sendMatrix(0, m1);
    sendMatrix(0, m2);

    return recvMatrix(0);
}

void multMatrix_stub::writeMatrix(matrix_t* m, const char *fileName){
    /* CÓDIGO ANTIGUO PARA ESCRIBIR EN REMOTO
    
     int op = OP_WRITEMATRIX;

    sendMSG(0, (void*)&op, sizeof(int));

    sendMSG(0, fileName, strlen(fileName));

    sendMatrix(0, m); */
    
    mm->writeMatrix(m, fileName);

}

matrix_t *multMatrix_stub::createIdentity(int rows, int cols){
    return createMatrixOP(OP_CREATEIDENTITY, rows, cols);
}

matrix_t *multMatrix_stub::createRandMatrix(int rows, int cols){
    return createMatrixOP(OP_CREATERANDMATRIX, rows, cols);
}

matrix_t *multMatrix_stub::createMatrixOP(int op, int rows, int cols){
    matrix_t *result;

    sendMSG(0, (void*)&op, sizeof(int));
    sendMSG(0, (void*)&rows, sizeof(int));
    sendMSG(0, (void*)&cols, sizeof(int));

    result = recvMatrix(0);
    return result;
}


multMatrix_stub::~multMatrix_stub()
{
    int op=OP_FIN;
    sendMSG(0,(void*)&op,sizeof(int));

    closeConnection(0);
}
