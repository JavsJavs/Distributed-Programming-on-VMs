#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "utils.h"

#define CHUNK_LENGTH 512

void sendChunk(int clientID, char* data, long unsigned int dataLength);
void receiveChunk(int clientID, char* &data, long unsigned int* dataLength);


