#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include "cliente.h"
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <pthread.h>
#include <semaphore.h>

void verificarMd5(char* nombre,char* md5enviado,char* nombreUsuario){
  
  char outMd5[64];
  int op;
  char bufDir[64];
  memset(outMd5,'\0',64);
  memset(bufDir,'\0',64);
  snprintf(bufDir, sizeof bufDir, "Directorio/%s/publico/%s",nombreUsuario,nombre);
  op=open(bufDir, O_RDWR,0600);
  md5(op,outMd5);
  if(strcmp(outMd5,md5enviado)!=0){
    printf("\n ERROR: al actualizar el archivo %s",nombre);
    remove(bufDir);
    char bufDirTemp[64];
    snprintf(bufDirTemp, sizeof bufDirTemp, "Directorio/%s/temporario/%s",nombreUsuario,nombre);
    rename(bufDirTemp,bufDir);
  }else{
    printf(" \n El archivo %s se actualizo correctamente \n",nombre);
  }
  close(op);
  return ;     
} 
