#include "multMatrix_stub.h"
#include "multmatrix.h"
#include "matrix_func.h"


multMatrix_stub::multMatrix_stub(const char *ip){

    if(ip == nullptr){
        ip = "127.0.0.1";
    }

    conn = initClient((char*)ip,65065);

}

void multMatrix_stub::writeMatrix(matrix_t* matrix, const char *matrix_name){

    int op = OP_WRITE;
    sendMSG(0, (void*)&op, sizeof(int));

    sendMSG(0, matrix_name, strlen(matrix_name));
    sendMatrix(0, matrix);

}

matrix_t* multMatrix_stub::readMatrix(const char* matrix_name){

    int op = OP_READ;
    matrix_t *result;

    sendMSG(0, (void*)&op, sizeof(int));
    sendMSG(0, matrix_name, strlen(matrix_name));

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

matrix_t *multMatrix_stub::createRandMatrix(int n_rows, int n_cols){

    int op = OP_RANDOM;
    matrix_t *matrix;

    sendMSG(0, (void*)&op, sizeof(int));
    sendMSG(0, (void*)&n_rows, sizeof(int));
    sendMSG(0, (void*)&n_cols, sizeof(int));

    matrix = receiveMatrix(0);
    return matrix;

}

matrix_t *multMatrix_stub::createIdentity(int n_rows, int n_cols){

    int op = OP_IDENTITY;
    matrix_t *matrix;

    sendMSG(0, (void*)&op, sizeof(int));
    sendMSG(0, (void*)&n_rows, sizeof(int));
    sendMSG(0, (void*)&n_cols, sizeof(int));

    matrix = receiveMatrix(0);
    return matrix;

}

multMatrix_stub::~multMatrix_stub(){

    int op = OP_EXIT;
    sendMSG(0,(void*)&op,sizeof(int));

    closeConnection(0);
    
}