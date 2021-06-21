#include "matrix_func.h"

void sendMatrix(int clientID, matrix_t* matrix){
    int rows, cols;
    int* data;
    rows = matrix->rows;
    cols = matrix->cols;
    data = matrix->data;
    sendMSG(clientID, (void*)&rows, sizeof(int));
    sendMSG(clientID, (void*)&cols, sizeof(int));
    sendMSG(clientID, (void*)&data, rows * cols);
}

matrix_t* receiveMatrix(int clientID){
    int rows, cols, bufLen;
    int* data;
    char* buffer;
    recvMSG(clientID, (void**)&buffer, &bufLen);
    rows = ((int*)buffer)[0];
    delete[] buffer;
    recvMSG(clientID, (void**)&buffer, &bufLen);
    cols = ((int*)buffer)[0];
    delete[] buffer;
    recvMSG(clientID, (void**)&buffer, &bufLen);
    data = ((int**)buffer)[0];
    delete[] buffer;
    matrix_t* matrix;
    matrix->rows = rows;
    matrix->cols = cols;
    matrix->data = data;
    return matrix;
}