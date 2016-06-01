#include"servidor.h"
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
  char md5[64];
  int tamanoContenido;
  char bufContenido[1024];
}NombreArchivo;



void mandarArchivos(Usuario* usuario){
  int leido=0;
  char bufLeido[512];
  char bufDir[64];
  memset(bufDir,'\0',64);
  memset(bufLeido,'\0',512);
  char* tok;
  int vacio,cantArchivos,op;
  Info info;
  NombreArchivo nombreArchivo;

  if((leido=read(usuario->dscAccept ,&info, sizeof info))<0){
    perror("Error: leer info (mandararchivos.c) ");
    return;
  }
  if((leido=read(usuario->dscAccept ,bufLeido, sizeof bufLeido))>0){
    op=0;
    cantArchivos=0;
    tok = strtok (bufLeido,"\n");
    while (tok != NULL){
      vacio=1;
      cantArchivos++;
      snprintf(bufDir, sizeof bufDir, "Directorio/%s/publico/%s",usuario->usuario,tok);
                        
      op=open(bufDir,O_RDONLY,0600);
      memset(&nombreArchivo,'\0',sizeof nombreArchivo);          
      strcat(nombreArchivo.nombre,tok);
      printf("\nActualizo el archivo %s \n",nombreArchivo.nombre);
      strcat(nombreArchivo.head.head,headM);
      strcat(nombreArchivo.head.accion,"InicioArchivo");

      md5(op,nombreArchivo.md5);                   
      lseek (op, 0, SEEK_SET );

      while((nombreArchivo.tamanoContenido=read(op,nombreArchivo.bufContenido,sizeof(nombreArchivo.bufContenido)))>0){
	vacio=0;
        printf("mando arvhivo %s",nombreArchivo.nombre);
	write(usuario->dscAccept,&nombreArchivo,sizeof nombreArchivo);
	memset(nombreArchivo.bufContenido,'\0',sizeof nombreArchivo.bufContenido);
        memset(nombreArchivo.head.accion,'\0',sizeof nombreArchivo.head.accion);
  	strcat(nombreArchivo.head.accion,"Archivo");
        nombreArchivo.tamanoContenido=0;                        
      }      
      if(vacio){
	write(usuario->dscAccept,&nombreArchivo,sizeof nombreArchivo);
      }
      close(op);
      tok=strtok (NULL, "\n");
    }


  }
  memset(&nombreArchivo,'\0',sizeof nombreArchivo); 
  strcat(nombreArchivo.head.head,headM);  
  if(cantArchivos!=info.cantidad){
    strcat(nombreArchivo.head.accion,"faltoArchivo");
  }else {
   strcat(nombreArchivo.head.accion,"finalizarEnvio");
  }
    write(usuario->dscAccept,&nombreArchivo,sizeof nombreArchivo);
  return;
}


