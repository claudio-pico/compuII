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

int actualizarDirectorio(Cliente* cliente){

 struct dirent *dt;
 char a[64]="Directorio/";
 char buf[512];
 char buf2[512];
 int desMd5;
 char* tok;
 char archivoMd5[124];
 memset(archivoMd5,'\0',124);
 snprintf(archivoMd5, sizeof archivoMd5, "%stemporario/%s.md5",a,cliente->usuario);
        if((desMd5=open(archivoMd5,O_RDWR | O_CREAT, 0600))<0){
 		perror("al abrir archivo (actualizar.c)");
        	return -1;
 	}
 strcat(a,cliente->usuario);
 strcat(a,"/publico/");
       
 	while((dt=readdir(cliente->dirPublico)) != NULL){    
               	if((strcmp(dt->d_name,".")!=0)&&(strcmp(dt->d_name,"..")!=0)){
         		memset(buf,'\0',512);
                        memset(buf2,'\0',512);
     			snprintf(buf, sizeof buf, "md5sum %s%s>%s",a,dt->d_name,archivoMd5);	
               		write(1,buf,sizeof buf);
                        system(buf);
                       if((lseek(desMd5,0,SEEK_SET))<0){
                        perror("posicionar el puntero(actualizar.c)");
                        return -1;
 
                        }
                      // lee el md5 que se escribio con sistem(buf) y parsea el num para 
                      // adjuntarlo al nombre y mandarlo.
                       while(read(desMd5,buf2,sizeof buf2)>0){                                      
                        	tok = strtok (buf2,"\n ");
                        
                           	char r[64];
                         	memset(r,'\0',64);
                        	strcat(r,tok);
                        	strcat(r,"/");
                                 
                                tok=strtok (NULL, "\n ");
                        	strcat(r,dt->d_name);
                        	strcat(r,"\n");
                        	write(1,r,sizeof r);
                        	write(cliente->desSocket,r,sizeof r);
                           
	        	}
         	} 
 
	}
  close(desMd5);
   
  return 0;
}
