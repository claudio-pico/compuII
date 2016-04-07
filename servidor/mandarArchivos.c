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
   char bufContenido[1024];
      }NombreArchivo;



void mandarArchivos(Usuario* usuario){
int leido=0;
int op,leeArchivo;
char bufLeido[512];
char bufDir[64];
memset(bufDir,'\0',64);
memset(bufLeido,'\0',512);
char* tok;
int vacio;
printf("estoy en mandar empiexo a eer buuf \n");
        NombreArchivo nombreArchivo;
	if((leido=read(usuario->dscAccept ,bufLeido, sizeof bufLeido))>0){
	   op=0;
           tok = strtok (bufLeido,"\n");
                 while (tok != NULL){
                        vacio=1;
                	snprintf(bufDir, sizeof bufDir, "Directorio/%s/publico/%s",usuario->usuario,tok);
                        
                        op=open(bufDir, O_RDWR,0600);
                  	leeArchivo=0;
                        memset(nombreArchivo.nombre,'\0',64);          
                        strcat(nombreArchivo.nombre,tok);
                        
                        memset(nombreArchivo.head.head,'\0',11);
                        strcat(nombreArchivo.head.head,headM);
                        
                        memset(nombreArchivo.head.accion,'\0',30);
                        strcat(nombreArchivo.head.accion,"InicioArchivo");
                      
                        memset(nombreArchivo.bufContenido,'\0',1024);
                        while((leeArchivo=read(op,nombreArchivo.bufContenido,sizeof(nombreArchivo.bufContenido)))>0){
                               vacio=0;
                               write(usuario->dscAccept,&nombreArchivo,sizeof nombreArchivo);
                               memset(nombreArchivo.bufContenido,'\0',1024);
                               strcat(nombreArchivo.head.accion,"Archivo");
                               
                  	}      
                        if(vacio){
                        write(usuario->dscAccept,&nombreArchivo,sizeof nombreArchivo);
                        }
                  close(op);
                  tok=strtok (NULL, "\n");
 	        }


       }
     strcat(nombreArchivo.head.accion,"finalizar");
     memset(nombreArchivo.nombre,'\0',64);
     memset(nombreArchivo.bufContenido,'\0',1024);
     write(usuario->dscAccept,&nombreArchivo,sizeof nombreArchivo);
     printf("salgo de mandar");
return;
}

