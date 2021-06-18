#include "file_func.h"

void sendChunk(int clientID, char* data, long unsigned int dataLength){
    int segments, i, difference;
    segments = dataLength / CHUNK_LENGTH + 1;
    difference = dataLength % CHUNK_LENGTH + 1;
    sendMSG(clientID, (void*) &dataLength, sizeof(int));
    for(i = 0; i < segments - 1; i++){
        sendMSG(clientID, (void*) data + CHUNK_LENGTH * i, CHUNK_LENGTH);      
    }
    sendMSG(clientID, (void*) data + CHUNK_LENGTH * i, difference);
}

void receiveChunk(int clientID, char* &data, long unsigned int* dataLength){
    int segments, i, j, buffLen;
    char* buffer = 0x00;
    recvMSG(clientID, (void**)&buffer, &buffLen);
    *dataLength = ((int*)buffer)[0];
    delete[] buffer;
    segments = *dataLength / CHUNK_LENGTH + 1;
    data = new char[*dataLength];
    for(i = 0; i < segments; i++){
        recvMSG(clientID, (void**)&buffer, &buffLen);
        for(j = 0; j < buffLen; j++){
            data[j + CHUNK_LENGTH  * i] = buffer[j];
        }
        delete[] buffer;
    }
}