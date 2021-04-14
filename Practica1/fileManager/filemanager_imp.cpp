#include "filemanager_imp.h"
using namespace std;

filemanager_imp::filemanager_imp(int clientId){
    this->fm = new FileManager("../dirprueba/");
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
            cout<<"Dos: "<<endl;           
            recvMSG(clientId, (void**)&buffer, &buffLen);
            fileName = (char*)buffer;
            delete[] buffer;
            cout<<"Tres: "<<endl;
            recvMSG(clientId, (void**)&buffer, &buffLen);
            data = (char*)buffer;
            delete[] buffer;
            cout<<"Cuatro: "<<endl;
            recvMSG(clientId, (void**)&buffer, &buffLen);
            dataLength = (unsigned long int)buffer;
            delete[] buffer;
            cout<<"Cinco: "<<endl;
            this->fm->readFile(fileName, data, dataLength);
            sendMSG(clientId, (void*)*data, dataLength);    
            delete[] data;  }  
            cout<<"Seis: "<<endl;    
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
            int size = (int)vectorSt->size();
            sendMSG(clientId, (void*)&size, sizeof(int));            
            for(unsigned int i=0; i<size; ++i){
                char* file = (char*) vectorSt->at(i)->c_str();
                sendMSG(clientId, (void*)file, strlen(file));                                    
            }
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


/*
#define SEGMENT 5000 //approximate target size of small file

long file_size(char *name);//function definition below

int main(void){
    int segments=0, i, len, accum;
    FILE *fp1, *fp2;
    long sizeFile = filesize(largeFileName);
    segments = sizeFile/SEGMENT + 1;//ensure end of file
    char filename[260]={"c:\play\smallFileName"};//base name for small files.
    char largeFileName[]={"c:\play\largeFileName.txt"};//change to your path
    char smallFileName[260];
    char line[1080];

    fp1 = fopen(largeFileName, "r");
    if(fp1){
        for(i=0;i<segments;i++){
            accum = 0;
            sprintf(smallFileName, "%s%d.txt", filename, i);
            fp2 = fopen(smallFileName, "w");
            if(fp2){
                while(fgets(line, 1080, fp1) && accum <= SEGMENT){
                    accum += strlen(line);//track size of growing file
                    fputs(line, fp2);
                }
                fclose(fp2);
            }
        }
        fclose(fp1);
    }
    return 0;
}

long file_size(char *name){
    FILE *fp = fopen(name, "rb"); //must be binary read to get bytes
    long size=-1;
    if(fp){
        fseek (fp, 0, SEEK_END);
        size = ftell(fp)+1;
        fclose(fp);
    }
    return size;
}
*/