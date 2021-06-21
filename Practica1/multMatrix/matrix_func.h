#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "utils.h"
#include "multmatrix.h"


void sendMatrix(int clientID, matrix_t* matrix);
matrix_t* receiveMatrix(int clientID);