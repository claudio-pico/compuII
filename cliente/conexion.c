#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include<assert.h>
#include<arpa/inet.h>
#include"cliente.h"
int conexion(char* puerto, char* usuario, char* contrasena){
       
	int desSocket;

        struct sockaddr_in* ptrCliente;
        ptrCliente = (struct sockaddr_in *) malloc(sizeof(struct sockaddr_in));
	desSocket=socket(PF_INET,SOCK_STREAM,0);
	ptrCliente->sin_family=AF_INET;
	ptrCliente->sin_port=htons(atoi(puerto));
        inet_aton ("127.0.0.1",&ptrCliente->sin_addr);

        if((connect(desSocket, (struct sockaddr *)ptrCliente, sizeof *ptrCliente))<0){
		perror("connect (servidorGyC)");
		return -1;
	}

       validar(usuario,contrasena,desSocket); 
          
       free(ptrCliente);

	return 0;
}
