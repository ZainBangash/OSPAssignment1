#ifndef Task4_H
#define Task4_H

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
#include <thread>
#include <errno.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sched.h>
#include <sys/types.h>
#include <sys/resource.h>

#define WORDLENGTH 3
#define TOTALWORDLENGTHS 13
#define STARTINGINDEX 0

std::string dirtyFileName;
std::string cleanFileName;
std::vector<std::string> globalArray;
std::vector<std::vector<int>> indexArray;
const char* fifoName[13] = {"fifo3","fifo4","fifo5","fifo6","fifo7","fifo8","fifo9","fifo10","fifo11","fifo12","fifo13","fifo14","fifo15"};
const int prioList[13] = {2,10,18,26,31,29,25,20,13,8,6,4,1};


int main(int argc, char* argv[]); 
void* map4(void* arg);
void* reduce4(void* arg);
void* sort(void* arg);
bool compareString(const int &V1, const int &V2);
void TaskFilter(std::string dirtyFileName);
static void setScheduling(pthread_t &th, int policy, int priority);


#endif // Task4_H
