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
  int tamanoContenido;
  char bufContenido[1024];
}NombreArchivo;

int recibirArchivo(char* bufNombreArchivos, Usuario* usuario,int cantArchivos){
  char bufDir[64],bufDirTem[64]; 
  char archivoAnterior[64];
  char md5Anterior[64];
  write(1,bufNombreArchivos, 512);
  struct NombreArchivo nombreArchivo;
  int op;
  //mando lo archivos que necesito para actualizar
  Info info;
  memset(&info,'\0',sizeof info);
  strcat(info.head.head,headM);; 
  strcat(info.head.accion,"informacion");
  info.cantidad=cantArchivos;
  write(usuario->desSocket,&info,sizeof info);
  write(usuario->desSocket,bufNombreArchivos,512);
  
  //recibo archivos para actualizar 
  int contadorArchivos=0;
  cantArchivos++;
  while(cantArchivos>contadorArchivos){
    memset(&nombreArchivo,'\0',sizeof nombreArchivo);
    if((read(usuario->desSocket,&nombreArchivo, sizeof nombreArchivo))>0){
      if((strcmp(nombreArchivo.head.head,headM))==0 && (strcmp(nombreArchivo.head.accion,"InicioArchivo"))==0){
        contadorArchivos++;
        //verifico que el archivo anterior fue correctamente modificado.
        if(strlen(archivoAnterior)!=0){
          verificarMd5(archivoAnterior,md5Anterior,usuario->usuario);
        }
        memset(archivoAnterior,'\0',sizeof archivoAnterior);
        memset(md5Anterior,'\0',sizeof md5Anterior);
        strcat(archivoAnterior,nombreArchivo.nombre);
        strcat(md5Anterior,nombreArchivo.md5);     
  	memset(bufDir,'\0',sizeof bufDir);
	snprintf(bufDir, sizeof bufDir, "Directorio/%s/publico/%s",usuario->usuario,nombreArchivo.nombre);
	if(op>0){
	  close(op);
	}
	op=0;
        memset(bufDirTem,'\0',sizeof bufDirTem);
        snprintf(bufDirTem, sizeof bufDir, "Directorio/%s/temporario/%s",usuario->usuario,nombreArchivo.nombre);
	rename(bufDir,bufDirTem);
	op=open(bufDir,O_WRONLY | O_CREAT |O_APPEND,0600);
        write(op,nombreArchivo.bufContenido,nombreArchivo.tamanoContenido); 
        printf("\n Escibi el archivo %s \n",nombreArchivo.nombre);
        memset(&nombreArchivo,'\0',sizeof nombreArchivo); 
      }else if((strcmp(nombreArchivo.head.head,headM))==0 && (strcmp(nombreArchivo.head.accion,"Archivo"))==0){    
        printf("\n sigo escribiendo %s \n",nombreArchivo.nombre);
        write(op,nombreArchivo.bufContenido,nombreArchivo.tamanoContenido);
        memset(&nombreArchivo,'\0',sizeof nombreArchivo);
      }else if((strcmp(nombreArchivo.head.head,headM))==0 && (strcmp(nombreArchivo.head.accion,"faltoArchivo"))==0){
	printf ("Error : La actualizacion no fue completa \n");
	return 1; 
      }else if((strcmp(nombreArchivo.head.head,headM))==0 && (strcmp(nombreArchivo.head.accion,"finalizarEnvio"))==0){
        contadorArchivos++;
        if(contadorArchivos!=cantArchivos){   
	  printf ("Error : La actualizacion no fue completa \n");
	  return -1;
	}
        printf("pase por finalizar");
      }
    }
  }
  close(op);
  if(strlen(archivoAnterior)!=0){
    verificarMd5(archivoAnterior,md5Anterior,usuario->usuario);
  }
  return 1;
}
