#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include"cliente.h"
#include <unistd.h>


int validar(Usuario* usuario){
	
  char usuCont[42];
  char res[128];
  memset(usuCont, '\0', 42);
  memset(res, '\0', 128);

  strcat(usuCont,usuario->usuario);
  strcat(usuCont,"-");
  strcat(usuCont,usuario->contrasena);
  if(write(usuario->desSocket,usuCont,sizeof usuCont)<0){
    perror("ERROR:pasando Usuario y contra (validar)");
    return -1;

  }
  //leo la respuesta del servidor si es -1 no existe usuario-contraseña   
  if(read(usuario->desSocket ,res, sizeof res)<0){
    perror("ERROR:resp de servidor (validar)");
    return -1;

  }

  if(strcmp(res,"-1")==0){
    write (1,"Revise Usuario y Contraseña" ,32 );
    close(usuario->desSocket);
    return -1;
  }
  return 0;
}
