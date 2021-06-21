#include "multMatrix_stub.h"
#include "multmatrix.h"
#include "matrix_func.h"


multMatrix_stub::multMatrix_stub(const char *ip){
    if(ip == nullptr)
        ip = "127.0.0.1";
    conn = initClient((char*)ip,65321);
}


matrix_t* multMatrix_stub::readMatrix(const char* fileName){
    int op = OP_READ;
    matrix_t *result;
    sendMSG(0, (void*)&op, sizeof(int));
    sendMSG(0, fileName, strlen(fileName));
    result = receiveMatrix(0);
    return result;
}

matrix_t *multMatrix_stub::multMatrices(matrix_t* matrix1, matrix_t *matrix2){
    int op = OP_MULT;
    sendMSG(0, (void*)&op, sizeof(int));
    sendMatrix(0, matrix1);
    sendMatrix(0, matrix2);
    return receiveMatrix(0);
}

void multMatrix_stub::writeMatrix(matrix_t* matrix, const char *fileName){
    int op = OP_WRITE;
    sendMSG(0, (void*)&op, sizeof(int));
    sendMSG(0, fileName, strlen(fileName));
    sendMatrix(0, matrix);
}

matrix_t *multMatrix_stub::createIdentity(int rows, int cols){
    return createMatrixOP(OP_IDENTITY, rows, cols);
}

matrix_t *multMatrix_stub::createRandMatrix(int rows, int cols){
    return createMatrixOP(OP_RANDOM, rows, cols);
}

matrix_t *multMatrix_stub::createMatrixOP(int op, int rows, int cols){
    matrix_t *result;

    sendMSG(0, (void*)&op, sizeof(int));
    sendMSG(0, (void*)&rows, sizeof(int));
    sendMSG(0, (void*)&cols, sizeof(int));

    result = receiveMatrix(0);
    return result;
}


multMatrix_stub::~multMatrix_stub()
{
    int op = OP_EXIT;
    sendMSG(0,(void*)&op,sizeof(int));

    closeConnection(0);
}
