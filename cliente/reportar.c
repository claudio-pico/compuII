#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include"cliente.h"
#include <unistd.h>
#include<fcntl.h>
#include<dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h> 

typedef struct Archivos{
   char nombre[32];
   char md5[64];
   time_t tmpMod;
      }Archivos ;

int reportar(Usuario* usuario){
 
 struct dirent *dt;
 char buf[512];//creo el path para abrir los archivos
 char buf2[512];
 int op;
 char outMd5[64];
 char dir[64]="Directorio/";
 strcat(dir,usuario->usuario);
 strcat(dir,"/publico/");
 char* tok; 
 printf("reportar\n");
struct stat status;

    while((dt=readdir(usuario->dirPublico)) != NULL){    
 	if((strcmp(dt->d_name,".")!=0)&&(strcmp(dt->d_name,"..")!=0)){
        	memset(buf,'\0',512);
        	memset(buf2,'\0',512);
        	snprintf(buf, sizeof buf, "%s%s",dir,dt->d_name);
        	op=0;
        	op=open(buf, O_RDWR,0600);
        	md5(op,outMd5);                       
            
       		stat(buf,&status);
                printf("  tmMod:%ld \n",status.st_mtime);
  
       	    //El -mtime se actualiza cuando se modifica un archivo. 
            //Cada vez que actualice el contenido de un archivo o guardar un archivo mtime se actualiza.
       		if(strlen(outMd5)>0){                                      
       		        Archivos archivo;         
                	memset(archivo.md5,'\0',64);
                	memset(archivo.nombre,'\0',64);
                 	
                        tok = strtok (outMd5,"\n ");
                        strcat(archivo.md5,tok);
                                              
                        tok=strtok (NULL, "\n ");
                        strcat(archivo.nombre,dt->d_name);
                        
                        archivo.tmpMod=status.st_mtime;
                         printf("nombre: %s md5:%s tmMod:%ld leer:%s\n",archivo.nombre,archivo.md5,archivo.tmpMod,ctime(&archivo.tmpMod));
                        
                        write(usuario->desSocket,&archivo,sizeof archivo);  
                        sleep(1);
                       }
            } 
          sleep(3);
         close(op); 
    }   
   
  return 0;
}
