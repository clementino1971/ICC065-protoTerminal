#ifndef PROTOTERMINAL_H
#define PROTOTERMINAL_H

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<dirent.h>
#include<errno.h>
#include <unistd.h>


void ls(const char *dir); //operação de list, nao print com cores difernetes nem em colunas
void pwd(); //da o caminho do diretorio atual 
#endif