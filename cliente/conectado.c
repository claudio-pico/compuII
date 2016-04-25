#include "cliente.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int conectado(int desSocket){

  int leido;
  char buf2[2048];
  memset(buf2, '\0', 2048);
  char* tok;	
  char archivo[30];
       
  char msj2[128]="estoy en coenctado";
  write(1,msj2,sizeof msj2);
	
  while ((leido = read(STDIN_FILENO ,buf2, sizeof buf2))>0){	

    tok = strtok(buf2,"\n");

    while (tok != NULL){ 
      strcat(archivo,tok);
                        
      if(write(desSocket,archivo,sizeof archivo)<0){
	perror("Error en write: ");
	return -1;
      }
 
      close(desSocket);
      tok=strtok(NULL,"\n"); 

    }
  }

  return 0;
}
