#ifndef Task2_H
#define Task2_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <random>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <wait.h>
#include <vector>
#include <set>
#include <cstring>
#include <limits>

#define WORDLENGTH 3
#define TOTALWORDLENGTHS 13

std::vector<std::string> globalArray;

int main(int argc, char* argv[]);
void reduce2(std::string cleanFileName);
void TaskFilter(std::string dirtyFileName);
pid_t Map2();

#endif // Task2_H