#include"servidor.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include<assert.h>
#include<arpa/inet.h>
#include <unistd.h>
#include <netinet/tcp.h>
#include <sys/wait.h>
#include <netdb.h>
int dscSocket,dscAccept,opt;

int main (int argc , char* argv[]){
  struct addrinfo hints;
  struct addrinfo *result, *rp;
  int dscSocket, s;
  if (argc < 2) {
    fprintf(stderr, "Usage: %s port\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  memset(&hints, 0, sizeof(struct addrinfo));
  hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_flags = AI_PASSIVE;    /* For wildcard IP address */
  hints.ai_protocol = 0;          /* Any protocol */
  hints.ai_canonname = NULL;
  hints.ai_addr = NULL;
  hints.ai_next = NULL;  
  if (argc >2) {
    if(strcmp(argv[2], "ipv6") == 0){
      hints.ai_family = AF_INET6;
    }else if(strcmp(argv[2], "ipv4")==0){
      hints.ai_family = AF_INET;
    }
  }

  s = getaddrinfo(NULL, argv[1], &hints, &result);
  if (s != 0) {
    fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
    exit(EXIT_FAILURE);
  }

  /* getaddrinfo() returns a list of address structures.
     Try each address until we successfully bind(2).
     If socket(2) (or bind(2)) fails, we (close the socket
     and) try the next address. */
  for (rp = result; rp != NULL; rp = rp->ai_next) {
    dscSocket = socket(rp->ai_family, rp->ai_socktype,
		       rp->ai_protocol);
    if (dscSocket == -1){
      continue;
    }else{
      break;
    }
    close(dscSocket);
  }	
  freeaddrinfo(result);
  // si no hay nadie en lisen es decir escuchando.Para reutilizar la combinacionj IP y puerto
  opt=1;
  setsockopt(dscSocket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof opt);
  setsockopt(dscSocket, SOL_SOCKET, SO_KEEPALIVE, &opt,sizeof opt); 
  if (bind(dscSocket, rp->ai_addr, rp->ai_addrlen)){
    perror("Error bind (servidorGyC.c)");
    return -1;
  }
  listen(dscSocket,15);
  while ((dscAccept= accept(dscSocket, NULL, 0))>0){

    if(fork()==0){
      int pipefd[2];
      if (pipe(pipefd) == -1) {
        perror("pipe");
      }    
      printf("\n\n************entre en accept ************\n\n");
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
	if(fork()==0){
	  printf("entre al hijo del log \n");
	  logRead(pipefd,usuario.usuario);
	  printf("salgo hijo");
        }else{
	  printf("entre al padre \n ");
	  usuario.pipefd=pipefd[1];
	  close(pipefd[0]);
	  // tengo q poner un while para que se quede en el usuario 
	  if(directorio(&usuario)==0){ 
	    printf("\n\n************actualizo el servidor ************\n\n");  
	    if(actualizarArchivos(&usuario)==0){
	      printf("esto es lo ultmimo us:%s cont: %s  termina\n",usuario.usuario, usuario.contrasena);
	    }
	    printf("\n\n\n\n************actualizo el cliente ************\n\n");
	    reportar(&usuario);
	    mandarArchivos(&usuario);
	  }
     
	  printf("\n\n************salid e accep ******** \n\n");
	  wait(NULL);
	  close(dscAccept);
	}
      }
    } 
  }
  return 0;
}
