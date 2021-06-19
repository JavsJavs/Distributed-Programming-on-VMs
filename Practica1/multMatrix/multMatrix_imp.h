#pragma once
#ifndef FILEMANAGER_IMP_H
#define FILEMANAGER_IMP_H
#include <string>
#include "multmatrix.h"
#include "utils.h"
#include "matrix_func.h"

#define OP_READ 0
#define OP_WRITE 1
#define OP_MULT 2
#define OP_IDENTITY 3
#define OP_RANDOM 4
#define OP_EXIT 5


class multMatrix_imp{
    int clientID;
    multMatrix *multMatrix;

    public:
        bool salir = false;
        multMatrix_imp();
        void recvOP();
        ~multMatrix_imp();
}

#endif