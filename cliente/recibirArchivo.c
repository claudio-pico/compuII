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
  char md5[64];
  char bufContenido[1024];
}NombreArchivo;

int recibirArchivo(char* bufNombreArchivos, Usuario* usuario,int cantArchivos){
  printf("estoy en recibir archivo \n");
  char bufDir[64],bufDirTem[64]; 
  char archivoAnterior[32];
  char md5Anterior[64];
  write(1,bufNombreArchivos, 512);
  struct NombreArchivo nombreArchivo;
  int op;
  Info info;
  memset(info.head.head,'\0',11);
  strcat(info.head.head,headM);
  memset(info.head.accion,'\0',30);
  strcat(info.head.accion,"informacion");
  info.cantidad=cantArchivos;
  write(usuario->desSocket,&info,sizeof info);
  write(usuario->desSocket,bufNombreArchivos,512);
  int contadorArchivos=0;
  while(cantArchivos>contadorArchivos){
    memset(nombreArchivo.nombre,'\0',64);
    if((read(usuario->desSocket,&nombreArchivo, sizeof nombreArchivo))>0){
      if((strcmp(nombreArchivo.head.head,headM))==0 && (strcmp(nombreArchivo.head.accion,"InicioArchivo"))==0){
        contadorArchivos++;
        //verifico que el archivo anterior fue correctamente modificado.
        if(strlen(archivoAnterior)!=0){
          verificarMd5(archivoAnterior,md5Anterior,usuario->usuario);
        }
        memset(archivoAnterior,'\0',64);
        memset(md5Anterior,'\0',64);
        strcat(archivoAnterior,nombreArchivo.nombre);
        strcat(md5Anterior,nombreArchivo.md5);     
  	memset(bufDir,'\0',64);
	snprintf(bufDir, sizeof bufDir, "Directorio/%s/publico/%s",usuario->usuario,nombreArchivo.nombre);
	if(op>0){
	  close(op);
	}
	op=0;
        memset(bufDirTem,'\0',64);
        snprintf(bufDirTem, sizeof bufDir, "Directorio/%s/temporario/%s",usuario->usuario,nombreArchivo.nombre);
	if(rename(bufDir,bufDirTem)==0){///puede qque no sea necesario crearlo
          op=open(bufDir,O_CREAT,0600); 
	}	
	op=open(bufDir,O_WRONLY | O_CREAT,0600);
        write(1,nombreArchivo.bufContenido,sizeof nombreArchivo.bufContenido);
	write(op,nombreArchivo.bufContenido,strlen(nombreArchivo.bufContenido));            
      }else if((strcmp(nombreArchivo.head.head,headM))==0 && (strcmp(nombreArchivo.head.accion,"Archivo"))==0){   
	write(op,nombreArchivo.bufContenido,strlen(nombreArchivo.bufContenido));
                 	
      }else if((strcmp(nombreArchivo.head.head,headM))==0 && (strcmp(nombreArchivo.head.accion,"faltoArchivo"))==0){
	printf ("Error : La actualizacion no fue completa \n");
	return 1; 
      }
    }
  }
  if(strlen(archivoAnterior)!=0){
    verificarMd5(archivoAnterior,md5Anterior,usuario->usuario);
  }
  close(op);
  printf("salgo de recibir \n");
  return 1;
}
