#include"servidor.h"
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
  int tamanoContenido;
  char bufContenido[1024];
}NombreArchivo;

int recibirArchivo(char* bufNombreArchivos, Usuario* usuario){
  char bufDir[64];
  /* Envio los nombres de los archivos de que voy a necesitar para actualizar*/
  write(1,bufNombreArchivos, 512);
  struct NombreArchivo nombreArchivo;
  int op;
  write(usuario->dscAccept,bufNombreArchivos,512);
  /*recibo los archivos para actualizar*/
  do{
    memset(&nombreArchivo,'\0',sizeof nombreArchivo);
    if((read(usuario->dscAccept,&nombreArchivo, sizeof nombreArchivo))>0){
      if((strcmp(nombreArchivo.head.head,headM))==0 && (strcmp(nombreArchivo.head.accion,"InicioArchivo"))==0){
	memset(bufDir,'\0',sizeof bufDir);
	snprintf(bufDir, sizeof bufDir, "Directorio/%s/publico/%s",usuario->usuario,nombreArchivo.nombre);
	if(op>0){
	  close(op);
	}
	op=0;
	if(remove(bufDir)<0){
	  op=open(bufDir,O_CREAT|O_APPEND,0600); 
	}	
	op=open(bufDir,O_WRONLY | O_CREAT |O_APPEND,0600);
         printf("Actualizo el archivo %s tamaño %d\n",nombreArchivo.nombre,nombreArchivo.tamanoContenido);
         write(op,nombreArchivo.bufContenido,nombreArchivo.tamanoContenido);
         logWrite(usuario->pipefd,nombreArchivo.nombre);
         memset(&nombreArchivo,'\0',sizeof nombreArchivo);
      }else if((strcmp(nombreArchivo.head.head,headM))==0 && (strcmp(nombreArchivo.head.accion,"Archivo"))==0){   
         printf("Sigo actualizando %s tamaño %d\n",nombreArchivo.nombre,nombreArchivo.tamanoContenido);
         write(op,nombreArchivo.bufContenido,nombreArchivo.tamanoContenido);
         memset(&nombreArchivo,'\0',sizeof nombreArchivo);
      }else{
	if(op>0){
	  close(op);
	}
      }
    }
  }while(strcmp(nombreArchivo.head.accion,"finalizar")!=0);
  return 1;
}
