#include"servidor.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

void contarArchivosBuf(char* bufLeido){
  char* tok;
  tok = strtok (bufLeido,"\n");
  while (tok != NULL){   
    strcat(bufResultado,archivo.nombre);
    strcat(bufResultado,"\n");
  }
