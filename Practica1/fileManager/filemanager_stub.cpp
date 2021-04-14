#include "filemanager_stub.h"

filemanager_stub::filemanager_stub(string path)
{
     this->conn=initClient("10.0.2.5", 65069);
     this->dirPath = path;
}

vector<string*>* filemanager_stub::listFiles(){
     int op = OP_LIST;
     char* buffer = 0x00;
     int buffLen = 0;
     vector<string*>* result = 0x00;
     sendMSG(0, (void*)&op, sizeof(int));
     recvMSG(0, (void**)&buffer, &buffLen);
     result = ((vector<string*>*)buffer);
     delete[] buffer;
     return result;
}

void filemanager_stub::readFile(char* fileName, char* &data, unsigned long int & dataLength){
     int op = OP_READ;
     int longitud = (int)dataLength;
     sendMSG(0, (void*)&op, sizeof(int));
     sendMSG(0, (void*)&fileName, strlen(fileName));
     sendMSG(0, (void*)&data, strlen(data));
     sendMSG(0, (void*)&dataLength, sizeof(unsigned long int));
     recvMSG(0, (void**)&data, longitud);
     int finalData = ((char*)data)[0];
}

void filemanager_stub::writeFile(char* fileName, char* data, unsigned long int dataLength){
     int op = OP_WRITE;
     sendMSG(0, (void*)&op, sizeof(int));
     sendMSG(0, (void*)&fileName, strlen(fileName));
     sendMSG(0, (void*)&data, strlen(data));
     sendMSG(0, (void*)&dataLength, sizeof(unsigned long int));
}

void filemanager_stub::freeListedFiles(vector<string*>* fileList){
     int op = OP_FREE;
     sendMSG(0, (void*)&op, sizeof(int));
     sendMSG(0, (void*)&fileList, sizeof(fileList));
}