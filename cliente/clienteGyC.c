#include "cliente.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> 
#include <sys/socket.h>

#include <netinet/in.h>
#include<assert.h>
#include<arpa/inet.h>
#include"cliente.h"
int main(int argc ,char* argv[] ){

	int op;
        Usuario usuario;
	char* puerto="2000";
        memset(usuario.usuario,'\0',30);
        memset(usuario.contrasena,'\0',30);	
	while ((op = getopt (argc, argv, "p:d:u:c:")) != -1) { 
	switch (op) {
        case 'p': puerto = optarg; 
				  break; 
        	        case 'u': strcpy(usuario.usuario,optarg);
                                  break;
                        case 'c': strcpy(usuario.contrasena,optarg);
                                  break;
                  	case '?': 
				  return -1; 
				  break; 
			default: 
				  break;
		}  
        }

      if(!(strlen(usuario.usuario)>0) ||!(strlen(usuario.contrasena)>0)){
           char msj[128]="ERROR: Ingrese Usuario y Contraseña(ejemplo ./clienteGyC -u usuario -c Contraseña) \n";
	   if(write(1,msj,sizeof msj)<0){
		perror("Error en write: ");
                return -1;
           }
         return -1;
       
       }
    if(conexion(puerto,&usuario)==0){
      if(directorio(&usuario)==0){
          reportar(&usuario);
          mandarArchivos(&usuario);
        }
    }
     printf("conexionDes\n"); 

       //conectado(desSocket);     
       return 0;    
}

