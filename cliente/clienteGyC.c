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
        Cliente cliente;
	char* puerto="2000";
        cliente.usuario=NULL;
        cliente.contrasena=NULL;
      
//        memset(cliente.usuario,'\0',30);
 //       memset(cliente.contrasena,'\0',30);
     printf("entre \n");	
	while ((op = getopt (argc, argv, "p:d:u:c:")) != -1) { 
	switch (op) {
        case 'p': puerto = optarg; 
				  break; 
        	        case 'u': cliente.usuario= optarg;
                                  break;
                        case 'c': cliente.contrasena = optarg;
                                  break;
                  	case '?': 
				  return -1; 
				  break; 
			default: 
				  break;
		}  
        }

       if(!(strlen(cliente.usuario)>0) ||!(strlen(cliente.contrasena)>0)){
           char msj[128]="ERROR: Ingrese Usuario y Contraseña(ejemplo ./clienteGyC -u usuario -c Contraseña) \n";
	   if(write(1,msj,sizeof msj)<0){
		perror("Error en write: ");
                return -1;
           }
         return -1;
       
       }

    if(conexion(puerto,&cliente)==0){
      if(directorio(&cliente)==0){
          printf("voya entra a actualiza\n");
          actualizarDirectorio(&cliente);
          printf("en el if");
       }
    }
     printf("conexionDes\n"); 

       //conectado(desSocket);     
       return 0;    
}

