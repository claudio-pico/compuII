#include"cliente.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include<assert.h>
#include<arpa/inet.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


typedef struct NombreArchivo{
  struct Head head;
  char nombre[64];
  int tamanoContenido;
  char bufContenido[1024];
}NombreArchivo;



void mandarArchivos(Usuario* usuario){
  int leido=0;
  int op=0;
  char bufLeido[512];
  char bufDir[64];
  memset(bufDir,'\0',64);
  memset(bufLeido,'\0',512);
  char* tok;
  int vacio;
  NombreArchivo nombreArchivo;
  
  if((leido=read(usuario->desSocket ,bufLeido, sizeof bufLeido))>0){
    tok = strtok (bufLeido,"\n");
    while (tok != NULL){
      vacio=1;
      snprintf(bufDir, sizeof bufDir, "Directorio/%s/publico/%s",usuario->usuario,tok);
      op=open(bufDir, O_RDWR,0600);
      memset(&nombreArchivo,'\0',sizeof nombreArchivo);
      
      strcat(nombreArchivo.nombre,tok);
      strcat(nombreArchivo.head.head,headM);
      strcat(nombreArchivo.head.accion,"InicioArchivo");
      printf("\n actualizo %s \n",tok);               
      while((nombreArchivo.tamanoContenido=read(op,nombreArchivo.bufContenido,sizeof(nombreArchivo.bufContenido)))>0){
	vacio=0;
        write(usuario->desSocket,&nombreArchivo, sizeof nombreArchivo);
	memset(nombreArchivo.bufContenido,'\0',sizeof nombreArchivo.bufContenido);
        memset(nombreArchivo.head.accion,'\0',sizeof nombreArchivo.head.accion);
        strcat(nombreArchivo.head.accion,"Archivo");
        nombreArchivo.tamanoContenido=0;                              
      }      
      if(vacio){
	write(usuario->desSocket,&nombreArchivo,sizeof nombreArchivo);
      }
      close(op);
      tok=strtok (NULL, "\n");
    }

  }
  memset(&nombreArchivo,'\0',sizeof nombreArchivo);
  strcat(nombreArchivo.head.head,headM);
  strcat(nombreArchivo.head.accion,"finalizar");
  write(usuario->desSocket,&nombreArchivo,sizeof nombreArchivo);
  return;
}
