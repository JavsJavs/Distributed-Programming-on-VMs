#include "filemanager_stub.h"
#include "filemanager.h"

filemanager_stub::filemanager_stub(const char * path)
{
     this->conn=initClient("10.0.2.5", 65069);
     sendMSG(0, path, strlen(path));
}

vector<string*>* filemanager_stub::listFiles(){
     vector<string*>* flist = new vector<string*>();
     int op = OP_LIST;
     char* buffer = 0x00;
     int bufferSize = 0;
     int n_files;

     sendMSG(0, (void*)&op, sizeof(int));

     recvMSG(0,(void**)&buffer, &bufferSize);
     n_files=((int*)buffer)[0];

     for (int i=1; i<=n_files; i++){
          recvMSG(0, (void**)&buffer, &bufferSize);
          flist->push_back(new string(buffer));
     }

     return flist;
}

void filemanager_stub::readFile(char* fileName, char* &data, unsigned long int & dataLength){
     int op = OP_READ;
     sendMSG(0, (void*)&op, sizeof(int));
     sendMSG(0, fileName, strlen(fileName));
     receiveChunk(0, data, &dataLength);
}

void filemanager_stub::writeFile(char* fileName, char* data, unsigned long int dataLength){
     int op = OP_WRITE;
     sendMSG(0, (void*)&op, sizeof(int));
     sendMSG(0, fileName, strlen(fileName) + 1);
     sendChunk(0, data, dataLength);
}

void filemanager_stub::freeListedFiles(vector<string*>* fileList){
     FileManager("./").freeListedFiles(fileList);
}

filemanager_stub::~filemanager_stub()
{
    int op = OP_EXIT;
    sendMSG(0,(void*)&op,sizeof(int));
    closeConnection(0);
}
































