#pragma once
#ifndef MULTMATRIX_STUB_H
#define MULTMATRIX_STUB_H
#include <vector>
#include <string>
#include <iostream>
#include "multmatrix.h"
#include "utils.h"
#include "matrix_func.h"

#define OP_READ 0
#define OP_WRITE 1
#define OP_MULT 2
#define OP_IDENTITY 3
#define OP_RANDOM 4
#define OP_EXIT 5


class multMatrix_stub{
    connection_t conn;
    matrix_t *createMatrixOP(int op, int rows, int cols);
    multMatrix* mMatrix;

public:
    multMatrix_stub(const char *ip = nullptr);
    matrix_t* readMatrix(const char* fileName);
    matrix_t *multMatrices(matrix_t* m1, matrix_t *m2);
    void writeMatrix(matrix_t* m, const char *fileName);
    ~multMatrix_stub();
    matrix_t *createIdentity(int rows, int cols);
    matrix_t *createRandMatrix(int rows, int cols);
};

#endif