#include"head.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include<assert.h>
#include<arpa/inet.h>
#include <unistd.h>

int dscSocket,sd,opt;

int main (int argc , char* argv[]){
	
        struct sockaddr_in local={}; /*Estructura de socket del servidor */

 	//socket:crea socket PF_INET: hacer referencia a TCP/IP STREA:secuencia TCP
  	if((dscSocket=socket(PF_INET,SOCK_STREAM,0))<0){
   		perror("Error en la creacion de socket (servidorGyC.c)");
   		return -1;
        }
        printf("cree el socket");

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
            
  	 while ((sd= accept(dscSocket, NULL, 0))>0){
           char buf[1024];
           memset(buf,'\0',1024);
	   int loe;
           validarServidor(sd);
           write(1,"sali del validar",16);   
          }
    return 0;
}
