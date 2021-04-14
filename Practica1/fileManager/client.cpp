#include "filemanager.h"
#include "filemanager_stub.h"
#include "utils.h"
#include <string>
#include <iostream>
using namespace std;

int main(int argc, char **argv){

    filemanager_stub *manager = new filemanager_stub("./dirprueba/");

    vector<string*>* files = manager->listFiles();
    cout << "El directorio contiene:\n" << files << "\n";

    char* fileName = "resultado.txt";
    char* data = "Muchos datos increibles y bonitos para todo su corazon";
    unsigned long int dataLength = strlen(data)
    manager->writeFile(fileName, data, dataLength);
    cout << "Archivo " << fileName << "  sobreescrito\n";


    char* fileName = "resultado.txt";
    char* data = 0x00;
    unsigned long int dataLength = 0;
    manager->readFile(fileName, data, dataLength); 
    cout << "Archivo " << fileName << " leído, contiene:\n" << data << "\n";

    manager->freeListedFiles(files);
    cout << "La siguiente lista de archivos ha sido liberada:\n" << files << "\n";
    return 0;
}