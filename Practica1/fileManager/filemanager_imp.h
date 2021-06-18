#pragma once
#ifndef FILEMANAGER_IMP_H
#define FILEMANAGER_IMP_H
#include "filemanager.h"
#include "utils.h"
#include "file_func.h"

#define OP_READ 0
#define OP_WRITE 1
#define OP_FREE 2
#define OP_LIST 3
#define OP_EXIT 4

class filemanager_imp{
    int clientID;
    FileManager* fm;
    public:
        bool salir = false;
        filemanager_imp(int clientID);
        void recvOP();
        ~filemanager_imp();
};

#endif