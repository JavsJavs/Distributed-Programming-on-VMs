#include "filemanager_imp.h"
using namespace std;

filemanager_imp::filemanager_imp(int clientID)
{
    char *buff;
    int pathLen;
    this->clientID=clientID;
    recvMSG(clientID, (void**)&buff, &pathLen);
    string path = string(buff, pathLen);
    fm = new FileManager(path);
}

void filemanager_imp::recvOP(){
    int op = -1, buffLen;
    char* buffer = 0x00;
    recvMSG(clientID, (void**)&buffer, &buffLen);
    op = ((int*)buffer)[0];
    delete[] buffer;
    unsigned long int dataLength = 0;
    char* fileName = 0x00;
    char* data = 0x00;
    switch (op) {
        case OP_READ:{
            char *nombre, *data;
            int len;
            unsigned long int datalen;
            recvMSG(clientID, (void**)&nombre, &len);
            fm->readFile(nombre, data, datalen);
            sendChunk(clientID, data, datalen);    
        break;
        }
        case OP_WRITE:{
            char *nombre, *data = nullptr;
            unsigned long int datalen;
            int len;

            recvMSG(clientID, (void**)&nombre, &len);
            receiveChunk(clientID, data, &datalen);

            fm->writeFile(nombre, data, datalen);

            delete [] nombre;
            delete [] data;
            break;
        }
        case OP_EXIT:{
            salir = true;       
            break;
        }
        case OP_LIST:{
            vector<string*>* flist = fm->listFiles();
            int size = flist->size();

            sendMSG(clientID, (void*) &size, sizeof(int));

            for(int i = 0; i < flist->size(); i++){
                sendMSG(clientID, (void *) flist->at(i)->c_str(), flist->at(i)->length() + 1);
            }

            fm->freeListedFiles(flist);
        break;
        }
        default:
            cout<<"Entramos al default :O";
        break;
    }
}

filemanager_imp::~filemanager_imp()
{
    delete fm; 
    closeConnection(clientID);
}
