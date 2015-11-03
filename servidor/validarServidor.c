#include"head.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int validarServidor(int sd){
char buf[512];
memset(buf,'\0',512);

int op,leido,loe;
char* tok;
char buf2[512];
char uc[512];
memset(buf2,'\0',512);

	if((loe=read(sd, buf, sizeof buf))<0){
                        perror("Error en read: (validarServidor)");
                        close(sd);
                        return -1;}
  //-----buscar en archivo-------                      
	op=open("usuarios.txt", O_RDWR,0600);
        if(op==-1){
            perror("Error en la apertura del archivo2 \n");
            return -1;
        }
    int bandera=0;
        while((leido = read(op ,buf2, sizeof buf2))>0){
            tok = strtok (buf2,"\n");	
        	while (tok != NULL && bandera==0){
                  memset(uc,'\0',512);
                  strcat(uc,tok);       
	        	if(strcmp(buf,uc)==0){
                  		if(write(sd,"0",1)<0){
                        	   perror("Error en 1write :(validarSevidor)\n ");
                        	   return -1;
                  	         }
                 	       bandera=1;
                	}
	 		tok=strtok (NULL, "\n");
                }
              
  //---------------------------
          }
         
     	 if(bandera==0){
        	 if(write(sd,"-1",2)<0){
             		perror("Error en write3 :(validarSevidor)\n ");
            	 	return -1;
           	 }
       		return -1;
         }

    return 0;
}
