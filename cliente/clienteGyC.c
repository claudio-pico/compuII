#include "cliente.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> 
#include <sys/socket.h>

#include <netinet/in.h>
#include<assert.h>
#include<arpa/inet.h>

int main(int argc ,char* argv[] ){

	int op;
	char* puerto="2000";
        char* usuario=NULL;
        char* contrasena=NULL;
     printf("entre \n");	
	while ((op = getopt (argc, argv, "p:d:u:c:")) != -1) { 
	switch (op) {
        case 'p': puerto = optarg; 
				  break; 
        	        case 'u': usuario = optarg;
                                  break;
                        case 'c': contrasena = optarg;
                                  break;
                  	case '?': 
				  return -1; 
				  break; 
			default: 
				  break;
		}  
        }

       if(usuario==NULL || contrasena==NULL){
           char msj[128]="ERROR: Ingrese Usuario y Contraseña(ejemplo ./clienteGyC -u usuario -c Contraseña) \n";
	   if(write(1,msj,sizeof msj)<0){
		perror("Error en write: ");
                return -1;
           }
         return -1;
       
       }

     conexion(puerto,usuario,contrasena);
     printf("conexionDes\n"); 

       //conectado(desSocket);     
       return 0;    
}

