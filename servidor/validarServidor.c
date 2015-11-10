#include"head.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int validarServidor(Usuario* usuario){
char buf[512];
memset(buf,'\0',512);

int op,leido,loe;
char* tok;
char buf2[512];
char uc[128];
memset(buf2,'\0',512);

	if((loe=read(usuario->dscAccept, buf, sizeof buf))<0){
                        perror("Error en read: (validarServidor)");
                        close(usuario->dscAccept);
                        return -1;}
  //-----buscar en archivo-------                      
	op=open("usuarios.txt", O_RDWR,0600);
        if(op==-1){
            perror("Error en la apertura del archivo2(validarServidor.c) \n");
            return -1;
        }
     
 
        while((leido = read(op ,buf2, sizeof buf2))>0){
            tok = strtok (buf2,"\n");	
        	while (tok != NULL && strlen(usuario->usuario)==0){
                  memset(uc,'\0',128);
                  strcat(uc,tok);    
                        //strcmp compara dos cadenas   
	        	if(strcmp(buf,uc)==0){
                               char* tokUC;
                               tokUC=strtok (uc,"-");
                               strcpy(usuario->usuario,tokUC);
                               tokUC=strtok (NULL, "\n");
                               strcpy(usuario->contrasena,tokUC);
                  		if(write(usuario->dscAccept,"0",1)<0){
                        	   perror("Error en 1write :(validarSevidor)\n ");
                        	   return -1;
                  	         }

                 	       
                	}
	 		tok=strtok (NULL, "\n");
                }
              
  //---------------------------
          }
         
     	 if(strlen(usuario->usuario)==0){
        	 if(write(usuario->dscAccept,"-1",2)<0){
             		perror("Error en write3 :(validarSevidor)\n ");
            	 	return -1;
           	 }
       		return -1;
         }

    return 0;
}
