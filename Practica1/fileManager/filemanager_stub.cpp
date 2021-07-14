#include "filemanager_stub.h"
#include "filemanager.h"

filemanager_stub::filemanager_stub(const char * path){

     this->conn=initClient("10.0.2.5", 65069);
     sendMSG(0, path, strlen(path));
}

void filemanager_stub::writeFile(char* file_name, char* data, unsigned long int dataLength){
     int op = OP_WRITE;

     sendMSG(0, (void*)&op, sizeof(int));
     sendMSG(0, file_name, strlen(file_name) + 1);
     sendChunk(0, data, dataLength);

}

void filemanager_stub::readFile(char* file_name, char* &data, unsigned long int & dataLength){

     int op = OP_READ;

     sendMSG(0, (void*)&op, sizeof(int));
     sendMSG(0, file_name, strlen(file_name));
     receiveChunk(0, data, &dataLength);
}


vector<string*>* filemanager_stub::listFiles(){

     int op = OP_LIST;
     vector<string*>* file_list = new vector<string*>();

     char* buffer = 0x00;
     int files_n;
     int bufferSize = 0;

     sendMSG(0, (void*)&op, sizeof(int));
     recvMSG(0,(void**)&buffer, &bufferSize);
     files_n=((int*)buffer)[0];

     for (int i=1; i <= files_n; i++){

          recvMSG(0, (void**)&buffer, &bufferSize);
          file_list->push_back(new string(buffer));
     
     }

     return file_list;
}


void filemanager_stub::freeListedFiles(vector<string*>* file_list){
     FileManager("./").freeListedFiles(file_list);
}


filemanager_stub::~filemanager_stub()
{
    int op = OP_EXIT;

    sendMSG(0,(void*)&op,sizeof(int));
    closeConnection(0);
}