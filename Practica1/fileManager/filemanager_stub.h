#pragma once
#ifndef FILEMANAGER_STUB_H
#define FILEMANAGER_STUB_H
#include "utils.h"
#include "filemanager.h"
#include "file_func.h"
using namespace std;

#define OP_READ 0
#define OP_WRITE 1
#define OP_FREE 2
#define OP_LIST 3
#define OP_EXIT 4


class filemanager_stub{
        connection_t conn;
        public:
            filemanager_stub(const char * path);
            vector<string*>* listFiles();
            void readFile(char* fileName, char* &data, unsigned long int & dataLength);
            void writeFile(char* fileName, char* data, unsigned long int dataLength);
            void freeListedFiles(vector<string*>* fileList);
            ~filemanager_stub();
};

#endif