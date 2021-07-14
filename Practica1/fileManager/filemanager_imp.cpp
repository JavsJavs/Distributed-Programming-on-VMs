#include "filemanager_imp.h"
using namespace std;

filemanager_imp::filemanager_imp(int clientID){

    char *buff;
    int pathLen;
    this->clientID=clientID;

    recvMSG(clientID, (void**)&buff, &pathLen);
    string path = string(buff, pathLen);

    fileManager = new FileManager(path);

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

        case OP_WRITE:{

            char *file_name, *data = nullptr;
            int len;
            unsigned long int datalen;

            recvMSG(clientID, (void**)&file_name, &len);
            receiveChunk(clientID, data, &datalen);

            fileManager->writeFile(file_name, data, datalen);

            delete [] file_name;
            delete [] data;
            break;
        }

        case OP_READ:{

            char *file_name, *data;
            int len;
            unsigned long int datalen;

            recvMSG(clientID, (void**)&file_name, &len);
            fileManager->readFile(file_name, data, datalen);
            sendChunk(clientID, data, datalen);    
            break;

        }

        case OP_LIST:{

            vector<string*>* file_list = fileManager->listFiles();
            int size = file_list->size();

            sendMSG(clientID, (void*) &size, sizeof(int));

            for( int i = 0; i < file_list->size(); i++ ){

                sendMSG(clientID, (void *) file_list->at(i)->c_str(), file_list->at(i)->length() + 1);

            }

            fileManager->freeListedFiles(file_list);
            break;

        }
                case OP_EXIT:{

            salir = true;       
            break;

        }
        default:

            cout<<"Default";

        break;
    }
}

filemanager_imp::~filemanager_imp(){

    delete fileManager; 
    closeConnection(clientID);

}