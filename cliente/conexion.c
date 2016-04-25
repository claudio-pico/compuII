#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include<assert.h>
#include<arpa/inet.h>
#include"cliente.h"
#include <netinet/tcp.h>
int conexion(char* puerto,Usuario* usuario){
       
  int desSocket;

  struct sockaddr_in clienteConex;
  // ptrCliente = (struct sockaddr_in *) malloc(sizeof(struct sockaddr_in));
  desSocket=socket(PF_INET,SOCK_STREAM,0); //sock_stream es TCP sock_stream es TCP
  clienteConex.sin_family=AF_INET;//TCP/IP version IP4
  clienteConex.sin_port=htons(atoi(puerto));
  inet_aton ("127.0.0.1",&clienteConex.sin_addr);
  //--------------------------
 
   int optval;
   socklen_t optlen = sizeof(optval);

   /* mustra estado  keepalive */
   if(getsockopt(desSocket, SOL_SOCKET, SO_KEEPALIVE, &optval, &optlen) < 0) {
      perror("getsockopt()");
      close(desSocket);
   }
   printf("SO_KEEPALIVE is %s\n", (optval ? "ON" : "OFF"));

   /*activa thdesSockete  */
   

   optval = 1;
   optlen = sizeof(optval);
   if(setsockopt(desSocket, SOL_SOCKET, SO_KEEPALIVE, &optval, optlen) < 0) {
      perror("setsockopt()");
      close(desSocket);
   }
   
/*   int keepcnt = 5;  //maximo de pruebas que manda antes de terminar la conexion.
   int keepidle = 30;  //El tiempo (en segundos) que la conexión tiene que permanecer inactiva antes de que TCP inicia el envío.
   int keepintvl = 120; //El tiempo (en segundos) entre peubas de actividad individuales.

   setsockopt(desSocket, IPPROTO_TCP, TCP_KEEPCNT, &keepcnt, sizeof(int));
   setsockopt(desSocket, IPPROTO_TCP, TCP_KEEPIDLE, &keepidle, sizeof(int));
   setsockopt(desSocket, IPPROTO_TCP, TCP_KEEPINTVL, &keepintvl, sizeof(int));
*/
   /* mustra otra ves el estado de keepalive */
   if(getsockopt(desSocket, SOL_SOCKET, SO_KEEPALIVE, &optval, &optlen) < 0) {
      perror("getsockopt()");
      close(desSocket);
   }
   printf("SO_KEEPALIVE is %s\n", (optval ? "ON" : "OFF"));
//-------------------------------------------------------------

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
