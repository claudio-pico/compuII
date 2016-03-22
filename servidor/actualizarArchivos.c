#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include"servidor.h"
#include <unistd.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>

typedef struct Archivos{
   char nombre[32];
   char md5[64];   
   time_t tmpMod;
      }Archivos ;

//lee los archivos del servidor y los compara con los que le manda el cliente
//comparando el md5 y luego envia los nuevos archivos del servidor.
int actualizarArchivos(Usuario* usuario){ 

 char bufMd5[512];
 char bufDir[512];
 char outMd5[64];
 
  Archivos archivo;
  memset(archivo.nombre,'\0',64);         
  memset(archivo.md5,'\0',64);
  struct stat statusLocal; 
  int op=0;
  int encontroArchivo=0;
  int leido;
 //recibe los md5 y los nomb de los archivos 
 while((leido=read(usuario->dscAccept ,&archivo, sizeof archivo))){
                encontroArchivo=0;
                struct dirent *dt;
    		while(((dt=readdir(usuario->dirPublico))!= NULL) && encontroArchivo==0){
     		memset(bufMd5,'\0',512);
                memset(bufDir,'\0',512);
                        // 3 casos
                        //  md5C != md5S fecha ac>as actualiza local
                        //  md5C != md5S fecha ac<as actualiza no actualiza local
                        //  md5 isuales no actuliza nada 
      			if((strcmp(dt->d_name,".")!=0)&&(strcmp(dt->d_name,"..")!=0)){
         		   if(strcmp(dt->d_name,archivo.nombre)==0){
                               encontroArchivo=1;
                                snprintf(bufDir, sizeof bufDir, "Directorio/%s/publico/%s",usuario->usuario,dt->d_name);
                                op=0;
                                op=open(bufDir, O_RDWR,0600);
                                md5(op,outMd5);
                                if(strcmp(outMd5,archivo.md5)!=0){
                                    // si tmpMod esta en segundo, es mas grande quiere decir q es el ultimo en modificarse
                                        stat(bufDir,&statusLocal);
                                  	if(archivo.tmpMod>statusLocal.st_mtime){
                                      	 printf("esta elarchivo \n");
                                         write(1,outMd5,strlen(outMd5)); 
                                         write(1,dt->d_name,strlen(dt->d_name));
                                         write(1,"\n\n",3);                        
                                        }
              			 }
                            }
       			}          
      		}
               //los archivos que no estan en local 
              if(encontroArchivo==0){
                // agregar a la lista
               printf("los que no estan en el servidor : %s\n",archivo.nombre);
   
               } 
      		rewinddir(usuario->dirPublico);    
  }
  return 0;
}

