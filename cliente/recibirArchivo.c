#include"cliente.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <assert.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

typedef struct NombreArchivo{
  struct Head head;
  char nombre[64];
  char bufContenido[1024];
}NombreArchivo;

int recibirArchivo(char* bufNombreArchivos, Usuario* usuario){
  printf("estoy en recibir archivo \n");
  char bufDir[64];
  write(1,bufNombreArchivos, 512);
  struct NombreArchivo nombreArchivo;
  int op;
  int termino=1;
  write(usuario->desSocket,bufNombreArchivos,512);
  while(termino){
    memset(nombreArchivo.nombre,'\0',64);
    if((read(usuario->desSocket,&nombreArchivo, sizeof nombreArchivo))>0){
      if((strcmp(nombreArchivo.head.head,headM))==0 && (strcmp(nombreArchivo.head.accion,"InicioArchivo"))==0){
	memset(bufDir,'\0',64);
	snprintf(bufDir, sizeof bufDir, "Directorio/%s/publico/%s",usuario->usuario,nombreArchivo.nombre);
	if(op>0){
	  close(op);
	}
	op=0;

	if(remove(bufDir)<0){
	  op=open(bufDir,O_CREAT,0600); 
	}	
	op=open(bufDir,O_WRONLY | O_CREAT,0600);
	write(op,nombreArchivo.bufContenido,sizeof(nombreArchivo.bufContenido));            
      }else if((strcmp(nombreArchivo.head.head,headM))==0 && (strcmp(nombreArchivo.head.accion,"Archivo"))==0){   
	write(op,nombreArchivo.bufContenido,sizeof(nombreArchivo.bufContenido));
                 	
      }else{
	termino=0;
	if(op>0){
	  close(op);
	}
      }
    }


  }
  return 1;
}
