#pragma once
#ifndef FILEMANAGER_H
#define FILEMANAGER_H
#endif
#include "utils.h"
using namespace std;

#define OP_FIN  -1
#define OP_READ 0
#define OP_WRITE 1
#define OP_FREE 2
#define OP_LIST 3


class filemanager_stub{
        connection_t conn;
        string dirPath;
        map<string, string*> files;
        public:
            filemanager_stub(string path);
            vector<string*>* listFiles();
            void readFile(char* fileName, char* &data, unsigned long int & dataLength);
            void writeFile(char* fileName, char* data, unsigned long int dataLength);
            void freeListedFiles(vector<string*>* fileList);
            ~filemanager_stub();
};