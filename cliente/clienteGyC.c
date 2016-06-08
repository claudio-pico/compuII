#include "cliente.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include<assert.h>
#include<arpa/inet.h>
#include"cliente.h"
int main(int argc ,char* argv[] ){

  int op;
  Usuario usuario;
  char* puerto="2000";
  char* ip="127.0.0.1";
  memset(usuario.usuario,'\0',sizeof usuario.usuario);
  memset(usuario.contrasena,'\0',sizeof usuario.contrasena);	
  while ((op = getopt (argc, argv, "i:p:u:c:")) != -1) { 
    switch (op) {
    case 'i': ip = optarg;
      break;
    case 'p': puerto = optarg; 
      break; 
    case 'u': strcpy(usuario.usuario,optarg);
      break;
    case 'c': strcpy(usuario.contrasena,optarg);
      break;
    case '?': 
      return -1; 
      break; 
    default: 
      break;
    }  
  }

  if(!(strlen(usuario.usuario)>0) ||!(strlen(usuario.contrasena)>0)){
    char msj[128]="ERROR: Ingrese Usuario y Contraseña(ejemplo ./clienteGyC -u usuario -c Contraseña) \n";
    if(write(1,msj,sizeof msj)<0){
      perror("Error en write: ");
      return -1;
    }
    return -1;
       
  }
  if(conexion(ip,puerto,&usuario)==0){
    if(directorio(&usuario)==0){
      printf("\n\n************actualizo el servidor ************\n\n");
      reportar(&usuario);
      mandarArchivos(&usuario);
      printf("\n\n \n\n************actualizo el cliente ************\n\n");
      if(actualizarArchivos(&usuario)){
        return -1;

      }
    }
  }
  close(usuario.desSocket);
  printf("conexionDes\n"); 
  return 0;    
}

