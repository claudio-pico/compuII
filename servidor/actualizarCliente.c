#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include"head.h"
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>


typedef struct Archivos{
   char nombre[32];
   char md5[64];     
}Archivos ;

//lee los archivos del servidor y los compara con los que le manda el cliente
//comparando el md5 y luego envia los nuevos archivos del servidor.
int actualizarCliente(Usuario* usuario){

 struct stat estru; 
 char buf2[512];
 char bufLectura[512];//es probable q sea mas grande DUDA del tamaño
 char* tok;
 char md5[128];
 int leido;
 char bufMd5[512];

 memset(md5,'\0',128);
 memset(bufLectura,'\0',512); 
 
 char archivoMd5[124];
 memset(archivoMd5,'\0',124);
 snprintf(archivoMd5, sizeof archivoMd5, "Directorio/temporario/%s.md5",usuario->usuario);
        int desMd5;
        if((desMd5=open(archivoMd5,O_RDWR | O_CREAT, 0600))<0){
                perror("al abrir archivo (actualizar.c)");
                return -1;
        }

 //recibe los md5 y los nomb de los archivos 
 while((leido=read(usuario->dscAccept ,bufLectura, sizeof bufLectura))>0){
//  write(1,bufLectura,sizeof bufLectura);
  write(1,"\n\n",1);
 
 	tok=strtok(bufLectura,"\n/");
      
 	while(tok!=NULL){
    		struct dirent *dt;
  		Archivos archivo;         
      		memset(archivo.md5,'\0',64);    
      		strcat(archivo.md5,tok);

   		tok=strtok(NULL,"\n/");
   		if(tok==NULL){return 0;}
      
  		memset(archivo.nombre,'\0',32); 
   		strcat(archivo.nombre,tok);
   	
    		while((dt=readdir(usuario->dirPublico)) != NULL){
     		memset(bufMd5,'\0',512);
      			if((strcmp(dt->d_name,".")!=0)&&(strcmp(dt->d_name,"..")!=0)){
         			if(strcmp(dt->d_name,archivo.nombre)==0){ 	
                                	snprintf(bufMd5, sizeof bufMd5, "md5sum Directorio/%s/publico/%s>%s",usuario->usuario,dt->d_name,archivoMd5);
                                       memset(buf2,'\0',512);	
                                       system(bufMd5);
                                          if((lseek(desMd5,0,SEEK_SET))<0){
                                            perror("posicionar el puntero(actualizar.c)");
                                           return -1;
                                             }

                                        while(read(desMd5,buf2,sizeof buf2)>0){
                                		Archivos archivoMd5;
                                                tok = strtok (buf2,"\n ");
                                		memset(archivoMd5.md5,'\0',64);
                                		strcat(archivoMd5.md5,tok);
                          
                                		tok=strtok (NULL, "\n ");
                                		memset(archivoMd5.nombre,'\0',32);
                                                strcat(archivoMd5.nombre,dt->d_name);
                                                //compara los que son iguales y los muestra.
                                                if(strcmp(archivoMd5.md5,archivo.md5)==0){
                                                 write (1,archivoMd5.nombre,sizeof archivoMd5.nombre);
                                                }

                        		}
         			 }
       			}          
      		}
      		rewinddir(usuario->dirPublico);
    	
  tok=strtok(NULL,"\n/");
  }
  }
  close(desMd5);
  return 0;
}

