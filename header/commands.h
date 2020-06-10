#ifndef COMMANDS_H
#define COMMANDS_H

#include<iostream>
#include<string.h>
#include<stdlib.h>
#include<dirent.h>
#include<errno.h>
#include <unistd.h>


void ls(char *dir); //operação de list, nao print com cores difernetes nem em colunas
void pwd(char *dir); //da o caminho do diretorio atual 
#endif
