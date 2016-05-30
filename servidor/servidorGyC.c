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
  setsockopt(dscSocket, SOL_SOCKET, SO_KEEPALIVE, &opt,sizeof opt);
/*   int keepcnt = 5;
   int keepidle = 30;
   int keepintvl = 120;

   setsockopt(dscSocket, IPPROTO_TCP, TCP_KEEPCNT, &keepcnt, sizeof(int));
   setsockopt(dscSocket, IPPROTO_TCP, TCP_KEEPIDLE, &keepidle, sizeof(int));
   setsockopt(dscSocket, IPPROTO_TCP, TCP_KEEPINTVL, &keepintvl, sizeof(int));
 */
  if(bind(dscSocket,(struct sockaddr*) &local,sizeof local)){
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
//	  sleep(2);
          reportar(&usuario);
	  mandarArchivos(&usuario);
	}
     
     /*  char nada[512]; 
       if((read(usuario.dscAccept ,&nada, sizeof nada))>0){

       }*/	   
      printf("\n\n************salid e accep ******** \n\n");
      wait(NULL);
      close(dscAccept);
     }
     }
    } 
  }
  return 0;
}
