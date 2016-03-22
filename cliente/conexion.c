#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include<assert.h>
#include<arpa/inet.h>
#include"cliente.h"
int conexion(char* puerto,Usuario* usuario){
       
	int desSocket;

        struct sockaddr_in clienteConex;
       // ptrCliente = (struct sockaddr_in *) malloc(sizeof(struct sockaddr_in));
	desSocket=socket(PF_INET,SOCK_STREAM,0);
	clienteConex.sin_family=AF_INET;
	clienteConex.sin_port=htons(atoi(puerto));
        inet_aton ("127.0.0.1",&clienteConex.sin_addr);

        if((connect(desSocket, (struct sockaddr*)&clienteConex, sizeof clienteConex))<0){
		perror("connect (servidorGyC)");
		return -1;
	}
        
       usuario->desSocket=desSocket;
       if(validar(usuario)<0){
        return -1;
        } 
         
	return 0;
}
