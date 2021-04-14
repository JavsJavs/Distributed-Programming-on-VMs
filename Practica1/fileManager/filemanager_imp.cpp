#include "filemanager_imp.h"


filemanager_imp::filemanager_imp(int clientId){
    this->fm = new FileManager("./dirprueba/");
    this->clientId = clientId;
}

void filemanager_imp::recvOP(){
    int op = -1, buffLen;
    char* buffer = 0x00;
    recvMSG(clientId, (void**)&buffer, &buffLen);
    op = ((int*)buffer)[0];
    delete[] buffer;
    unsigned long int dataLength = 0;
    char* fileName = 0x00;
    char* data = 0x00;
    switch (op) {
        case OP_READ:{           
            recvMSG(clientId, (void**)&buffer, &buffLen);
            fileName = (char*)buffer;
            delete[] buffer;
            recvMSG(clientId, (void**)&buffer, &buffLen);
            data = (char*)buffer;
            delete[] buffer;
            recvMSG(clientId, (void**)&buffer, &buffLen);
            dataLength = (unsigned long int)buffer;
            delete[] buffer;
            this->fm->readFile(fileName, data, dataLength);
            sendMSG(clientId, (void*)*data, dataLength);    
            delete[] data;  }      
        break;
        case OP_WRITE:{
            recvMSG(clientId, (void**)buffer, &buffLen);
            fileName = (char*)buffer;
            delete[] buffer;
            recvMSG(clientId, (void**)buffer, &buffLen);
            data = (char*)buffer;
            delete[] buffer;
            recvMSG(clientId, (void**)buffer, &buffLen);
            dataLength = (unsigned long int)buffer;
            delete[] buffer;
            this->fm->writeFile(fileName, data, dataLength);  
            delete[] data; }
        break;
        case OP_FREE:{
            vector<string*>* fileList;
            recvMSG(clientId, (void**)buffer, &buffLen);
            fileList = (vector<string*>*)buffer;
            this->fm->freeListedFiles(fileList);    }        
        break;
        case OP_LIST:{
            vector<string*>* vectorSt = this->fm->listFiles();
            sendMSG(clientId, vectorSt, sizeof(vectorSt));
        }
        break;
        default:
            cout<<"Entramos al default :O";
        break;
    }
}

filemanager_imp::~filemanager_imp(){
    cout<<"Oju no para de destrui";
    delete this->fm;
}