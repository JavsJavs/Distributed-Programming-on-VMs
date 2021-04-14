#include <iostream>
#include "filemanager_stub.h"

int main(int argc,char** argv)
{
    cout<<"Debuggin uno"<<endl;
    filemanager_stub *fm=new filemanager_stub("./dirprueba/");
    cout<<"Debuggin dos"<<endl;
    vector<string*>* vfiles=fm->listFiles();
    cout<<"Lista de ficheros en el directorio de prueba:\n";
    cout<<"Debugging tres: "<<vfiles->size()<<endl;
    for(unsigned int i=0; i<vfiles->size(); ++i)
    {
        cout<<"Fichero: "<<vfiles->at(i)->c_str()<<endl;
    }
    cout<<"Leyendo el primer fichero del directorio de prueba:\n";
    
    char* data=nullptr;
    unsigned long int fileLen=0;
    fm->readFile(&(*(vfiles->at(0)))[0],data,fileLen);
    cout<<"Escribiendo el primer fichero del directorio de prueba:\n";
    fm->writeFile(&(*(vfiles->at(0)))[0],data,fileLen);
    cout<<"Escribiendo el primer fichero del directorio en el directorio local:\n";
    FILE* f=fopen(&(*(vfiles->at(0)))[0], "w");
    fwrite(data, fileLen, 1, f);
    fclose(f);
    cout<<"Liberando lista de ficheros:\n";
    fm->freeListedFiles(vfiles);

    cout<<"Liberando datos de fichero leído:\n";

    delete[] data;
    return 0;
}
