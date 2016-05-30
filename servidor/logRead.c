#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "servidor.h"
#include <sys/wait.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
void logRead(int* pipefd, char* usuario){
    close(pipefd[1]);
    char nombreArchivo[32];
    char bufDir[32];
    int op;
printf("estoy en logRead pipe %d usu %s\n \n  ",pipefd[1],usuario);
    memset(nombreArchivo,'\0',32);
    memset(bufDir,'\0',32);
    snprintf(bufDir, sizeof bufDir, "Directorio/%s/log.txt",usuario);
    op=open(bufDir,O_WRONLY | O_CREAT |O_APPEND,0600);
    while(read(pipefd[0],nombreArchivo,sizeof nombreArchivo)>0){
    printf("entre a logRead %s\n ",nombreArchivo);     
    write(op,"se modifico --->",16);
    write(op,nombreArchivo,strlen(nombreArchivo));
    write(op,"\n",2);
     memset(nombreArchivo,'\0',32);
    memset(bufDir,'\0',32);

   }

}
