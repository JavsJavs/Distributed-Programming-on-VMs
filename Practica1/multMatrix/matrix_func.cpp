#include "matrix_func.h"

void sendMatrix(int clientID, matrix_t* matrix){
    int n_rows, n_cols;
    int* data;
    n_rows = matrix->rows;
    n_cols = matrix->ols;
    data = matrix->data;
    sendMSG(clientID, (void*)&n_rows, sizeof(int));
    sendMSG(clientID, (void*)&n_cols, sizeof(int));
    sendMSG(clientID, (void*)&data, n_rows * n_cols);
}

matrix_t* receiveMatrix(int clientID){

    int n_rows, n_cols, bufLen;
    int* data;
    char* buffer;
    matrix_t* matrix;

    recvMSG(clientID, (void**)&buffer, &bufLen);
    n_rows = ((int*)buffer)[0];
    delete[] buffer;

    recvMSG(clientID, (void**)&buffer, &bufLen);
    n_cols = ((int*)buffer)[0];
    delete[] buffer;

    recvMSG(clientID, (void**)&buffer, &bufLen);
    data = ((int**)buffer)[0];
    delete[] buffer;
    
    matrix->rows = n_rows;
    matrix->cols = n_cols;
    matrix->data = data;
    
    return matrix;

}