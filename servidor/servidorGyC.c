#include"servidor.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include<assert.h>
#include<arpa/inet.h>
#include <unistd.h>

int dscSocket,dscAccept,opt;

int main (int argc , char* argv[]){
	
	struct sockaddr_in local={}; /*Estructura de socket del servidor */

	//socket:crea socket PF_INET: hacer referencia a TCP/IP STREA:secuencia TCP
	if((dscSocket=socket(PF_INET,SOCK_STREAM,0))<0){
		perror("Error en la creacion de socket (servidorGyC.c)");
		return -1;
	}
        printf("nueva coneccion \n");
	//estructura TCP/IP
	assert(argc ==3);
	local.sin_family=AF_INET;
	local.sin_port=htons(atoi(argv[2]));
	inet_aton(argv[1],&local.sin_addr); //esta funcion pasa de ascci a red.
	
	// si no hay nadie en lisen es decir escuchando.Para reutilizar la combinacionj IP y puerto
	opt=1;
	setsockopt(dscSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof opt);
	
	if(bind(dscSocket,(struct sockaddr*) &local,sizeof local)){
		perror("Error bind (servidorGyC.c)");
		return -1;
	}
  
	listen(dscSocket,15);
	    
	 while ((dscAccept= accept(dscSocket, NULL, 0))>0){
	   struct Usuario usuario;
	   memset(usuario.usuario,'\0',30);
	   memset(usuario.contrasena,'\0',30);
	   
	   usuario.dscAccept=dscAccept;
	   /*valida que exista el usuario 
	     Struct Usuario
	     return 0 o -1
	    */        
	   if(validarServidor(&usuario)==0){;           
		/*
		abre los directorio si no existe los crea
		 nombre de usuario
		*/
                 // tengo q poner un while para que se quede en el usuario 
 	    	if(directorio(&usuario)==0){   
		       if(actualizarArchivos(&usuario)==0){
		 	printf("esto es lo ultmimo us:%s cont: %s  termina\n",usuario.usuario, usuario.contrasena);
		    	}
                  }
	   }
		  
	close(dscAccept);
	 }
    return 0;
}
