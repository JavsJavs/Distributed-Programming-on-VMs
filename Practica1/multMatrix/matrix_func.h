#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "utils.h"
#include "multmatrix.h"

#define CHUNK_LENGTH 512

void sendMatrix(int clientID, matrix_t* matrix);
matrix_t* receiveMatrix(int clientID);