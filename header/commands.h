#ifndef COMMANDS_H
#define COMMANDS_H

#include<iostream>
#include<vector>
#include<string.h>
#include<string>
#include<stdlib.h>
#include<dirent.h>
#include<errno.h>
#include <unistd.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include <pwd.h>

using namespace std;

void ls(vector<string>); //operação de list, nao print com cores difernetes nem em colunas

void pwd(char *dir); //da o caminho do diretorio atual

void run(vector<string> command); //execute the commands from protoTerminal.cpp

void cd(vector<string>); //muda o diretorio

#endif
