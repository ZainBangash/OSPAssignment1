#ifndef Task3_H
#define Task3_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>
#include <vector>
#include <cstring>
#include <limits>
#include <pthread.h>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>

#define WORDLENGTH 3
#define TOTALWORDLENGTHS 13
#define STARTINGINDEX 0

pthread_mutex_t fifoMutex;
std::string dirtyFileName;
std::string cleanFileName;
std::vector<std::string> globalArray;
std::vector<std::vector<int>> indexArray;
const char* fifoName[13] = {"fifo3","fifo4","fifo5","fifo6","fifo7","fifo8","fifo9","fifo10","fifo11","fifo12","fifo13","fifo14","fifo15"};


int main(int argc, char* argv[]); 
void* map3(void* arg);
void* reduce3(void* arg);
void* sort(void* arg);
bool compareString(const int &V1, const int &V2);
void TaskFilter(std::string dirtyFileName);


#endif // Task3_H
