#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "servidor.h"
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
void logWrite(int pipefd, char* nombreArchivo){
   printf("****************estoy en log write %d----------------------",pipefd );
   write(pipefd,nombreArchivo,strlen(nombreArchivo));
 return;
 }
