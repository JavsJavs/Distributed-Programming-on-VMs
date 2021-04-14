#pragma once
#include "filemanager.h"
#include "utils.h"

#define OP_FIN  -1
#define OP_READ 0
#define OP_WRITE 1
#define OP_FREE 2
#define OP_LIST 3

class filemanager_imp{
    int clientId;
    FileManager* fm;
    public:
        bool salir = false;
        filemanager_imp(int clientId);
        void recvOP();
        ~filemanager_imp();
};